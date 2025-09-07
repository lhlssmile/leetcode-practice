# Rust高级特性学习笔记

## 1. Derive宏 - 自动实现Trait

### 什么是 `#[derive(...)]`？

`#[derive(...)]` 是Rust的**属性宏**（Attribute Macro），它可以自动为你的结构体或枚举实现常用的trait。这样你就不需要手动写这些trait的实现代码了。

```rust
// 不使用derive，需要手动实现
struct Point {
    x: i32,
    y: i32,
}

// 手动实现Debug trait
impl std::fmt::Debug for Point {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.debug_struct("Point")
            .field("x", &self.x)
            .field("y", &self.y)
            .finish()
    }
}

// 使用derive，自动实现
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32,
}
```

### 常用的可derive的trait

#### 1. `Debug` - 调试输出
```rust
#[derive(Debug)]
struct Person {
    name: String,
    age: u32,
}

let person = Person { name: "Alice".to_string(), age: 30 };
println!("{:?}", person); // 输出: Person { name: "Alice", age: 30 }
println!("{:#?}", person); // 美化输出
```

#### 2. `Clone` - 深拷贝
```rust
#[derive(Clone)]
struct Data {
    value: String,
}

let data1 = Data { value: "hello".to_string() };
let data2 = data1.clone(); // 创建一个完全独立的副本
```

#### 3. `Copy` - 浅拷贝（栈上复制）
```rust
#[derive(Copy, Clone)] // Copy需要Clone
struct Point {
    x: i32,
    y: i32,
}

let p1 = Point { x: 1, y: 2 };
let p2 = p1; // 自动复制，p1仍然可用
println!("{:?} {:?}", p1, p2); // 都可以使用
```

**注意**: Copy只能用于所有字段都实现了Copy的类型（如基本数据类型）

#### 4. `PartialEq` - 部分相等比较
```rust
#[derive(PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

let p1 = Point { x: 1, y: 2 };
let p2 = Point { x: 1, y: 2 };
assert_eq!(p1, p2); // 可以使用 == 比较
```

#### 5. `Eq` - 完全相等
```rust
#[derive(PartialEq, Eq)] // Eq需要PartialEq
struct Point {
    x: i32,
    y: i32,
}
// Eq表示这个类型的相等关系是自反的、对称的、传递的
```

#### 6. `PartialOrd` 和 `Ord` - 排序
```rust
#[derive(PartialEq, Eq, PartialOrd, Ord)]
struct Point {
    x: i32,
    y: i32,
}

let mut points = vec![
    Point { x: 3, y: 1 },
    Point { x: 1, y: 2 },
    Point { x: 2, y: 3 },
];
points.sort(); // 可以排序
```

#### 7. `Hash` - 哈希
```rust
use std::collections::HashMap;

#[derive(Hash, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32,
}

let mut map = HashMap::new();
map.insert(Point { x: 1, y: 2 }, "value");
```

## 2. Trait系统详解

### 什么是Trait？

Trait类似于其他语言中的接口（Interface），它定义了一组方法签名，类型可以实现这些trait来获得特定的行为。

```rust
// 定义一个trait
trait Drawable {
    fn draw(&self);
    
    // 可以有默认实现
    fn area(&self) -> f64 {
        0.0
    }
}

// 为类型实现trait
struct Circle {
    radius: f64,
}

impl Drawable for Circle {
    fn draw(&self) {
        println!("Drawing a circle with radius {}", self.radius);
    }
    
    fn area(&self) -> f64 {
        3.14159 * self.radius * self.radius
    }
}
```

### Trait作为参数

```rust
// 接受实现了Drawable trait的任何类型
fn render_shape(shape: &dyn Drawable) {
    shape.draw();
}

// 或者使用泛型
fn render_shape_generic<T: Drawable>(shape: &T) {
    shape.draw();
}

// 多个trait约束
fn process<T: Drawable + Clone>(item: T) {
    // T必须同时实现Drawable和Clone
}
```

### Trait边界（Trait Bounds）

```rust
// where子句，更清晰的语法
fn complex_function<T, U>(t: T, u: U) -> i32
where
    T: Drawable + Clone,
    U: Clone + Debug,
{
    // 函数体
    42
}
```

