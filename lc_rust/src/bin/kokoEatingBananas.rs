// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

// use std::cmp;
// use std::collections::HashMap;

// 标准二分查找实现
fn min_eating_speed_binary_search(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let mut left = 1;
    let mut right = *piles.iter().max().unwrap();
    
    while left < right {
        let mid = left + (right - left) / 2;
        let total_hours: i32 = piles
            .iter()
            .map(|&pile| (pile + mid - 1) / mid)  // ceil(pile / mid)
            .sum();
        
        if total_hours <= h {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    left
}

// 函数式编程版本
fn min_eating_speed_functional(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let can_finish = |k: i32| -> bool {
        piles
            .iter()
            .map(|&pile| (pile + k - 1) / k)
            .sum::<i32>() <= h
    };
    
    let max_pile = *piles.iter().max().unwrap();
    
    (1..=max_pile)
        .find(|&k| can_finish(k))
        .unwrap_or(max_pile)
}

// 高级函数式版本 - 使用fold和scan
fn min_eating_speed_advanced_functional(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let max_pile = *piles.iter().max().unwrap();
    let total_bananas: i32 = piles.iter().sum();
    
    // 使用scan进行有状态的搜索
    let search_range = (1..=max_pile)
        .scan(false, |found, k| {
            if *found {
                return None; // 已找到，停止搜索
            }
            
            let hours_needed = piles
                .iter()
                .fold(0, |acc, &pile| acc + (pile + k - 1) / k);
            
            if hours_needed <= h {
                *found = true;
                Some(Some(k))
            } else {
                Some(None)
            }
        })
        .flatten()
        .next();
    
    search_range.unwrap_or(max_pile)
}

// 泛型和Trait版本
trait BinarySearchable<T> {
    fn binary_search_min<F>(&self, predicate: F) -> Option<T>
    where
        F: Fn(T) -> bool,
        T: Copy + Ord + std::ops::Add<Output = T> + std::ops::Sub<Output = T> + std::ops::Div<Output = T> + From<u8>;
}

struct Range<T> {
    start: T,
    end: T,
}

impl<T> BinarySearchable<T> for Range<T>
where
    T: Copy + Ord + std::ops::Add<Output = T> + std::ops::Sub<Output = T> + std::ops::Div<Output = T> + From<u8>,
{
    fn binary_search_min<F>(&self, predicate: F) -> Option<T>
    where
        F: Fn(T) -> bool,
    {
        let mut left = self.start;
        let mut right = self.end;
        let two = T::from(2);
        
        while left < right {
            let mid = left + (right - left) / two;
            if predicate(mid) {
                right = mid;
            } else {
                left = mid + T::from(1);
            }
        }
        
        if predicate(left) {
            Some(left)
        } else {
            None
        }
    }
}

fn min_eating_speed_generic(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let max_pile = *piles.iter().max().unwrap();
    let range = Range { start: 1, end: max_pile };
    
    let predicate = |k: i32| -> bool {
        piles
            .iter()
            .map(|&pile| (pile + k - 1) / k)
            .sum::<i32>() <= h
    };
    
    range.binary_search_min(predicate).unwrap_or(max_pile)
}

// 使用闭包和高阶函数的版本
fn min_eating_speed_closure(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let max_pile = *piles.iter().max().unwrap();
    
    // 创建一个返回闭包的函数
    let piles_clone = piles.clone();
    let checker = move |k: i32| -> bool {
        piles_clone
            .iter()
            .map(|&pile| (pile + k - 1) / k)
            .sum::<i32>() <= h
    };
    
    // 使用partition_point进行二分查找
    let result = (1..=max_pile)
        .collect::<Vec<_>>()
        .partition_point(|&k| !checker(k));
    
    if result <= max_pile as usize {
        result as i32 + 1
    } else {
        max_pile
    }
}

// 使用Iterator适配器的高级版本
fn min_eating_speed_iterator_advanced(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let max_pile = *piles.iter().max().unwrap();
    
    // 使用try_fold进行早期退出的搜索
    let result = (1..=max_pile)
        .try_fold(None::<i32>, |acc, k| {
            let hours_needed = piles
                .iter()
                .try_fold(0, |sum, &pile| {
                    let hours = (pile + k - 1) / k;
                    let new_sum = sum + hours;
                    if new_sum > h {
                        Err(()) // 早期退出
                    } else {
                        Ok(new_sum)
                    }
                });
            
            match hours_needed {
                Ok(_) => Err(k), // 找到答案，退出
                Err(_) => Ok(acc), // 继续搜索
            }
        });
    
    match result {
        Err(k) => k, // 找到的答案
        Ok(_) => max_pile, // 没找到，返回最大值
    }
}

// 使用自定义Iterator的版本
struct BinarySearchIterator {
    left: i32,
    right: i32,
    predicate: Box<dyn Fn(i32) -> bool>,
}

impl BinarySearchIterator {
    fn new<F>(left: i32, right: i32, predicate: F) -> Self
    where
        F: Fn(i32) -> bool + 'static,
    {
        Self {
            left,
            right,
            predicate: Box::new(predicate),
        }
    }
}

impl Iterator for BinarySearchIterator {
    type Item = i32;
    
    fn next(&mut self) -> Option<Self::Item> {
        if self.left >= self.right {
            return None;
        }
        
        let mid = self.left + (self.right - self.left) / 2;
        
        if (self.predicate)(mid) {
            self.right = mid;
        } else {
            self.left = mid + 1;
        }
        
        if self.left == self.right {
            Some(self.left)
        } else {
            Some(mid) // 返回中间值用于调试
        }
    }
}

fn min_eating_speed_custom_iterator(piles: Vec<i32>, h: i32) -> i32 {
    if piles.is_empty() {
        return 0;
    }
    
    let max_pile = *piles.iter().max().unwrap();
    let piles_clone = piles.clone();
    
    let predicate = move |k: i32| -> bool {
        piles_clone
            .iter()
            .map(|&pile| (pile + k - 1) / k)
            .sum::<i32>() <= h
    };
    
    let search_iter: BinarySearchIterator = BinarySearchIterator::new(1, max_pile, predicate);
    search_iter.last().unwrap_or(max_pile)
}

// 使用Result和错误处理的版本
#[derive(Debug)]
enum EatingError {
    EmptyPiles,
    ImpossibleToFinish,
    InvalidInput,
}

fn min_eating_speed_with_error_handling(piles: Vec<i32>, h: i32) -> Result<i32, EatingError> {
    if piles.is_empty() {
        return Err(EatingError::EmptyPiles);
    }
    
    if h <= 0 {
        return Err(EatingError::InvalidInput);
    }
    
    let max_pile = *piles.iter().max().unwrap();
    
    // 检查是否可能完成
    if h < piles.len() as i32 {
        return Err(EatingError::ImpossibleToFinish);
    }
    
    let mut left = 1;
    let mut right = max_pile;
    
    while left < right {
        let mid = left + (right - left) / 2;
        let total_hours: i32 = piles
            .iter()
            .map(|&pile| (pile + mid - 1) / mid)
            .sum();
        
        if total_hours <= h {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    Ok(left)
}

fn main() {
    let test_cases = vec![
        (vec![3, 6, 7, 11], 8),
        (vec![30, 11, 23, 4, 20], 5),
        (vec![30, 11, 23, 4, 20], 6),
        (vec![1, 1, 1, 1], 4),
        (vec![312884470], 312884469),
    ];
    
    println!("=== 爱吃香蕉的珂珂 ===");
    
    for (i, (piles, h)) in test_cases.iter().enumerate() {
        println!("\n测试用例 {}: piles={:?}, h={}", i + 1, piles, h);
        
        let result1 = min_eating_speed_binary_search(piles.clone(), *h);
        let result2 = min_eating_speed_functional(piles.clone(), *h);
        let result3 = min_eating_speed_advanced_functional(piles.clone(), *h);
        let result4 = min_eating_speed_generic(piles.clone(), *h);
        let result5 = min_eating_speed_closure(piles.clone(), *h);
        let result6 = min_eating_speed_iterator_advanced(piles.clone(), *h);
        let result7 = min_eating_speed_custom_iterator(piles.clone(), *h);
        
        println!("标准二分查找: {}", result1);
        println!("函数式版本: {}", result2);
        println!("高级函数式: {}", result3);
        println!("泛型版本: {}", result4);
        println!("闭包版本: {}", result5);
        println!("Iterator高级版本: {}", result6);
        println!("自定义Iterator: {}", result7);
        
        // 错误处理版本
        match min_eating_speed_with_error_handling(piles.clone(), *h) {
            Ok(result) => println!("错误处理版本: {}", result),
            Err(e) => println!("错误处理版本: 错误 - {:?}", e),
        }
        
        // 验证结果一致性
        let results = vec![result1, result2, result3, result4, result5, result6, result7];
        assert!(results.iter().all(|&r| r == result1), "结果不一致!");
    }
    
    println!("\n=== Rust高级特性说明 ===");
    println!("1. scan(): 有状态的迭代器转换，可以提前终止");
    println!("2. fold(): 累积操作，可以用于复杂的聚合计算");
    println!("3. try_fold(): 可失败的fold，支持早期退出");
    println!("4. partition_point(): 在已排序序列中找到分割点");
    println!("5. 泛型Trait: 为任意类型实现二分查找");
    println!("6. 自定义Iterator: 实现Iterator trait创建专用迭代器");
    println!("7. 闭包捕获: 闭包可以捕获外部环境的变量");
    println!("8. 高阶函数: 函数作为参数和返回值");
    println!("9. Result<T, E>: Rust的错误处理机制");
    println!("10. Box<dyn Trait>: 动态分发的trait对象");
}

/*
高级特性详解:

1. **scan()函数**:
   - 有状态的迭代器转换，类似fold但产生中间结果
   - 可以通过返回None提前终止迭代
   - 适合需要累积状态并在满足条件时停止的场景

2. **try_fold()函数**:
   - 可失败的fold操作，支持早期退出
   - 当遇到错误或满足条件时可以立即返回
   - 比普通fold更高效，避免不必要的计算

3. **partition_point()函数**:
   - 在已排序序列中找到满足谓词的分割点
   - 内部使用二分查找，时间复杂度O(log n)
   - 适合在有序数据中查找边界

4. **泛型Trait系统**:
   - 定义通用的二分查找行为
   - 支持多种数值类型
   - 类型约束确保类型安全

5. **自定义Iterator**:
   - 实现Iterator trait创建专用迭代器
   - 可以封装复杂的迭代逻辑
   - 与标准库Iterator方法无缝集成

6. **闭包和高阶函数**:
   - 闭包可以捕获外部环境
   - 函数可以返回闭包
   - 支持函数式编程范式

7. **错误处理**:
   - Result<T, E>类型表示可能失败的操作
   - 自定义错误类型提供详细错误信息
   - 强制错误处理，提高代码健壮性

8. **动态分发**:
   - Box<dyn Trait>实现运行时多态
   - 允许存储不同类型但实现相同trait的对象
   - 在需要类型擦除时很有用

9. **零成本抽象**:
   - 高级抽象在编译时被优化
   - 运行时性能与手写循环相当
   - 既保证性能又提高代码可读性
*/