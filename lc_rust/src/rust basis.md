# RUST 基础教程（LeetCode刷题向）

## 1. Rust 基本语法

### 1.1 变量与基本类型

```rust
// 变量声明（默认不可变）
let x = 5;

// 可变变量
let mut y = 5;
y = 6; // 可以修改

// 基本数据类型
let i: i32 = 42;        // 32位有符号整数
let u: u64 = 42;        // 64位无符号整数
let f: f64 = 3.14;      // 64位浮点数
let b: bool = true;     // 布尔值
let c: char = 'z';      // 字符
let s: &str = "hello"; // 字符串切片

// 复合类型
let tup: (i32, f64, bool) = (500, 6.4, true); // 元组
let arr: [i32; 5] = [1, 2, 3, 4, 5];          // 数组
```

### 1.2 控制流

```rust
// if 表达式
let number = 6;
if number % 4 == 0 {
    println!("number is divisible by 4");
} else if number % 3 == 0 {
    println!("number is divisible by 3");
} else {
    println!("number is not divisible by 4 or 3");
}

// 在 let 语句中使用 if
let condition = true;
let number = if condition { 5 } else { 6 };

// 循环
// loop - 无限循环
let mut counter = 0;
let result = loop {
    counter += 1;
    if counter == 10 {
        break counter * 2; // 可以从循环返回值
    }
};

// while 循环
let mut number = 3;
while number != 0 {
    number -= 1;
}

// for 循环（遍历集合）
let a = [10, 20, 30, 40, 50];
for element in a.iter() {
    println!("{}", element);
}

// for 循环（范围）
for number in 1..4 { // 不包含上界
    println!("{}", number);
}
```

### 1.3 函数与方法

```rust
// 函数定义
fn add(x: i32, y: i32) -> i32 {
    x + y // 注意没有分号，这是一个表达式，会作为返回值
}

// 方法（与结构体或枚举关联的函数）
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // 关联函数（类似静态方法）
    fn new(width: u32, height: u32) -> Rectangle {
        Rectangle { width, height }
    }
    
    // 方法（第一个参数是 self）
    fn area(&self) -> u32 {
        self.width * self.height
    }
    
    // 可变方法
    fn resize(&mut self, width: u32, height: u32) {
        self.width = width;
        self.height = height;
    }
}
```

## 2. Rust 数据结构（LeetCode常用）

### 2.1 Vec（动态数组）

```rust
// 创建空 Vec
let mut v: Vec<i32> = Vec::new();

// 使用宏创建 Vec
let v = vec![1, 2, 3, 4, 5];

// 添加元素
v.push(6);

// 访问元素
let third: &i32 = &v[2]; // 索引访问（可能导致 panic）
let third: Option<&i32> = v.get(2); // 安全访问（返回 Option）

// 遍历
for i in &v {
    println!("{}", i);
}

// 遍历并修改
for i in &mut v {
    *i += 50;
}

// 常用方法
v.len();       // 长度
v.is_empty();  // 是否为空
v.pop();       // 移除并返回最后一个元素
v.remove(1);   // 移除指定索引的元素
v.clear();     // 清空
```

### 2.2 String 和 &str

```rust
// 创建字符串
let mut s = String::new();
let s = String::from("hello");
let s = "hello".to_string();

// 追加内容
s.push('!');           // 追加字符
s.push_str(" world"); // 追加字符串

// 连接字符串
let s1 = String::from("Hello, ");
let s2 = String::from("world!");
let s3 = s1 + &s2; // 注意：s1 被移动了，不能再使用

// 格式化宏
let s = format!("{}-{}-{}", "hello", "world", 2023);

// 字符串切片
let hello = "hello world";
let s = &hello[0..5]; // s = "hello"

// 遍历字符
for c in "hello".chars() {
    println!("{}", c);
}

// 遍历字节
for b in "hello".bytes() {
    println!("{}", b);
}
```

### 2.3 HashMap（哈希表）

```rust
use std::collections::HashMap;

// 创建
let mut scores = HashMap::new();

// 插入
scores.insert(String::from("Blue"), 10);
scores.insert(String::from("Yellow"), 50);

// 访问
let team_name = String::from("Blue");
let score = scores.get(&team_name); // 返回 Option<&V>

// 遍历
for (key, value) in &scores {
    println!("{}: {}", key, value);
}

// 更新
// 覆盖已有的值
scores.insert(String::from("Blue"), 25);

// 只在键不存在时插入
scores.entry(String::from("Yellow")).or_insert(50);

// 根据旧值更新
let text = "hello world wonderful world";
let mut map = HashMap::new();
for word in text.split_whitespace() {
    let count = map.entry(word).or_insert(0);
    *count += 1;
}
```

