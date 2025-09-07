// LeetCode 1013: 将数组分成和相等的三个部分
// 给定一个整数数组，判断是否可以将其分成三个非空的连续子数组，使得这三个子数组的和相等

use std::collections::HashMap;
use std::iter::Iterator;

// 标准实现
fn can_three_parts_equal_sum_standard(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let mut part = 0;
    let mut current_sum = 0;
    
    for x in arr {
        current_sum += x;
        if current_sum == sum / 3 {
            current_sum = 0;
            part += 1;
        }
    }
    
    part >= 3
}

// 函数式编程版本
fn can_three_parts_equal_sum_functional(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let target = sum / 3;
    let (_, part_count) = arr
        .into_iter()
        .fold((0, 0), |(current_sum, part_count), x| {
            let new_sum = current_sum + x;
            if new_sum == target {
                (0, part_count + 1)
            } else {
                (new_sum, part_count)
            }
        });
    
    part_count >= 3
}

// 使用scan的高级版本
fn can_three_parts_equal_sum_scan(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let target = sum / 3;
    let part_count = arr
        .into_iter()
        .scan(0, |current_sum, x| {
            *current_sum += x;
            if *current_sum == target {
                let result = Some(1);
                *current_sum = 0;
                result
            } else {
                Some(0)
            }
        })
        .sum::<i32>();
    
    part_count >= 3
}

// 使用Iterator适配器链的版本
fn can_three_parts_equal_sum_iterator_chain(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let target = sum / 3;
    let mut current_sum = 0;
    
    arr.into_iter()
        .map(|x| {
            current_sum += x;
            if current_sum == target {
                current_sum = 0;
                1
            } else {
                0
            }
        })
        .sum::<i32>() >= 3
}

// 使用闭包和高阶函数的版本
fn can_three_parts_equal_sum_closure(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let target = sum / 3;
    let mut current_sum = 0;
    
    let count_parts = |nums: Vec<i32>| -> i32 {
        nums.into_iter()
            .filter_map(|x| {
                current_sum += x;
                if current_sum == target {
                    current_sum = 0;
                    Some(1)
                } else {
                    None
                }
            })
            .sum()
    };
    
    count_parts(arr) >= 3
}

// 使用泛型和Trait的版本
trait ThreePartChecker<T> {
    fn can_split_into_three_equal_parts(&self) -> bool;
    fn calculate_sum(&self) -> T;
}

impl ThreePartChecker<i32> for Vec<i32> {
    fn can_split_into_three_equal_parts(&self) -> bool {
        let sum = self.calculate_sum();
        if sum % 3 != 0 {
            return false;
        }
        
        let target = sum / 3;
        let mut current_sum = 0;
        let mut part_count = 0;
        
        for &x in self {
            current_sum += x;
            if current_sum == target {
                current_sum = 0;
                part_count += 1;
            }
        }
        
        part_count >= 3
    }
    
    fn calculate_sum(&self) -> i32 {
        self.iter().sum()
    }
}

fn can_three_parts_equal_sum_trait(arr: Vec<i32>) -> bool {
    arr.can_split_into_three_equal_parts()
}

// 使用自定义Iterator的版本
struct PartitionIterator {
    arr: Vec<i32>,
    index: usize,
    current_sum: i32,
    target: i32,
}

impl PartitionIterator {
    fn new(arr: Vec<i32>) -> Option<Self> {
        let sum: i32 = arr.iter().sum();
        if sum % 3 != 0 {
            return None;
        }
        
        Some(Self {
            arr,
            index: 0,
            current_sum: 0,
            target: sum / 3,
        })
    }
}

impl Iterator for PartitionIterator {
    type Item = bool; // true表示找到一个部分
    
    fn next(&mut self) -> Option<Self::Item> {
        if self.index >= self.arr.len() {
            return None;
        }
        
        self.current_sum += self.arr[self.index];
        self.index += 1;
        
        if self.current_sum == self.target {
            self.current_sum = 0;
            Some(true)
        } else {
            Some(false)
        }
    }
}

