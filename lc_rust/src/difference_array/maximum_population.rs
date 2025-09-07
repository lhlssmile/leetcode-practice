//! LeetCode 1854. 人口最多的年份
//!
//! 给你一个二维整数数组 logs，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。
//! 年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在区间 [birthi, deathi - 1] 内。
//! 注意，人在死亡当年不被计入人口内。
//! 返回 人口最多 的年份。
//!
//! 算法思路：差分数组
//! 1. 使用差分数组记录每年人口变化
//! 2. 出生年份+1，死亡年份-1
//! 3. 通过前缀和还原每年实际人口
//! 4. 找到人口最多的年份
//!
//! 时间复杂度：O(n + 101) = O(n)
//! 空间复杂度：O(101) = O(1)

use std::collections::{HashMap, BTreeMap};
use std::cmp::Ordering;
use std::time::Instant;
use std::fmt;

/// 日志条目类型：[出生年份, 死亡年份]
type LogEntry = [i32; 2];

/// 人口数据结构
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct PopulationData {
    pub year: i32,
    pub population: i32,
}

/// 算法结果
#[derive(Debug, Clone)]
pub struct AlgorithmResult {
    pub year: i32,
    pub max_population: i32,
    pub execution_time: Option<std::time::Duration>,
}

/// 人口事件
#[derive(Debug, Clone, PartialEq, Eq)]
struct PopulationEvent {
    year: i32,
    change: i32,  // +1 for birth, -1 for death
}

impl Ord for PopulationEvent {
    fn cmp(&self, other: &Self) -> Ordering {
        match self.year.cmp(&other.year) {
            Ordering::Equal => self.change.cmp(&other.change), // 死亡事件(-1)在出生事件(1)前
            other => other,
        }
    }
}

impl PartialOrd for PopulationEvent {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

/// 人口计算器特征
pub trait PopulationCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32;
    fn get_complexity(&self) -> (&'static str, &'static str);
    fn name(&self) -> &'static str;
}

/// 差分数组解法（主要实现）
pub fn maximum_population(logs: Vec<Vec<i32>>) -> i32 {
    let mut diff = [0; 101];  // 1950-2050年的差分数组
    
    // 构建差分数组
    for log in &logs {
        let birth = log[0] as usize;
        let death = log[1] as usize;
        diff[birth - 1950] += 1;   // 出生年份人口+1
        diff[death - 1950] -= 1;   // 死亡年份人口-1
    }
    
    let mut max_pop = 0;
    let mut year = 1950;
    let mut curr = 0;
    
    // 通过前缀和还原实际人口，同时找最大值
    for (i, &change) in diff.iter().enumerate() {
        curr += change;
        if curr > max_pop {
            max_pop = curr;
            year = 1950 + i as i32;
        }
    }
    
    year
}

/// 差分数组解法（适配器版本）
pub fn maximum_population_adapter(logs: &[LogEntry]) -> i32 {
    let logs_vec: Vec<Vec<i32>> = logs.iter()
        .map(|&[birth, death]| vec![birth, death])
        .collect();
    maximum_population(logs_vec)
}

/// 暴力解法计算器
#[derive(Debug, Default)]
pub struct BruteForceCalculator;

impl PopulationCalculator for BruteForceCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32 {
        let mut max_pop = 0;
        let mut result_year = 1950;
        
        // 枚举每一年
        for year in 1950..=2050 {
            let mut population = 0;
            
            // 统计这一年的人口
            for &[birth, death] in logs {
                if year >= birth && year < death {
                    population += 1;
                }
            }
            
            // 更新最大人口年份
            if population > max_pop {
                max_pop = population;
                result_year = year;
            }
        }
        
        result_year
    }
    
    fn get_complexity(&self) -> (&'static str, &'static str) {
        ("O(101 * n)", "O(1)")
    }
    
    fn name(&self) -> &'static str {
        "暴力解法"
    }
}

/// 差分数组计算器
#[derive(Debug, Default)]
pub struct DifferenceArrayCalculator;

impl PopulationCalculator for DifferenceArrayCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32 {
        maximum_population_adapter(logs)
    }
    
    fn get_complexity(&self) -> (&'static str, &'static str) {
        ("O(n + 101)", "O(101)")
    }
    
    fn name(&self) -> &'static str {
        "差分数组"
    }
}