### 2.4 HashSet（集合）

```rust
use std::collections::HashSet;

// 创建
let mut set = HashSet::new();

// 插入
set.insert(1);
set.insert(2);
set.insert(3);

// 检查是否包含
if set.contains(&1) {
    println!("包含 1");
}

// 移除
set.remove(&1);

// 集合操作
let set1: HashSet<_> = [1, 2, 3].iter().cloned().collect();
let set2: HashSet<_> = [2, 3, 4].iter().cloned().collect();

// 交集
let intersection: HashSet<_> = set1.intersection(&set2).cloned().collect();

// 并集
let union: HashSet<_> = set1.union(&set2).cloned().collect();

// 差集
let difference: HashSet<_> = set1.difference(&set2).cloned().collect();
```

### 2.5 BinaryHeap（优先队列）

```rust
use std::collections::BinaryHeap;

// 创建（默认是最大堆）
let mut heap = BinaryHeap::new();

// 插入
heap.push(3);
heap.push(5);
heap.push(1);

// 查看最大值
if let Some(&max) = heap.peek() {
    println!("最大值是: {}", max);
}

// 弹出最大值
while let Some(max) = heap.pop() {
    println!("{}", max);
}

// 创建最小堆（使用 Reverse 包装器）
use std::cmp::Reverse;
let mut min_heap = BinaryHeap::new();
min_heap.push(Reverse(3));
min_heap.push(Reverse(5));
min_heap.push(Reverse(1));

// 弹出最小值
while let Some(Reverse(min)) = min_heap.pop() {
    println!("{}", min);
}
```

### 2.6 VecDeque（双端队列）

```rust
use std::collections::VecDeque;

// 创建
let mut deque = VecDeque::new();

// 添加元素
deque.push_back(1);   // 在尾部添加
deque.push_front(2);  // 在头部添加

// 移除元素
let front = deque.pop_front(); // 从头部移除
let back = deque.pop_back();   // 从尾部移除
```

## 3. LeetCode 常用算法模式

### 3.1 二分查找

```rust
fn binary_search(nums: &[i32], target: i32) -> Option<usize> {
    let mut left = 0;
    let mut right = nums.len();
    
    while left < right {
        let mid = left + (right - left) / 2;
        if nums[mid] == target {
            return Some(mid);
        } else if nums[mid] < target {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    None
}
```

### 3.2 双指针技巧

```rust
// 从两端向中间移动的双指针（如两数之和）
fn two_sum(numbers: &[i32], target: i32) -> Option<(usize, usize)> {
    let mut left = 0;
    let mut right = numbers.len() - 1;
    
    while left < right {
        let sum = numbers[left] + numbers[right];
        if sum == target {
            return Some((left, right));
        } else if sum < target {
            left += 1;
        } else {
            right -= 1;
        }
    }
    
    None
}

// 快慢指针（如检测链表环）
fn has_cycle(head: Option<&Box<ListNode>>) -> bool {
    let mut slow = head;
    let mut fast = head;
    
    while fast.is_some() && fast.unwrap().next.is_some() {
        slow = slow.unwrap().next.as_ref();
        fast = fast.unwrap().next.as_ref().unwrap().next.as_ref();
        
        if slow == fast {
            return true;
        }
    }
    
    false
}
```

### 3.3 滑动窗口

```rust
// 最长无重复字符子串
fn length_of_longest_substring(s: String) -> i32 {
    use std::collections::HashMap;
    let mut map = HashMap::new();
    let chars: Vec<char> = s.chars().collect();
    let mut max_len = 0;
    let mut start = 0;
    
    for (end, &c) in chars.iter().enumerate() {
        if let Some(&pos) = map.get(&c) {
            if pos >= start {
                start = pos + 1;
            }
        }
        map.insert(c, end);
        max_len = max_len.max((end - start + 1) as i32);
    }
    
    max_len
}
```

### 3.4 深度优先搜索 (DFS)