fn can_three_parts_equal_sum_custom_iterator(arr: Vec<i32>) -> bool {
    if let Some(iter) = PartitionIterator::new(arr) {
        iter.filter(|&found_part| found_part).count() >= 3
    } else {
        false
    }
}

// 使用Result和错误处理的版本
#[derive(Debug)]
enum PartitionError {
    NotDivisibleByThree,
    InsufficientParts,
    EmptyArray,
}

fn can_three_parts_equal_sum_with_error_handling(arr: Vec<i32>) -> Result<bool, PartitionError> {
    if arr.is_empty() {
        return Err(PartitionError::EmptyArray);
    }
    
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return Err(PartitionError::NotDivisibleByThree);
    }
    
    let target = sum / 3;
    let mut current_sum = 0;
    let mut part_count = 0;
    
    for x in arr {
        current_sum += x;
        if current_sum == target {
            current_sum = 0;
            part_count += 1;
        }
    }
    
    if part_count >= 3 {
        Ok(true)
    } else {
        Err(PartitionError::InsufficientParts)
    }
}

// 使用状态机模式的版本
#[derive(Debug, Clone, Copy)]
enum PartitionState {
    Searching,
    FoundFirst,
    FoundSecond,
    FoundThird,
}

struct StateMachine {
    state: PartitionState,
    current_sum: i32,
    target: i32,
}

impl StateMachine {
    fn new(target: i32) -> Self {
        Self {
            state: PartitionState::Searching,
            current_sum: 0,
            target,
        }
    }
    
    fn process(&mut self, value: i32) {
        self.current_sum += value;
        
        if self.current_sum == self.target {
            self.state = match self.state {
                PartitionState::Searching => PartitionState::FoundFirst,
                PartitionState::FoundFirst => PartitionState::FoundSecond,
                PartitionState::FoundSecond => PartitionState::FoundThird,
                PartitionState::FoundThird => PartitionState::FoundThird,
            };
            self.current_sum = 0;
        }
    }
    
    fn is_complete(&self) -> bool {
        matches!(self.state, PartitionState::FoundThird)
    }
}

fn can_three_parts_equal_sum_state_machine(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let mut machine = StateMachine::new(sum / 3);
    
    for value in arr {
        machine.process(value);
        if machine.is_complete() {
            return true;
        }
    }
    
    false
}

// 使用并行处理的版本（需要rayon crate）
#[cfg(feature = "parallel")]
use rayon::prelude::*;

#[cfg(feature = "parallel")]
fn can_three_parts_equal_sum_parallel(arr: Vec<i32>) -> bool {
    let sum: i32 = arr.par_iter().sum();
    if sum % 3 != 0 {
        return false;
    }
    
    let target = sum / 3;
    let mut current_sum = 0;
    let mut part_count = 0;
    
    // 注意：并行处理在这种累积场景下可能不适用
    // 这里展示概念，实际应用需要更复杂的分割策略
    for x in arr {
        current_sum += x;
        if current_sum == target {
            current_sum = 0;
            part_count += 1;
        }
    }
    
    part_count >= 3
}

// 使用生成器模式的版本
struct PartitionGenerator {
    arr: Vec<i32>,
    target: i32,
}

impl PartitionGenerator {
    fn new(arr: Vec<i32>) -> Option<Self> {
        let sum: i32 = arr.iter().sum();
        if sum % 3 != 0 {
            return None;
        }
        
        Some(Self {
            arr,
            target: sum / 3,
        })
    }
    
    fn generate_partitions(self) -> impl Iterator<Item = bool> {
        let mut current_sum = 0;
        
        self.arr.into_iter().map(move |x| {
            current_sum += x;
            if current_sum == self.target {
                current_sum = 0;
                true
            } else {
                false
            }
        })
    }
}

