// Rust版本 - 拼车问题 (LeetCode 1094)
// 展示Rust高级特性和函数式编程

use std::collections::{BTreeMap, HashMap};
use std::cmp::Ordering;

// 定义事件结构体
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
struct Event {
    location: i32,
    change: i32,
}

// 为Event实现排序
impl Ord for Event {
    fn cmp(&self, other: &Self) -> Ordering {
        match self.location.cmp(&other.location) {
            Ordering::Equal => self.change.cmp(&other.change), // 下车优先（负数在前）
            other => other,
        }
    }
}

impl PartialOrd for Event {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

// 定义Trait用于扩展功能
trait CarPoolingExt {
    fn car_pooling(&self, capacity: i32) -> bool;
    fn car_pooling_diff_array(&self, capacity: i32) -> bool;
}

// 为Vec<Vec<i32>>实现CarPoolingExt trait
impl CarPoolingExt for Vec<Vec<i32>> {
    fn car_pooling(&self, capacity: i32) -> bool {
        car_pooling_events(self, capacity)
    }
    
    fn car_pooling_diff_array(&self, capacity: i32) -> bool {
        car_pooling_diff_array(self, capacity)
    }
}

// 标准实现 - 事件排序法
fn car_pooling_events(trips: &[Vec<i32>], capacity: i32) -> bool {
    let mut events: Vec<Event> = trips
        .iter()
        .flat_map(|trip| {
            let passengers = trip[0];
            let from = trip[1];
            let to = trip[2];
            [
                Event { location: from, change: passengers },   // 上车事件
                Event { location: to, change: -passengers },    // 下车事件
            ]
        })
        .collect();
    
    events.sort();
    
    let mut current_passengers = 0;
    
    for event in events {
        current_passengers += event.change;
        if current_passengers > capacity {
            return false;
        }
    }
    
    true
}

// 差分数组法
fn car_pooling_diff_array(trips: &[Vec<i32>], capacity: i32) -> bool {
    let mut diff = BTreeMap::new();
    
    // 构建差分数组
    for trip in trips {
        let passengers = trip[0];
        let from = trip[1];
        let to = trip[2];
        
        *diff.entry(from).or_insert(0) += passengers;
        *diff.entry(to).or_insert(0) -= passengers;
    }
    
    let mut current_passengers = 0;
    
    // 按位置顺序处理
    for &change in diff.values() {
        current_passengers += change;
        if current_passengers > capacity {
            return false;
        }
    }
    
    true
}

// 高级函数式编程版本1 - 使用fold和scan
fn car_pooling_functional_v1(trips: &[Vec<i32>], capacity: i32) -> bool {
    let events = trips
        .iter()
        .flat_map(|trip| {
            let [passengers, from, to] = [trip[0], trip[1], trip[2]];
            [(from, passengers), (to, -passengers)]
        })
        .collect::<Vec<_>>();
    
    let mut sorted_events = events;
    sorted_events.sort_by(|a, b| match a.0.cmp(&b.0) {
        Ordering::Equal => a.1.cmp(&b.1),
        other => other,
    });
    
    sorted_events
        .into_iter()
        .scan(0, |current_passengers, (_, change)| {
            *current_passengers += change;
            Some(*current_passengers)
        })
        .all(|passengers| passengers <= capacity)
}

// 高级函数式编程版本2 - 使用Iterator适配器和闭包
fn car_pooling_functional_v2(trips: &[Vec<i32>], capacity: i32) -> bool {
    use std::iter::once;
    
    let passenger_changes = trips
        .iter()
        .flat_map(|trip| {
            let passengers = trip[0];
            let from = trip[1];
            let to = trip[2];
            
            once((from, passengers)).chain(once((to, -passengers)))
        })
        .fold(BTreeMap::new(), |mut acc, (location, change)| {
            *acc.entry(location).or_insert(0) += change;
            acc
        });
    
    passenger_changes
        .values()
        .scan(0, |current, &change| {
            *current += change;
            Some(*current)
        })
        .all(|passengers| passengers <= capacity)
}

// 高级函数式编程版本3 - 使用自定义Iterator和泛型
struct TripEventIterator<I> {
    trips: I,
    current_trip: Option<Vec<i32>>,
    event_index: usize,
}

impl<I> TripEventIterator<I>
where
    I: Iterator<Item = Vec<i32>>,
{
    fn new(trips: I) -> Self {
        Self {
            trips,
            current_trip: None,
            event_index: 0,
        }
    }
}

impl<I> Iterator for TripEventIterator<I>
where
    I: Iterator<Item = Vec<i32>>,
{
    type Item = (i32, i32); // (location, change)
    
    fn next(&mut self) -> Option<Self::Item> {
        loop {
            if let Some(ref trip) = self.current_trip {
                let passengers = trip[0];
                let from = trip[1];
                let to = trip[2];
                
                match self.event_index {
                    0 => {
                        self.event_index = 1;
                        return Some((from, passengers));
                    }
                    1 => {
                        self.event_index = 0;
                        self.current_trip = None;
                        return Some((to, -passengers));
                    }
                    _ => unreachable!(),
                }
            } else {
                self.current_trip = self.trips.next();
                if self.current_trip.is_none() {
                    return None;
                }
            }
        }
    }
}

fn car_pooling_custom_iterator(trips: &[Vec<i32>], capacity: i32) -> bool {
    let events = TripEventIterator::new(trips.iter().cloned())
        .collect::<Vec<_>>();
    
    let mut sorted_events = events;
    sorted_events.sort_by(|a, b| match a.0.cmp(&b.0) {
        Ordering::Equal => a.1.cmp(&b.1),
        other => other,
    });
    
    sorted_events
        .into_iter()
        .scan(0, |current, (_, change)| {
            *current += change;
            Some(*current)
        })
        .all(|passengers| passengers <= capacity)
}

// 使用Result类型进行错误处理的版本
#[derive(Debug)]
enum CarPoolingError {
    InvalidTrip(String),
    CapacityExceeded(i32),
}

fn car_pooling_with_error_handling(
    trips: &[Vec<i32>], 
    capacity: i32
) -> Result<bool, CarPoolingError> {
    // 验证输入
    for (i, trip) in trips.iter().enumerate() {
        if trip.len() != 3 {
            return Err(CarPoolingError::InvalidTrip(
                format!("Trip {} has invalid format", i)
            ));
        }
        if trip[0] < 0 || trip[1] < 0 || trip[2] < 0 || trip[1] >= trip[2] {
            return Err(CarPoolingError::InvalidTrip(
                format!("Trip {} has invalid values: {:?}", i, trip)
            ));
        }
    }
    
    let events = trips
        .iter()
        .flat_map(|trip| {
            let passengers = trip[0];
            let from = trip[1];
            let to = trip[2];
            [(from, passengers), (to, -passengers)]
        })
        .collect::<Vec<_>>();
    
    let mut sorted_events = events;
    sorted_events.sort_by(|a, b| match a.0.cmp(&b.0) {
        Ordering::Equal => a.1.cmp(&b.1),
        other => other,
    });
    
    let mut current_passengers = 0;
    
    for (location, change) in sorted_events {
        current_passengers += change;
        if current_passengers > capacity {
            return Err(CarPoolingError::CapacityExceeded(current_passengers));
        }
    }
    
    Ok(true)
}

// 使用泛型和Trait约束的版本
trait Passenger {
    fn count(&self) -> i32;
}

trait Location {
    fn position(&self) -> i32;
}

#[derive(Debug, Clone)]
struct Trip<P, L> {
    passengers: P,
    from: L,
    to: L,
}

impl<P: Passenger, L: Location> Trip<P, L> {
    fn to_events(&self) -> [(i32, i32); 2] {
        let passengers = self.passengers.count();
        let from = self.from.position();
        let to = self.to.position();
        [(from, passengers), (to, -passengers)]
    }
}

impl Passenger for i32 {
    fn count(&self) -> i32 {
        *self
    }
}

impl Location for i32 {
    fn position(&self) -> i32 {
        *self
    }
}

fn car_pooling_generic<P, L>(trips: &[Trip<P, L>], capacity: i32) -> bool
where
    P: Passenger + Clone,
    L: Location + Clone,
{
    let events = trips
        .iter()
        .flat_map(|trip| trip.to_events())
        .collect::<Vec<_>>();
    
    let mut sorted_events = events;
    sorted_events.sort_by(|a, b| match a.0.cmp(&b.0) {
        Ordering::Equal => a.1.cmp(&b.1),
        other => other,
    });
    
    sorted_events
        .into_iter()
        .scan(0, |current, (_, change)| {
            *current += change;
            Some(*current)
        })
        .all(|passengers| passengers <= capacity)
}

fn main() {
    // 测试用例
    let test_cases = vec![
        (vec![vec![2,1,5], vec![3,3,7]], 4, false),      // 测试用例1
        (vec![vec![2,1,5], vec![3,3,7]], 5, true),       // 测试用例2
        (vec![vec![2,1,5], vec![3,5,7]], 3, true),       // 测试用例3
        (vec![vec![3,2,7], vec![3,7,9], vec![8,3,9]], 11, true), // 测试用例4
    ];
    
    println!("=== 拼车问题测试 ===");
    
    for (i, (trips, capacity, expected)) in test_cases.iter().enumerate() {
        println!("测试用例 {}: trips = {:?}, capacity = {}", i + 1, trips, capacity);
        
        // 标准实现
        let result1 = car_pooling_events(trips, *capacity);
        println!("事件排序法: {}", result1);
        
        // 差分数组法
        let result2 = car_pooling_diff_array(trips, *capacity);
        println!("差分数组法: {}", result2);
        
        // 函数式编程版本1
        let result3 = car_pooling_functional_v1(trips, *capacity);
        println!("函数式v1: {}", result3);
        
        // 函数式编程版本2
        let result4 = car_pooling_functional_v2(trips, *capacity);
        println!("函数式v2: {}", result4);
        
        // 自定义Iterator版本
        let result5 = car_pooling_custom_iterator(trips, *capacity);
        println!("自定义Iterator: {}", result5);
        
        // Trait扩展版本
        let result6 = trips.car_pooling(*capacity);
        println!("Trait扩展: {}", result6);
        
        // 错误处理版本
        match car_pooling_with_error_handling(trips, *capacity) {
            Ok(result) => println!("错误处理版本: {}", result),
            Err(e) => println!("错误处理版本: Error - {:?}", e),
        }
        
        // 泛型版本
        let generic_trips: Vec<Trip<i32, i32>> = trips
            .iter()
            .map(|trip| Trip {
                passengers: trip[0],
                from: trip[1],
                to: trip[2],
            })
            .collect();
        let result7 = car_pooling_generic(&generic_trips, *capacity);
        println!("泛型版本: {}", result7);
        
        println!("预期结果: {}", expected);
        let all_correct = [result1, result2, result3, result4, result5, result6, result7]
            .iter()
            .all(|&r| r == *expected);
        println!("结果: {}", if all_correct { "✓" } else { "✗" });
        println!();
    }
}

/*
Rust高级特性详解：

1. **结构体和Trait系统**:
   - Event结构体实现了Debug, Clone, Copy, PartialEq, Eq, Ord, PartialOrd
   - 自定义Trait CarPoolingExt为Vec<Vec<i32>>扩展功能
   - Passenger和Location trait定义了抽象行为

2. **所有权和借用**:
   - 使用&[Vec<i32>]避免不必要的所有权转移
   - 智能使用引用和解引用
   - 零拷贝的数据处理

3. **Iterator适配器链式操作**:
   - flat_map: 将嵌套结构展平
   - scan: 有状态的map操作，类似fold但产生中间结果
   - fold: 累积操作，将Iterator折叠为单个值
   - all: 检查所有元素是否满足条件
   - collect: 将Iterator收集为集合
   - chain: 连接多个Iterator

4. **函数式编程特性**:
   - 闭包捕获: |current, &change| 捕获外部变量
   - 高阶函数: 函数作为参数传递
   - 惰性求值: Iterator只在需要时计算
   - 不可变数据结构的偏好

5. **模式匹配和解构**:
   - let [passengers, from, to] = [trip[0], trip[1], trip[2]]
   - match表达式进行复杂条件判断
   - if let和while let进行Option/Result处理

6. **泛型和Trait约束**:
   - <P: Passenger + Clone, L: Location + Clone>
   - 类型参数约束确保类型安全
   - 零成本抽象，编译时单态化

7. **错误处理**:
   - Result<T, E>类型进行可恢复错误处理
   - 自定义错误类型CarPoolingError
   - ?操作符进行错误传播

8. **自定义Iterator**:
   - 实现Iterator trait创建自定义迭代器
   - 状态管理和惰性计算
   - 组合性和可重用性

9. **内存安全**:
   - 编译时借用检查防止数据竞争
   - 无垃圾回收的零成本抽象
   - 栈分配优先，避免不必要的堆分配

10. **类型系统高级特性**:
    - 关联类型: type Item = (i32, i32)
    - Trait对象和动态分发
    - 生命周期参数管理引用有效性

这些特性使得Rust代码既安全又高效，同时保持了很高的表达能力。
函数式编程风格让代码更加简洁和可读，而类型系统确保了编译时的正确性。
*/