```rust
// 二叉树的 DFS 遍历
fn dfs(root: Option<&Box<TreeNode>>, result: &mut Vec<i32>) {
    if let Some(node) = root {
        // 前序遍历
        result.push(node.val);
        dfs(node.left.as_ref(), result);
        dfs(node.right.as_ref(), result);
        
        // 中序遍历
        // dfs(node.left.as_ref(), result);
        // result.push(node.val);
        // dfs(node.right.as_ref(), result);
        
        // 后序遍历
        // dfs(node.left.as_ref(), result);
        // dfs(node.right.as_ref(), result);
        // result.push(node.val);
    }
}
```

### 3.5 广度优先搜索 (BFS)

```rust
// 二叉树的层序遍历
fn level_order(root: Option<&Box<TreeNode>>) -> Vec<Vec<i32>> {
    use std::collections::VecDeque;
    let mut result = Vec::new();
    
    if root.is_none() {
        return result;
    }
    
    let mut queue = VecDeque::new();
    queue.push_back(root.unwrap());
    
    while !queue.is_empty() {
        let level_size = queue.len();
        let mut current_level = Vec::new();
        
        for _ in 0..level_size {
            if let Some(node) = queue.pop_front() {
                current_level.push(node.val);
                
                if let Some(left) = &node.left {
                    queue.push_back(left);
                }
                
                if let Some(right) = &node.right {
                    queue.push_back(right);
                }
            }
        }
        
        result.push(current_level);
    }
    
    result
}
```

### 3.6 动态规划

```rust
// 斐波那契数列
fn fibonacci(n: usize) -> u64 {
    let mut dp = vec![0; n + 1];
    dp[0] = 0;
    dp[1] = 1;
    
    for i in 2..=n {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    dp[n]
}

// 最长递增子序列
fn longest_increasing_subsequence(nums: &[i32]) -> i32 {
    if nums.is_empty() {
        return 0;
    }
    
    let n = nums.len();
    let mut dp = vec![1; n];
    
    for i in 1..n {
        for j in 0..i {
            if nums[i] > nums[j] {
                dp[i] = dp[i].max(dp[j] + 1);
            }
        }
    }
    
    *dp.iter().max().unwrap()
}
```

## 4. Rust LeetCode 实用技巧

### 4.1 常用标准库函数

```rust
// 数学运算
num.min(other);  // 最小值
num.max(other);  // 最大值
num.abs();       // 绝对值
num.pow(n);      // 幂运算

// 迭代器方法
iter.collect();  // 收集到集合
iter.sum();      // 求和
iter.fold(init, |acc, x| acc + x);  // 折叠操作
iter.filter(|&x| x > 0);            // 过滤
iter.map(|x| x * 2);                // 映射
iter.enumerate();                   // 带索引迭代
```

### 4.2 常见 LeetCode 数据结构定义

```rust
// 链表节点
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode {
            next: None,
            val
        }
    }
}

// 二叉树节点
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None
        }
    }
}
```

### 4.3 处理 Option 和 Result

```rust
// 使用 ? 运算符简化错误处理
fn process() -> Option<i32> {
    let a = some_function()?;  // 如果返回 None，则提前返回 None
    let b = another_function()?;
    Some(a + b)
}

// 使用 unwrap_or 提供默认值
let val = option.unwrap_or(0);

// 使用 map 转换 Option 内的值
let doubled = option.map(|x| x * 2);

// 使用 and_then 链式处理 Option
let result = option
    .and_then(|x| some_function(x))
    .and_then(|y| another_function(y));
```

### 4.4 常用宏

```rust
// vec! 宏创建向量
let v = vec![1, 2, 3, 4, 5];

// 创建哈希表
let map = hashmap!{
    "key1" => "value1",
    "key2" => "value2"
};

// 格式化字符串
let s = format!("{} + {} = {}", 1, 2, 3);
```

## 5. 刷题建议

1. **熟悉 Rust 所有权系统**：理解借用、引用和生命周期，避免与编译器斗争。

2. **使用标准库**：Rust 标准库提供了丰富的数据结构和算法，充分利用它们。

3. **迭代器优先**：Rust 的迭代器非常强大，可以简化很多操作，提高代码可读性。

4. **模式匹配**：善用 match 和 if let 进行模式匹配，处理 Option 和 Result。

5. **避免过度优化**：先写出正确的代码，再考虑性能优化。

6. **练习常见算法模式**：熟悉上面提到的算法模式，它们在 LeetCode 中经常出现。

7. **参考他人代码**：学习 Rust 社区中优秀的解决方案，提高自己的 Rust 编程水平。

祝你在 LeetCode 上用 Rust 刷题愉快！🦀