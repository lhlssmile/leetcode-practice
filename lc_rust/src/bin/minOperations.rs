// LeetCode 题目：最小操作数
// 给定查询数组，每个查询包含[l, r]，需要计算最小操作数

use std::collections::HashMap;
use std::ops::Range;

// 标准实现
fn prefix(n: i64) -> i64 {
    let mut ans = 0;
    let mut base = 1i64;
    let mut k = 1i64;
    
    loop {
        let next_base = base * 4;
        let l = base;
        let r = next_base - 1;
        
        if n >= r {
            ans += (r - l + 1) * k;
        } else {
            ans += (n - l + 1) * k;
            break;
        }
        
        base = next_base;
        k += 1;
    }
    
    ans
}

fn min_operations_standard(queries: Vec<Vec<i32>>) -> i64 {
    let mut total = 0i64;
    
    for query in queries {
        let l = query[0] as i64;
        let r = query[1] as i64;
        let s = prefix(r) - prefix(l - 1);
        total += (s + 1) / 2;
    }
    
    total
}

// 函数式编程版本
fn min_operations_functional(queries: Vec<Vec<i32>>) -> i64 {
    queries
        .iter()
        .map(|query| {
            let (l, r) = (query[0] as i64, query[1] as i64);
            let s = prefix(r) - prefix(l - 1);
            (s + 1) / 2
        })
        .sum()
}

// 使用Iterator适配器的高级版本
fn min_operations_iterator_advanced(queries: Vec<Vec<i32>>) -> i64 {
    queries
        .into_iter()
        .map(|query| (query[0] as i64, query[1] as i64))
        .map(|(l, r)| prefix(r) - prefix(l - 1))
        .map(|s| (s + 1) / 2)
        .sum()
}

// 使用fold的版本
fn min_operations_fold(queries: Vec<Vec<i32>>) -> i64 {
    queries
        .iter()
        .fold(0i64, |acc, query| {
            let l = query[0] as i64;
            let r = query[1] as i64;
            let s = prefix(r) - prefix(l - 1);
            acc + (s + 1) / 2
        })
}

// 使用缓存的优化版本
struct PrefixCalculator {
    cache: HashMap<i64, i64>,
}

impl PrefixCalculator {
    fn new() -> Self {
        Self {
            cache: HashMap::new(),
        }
    }
    
    fn prefix_cached(&mut self, n: i64) -> i64 {
        if let Some(&cached) = self.cache.get(&n) {
            return cached;
        }
        
        let result = self.calculate_prefix(n);
        self.cache.insert(n, result);
        result
    }
    
    fn calculate_prefix(&self, n: i64) -> i64 {
        let mut ans = 0;
        let mut base = 1i64;
        let mut k = 1i64;
        
        loop {
            let next_base = base * 4;
            let l = base;
            let r = next_base - 1;
            
            if n >= r {
                ans += (r - l + 1) * k;
            } else {
                ans += (n - l + 1) * k;
                break;
            }
            
            base = next_base;
            k += 1;
        }
        
        ans
    }
}

fn min_operations_cached(queries: Vec<Vec<i32>>) -> i64 {
    let mut calculator = PrefixCalculator::new();
    let mut total = 0i64;
    
    for query in queries {
        let l = query[0] as i64;
        let r = query[1] as i64;
        let s = calculator.prefix_cached(r) - calculator.prefix_cached(l - 1);
        total += (s + 1) / 2;
    }
    
    total
}

// 使用泛型和Trait的版本
trait PrefixCalculable {
    fn calculate_prefix(&self, n: i64) -> i64;
    fn calculate_range_sum(&self, l: i64, r: i64) -> i64 {
        self.calculate_prefix(r) - self.calculate_prefix(l - 1)
    }
}

struct StandardCalculator;

impl PrefixCalculable for StandardCalculator {
    fn calculate_prefix(&self, n: i64) -> i64 {
        prefix(n)
    }
}

struct OptimizedCalculator {
    cache: std::cell::RefCell<HashMap<i64, i64>>,
}

