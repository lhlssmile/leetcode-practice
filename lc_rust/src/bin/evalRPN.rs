// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

use std::collections::VecDeque;

// 标准实现
fn eval_rpn(tokens: Vec<String>) -> i32 {
    let mut stack = Vec::new();
    
    for token in tokens {
        match token.as_str() {
            "+" => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a + b);
            }
            "-" => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a - b);
            }
            "*" => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a * b);
            }
            "/" => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a / b);
            }
            _ => {
                stack.push(token.parse::<i32>().unwrap());
            }
        }
    }
    
    stack[0]
}

// 函数式编程实现
fn eval_rpn_functional(tokens: Vec<String>) -> i32 {
    tokens
        .into_iter()
        .fold(Vec::new(), |mut stack, token| {
            match token.as_str() {
                "+" | "-" | "*" | "/" => {
                    let b = stack.pop().unwrap();
                    let a = stack.pop().unwrap();
                    let result = match token.as_str() {
                        "+" => a + b,
                        "-" => a - b,
                        "*" => a * b,
                        "/" => a / b,
                        _ => unreachable!(),
                    };
                    stack.push(result);
                    stack
                }
                _ => {
                    stack.push(token.parse::<i32>().unwrap());
                    stack
                }
            }
        })
        .into_iter()
        .next()
        .unwrap()
}

fn main() {
    println!("=== 逆波兰表达式求值测试 ===");
    
    // 测试用例
    let test_cases = vec![
        (vec!["2".to_string(), "1".to_string(), "+".to_string(), "3".to_string(), "*".to_string()], 9),
        (vec!["4".to_string(), "13".to_string(), "5".to_string(), "/".to_string(), "+".to_string()], 6),
        (vec!["10".to_string(), "6".to_string(), "9".to_string(), "3".to_string(), "+".to_string(), "-11".to_string(), "*".to_string(), "/".to_string(), "*".to_string(), "17".to_string(), "+".to_string(), "5".to_string(), "+".to_string()], 22),
    ];
    
    for (i, (tokens, expected)) in test_cases.iter().enumerate() {
        let result1 = eval_rpn(tokens.clone());
        let result2 = eval_rpn_functional(tokens.clone());
        
        println!("测试用例 {}: {:?}", i + 1, tokens);
        println!("标准实现结果: {}, 函数式实现结果: {}, 期望结果: {}", result1, result2, expected);
        println!("标准实现正确: {}, 函数式实现正确: {}", result1 == *expected, result2 == *expected);
        println!();
    }
    
    println!("=== Rust特性说明 ===");
    println!("1. 模式匹配: match表达式处理不同操作符");
    println!("2. 函数式编程: fold方法实现累积计算");
    println!("3. 所有权系统: 安全的内存管理");
    println!("4. 错误处理: unwrap处理Option类型");
    println!("5. 类型推断: 编译器自动推断类型");
}

/*
Rust实现特点:

1. **内存安全**:
   - 编译时检查内存安全
   - 无需手动内存管理
   - 防止缓冲区溢出

2. **函数式编程**:
   - fold方法实现累积操作
   - 闭包和高阶函数
   - 不可变数据结构

3. **模式匹配**:
   - match表达式处理多种情况
   - 穷尽性检查
   - 解构和绑定

4. **类型系统**:
   - 强类型系统
   - 类型推断
   - 泛型支持

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/