/// 事件排序计算器
#[derive(Debug, Default)]
pub struct EventSortingCalculator;

impl PopulationCalculator for EventSortingCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32 {
        let mut events = Vec::new();
        
        // 收集所有事件
        for &[birth, death] in logs {
            events.push(PopulationEvent { year: birth, change: 1 });   // 出生事件
            events.push(PopulationEvent { year: death, change: -1 });  // 死亡事件
        }
        
        // 按年份排序，同年份死亡事件在前
        events.sort();
        
        let mut max_pop = 0;
        let mut result_year = 1950;
        let mut current_pop = 0;
        
        // 处理事件
        for event in events {
            current_pop += event.change;
            if current_pop > max_pop {
                max_pop = current_pop;
                result_year = event.year;
            }
        }
        
        result_year
    }
    
    fn get_complexity(&self) -> (&'static str, &'static str) {
        ("O(n log n)", "O(n)")
    }
    
    fn name(&self) -> &'static str {
        "事件排序"
    }
}

/// HashMap解法计算器
#[derive(Debug, Default)]
pub struct HashMapCalculator;

impl PopulationCalculator for HashMapCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32 {
        let mut changes = HashMap::new();
        
        // 记录每年的人口变化
        for &[birth, death] in logs {
            *changes.entry(birth).or_insert(0) += 1;   // 出生年份+1
            *changes.entry(death).or_insert(0) -= 1;   // 死亡年份-1
        }
        
        // 获取所有年份并排序
        let mut years: Vec<i32> = changes.keys().copied().collect();
        years.sort_unstable();
        
        let mut max_pop = 0;
        let mut result_year = 1950;
        let mut current_pop = 0;
        
        // 按年份顺序处理变化
        for year in years {
            current_pop += changes[&year];
            if current_pop > max_pop {
                max_pop = current_pop;
                result_year = year;
            }
        }
        
        result_year
    }
    
    fn get_complexity(&self) -> (&'static str, &'static str) {
        ("O(n log n)", "O(n)")
    }
    
    fn name(&self) -> &'static str {
        "HashMap解法"
    }
}

/// BTreeMap解法计算器
#[derive(Debug, Default)]
pub struct BTreeMapCalculator;

impl PopulationCalculator for BTreeMapCalculator {
    fn calculate(&self, logs: &[LogEntry]) -> i32 {
        let mut changes = BTreeMap::new();
        
        // 记录每年的人口变化
        for &[birth, death] in logs {
            *changes.entry(birth).or_insert(0) += 1;   // 出生年份+1
            *changes.entry(death).or_insert(0) -= 1;   // 死亡年份-1
        }
        
        let mut max_pop = 0;
        let mut result_year = 1950;
        let mut current_pop = 0;
        
        // BTreeMap自动按键排序
        for (&year, &change) in &changes {
            current_pop += change;
            if current_pop > max_pop {
                max_pop = current_pop;
                result_year = year;
            }
        }
        
        result_year
    }
    
    fn get_complexity(&self) -> (&'static str, &'static str) {
        ("O(n log n)", "O(n)")
    }
    
    fn name(&self) -> &'static str {
        "BTreeMap解法"
    }
}

/// 泛型差分数组工具
#[derive(Debug, Clone)]
pub struct DifferenceArray<T> {
    diff: Vec<T>,
    offset: i32,
}

impl<T> DifferenceArray<T>
where
    T: Default + Clone + std::ops::AddAssign + std::ops::SubAssign + Copy + PartialOrd,
{
    /// 创建新的差分数组
    pub fn new(start: i32, end: i32) -> Self {
        let size = (end - start + 1) as usize;
        Self {
            diff: vec![T::default(); size],
            offset: start,
        }
    }
    
    /// 区间更新
    pub fn update(&mut self, left: i32, right: i32, delta: T) {
        let left_idx = (left - self.offset) as usize;
        let right_idx = (right - self.offset) as usize;
        
        if left_idx < self.diff.len() {
            self.diff[left_idx] += delta;
        }
        
        if right_idx + 1 < self.diff.len() {
            self.diff[right_idx + 1] -= delta;
        }
    }
    
    /// 获取前缀和数组
    pub fn get_prefix_sum(&self) -> Vec<T> {
        let mut result = vec![T::default(); self.diff.len()];
        if !self.diff.is_empty() {
            result[0] = self.diff[0];
            for i in 1..self.diff.len() {
                result[i] = result[i - 1];
                result[i] += self.diff[i];
            }
        }
        result
    }
    
    /// 找到最大值的索引
    pub fn find_max_index(&self) -> i32 {
        let prefix_sum = self.get_prefix_sum();
        let mut max_val = T::default();
        let mut max_idx = 0;
        
        for (i, &val) in prefix_sum.iter().enumerate() {
            if val > max_val {
                max_val = val;
                max_idx = i;
            }
        }
        
        self.offset + max_idx as i32
    }
}