impl OptimizedCalculator {
    fn new() -> Self {
        Self {
            cache: std::cell::RefCell::new(HashMap::new()),
        }
    }
}

impl PrefixCalculable for OptimizedCalculator {
    fn calculate_prefix(&self, n: i64) -> i64 {
        let mut cache = self.cache.borrow_mut();
        
        if let Some(&cached) = cache.get(&n) {
            return cached;
        }
        
        let result = prefix(n);
        cache.insert(n, result);
        result
    }
}

fn min_operations_generic<T: PrefixCalculable>(queries: Vec<Vec<i32>>, calculator: &T) -> i64 {
    queries
        .iter()
        .map(|query| {
            let l = query[0] as i64;
            let r = query[1] as i64;
            let s = calculator.calculate_range_sum(l, r);
            (s + 1) / 2
        })
        .sum()
}

// 使用闭包和高阶函数的版本
fn min_operations_closure(queries: Vec<Vec<i32>>) -> i64 {
    let calculate_operations = |l: i64, r: i64| -> i64 {
        let s = prefix(r) - prefix(l - 1);
        (s + 1) / 2
    };
    
    queries
        .iter()
        .map(|query| calculate_operations(query[0] as i64, query[1] as i64))
        .sum()
}

// 使用并行处理的版本（需要rayon crate）
#[cfg(feature = "parallel")]
use rayon::prelude::*;

#[cfg(feature = "parallel")]
fn min_operations_parallel(queries: Vec<Vec<i32>>) -> i64 {
    queries
        .par_iter()
        .map(|query| {
            let l = query[0] as i64;
            let r = query[1] as i64;
            let s = prefix(r) - prefix(l - 1);
            (s + 1) / 2
        })
        .sum()
}

// 使用自定义Iterator的版本
struct QueryIterator {
    queries: Vec<Vec<i32>>,
    index: usize,
}

impl QueryIterator {
    fn new(queries: Vec<Vec<i32>>) -> Self {
        Self { queries, index: 0 }
    }
}

impl Iterator for QueryIterator {
    type Item = i64;
    
    fn next(&mut self) -> Option<Self::Item> {
        if self.index >= self.queries.len() {
            return None;
        }
        
        let query = &self.queries[self.index];
        let l = query[0] as i64;
        let r = query[1] as i64;
        let s = prefix(r) - prefix(l - 1);
        let result = (s + 1) / 2;
        
        self.index += 1;
        Some(result)
    }
}

fn min_operations_custom_iterator(queries: Vec<Vec<i32>>) -> i64 {
    QueryIterator::new(queries).sum()
}

// 使用Result和错误处理的版本
#[derive(Debug)]
enum CalculationError {
    InvalidQuery,
    EmptyQueries,
    NegativeValue,
}

fn min_operations_with_error_handling(queries: Vec<Vec<i32>>) -> Result<i64, CalculationError> {
    if queries.is_empty() {
        return Err(CalculationError::EmptyQueries);
    }
    
    let mut total = 0i64;
    
    for query in queries {
        if query.len() != 2 {
            return Err(CalculationError::InvalidQuery);
        }
        
        let l = query[0] as i64;
        let r = query[1] as i64;
        
        if l < 0 || r < 0 || l > r {
            return Err(CalculationError::NegativeValue);
        }
        
        let s = prefix(r) - prefix(l - 1);
        total += (s + 1) / 2;
    }
    
    Ok(total)
}

// 使用生成器模式的版本
struct OperationGenerator {
    queries: Vec<Vec<i32>>,
}

impl OperationGenerator {
    fn new(queries: Vec<Vec<i32>>) -> Self {
        Self { queries }
    }
    
    fn generate_operations(self) -> impl Iterator<Item = i64> {
        self.queries.into_iter().map(|query| {
            let l = query[0] as i64;
            let r = query[1] as i64;
            let s = prefix(r) - prefix(l - 1);
            (s + 1) / 2
        })
    }
}

fn min_operations_generator(queries: Vec<Vec<i32>>) -> i64 {
    OperationGenerator::new(queries)
        .generate_operations()
        .sum()
}