fn can_three_parts_equal_sum_generator(arr: Vec<i32>) -> bool {
    if let Some(generator) = PartitionGenerator::new(arr) {
        generator.generate_partitions().filter(|&found| found).count() >= 3
    } else {
        false
    }
}

fn main() {
    let test_cases = vec![
        vec![0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1],
        vec![0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1],
        vec![3, 3, 3],
        vec![1, 1, 1, 1],
        vec![0, 0, 0, 0],
    ];
    
    println!("=== 将数组分成和相等的三个部分 ===");
    
    for (i, arr) in test_cases.iter().enumerate() {
        println!("\n测试用例 {}: {:?}", i + 1, arr);
        
        let result1 = can_three_parts_equal_sum_standard(arr.clone());
        let result2 = can_three_parts_equal_sum_functional(arr.clone());
        let result3 = can_three_parts_equal_sum_scan(arr.clone());
        let result4 = can_three_parts_equal_sum_iterator_chain(arr.clone());
        let result5 = can_three_parts_equal_sum_closure(arr.clone());
        let result6 = can_three_parts_equal_sum_trait(arr.clone());
        let result7 = can_three_parts_equal_sum_custom_iterator(arr.clone());
        let result8 = can_three_parts_equal_sum_state_machine(arr.clone());
        let result9 = can_three_parts_equal_sum_generator(arr.clone());
        
        println!("标准实现: {}", result1);
        println!("函数式版本: {}", result2);
        println!("scan版本: {}", result3);
        println!("Iterator链版本: {}", result4);
        println!("闭包版本: {}", result5);
        println!("Trait版本: {}", result6);
        println!("自定义Iterator: {}", result7);
        println!("状态机版本: {}", result8);
        println!("生成器版本: {}", result9);
        
        // 错误处理版本测试
        match can_three_parts_equal_sum_with_error_handling(arr.clone()) {
            Ok(result) => println!("错误处理版本: {}", result),
            Err(e) => println!("错误处理版本: 错误 - {:?}", e),
        }
        
        // 验证结果一致性
        let results = vec![result1, result2, result3, result4, result5, result6, result7, result8, result9];
        assert!(results.iter().all(|&r| r == result1), "结果不一致!");
        println!("✓ 所有实现结果一致");
    }
    
    println!("\n=== Rust高级特性说明 ===");
    println!("1. Iterator适配器: scan, fold, filter_map等链式操作");
    println!("2. 闭包捕获: 函数式编程范式");
    println!("3. Trait系统: 自定义行为和泛型约束");
    println!("4. 自定义Iterator: 实现Iterator trait");
    println!("5. 错误处理: Result<T, E>和自定义错误类型");
    println!("6. 状态机模式: 枚举和模式匹配");
    println!("7. 生成器模式: 惰性计算");
    println!("8. 内存安全: 所有权和借用检查");
    println!("9. 零成本抽象: 编译时优化");
    println!("10. 模式匹配: match表达式和if let");
}

/*
Rust高级特性详解:

1. **Iterator适配器链**:
   - scan(): 有状态的map操作
   - fold(): 累积操作
   - filter_map(): 过滤和转换结合
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
   - 自定义错误类型
   - ?操作符
   - 强制错误处理

6. **状态机模式**:
   - 枚举表示状态
   - 模式匹配状态转换
   - 类型安全的状态管理
   - 编译时状态验证

7. **生成器模式**:
   - 惰性计算
   - 内存效率
   - 组合性
   - 函数式风格

8. **内存管理**:
   - 所有权系统
   - 借用和引用
   - 生命周期
   - 零成本抽象

9. **并发编程**:
   - Send和Sync trait
   - 线程安全保证
   - 数据竞争预防
   - 无锁数据结构

10. **模式匹配**:
    - match表达式
    - if let语法
    - 解构赋值
    - 穷尽性检查
*/