/// 使用泛型工具的解法
pub fn maximum_population_with_generic(logs: &[LogEntry]) -> i32 {
    let mut diff_array = DifferenceArray::<i32>::new(1950, 2050);
    
    for &[birth, death] in logs {
        diff_array.update(birth, death - 1, 1);
    }
    
    diff_array.find_max_index()
}

/// 函数式编程解法
pub fn maximum_population_functional(logs: &[LogEntry]) -> i32 {
    // 构建差分数组
    let diff = logs.iter().fold([0; 101], |mut acc, &[birth, death]| {
        acc[(birth - 1950) as usize] += 1;
        acc[(death - 1950) as usize] -= 1;
        acc
    });
    
    // 计算前缀和并找最大值
    let (_, year) = diff.iter().enumerate().fold(
        (0, 0, 1950),  // (current_pop, max_pop, result_year)
        |(mut curr, mut max_pop, mut year), (i, &change)| {
            curr += change;
            if curr > max_pop {
                max_pop = curr;
                year = 1950 + i as i32;
            }
            (curr, max_pop, year)
        },
    ).2;
    
    year
}

/// 迭代器解法
pub fn maximum_population_iterator(logs: &[LogEntry]) -> i32 {
    let mut diff = [0; 101];
    
    // 使用迭代器构建差分数组
    logs.iter().for_each(|&[birth, death]| {
        diff[(birth - 1950) as usize] += 1;
        diff[(death - 1950) as usize] -= 1;
    });
    
    // 使用scan计算前缀和，同时找最大值
    diff.iter()
        .enumerate()
        .scan(0, |curr, (i, &change)| {
            *curr += change;
            Some((1950 + i as i32, *curr))
        })
        .max_by_key(|(_, pop)| *pop)
        .map(|(year, _)| year)
        .unwrap_or(1950)
}

/// 并行计算版本（需要rayon crate）
#[cfg(feature = "parallel")]
pub fn maximum_population_parallel(logs: &[LogEntry]) -> i32 {
    use rayon::prelude::*;
    
    // 并行构建差分数组
    let diff = logs.par_iter().fold(
        || [0; 101],
        |mut acc, &[birth, death]| {
            acc[(birth - 1950) as usize] += 1;
            acc[(death - 1950) as usize] -= 1;
            acc
        },
    ).reduce(
        || [0; 101],
        |mut a, b| {
            for i in 0..101 {
                a[i] += b[i];
            }
            a
        },
    );
    
    // 串行计算前缀和（因为有依赖关系）
    let mut max_pop = 0;
    let mut year = 1950;
    let mut curr = 0;
    
    for (i, &change) in diff.iter().enumerate() {
        curr += change;
        if curr > max_pop {
            max_pop = curr;
            year = 1950 + i as i32;
        }
    }
    
    year
}

/// 算法管理器
#[derive(Debug)]
pub struct AlgorithmManager {
    calculators: Vec<Box<dyn PopulationCalculator>>,
}

impl Default for AlgorithmManager {
    fn default() -> Self {
        Self::new()
    }
}

impl AlgorithmManager {
    pub fn new() -> Self {
        let mut manager = Self {
            calculators: Vec::new(),
        };
        
        // 注册所有算法
        manager.register(Box::new(BruteForceCalculator));
        manager.register(Box::new(DifferenceArrayCalculator));
        manager.register(Box::new(EventSortingCalculator));
        manager.register(Box::new(HashMapCalculator));
        manager.register(Box::new(BTreeMapCalculator));
        
        manager
    }
    
