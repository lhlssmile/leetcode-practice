# Rust 迭代方法详解

## 目录
1. [数组遍历](#数组遍历)
2. [向量(Vec)遍历](#向量vec遍历)
3. [字符串遍历](#字符串遍历)
4. [HashMap遍历](#hashmap遍历)
5. [Range遍历](#range遍历)
6. [迭代器方法](#迭代器方法)
7. [与其他语言对比](#与其他语言对比)

## 数组遍历

### 基本for循环遍历

```rust
fn main() {
    let arr = [1, 2, 3, 4, 5];
    
    // 方法1：使用for循环直接遍历元素
    for element in arr {
        println!("元素值: {}", element);
    }
    
    // 方法2：使用索引遍历
    for i in 0..arr.len() {
        println!("索引: {}, 元素值: {}", i, arr[i]);
    }
    
    // 方法3：使用iter()方法
    for element in arr.iter() {
        println!("元素值: {}", element);
    }
    
    // 方法4：使用iter().enumerate()获取索引和值
    for (index, element) in arr.iter().enumerate() {
        println!("索引: {}, 元素值: {}", index, element);
    }
}
```

## 向量(Vec)遍历

```rust
fn main() {
    let vec = vec![10, 20, 30, 40, 50];
    
    // 方法1：使用for循环直接遍历元素
    for element in &vec {
        println!("元素值: {}", element);
    }
    
    // 方法2：使用索引遍历
    for i in 0..vec.len() {
        println!("索引: {}, 元素值: {}", i, vec[i]);
    }
    
    // 方法3：使用iter()方法
    for element in vec.iter() {
        println!("元素值: {}", element);
    }
    
    // 方法4：使用iter_mut()方法进行可变遍历
    let mut vec_mut = vec![10, 20, 30, 40, 50];
    for element in vec_mut.iter_mut() {
        *element += 5; // 修改元素值
    }
    println!("修改后的向量: {:?}", vec_mut);
    
    // 方法5：使用into_iter()消费向量
    for element in vec.into_iter() {
        println!("消费的元素: {}", element);
    }
    // 注意：此时vec已被消费，不能再使用
}
```

## 字符串遍历

```rust
fn main() {
    let s = String::from("你好，Rust！");
    
    // 方法1：按字节遍历
    for b in s.bytes() {
        println!("字节: {}", b);
    }
    
    // 方法2：按字符遍历
    for c in s.chars() {
        println!("字符: {}", c);
    }
    
    // 方法3：使用字符串切片遍历
    let s_slice = "Hello, Rust!";
    for c in s_slice.chars() {
        println!("字符: {}", c);
    }
    
    // 方法4：获取字符和索引
    for (i, c) in s.char_indices() {
        println!("索引: {}, 字符: {}", i, c);
    }
}
```

## HashMap遍历

```rust
use std::collections::HashMap;

fn main() {
    let mut map = HashMap::new();
    map.insert("apple", 5);
    map.insert("banana", 8);
    map.insert("orange", 10);
    
    // 方法1：遍历键值对
    for (key, value) in &map {
        println!("水果: {}, 数量: {}", key, value);
    }
    
    // 方法2：只遍历键
    for key in map.keys() {
        println!("水果: {}", key);
    }
    
    // 方法3：只遍历值
    for value in map.values() {
        println!("数量: {}", value);
    }
    
    // 方法4：遍历可变引用
    for (_, value) in map.iter_mut() {
        *value += 1; // 增加每种水果的数量
    }
    println!("更新后的map: {:?}", map);
}
```

## Range遍历

```rust
fn main() {
    // 方法1：基本范围遍历
    for i in 1..5 {  // 不包含上界
        println!("{}", i);  // 输出 1 2 3 4
    }
    
    // 方法2：包含上界的范围遍历
    for i in 1..=5 {  // 包含上界
        println!("{}", i);  // 输出 1 2 3 4 5
    }
    
    // 方法3：步进遍历
    for i in (0..10).step_by(2) {
        println!("{}", i);  // 输出 0 2 4 6 8
    }
    
    // 方法4：反向遍历
    for i in (1..=5).rev() {
        println!("{}", i);  // 输出 5 4 3 2 1
    }
}
```

## 迭代器方法

Rust的迭代器提供了丰富的方法，可以进行各种操作：

```rust
fn main() {
    let v = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    
    // map: 转换元素
    let doubled: Vec<i32> = v.iter().map(|x| x * 2).collect();
    println!("加倍后: {:?}", doubled);
    
    // filter: 过滤元素
    let even: Vec<&i32> = v.iter().filter(|x| *x % 2 == 0).collect();
    println!("偶数: {:?}", even);
    
    // fold: 累积计算
    let sum = v.iter().fold(0, |acc, x| acc + x);
    println!("总和: {}", sum);
    
    // any: 检查是否有任何元素满足条件
    let has_even = v.iter().any(|x| x % 2 == 0);
    println!("有偶数? {}", has_even);
    
    // all: 检查是否所有元素都满足条件
    let all_positive = v.iter().all(|x| *x > 0);
    println!("全是正数? {}", all_positive);
    
    // find: 查找第一个满足条件的元素
    let first_even = v.iter().find(|x| *x % 2 == 0);
    println!("第一个偶数: {:?}", first_even);
    
    // take: 获取前n个元素
    let first_three: Vec<&i32> = v.iter().take(3).collect();
    println!("前三个: {:?}", first_three);
    
    // skip: 跳过前n个元素
    let skip_three: Vec<&i32> = v.iter().skip(3).collect();
    println!("跳过前三个: {:?}", skip_three);
    
    // chain: 连接两个迭代器
    let v2 = vec![11, 12];
    let combined: Vec<&i32> = v.iter().chain(v2.iter()).collect();
    println!("合并后: {:?}", combined);
}
```

## 与其他语言对比

### Rust vs Python

| 特性 | Rust | Python |
|------|------|--------|
| 数组遍历 | `for element in arr {}` | `for element in arr:` |
| 带索引遍历 | `for (i, element) in arr.iter().enumerate() {}` | `for i, element in enumerate(arr):` |
| 范围遍历 | `for i in 0..5 {}` | `for i in range(5):` |
| 字典遍历 | `for (key, value) in &map {}` | `for key, value in dict.items():` |
| 迭代器方法 | `arr.iter().map(|x| x*2).collect()` | `[x*2 for x in arr]` 或 `map(lambda x: x*2, arr)` |
| 所有权特性 | 区分借用(`iter()`)和消费(`into_iter()`) | 无所有权概念，直接遍历 |

### Rust vs C++

| 特性 | Rust | C++ |
|------|------|-----|
| 数组遍历 | `for element in arr {}` | `for(auto& element : arr) {}` |
| 带索引遍历 | `for (i, element) in arr.iter().enumerate() {}` | `for(int i = 0; i < arr.size(); i++) {}` |
| 范围遍历 | `for i in 0..5 {}` | `for(int i = 0; i < 5; i++) {}` |
| 映射遍历 | `for (key, value) in &map {}` | `for(auto& [key, value] : map) {}` (C++17) |
| 迭代器方法 | `arr.iter().map(|x| x*2).collect()` | `std::transform(arr.begin(), arr.end(), result.begin(), [](int x){ return x*2; });` |
| 安全性 | 编译时检查边界、所有权 | 需手动检查边界，容易出现内存错误 |

### Rust vs Go

| 特性 | Rust | Go |
|------|------|----|
| 数组遍历 | `for element in arr {}` | `for _, element := range arr {}` |
| 带索引遍历 | `for (i, element) in arr.iter().enumerate() {}` | `for i, element := range arr {}` |
| 范围遍历 | `for i in 0..5 {}` | `for i := 0; i < 5; i++ {}` |
| 映射遍历 | `for (key, value) in &map {}` | `for key, value := range map {}` |
| 迭代器方法 | 丰富的函数式方法 | 较少的内置迭代器方法，通常需要自己实现 |
| 并发模型 | 基于所有权的线程安全 | 基于goroutine和channel的并发 |

### 总结

Rust的迭代方式结合了其他语言的优点，同时增加了所有权系统带来的安全性：

1. **表达力**：类似Python的简洁语法
2. **性能**：接近C++的高效执行
3. **安全性**：编译时检查避免常见错误
4. **灵活性**：丰富的迭代器方法支持函数式编程风格

最重要的是，Rust的迭代器是零成本抽象，意味着使用高级迭代器方法通常与手写循环一样高效，同时代码更加简洁易读。