fn main() {
    let test_queries = vec![
        vec![vec![1, 4], vec![2, 6], vec![3, 8]],
        vec![vec![1, 10], vec![5, 15]],
        vec![vec![1, 1], vec![2, 2], vec![3, 3]],
    ];
    
    println!("=== 最小操作数计算 ===");
    
    for (i, queries) in test_queries.iter().enumerate() {
        println!("\n测试用例 {}: {:?}", i + 1, queries);
        
        let result1 = min_operations_standard(queries.clone());
        let result2 = min_operations_functional(queries.clone());
        let result3 = min_operations_iterator_advanced(queries.clone());
        let result4 = min_operations_fold(queries.clone());
        let result5 = min_operations_cached(queries.clone());
        let result6 = min_operations_closure(queries.clone());
        let result7 = min_operations_custom_iterator(queries.clone());
        let result8 = min_operations_generator(queries.clone());
        
        // 泛型版本测试
        let standard_calc = StandardCalculator;
        let optimized_calc = OptimizedCalculator::new();
        let result9 = min_operations_generic(queries.clone(), &standard_calc);
        let result10 = min_operations_generic(queries.clone(), &optimized_calc);
        
        println!("标准实现: {}", result1);
        println!("函数式版本: {}", result2);
        println!("Iterator高级版本: {}", result3);
        println!("fold版本: {}", result4);
        println!("缓存版本: {}", result5);
        println!("闭包版本: {}", result6);
        println!("自定义Iterator: {}", result7);
        println!("生成器版本: {}", result8);
        println!("泛型版本(标准): {}", result9);
        println!("泛型版本(优化): {}", result10);
        
        // 错误处理版本测试
        match min_operations_with_error_handling(queries.clone()) {
            Ok(result) => println!("错误处理版本: {}", result),
            Err(e) => println!("错误处理版本: 错误 - {:?}", e),
        }
        
        // 验证结果一致性
        let results = vec![result1, result2, result3, result4, result5, result6, result7, result8, result9, result10];
        assert!(results.iter().all(|&r| r == result1), "结果不一致!");
        println!("✓ 所有实现结果一致");
    }
    
    println!("\n=== Rust高级特性说明 ===");
    println!("1. Iterator适配器: map, fold, sum等链式操作");
    println!("2. 闭包捕获: 函数式编程范式");
    println!("3. Trait系统: 泛型约束和多态");
    println!("4. 自定义Iterator: 实现Iterator trait");
    println!("5. 错误处理: Result<T, E>类型");
    println!("6. 内存安全: 借用检查器和所有权");
    println!("7. 零成本抽象: 编译时优化");
    println!("8. 模式匹配: match表达式");
    println!("9. 生命周期: 引用有效性保证");
    println!("10. 并发安全: Send和Sync trait");
}

/*
Rust高级特性详解:

1. **Iterator适配器链**:
   - map(): 转换每个元素
   - fold(): 累积操作
   - sum(): 求和操作
   - 惰性求值和零成本抽象

2. **函数式编程**:
   - 闭包: |x| x + 1
   - 高阶函数: 函数作为参数
   - 不可变性: 默认不可变
   - 纯函数: 无副作用

3. **Trait系统**:
   - 定义共同行为
   - 泛型约束
   - 默认实现
   - 孤儿规则

4. **自定义Iterator**:
   - 实现Iterator trait
   - next()方法定义
   - 与标准库无缝集成
   - 惰性计算

5. **错误处理**:
   - Result<T, E>类型
   - Option<T>类型
   - ?操作符
   - 强制错误处理

6. **内存管理**:
   - 所有权系统
   - 借用和引用
   - 生命周期
   - 零成本抽象

7. **并发编程**:
   - Send和Sync trait
   - 线程安全保证
   - 数据竞争预防
   - 无锁数据结构

8. **模式匹配**:
   - match表达式
   - if let语法
   - 解构赋值
   - 穷尽性检查

9. **泛型编程**:
   - 类型参数
   - 生命周期参数
   - 关联类型
   - 单态化

10. **宏系统**:
    - 声明式宏
    - 过程宏
    - 编译时代码生成
    - 元编程能力
*/