    pub fn register(&mut self, calculator: Box<dyn PopulationCalculator>) {
        self.calculators.push(calculator);
    }
    
    pub fn calculate_with_timing(&self, index: usize, logs: &[LogEntry]) -> Option<AlgorithmResult> {
        self.calculators.get(index).map(|calculator| {
            let start = Instant::now();
            let year = calculator.calculate(logs);
            let execution_time = start.elapsed();
            
            AlgorithmResult {
                year,
                max_population: self.get_population_at_year(logs, year),
                execution_time: Some(execution_time),
            }
        })
    }
    
    pub fn compare_algorithms(&self, logs: &[LogEntry]) -> Vec<(String, AlgorithmResult)> {
        self.calculators
            .iter()
            .enumerate()
            .filter_map(|(i, calculator)| {
                self.calculate_with_timing(i, logs)
                    .map(|result| (calculator.name().to_string(), result))
            })
            .collect()
    }
    
    fn get_population_at_year(&self, logs: &[LogEntry], year: i32) -> i32 {
        logs.iter()
            .filter(|&&[birth, death]| year >= birth && year < death)
            .count() as i32
    }
    
    pub fn get_algorithm_info(&self, index: usize) -> Option<(&str, (&str, &str))> {
        self.calculators.get(index).map(|calc| {
            (calc.name(), calc.get_complexity())
        })
    }
}

/// 人口数据生成器
pub struct PopulationGenerator {
    diff: [i32; 101],
    current_index: usize,
    current_population: i32,
}

impl PopulationGenerator {
    pub fn new(logs: &[LogEntry]) -> Self {
        let mut diff = [0; 101];
        
        // 构建差分数组
        for &[birth, death] in logs {
            diff[(birth - 1950) as usize] += 1;
            diff[(death - 1950) as usize] -= 1;
        }
        
        Self {
            diff,
            current_index: 0,
            current_population: 0,
        }
    }
}

impl Iterator for PopulationGenerator {
    type Item = PopulationData;
    
    fn next(&mut self) -> Option<Self::Item> {
        if self.current_index < 101 {
            self.current_population += self.diff[self.current_index];
            let data = PopulationData {
                year: 1950 + self.current_index as i32,
                population: self.current_population,
            };
            self.current_index += 1;
            Some(data)
        } else {
            None
        }
    }
}

/// 使用生成器的解法
pub fn maximum_population_generator(logs: &[LogEntry]) -> i32 {
    PopulationGenerator::new(logs)
        .max_by_key(|data| data.population)
        .map(|data| data.year)
        .unwrap_or(1950)
}

/// 错误类型
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum PopulationError {
    InvalidYear(i32),
    EmptyLogs,
    InvalidLogEntry,
}

impl fmt::Display for PopulationError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            PopulationError::InvalidYear(year) => write!(f, "无效年份: {}", year),
            PopulationError::EmptyLogs => write!(f, "日志为空"),
            PopulationError::InvalidLogEntry => write!(f, "无效的日志条目"),
        }
    }
}

impl std::error::Error for PopulationError {}

/// 带错误处理的解法
pub fn maximum_population_safe(logs: &[LogEntry]) -> Result<i32, PopulationError> {
    if logs.is_empty() {
        return Err(PopulationError::EmptyLogs);
    }
    
    // 验证输入
    for &[birth, death] in logs {
        if birth < 1950 || birth > 2050 || death < 1950 || death > 2050 {
            return Err(PopulationError::InvalidYear(birth.max(death)));
        }
        if birth >= death {
            return Err(PopulationError::InvalidLogEntry);
        }
    }
    
    Ok(maximum_population_adapter(logs))
}