### 关联类型（Associated Types）

```rust
trait Iterator {
    type Item; // 关联类型
    
    fn next(&mut self) -> Option<Self::Item>;
}

struct Counter {
    current: usize,
    max: usize,
}

impl Iterator for Counter {
    type Item = usize; // 指定关联类型
    
    fn next(&mut self) -> Option<Self::Item> {
        if self.current < self.max {
            let current = self.current;
            self.current += 1;
            Some(current)
        } else {
            None
        }
    }
}
```

### 生命周期（Lifetimes）

```rust
// 生命周期参数
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

// 结构体中的生命周期
struct ImportantExcerpt<'a> {
    part: &'a str,
}

impl<'a> ImportantExcerpt<'a> {
    fn level(&self) -> i32 {
        3
    }
}
```

## 3. 高级Trait特性

### Trait对象（Trait Objects）

```rust
trait Draw {
    fn draw(&self);
}

struct Button;
struct TextField;

impl Draw for Button {
    fn draw(&self) {
        println!("Drawing button");
    }
}

impl Draw for TextField {
    fn draw(&self) {
        println!("Drawing text field");
    }
}

// 使用trait对象存储不同类型
let components: Vec<Box<dyn Draw>> = vec![
    Box::new(Button),
    Box::new(TextField),
];

for component in components {
    component.draw();
}
```

### 操作符重载

```rust
use std::ops::Add;

#[derive(Debug, PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

impl Add for Point {
    type Output = Point;
    
    fn add(self, other: Point) -> Point {
        Point {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

let p1 = Point { x: 1, y: 2 };
let p2 = Point { x: 3, y: 4 };
let p3 = p1 + p2; // 使用+操作符
```

### 孤儿规则（Orphan Rule）

你只能为以下情况实现trait：
1. trait是你定义的
2. 类型是你定义的
3. 至少有一个是你定义的

```rust
// ✅ 可以：为自己的类型实现标准库trait
impl Display for MyStruct { ... }

// ✅ 可以：为标准库类型实现自己的trait
impl MyTrait for Vec<i32> { ... }

// ❌ 不可以：为标准库类型实现标准库trait
// impl Display for Vec<i32> { ... } // 编译错误
```

## 4. 实用示例

### 自定义derive宏的效果

```rust
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct Student {
    id: u32,
    grade: u8,
}

fn main() {
    let student1 = Student { id: 1, grade: 85 };
    let student2 = Student { id: 2, grade: 90 };
    
    // Debug
    println!("{:?}", student1);
    
    // Clone
    let student1_copy = student1.clone();
    
    // Copy (自动发生)
    let student1_copy2 = student1; // student1仍然可用
    
    // PartialEq
    println!("Equal: {}", student1 == student1_copy);
    
    // PartialOrd
    println!("student1 < student2: {}", student1 < student2);
    
    // Hash (可以用作HashMap的key)
    use std::collections::HashMap;
    let mut map = HashMap::new();
    map.insert(student1, "Alice");
    map.insert(student2, "Bob");
}
```

### 条件编译和cfg属性

```rust
#[cfg(target_os = "windows")]
fn get_config() -> String {
    "Windows config".to_string()
}

#[cfg(target_os = "linux")]
fn get_config() -> String {
    "Linux config".to_string()
}

#[cfg(debug_assertions)]
fn debug_print(msg: &str) {
    println!("DEBUG: {}", msg);
}

#[cfg(not(debug_assertions))]
fn debug_print(_msg: &str) {
    // 在release模式下什么都不做
}
```

## 5. 学习建议

1. **从简单开始**: 先熟悉基本的derive宏，如Debug、Clone、PartialEq
2. **理解所有权**: Trait系统与Rust的所有权系统紧密相关
3. **多练习**: 尝试为自己的类型实现不同的trait
4. **阅读标准库**: 看看标准库中的trait是如何定义和实现的
5. **循序渐进**: 从简单trait开始，逐步学习复杂特性如生命周期、关联类型等

记住：Trait是Rust最强大的特性之一，掌握它们将大大提升你的Rust编程能力！🦀