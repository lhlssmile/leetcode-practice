use std::collections::VecDeque;

struct Solution;

impl Solution {
    // 标准实现
    pub fn remove_kdigits(num: String, k: i32) -> String {
        let mut stack = Vec::new();
        let mut k = k as usize;
        
        for digit in num.chars() {
            // 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
            while !stack.is_empty() && k > 0 && stack.last().unwrap() > &digit {
                stack.pop();
                k -= 1;
            }
            stack.push(digit);
        }
        
        // 如果还没删完，从后面删
        while k > 0 && !stack.is_empty() {
            stack.pop();
            k -= 1;
        }
        
        // 去掉前导零并构建结果
        let result: String = stack.into_iter()
            .skip_while(|&c| c == '0')
            .collect();
        
        if result.is_empty() { "0".to_string() } else { result }
    }
    
    // 函数式编程版本 - 使用fold进行状态累积
    pub fn remove_kdigits_functional(num: String, k: i32) -> String {
        let (mut stack, remaining_k) = num.chars()
            .fold((Vec::new(), k as usize), |(mut stack, mut k), digit| {
                // 移除比当前数字大的栈顶元素
                while !stack.is_empty() && k > 0 && stack.last().unwrap() > &digit {
                    stack.pop();
                    k -= 1;
                }
                stack.push(digit);
                (stack, k)
            });
        
        // 如果还有剩余删除次数，从后面删除
        if remaining_k > 0 {
            let new_len = stack.len().saturating_sub(remaining_k);
            stack.truncate(new_len);
        }
        
        // 使用迭代器链式操作去掉前导零
        stack.into_iter()
            .skip_while(|&c| c == '0')
            .collect::<String>()
            .pipe(|s| if s.is_empty() { "0".to_string() } else { s })
    }
    
    // 高级函数式版本 - 使用闭包和高阶函数
    pub fn remove_kdigits_advanced(num: String, k: i32) -> String {
        // 定义处理单个数字的闭包
        let process_digit = |acc: (Vec<char>, usize), digit: char| -> (Vec<char>, usize) {
            let (mut stack, mut remaining_k) = acc;
            
            // 使用while_some模式（自定义扩展）
            while stack.last().map_or(false, |&top| top > digit && remaining_k > 0) {
                stack.pop();
                remaining_k -= 1;
            }
            
            stack.push(digit);
            (stack, remaining_k)
        };
        
        // 使用reduce处理所有数字
        let (mut result_stack, remaining_k) = num.chars()
            .fold((Vec::new(), k as usize), process_digit);
        
        // 处理剩余删除次数的函数
        let trim_remaining = |mut stack: Vec<char>, k: usize| -> Vec<char> {
            if k > 0 {
                let new_len = stack.len().saturating_sub(k);
                stack.truncate(new_len);
            }
            stack
        };
        
        // 去掉前导零的函数
        let remove_leading_zeros = |chars: Vec<char>| -> String {
            chars.into_iter()
                .skip_while(|&c| c == '0')
                .collect::<String>()
                .pipe(|s| if s.is_empty() { "0".to_string() } else { s })
        };
        
        // 函数组合：trim_remaining -> remove_leading_zeros
        result_stack
            .pipe(|stack| trim_remaining(stack, remaining_k))
            .pipe(remove_leading_zeros)
    }
    
    // 使用Iterator适配器的版本
    pub fn remove_kdigits_iterator(num: String, k: i32) -> String {
        use std::iter::once;
        
        let chars: Vec<char> = num.chars().collect();
        let mut k = k as usize;
        
        // 使用scan进行有状态的迭代
        let processed: Vec<char> = chars.into_iter()
            .scan(Vec::new(), |stack, digit| {
                // 移除比当前数字大的栈顶元素
                while !stack.is_empty() && k > 0 && stack.last().unwrap() > &digit {
                    stack.pop();
                    k -= 1;
                }
                stack.push(digit);
                Some(stack.clone())
            })
            .last()
            .unwrap_or_default();
        
        // 处理剩余删除次数并去掉前导零
        processed.into_iter()
            .take(processed.len().saturating_sub(k))
            .skip_while(|&c| c == '0')
            .collect::<String>()
            .pipe(|s| if s.is_empty() { "0".to_string() } else { s })
    }
}

// 自定义trait用于管道操作（函数式编程常用模式）
trait Pipe<T> {
    fn pipe<U, F>(self, f: F) -> U
    where
        F: FnOnce(Self) -> U,
        Self: Sized;
}

impl<T> Pipe<T> for T {
    fn pipe<U, F>(self, f: F) -> U
    where
        F: FnOnce(Self) -> U,
    {
        f(self)
    }
}

// 测试函数
fn test_all_versions() {
    let test_cases = vec![
        ("1432219".to_string(), 3),  // "1219"
        ("10200".to_string(), 1),    // "200"
        ("10".to_string(), 2),       // "0"
        ("9".to_string(), 1),        // "0"
        ("112".to_string(), 1),      // "11"
    ];
    
    println!("=== 标准版本 ===");
    for (num, k) in &test_cases {
        let result = Solution::remove_kdigits(num.clone(), *k);
        println!("remove_kdigits('{}', {}) = '{}'", num, k, result);
    }
    
    println!("\n=== 函数式版本 ===");
    for (num, k) in &test_cases {
        let result = Solution::remove_kdigits_functional(num.clone(), *k);
        println!("remove_kdigits_functional('{}', {}) = '{}'", num, k, result);
    }
    
    println!("\n=== 高级函数式版本 ===");
    for (num, k) in &test_cases {
        let result = Solution::remove_kdigits_advanced(num.clone(), *k);
        println!("remove_kdigits_advanced('{}', {}) = '{}'", num, k, result);
    }
    
    println!("\n=== Iterator版本 ===");
    for (num, k) in &test_cases {
        let result = Solution::remove_kdigits_iterator(num.clone(), *k);
        println!("remove_kdigits_iterator('{}', {}) = '{}'", num, k, result);
    }
}

fn main() {
    test_all_versions();
}

/*
Rust高级特性说明：

1. **Pipe Trait**: 
   - 自定义trait实现管道操作，类似于函数式语言中的管道操作符
   - 允许链式调用，提高代码可读性
   - 用法：value.pipe(|x| transform(x))

2. **fold函数**:
   - 类似于reduce，用于累积状态
   - 接受初始值和累积函数，遍历迭代器并累积结果
   - 用法：iter.fold(init, |acc, item| new_acc)

3. **scan函数**:
   - 有状态的map操作，维护内部状态
   - 每次迭代都可以访问和修改状态
   - 用法：iter.scan(state, |state, item| Some(result))

4. **闭包捕获**:
   - 闭包可以捕获外部变量（如k）
   - 支持move语义和借用语义
   - 用法：|acc, item| { /* 使用外部变量 */ }

5. **Iterator链式操作**:
   - skip_while: 跳过满足条件的前导元素
   - take: 取前n个元素
   - collect: 将迭代器收集为集合
   - map_or: 处理Option的值或提供默认值

6. **Option和Result的函数式处理**:
   - map_or: Option的map操作，提供默认值
   - unwrap_or_default: 获取值或使用默认值
   - saturating_sub: 安全的减法，防止下溢

7. **泛型和Trait约束**:
   - 自定义Pipe trait展示了Rust的trait系统
   - where子句用于复杂的trait约束
   - Self: Sized约束确保trait对象安全

这些特性展示了Rust强大的函数式编程能力，同时保持了内存安全和零成本抽象。
*/