/// 测试函数
pub fn test_maximum_population() {
    println!("=== Rust版本测试 ===");
    
    let test_cases = vec![
        ("测试用例1", vec![[1950, 1961], [1960, 1971], [1970, 1981]], 1960),
        ("测试用例2", vec![[1993, 1999], [2000, 2010]], 1993),
        ("测试用例3", vec![[1950, 1951], [1951, 1952], [1952, 1953]], 1950),
        ("测试用例4", vec![[1950, 1960], [1955, 1965], [1958, 1968]], 1958),
    ];
    
    let manager = AlgorithmManager::new();
    
    for (name, logs, expected) in &test_cases {
        println!("\n{}:", name);
        let results = manager.compare_algorithms(logs);
        
        for (algorithm_name, result) in results {
            let is_correct = result.year == *expected;
            let time_str = result.execution_time
                .map(|t| format!("{:.2}μs", t.as_nanos() as f64 / 1000.0))
                .unwrap_or_else(|| "N/A".to_string());
            
            println!("  {}: {} {} ({})", 
                algorithm_name, 
                result.year, 
                if is_correct { "✓" } else { "✗" },
                time_str
            );
        }
    }
    
    // 测试其他版本
    let test_logs = &test_cases[0].1;
    println!("\n其他版本测试:");
    println!("函数式版本: {}", maximum_population_functional(test_logs));
    println!("迭代器版本: {}", maximum_population_iterator(test_logs));
    println!("泛型版本: {}", maximum_population_with_generic(test_logs));
    println!("生成器版本: {}", maximum_population_generator(test_logs));
    
    // 测试错误处理
    println!("\n错误处理测试:");
    match maximum_population_safe(&[]) {
        Err(e) => println!("空日志错误: {}", e),
        Ok(_) => println!("应该返回错误"),
    }
    
    match maximum_population_safe(&[[1949, 1950]]) {
        Err(e) => println!("无效年份错误: {}", e),
        Ok(_) => println!("应该返回错误"),
    }
    
    #[cfg(feature = "parallel")]
    {
        println!("并行版本: {}", maximum_population_parallel(test_logs));
    }
}

/// 性能测试
pub fn performance_test() {
    println!("\n=== 性能测试 ===");
    
    // 生成大量测试数据
    use rand::Rng;
    let mut rng = rand::thread_rng();
    let large_logs: Vec<LogEntry> = (0..100_000)
        .map(|_| {
            let birth = rng.gen_range(1950..2030);
            let death = rng.gen_range(birth + 1..=2050.min(birth + 20));
            [birth, death]
        })
        .collect();
    
    let manager = AlgorithmManager::new();
    let mut results = manager.compare_algorithms(&large_logs);
    
    // 按执行时间排序
    results.sort_by(|a, b| {
        a.1.execution_time.unwrap_or_default()
            .cmp(&b.1.execution_time.unwrap_or_default())
    });
    
    println!("性能排名（从快到慢）:");
    for (name, result) in results {
        let time_str = result.execution_time
            .map(|t| format!("{:.2}ms", t.as_nanos() as f64 / 1_000_000.0))
            .unwrap_or_else(|| "N/A".to_string());
        println!("  {}: {} (结果: {})", name, time_str, result.year);
    }
}

/// 内存使用分析
pub fn memory_analysis() {
    println!("\n=== 内存分析 ===");
    
    // 分析不同算法的内存使用
    let algorithms = vec![
        ("差分数组", "101 * 4 bytes = 404 bytes"),
        ("暴力解法", "几个变量 ≈ 16 bytes"),
        ("事件排序", "2n * 12 bytes ≈ 24n bytes"),
        ("HashMap", "约 n * 16 bytes (取决于负载因子)"),
        ("BTreeMap", "约 n * 24 bytes (树节点开销)"),
    ];
    
    for (name, memory) in algorithms {
        println!("  {}: {}", name, memory);
    }
}

/// 主函数
pub fn main() {
    println!("=== LeetCode 1854: 人口最多的年份 (Rust版本) ===");
    test_maximum_population();
    performance_test();
    memory_analysis();
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_basic_cases() {
        let logs1 = vec![[1950, 1961], [1960, 1971], [1970, 1981]];
        assert_eq!(maximum_population_adapter(&logs1), 1960);
        
        let logs2 = vec![[1993, 1999], [2000, 2010]];
        assert_eq!(maximum_population_adapter(&logs2), 1993);
    }
    
    #[test]
    fn test_all_algorithms_consistency() {
        let logs = vec![[1950, 1961], [1960, 1971], [1970, 1981]];
        let expected = 1960;
        
        let manager = AlgorithmManager::new();
        let results = manager.compare_algorithms(&logs);
        
        for (name, result) in results {
            assert_eq!(result.year, expected, "算法 {} 结果不正确", name);
        }
    }
    
    #[test]
    fn test_functional_versions() {
        let logs = vec![[1950, 1961], [1960, 1971], [1970, 1981]];
        let expected = 1960;
        
        assert_eq!(maximum_population_functional(&logs), expected);
        assert_eq!(maximum_population_iterator(&logs), expected);
        assert_eq!(maximum_population_with_generic(&logs), expected);
        assert_eq!(maximum_population_generator(&logs), expected);
    }
    
    #[test]
    fn test_error_handling() {
        assert!(maximum_population_safe(&[]).is_err());
        assert!(maximum_population_safe(&[[1949, 1950]]).is_err());
        assert!(maximum_population_safe(&[[1950, 1950]]).is_err());
        assert!(maximum_population_safe(&[[1950, 1951]]).is_ok());
    }
    
    #[test]
    fn test_difference_array_utility() {
        let mut diff_array = DifferenceArray::<i32>::new(0, 10);
        diff_array.update(2, 5, 1);
        diff_array.update(4, 7, 2);
        
        let prefix_sum = diff_array.get_prefix_sum();
        assert_eq!(prefix_sum[2], 1);  // 位置2开始+1
        assert_eq!(prefix_sum[4], 3);  // 位置4累加+2，总共3
        assert_eq!(prefix_sum[6], 1);  // 位置6只有第一个区间的+1
    }
    
    #[test]
    fn test_population_generator() {
        let logs = vec![[1950, 1952], [1951, 1953]];
        let mut gen = PopulationGenerator::new(&logs);
        
        let data1 = gen.next().unwrap();
        assert_eq!(data1.year, 1950);
        assert_eq!(data1.population, 1);
        
        let data2 = gen.next().unwrap();
        assert_eq!(data2.year, 1951);
        assert_eq!(data2.population, 2);
    }
}

/*
Rust特性应用总结：

1. 所有权系统
   - 移动语义：Vec<Vec<i32>>的传递
   - 借用：&[LogEntry]避免不必要的复制
   - 生命周期：确保引用有效性
   - 智能指针：Box<dyn Trait>实现多态

2. 类型系统
   - 强类型：编译时类型检查
   - 泛型：DifferenceArray<T>通用实现
   - 特征：PopulationCalculator定义接口
   - 关联类型：Iterator::Item
   - 枚举：PopulationError错误处理

3. 函数式编程
   - 闭包：|acc, item| { ... }
   - 高阶函数：fold, map, filter
   - 迭代器：Iterator trait实现
   - 链式调用：iter().map().filter().collect()

4. 内存安全
   - 无空指针：Option<T>处理可能为空的值
   - 无缓冲区溢出：数组边界检查
   - 无内存泄漏：RAII自动管理资源
   - 无数据竞争：Send + Sync保证线程安全

5. 错误处理
   - Result<T, E>：可恢复错误
   - Option<T>：可能为空的值
   - panic!：不可恢复错误
   - 自定义错误类型：PopulationError

6. 并发编程
   - rayon：数据并行处理
   - 无锁数据结构：原子操作
   - 消息传递：channel通信
   - 共享状态：Arc + Mutex

7. 宏系统
   - 声明宏：macro_rules!
   - 过程宏：derive宏
   - 属性宏：#[cfg(feature = "parallel")]

8. 模块系统
   - pub：公开接口
   - mod：模块组织
   - use：导入声明
   - crate：包管理

9. 性能优化
   - 零成本抽象：编译时优化
   - 内联：#[inline]提示
   - SIMD：向量化计算
   - 内存布局：#[repr(C)]控制

算法复杂度对比：
1. 差分数组：O(n + 101) 时间，O(101) 空间 - 最优
2. 暴力解法：O(101 * n) 时间，O(1) 空间
3. 事件排序：O(n log n) 时间，O(n) 空间
4. HashMap：O(n log n) 时间，O(n) 空间
5. BTreeMap：O(n log n) 时间，O(n) 空间

内存安全保证：
- 编译时借用检查：防止悬垂指针
- 所有权转移：防止双重释放
- 生命周期标注：确保引用有效
- 类型系统：防止类型混淆

并发安全：
- Send：可在线程间转移所有权
- Sync：可在线程间共享引用
- 无数据竞争：编译时检查
- 原子操作：硬件级同步
*/