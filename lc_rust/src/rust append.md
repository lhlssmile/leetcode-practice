# Rust 进阶知识补充

## 1. Rust 所有权系统

所有权（Ownership）是 Rust 最独特的特性，它让 Rust 无需垃圾回收就能保证内存安全。

### 1.1 所有权规则

```rust
// 基本规则：
// 1. Rust 中每个值都有一个变量，称为其所有者
// 2. 每个值在任一时刻只能有一个所有者
// 3. 当所有者离开作用域，其值将被丢弃

{
    let s = String::from("hello"); // s 是有效的
    // 使用 s
} // 作用域结束，s 不再有效，内存自动释放

// 移动（Move）
let s1 = String::from("hello");
let s2 = s1; // s1 的所有权移动到 s2，s1 不再有效
// println!("{}", s1); // 编译错误！

// 克隆（Clone）
let s1 = String::from("hello");
let s2 = s1.clone(); // 深拷贝，s1 和 s2 都有效
println!("{}, {}", s1, s2); // 正常工作

// 栈上数据的复制（Copy）
let x = 5;
let y = x; // 整数是 Copy 类型，x 仍然有效
println!("{}, {}", x, y); // 正常工作
```

### 1.2 引用与借用

```rust
// 引用允许使用值但不获取其所有权

// 不可变引用
fn calculate_length(s: &String) -> usize { // s 是对 String 的引用
    s.len()
} // 这里 s 离开作用域，但它不拥有引用值的所有权，所以没有特殊操作

let s1 = String::from("hello");
let len = calculate_length(&s1); // 创建 s1 的引用

// 可变引用
fn change(s: &mut String) {
    s.push_str(", world");
}

let mut s = String::from("hello");
change(&mut s);

// 可变引用的限制：在特定作用域内，对同一数据只能有一个可变引用
let mut s = String::from("hello");
let r1 = &mut s;
// let r2 = &mut s; // 错误：不能同时有两个可变引用

// 不能同时拥有可变和不可变引用
let mut s = String::from("hello");
let r1 = &s; // 不可变引用
let r2 = &s; // 不可变引用
// let r3 = &mut s; // 错误：已经有不可变引用，不能再有可变引用

// 引用的作用域从声明开始，到最后一次使用结束
let mut s = String::from("hello");
let r1 = &s;
let r2 = &s;
println!("{} and {}", r1, r2); // r1 和 r2 的作用域到这里结束
let r3 = &mut s; // 正确：r1 和 r2 的作用域已结束
println!("{}", r3);
```

### 1.3 悬垂引用（Dangling References）

```rust
// Rust 编译器确保引用永远不会变成悬垂引用

// 错误示例
// fn dangle() -> &String { // 返回一个字符串的引用
//     let s = String::from("hello"); // s 是一个新字符串
//     &s // 返回字符串 s 的引用
// } // s 离开作用域并被丢弃，其引用指向的内存无效

// 正确做法：返回 String 而不是引用
fn no_dangle() -> String {
    let s = String::from("hello");
    s // 返回 s 并移出所有权
}
```

### 1.4 切片（Slice）

```rust
// 切片是对集合中部分连续元素的引用

// 字符串切片
let s = String::from("hello world");
let hello = &s[0..5]; // 或 &s[..5]
let world = &s[6..11]; // 或 &s[6..]
let whole = &s[..]; // 整个字符串的切片

// 字符串字面量是切片
let s = "Hello, world!"; // s 的类型是 &str

// 其他类型的切片
let a = [1, 2, 3, 4, 5];
let slice = &a[1..3]; // 类型是 &[i32]
```

## 2. 类型系统与类型转换

### 2.1 类型转换（as 关键字）

```rust
// 基本数值类型转换
let a = 5_i32;
let b = a as i64; // i32 转换为 i64
let c = a as u32; // i32 转换为 u32

// 当转换可能截断时要小心
let a = 300_i32;
let b = a as u8; // 300 超出 u8 范围，结果是 300 - 256 = 44

// 指针和引用转换
let a = 42_u32;
let p = &a as *const u32; // 引用转换为原始指针
let val = unsafe { *p }; // 解引用原始指针需要 unsafe

// 智能指针转换
let s = Box::new("hello");
let s_ref = &*s; // 解引用 Box 并获取引用

// 字符串类型转换
let s = String::from("hello");
let s_slice = &s[..]; // String 转换为 &str
let s_owned = s_slice.to_string(); // &str 转换为 String

// 数字与字符串转换
let num = 42;
let num_str = num.to_string(); // 数字转字符串
let parsed: i32 = "42".parse().unwrap(); // 字符串转数字

// as 用于类型转换的限制
// 只能用于某些特定类型之间的转换，如基本数值类型、指针类型等
// 对于复杂类型转换，需要实现 From/Into trait
```

### 2.2 类型推断与标注

```rust
// Rust 有类型推断，但有时需要明确标注类型

// 类型推断
let x = 5; // 推断为 i32
let y = 3.14; // 推断为 f64

// 显式类型标注
let x: u32 = 5;
let y: f32 = 3.14;

// 泛型函数中的类型标注
let v: Vec<i32> = Vec::new(); // 需要标注，因为无法推断
let v = Vec::<i32>::new(); // 另一种写法，称为 turbofish 语法
let v = vec![1, 2, 3]; // 使用 vec! 宏时可以推断

// 函数返回值需要标注类型
fn get_number() -> i32 {
    42
}
```

## 3. 函数与闭包

### 3.1 函数定义与参数

```rust
// 基本函数定义
fn greet(name: &str) -> String {
    format!("Hello, {}!", name)
}

// 多参数函数
fn add(a: i32, b: i32) -> i32 {
    a + b
}

// 无参数函数
fn say_hello() {
    println!("Hello!");
}

// 无返回值函数（返回单元类型 ()）
fn do_something() -> () {
    // 做一些事情
}

// 提前返回
fn check_number(x: i32) -> bool {
    if x < 0 {
        return false;
    }
    true
}

// 发散函数（永不返回）
fn forever() -> ! {
    loop {
        // 永远循环
    }
}
```

### 3.2 泛型函数

```rust
// 泛型函数定义
fn largest<T: PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];
    for item in list.iter() {
        if item > largest {
            largest = item;
        }
    }
    largest
}

// 多泛型参数
fn combine<T, U>(t: T, u: U) -> (T, U) {
    (t, u)
}

// 泛型约束
fn print_item<T: std::fmt::Display>(item: T) {
    println!("{}", item);
}

// 多约束
fn process<T: std::fmt::Display + Clone>(item: T) {
    let cloned = item.clone();
    println!("{}", cloned);
}

// where 子句（适用于复杂约束）
fn complex_function<T, U>(t: T, u: U) -> i32
where
    T: std::fmt::Display + Clone,
    U: Clone + std::fmt::Debug,
{
    println!("{}", t);
    println!("{:?}", u);
    42
}
```

### 3.3 高阶函数与闭包

```rust
// 函数作为参数
fn apply(f: fn(i32) -> i32, x: i32) -> i32 {
    f(x)
}

fn double(x: i32) -> i32 {
    x * 2
}

let result = apply(double, 5); // 结果为 10

// 闭包（匿名函数）
let add_one = |x| x + 1;
let result = add_one(5); // 结果为 6

// 带类型标注的闭包
let add_two = |x: i32| -> i32 { x + 2 };

// 捕获环境的闭包
let x = 4;
let equal_to_x = |z| z == x; // 闭包捕获了 x

// 闭包作为参数
fn process_with_closure<F>(closure: F, value: i32) -> i32
where
    F: Fn(i32) -> i32,
{
    closure(value)
}

let result = process_with_closure(|x| x * 3, 5); // 结果为 15

// 返回闭包
fn create_adder(n: i32) -> impl Fn(i32) -> i32 {
    move |x| x + n
}

let add_five = create_adder(5);
let result = add_five(10); // 结果为 15
```

## 4. 结构体与枚举

### 4.1 结构体定义与实例化

```rust
// 定义结构体
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

// 实例化结构体
let user1 = User {
    email: String::from("someone@example.com"),
    username: String::from("someusername123"),
    active: true,
    sign_in_count: 1,
};

// 可变结构体实例
let mut user2 = User {
    email: String::from("another@example.com"),
    username: String::from("anotherusername567"),
    active: true,
    sign_in_count: 1,
};
user2.email = String::from("newemail@example.com");

// 字段初始化简写
fn build_user(email: String, username: String) -> User {
    User {
        email,      // 等同于 email: email
        username,   // 等同于 username: username
        active: true,
        sign_in_count: 1,
    }
}

// 从其他实例创建实例
let user3 = User {
    email: String::from("third@example.com"),
    ..user1 // 其余字段从 user1 获取
};

// 元组结构体（有名称但字段无名）
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

let black = Color(0, 0, 0);
let origin = Point(0, 0, 0);

// 类单元结构体（没有字段）
struct AlwaysEqual;
let subject = AlwaysEqual;
```

### 4.2 结构体方法与关联函数

```rust
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    // 方法（第一个参数是 self）
    fn area(&self) -> u32 {
        self.width * self.height
    }
    
    // 需要修改自身的方法
    fn resize(&mut self, width: u32, height: u32) {
        self.width = width;
        self.height = height;
    }
    
    // 获取所有权的方法
    fn destroy(self) -> (u32, u32) {
        (self.width, self.height)
    }
    
    // 关联函数（不以 self 为参数，类似静态方法）
    fn square(size: u32) -> Rectangle {
        Rectangle {
            width: size,
            height: size,
        }
    }
}

// 使用方法
let mut rect = Rectangle { width: 30, height: 50 };
println!("Area: {}", rect.area());
rect.resize(60, 70);

// 使用关联函数
let square = Rectangle::square(20);
```

### 4.3 枚举与模式匹配

```rust
// 基本枚举
enum IpAddrKind {
    V4,
    V6,
}

let four = IpAddrKind::V4;

// 带数据的枚举
enum IpAddr {
    V4(String),
    V6(String),
}

let home = IpAddr::V4(String::from("127.0.0.1"));

// 不同类型数据的枚举
enum Message {
    Quit,                       // 无数据
    Move { x: i32, y: i32 },    // 匿名结构体
    Write(String),              // 包含一个字符串
    ChangeColor(i32, i32, i32), // 包含三个 i32 值
}

// 为枚举定义方法
impl Message {
    fn call(&self) {
        // 方法体
    }
}

// 使用 Option 枚举处理空值
fn find_user(id: i32) -> Option<String> {
    if id == 42 {
        Some(String::from("Alice"))
    } else {
        None
    }
}

// 模式匹配
let msg = Message::Write(String::from("hello"));

match msg {
    Message::Quit => println!("Quit"),
    Message::Move { x, y } => println!("Move to ({}, {})", x, y),
    Message::Write(text) => println!("Text message: {}", text),
    Message::ChangeColor(r, g, b) => println!("Change color to ({}, {}, {})", r, g, b),
}

// if let 简化匹配
let some_value = Some(3);
if let Some(3) = some_value {
    println!("three");
}
```

## 5. 错误处理

### 5.1 可恢复错误与 Result

```rust
// Result 枚举定义
// enum Result<T, E> {
//     Ok(T),
//     Err(E),
// }

// 返回 Result 的函数
fn get_username_from_file(path: &str) -> Result<String, std::io::Error> {
    use std::fs::File;
    use std::io::Read;
    
    let mut file = match File::open(path) {
        Ok(file) => file,
        Err(e) => return Err(e),
    };
    
    let mut username = String::new();
    match file.read_to_string(&mut username) {
        Ok(_) => Ok(username),
        Err(e) => Err(e),
    }
}

// 使用 ? 运算符简化错误处理
fn get_username_simplified(path: &str) -> Result<String, std::io::Error> {
    use std::fs::File;
    use std::io::Read;
    
    let mut file = File::open(path)?;
    let mut username = String::new();
    file.read_to_string(&mut username)?;
    Ok(username)
}

// 更简洁的写法
fn get_username_concise(path: &str) -> Result<String, std::io::Error> {
    use std::fs;
    fs::read_to_string(path)
}

// 处理 Result
let result = get_username_from_file("username.txt");
match result {
    Ok(username) => println!("Username: {}", username),
    Err(e) => println!("Error: {}", e),
}

// unwrap 和 expect
let username = get_username_from_file("username.txt").unwrap(); // 成功或 panic
let username = get_username_from_file("username.txt")
    .expect("Failed to read username file"); // 带自定义消息的 panic
```

### 5.2 不可恢复错误与 panic!

```rust
// 显式调用 panic!
fn divide(a: i32, b: i32) -> i32 {
    if b == 0 {
        panic!("Attempt to divide by zero");
    }
    a / b
}

// 数组越界会导致 panic
let v = vec![1, 2, 3];
let value = v[99]; // 这会导致 panic

// 使用 unwrap 可能导致 panic
let file = std::fs::File::open("nonexistent.txt").unwrap();

// 自定义错误类型
#[derive(Debug)]
enum AppError {
    IoError(std::io::Error),
    ParseError(std::num::ParseIntError),
    Custom(String),
}

impl From<std::io::Error> for AppError {
    fn from(error: std::io::Error) -> Self {
        AppError::IoError(error)
    }
}

impl From<std::num::ParseIntError> for AppError {
    fn from(error: std::num::ParseIntError) -> Self {
        AppError::ParseError(error)
    }
}

fn read_and_parse(path: &str) -> Result<i32, AppError> {
    let content = std::fs::read_to_string(path)?; // 自动转换为 AppError
    let number: i32 = content.trim().parse()?;    // 自动转换为 AppError
    if number < 0 {
        return Err(AppError::Custom(String::from("Number cannot be negative")));
    }
    Ok(number)
}
```

## 6. 智能指针

### 6.1 Box<T>

```rust
// Box<T> 用于在堆上分配值
let b = Box::new(5);
println!("{}", b); // 自动解引用

// 创建递归数据结构
enum List {
    Cons(i32, Box<List>),
    Nil,
}

use List::{Cons, Nil};
let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));

// 解引用
let x = 5;
let y = Box::new(x);
assert_eq!(5, x);
assert_eq!(5, *y); // 使用解引用运算符
```

### 6.2 Rc<T> 和 Arc<T>

```rust
// Rc<T> 允许多个所有者（引用计数）
use std::rc::Rc;

enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use List::{Cons, Nil};

let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
let b = Cons(3, Rc::clone(&a)); // 增加引用计数，不是深拷贝
let c = Cons(4, Rc::clone(&a)); // 再次增加引用计数

// 查看引用计数
println!("count after creating c = {}", Rc::strong_count(&a));

// Arc<T> 是线程安全的 Rc<T>
use std::sync::Arc;
use std::thread;

let numbers = Arc::new(vec![1, 2, 3]);

for _ in 0..3 {
    let numbers_clone = Arc::clone(&numbers);
    thread::spawn(move || {
        println!("{:?}", *numbers_clone);
    });
}
```

### 6.3 RefCell<T> 和 Mutex<T>

```rust
// RefCell<T> 允许在运行时检查借用规则
use std::cell::RefCell;

let data = RefCell::new(5);

// 可以同时有多个不可变借用
let a = data.borrow();
let b = data.borrow();
// let c = data.borrow_mut(); // 错误：已经有不可变借用

drop(a);
drop(b);

// 现在可以获取可变借用
let mut c = data.borrow_mut();
*c = 10;

// Mutex<T> 是线程安全的 RefCell<T>
use std::sync::Mutex;
use std::thread;

let counter = Arc::new(Mutex::new(0));
let mut handles = vec![];

for _ in 0..10 {
    let counter = Arc::clone(&counter);
    let handle = thread::spawn(move || {
        let mut num = counter.lock().unwrap();
        *num += 1;
    });
    handles.push(handle);
}

for handle in handles {
    handle.join().unwrap();
}

println!("Result: {}", *counter.lock().unwrap());
```

## 7. 并发编程

### 7.1 线程

```rust
use std::thread;
use std::time::Duration;

// 创建线程
let handle = thread::spawn(|| {
    for i in 1..10 {
        println!("hi number {} from the spawned thread!", i);
        thread::sleep(Duration::from_millis(1));
    }
});

// 主线程代码
for i in 1..5 {
    println!("hi number {} from the main thread!", i);
    thread::sleep(Duration::from_millis(1));
}

// 等待线程完成
handle.join().unwrap();

// 使用 move 闭包转移所有权
let v = vec![1, 2, 3];
let handle = thread::spawn(move || {
    println!("Here's a vector: {:?}", v);
});
handle.join().unwrap();
```

### 7.2 消息传递

```rust
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

// 创建通道
let (tx, rx) = mpsc::channel();

// 创建发送线程
thread::spawn(move || {
    let val = String::from("hi");
    tx.send(val).unwrap();
    // println!("{}", val); // 错误：val 的所有权已转移
});

// 接收消息
let received = rx.recv().unwrap();
println!("Got: {}", received);

// 发送多个消息
let (tx, rx) = mpsc::channel();
thread::spawn(move || {
    let vals = vec!["hi", "from", "the", "thread"];
    for val in vals {
        tx.send(String::from(val)).unwrap();
        thread::sleep(Duration::from_secs(1));
    }
});

// 迭代接收
for received in rx {
    println!("Got: {}", received);
}

// 多个生产者
let (tx, rx) = mpsc::channel();
let tx1 = tx.clone();

thread::spawn(move || {
    tx.send(String::from("hi from tx")).unwrap();
});

thread::spawn(move || {
    tx1.send(String::from("hi from tx1")).unwrap();
});

for received in rx {
    println!("Got: {}", received);
}
```

## 8. 宏（Macros）

### 8.1 声明宏

```rust
// 声明宏（macro_rules!）
macro_rules! say_hello {
    () => {
        println!("Hello!");
    };
}

say_hello!(); // 输出 "Hello!"

// 带参数的宏
macro_rules! say_hello {
    ($name:expr) => {
        println!("Hello, {}!", $name);
    };
}

say_hello!("Alice"); // 输出 "Hello, Alice!"

// 可变参数宏
macro_rules! print_all {
    ($($arg:expr),*) => {
        $(
            println!("{}", $arg);
        )*
    };
}

print_all!(1, "hello", true); // 输出三行

// 不同模式的宏
macro_rules! math {
    (add $a:expr, $b:expr) => {
        $a + $b
    };
    (sub $a:expr, $b:expr) => {
        $a - $b
    };
}

let sum = math!(add 5, 3); // 结果为 8
let diff = math!(sub 5, 3); // 结果为 2
```

### 8.2 过程宏

```rust
// 过程宏需要在单独的 crate 中定义
// 这里只展示用法

// 派生宏
#[derive(Debug, Clone, PartialEq)]
struct Point {
    x: i32,
    y: i32,
}

// 属性宏
#[route(GET, "/")]
fn index() {}

// 函数式宏
let sql = sql!(SELECT * FROM users WHERE id = 1);
```

## 9. 常见问题与最佳实践

### 9.1 常见编译错误及解决方法

```rust
// 1. 借用检查错误
let mut s = String::from("hello");
let r1 = &s;
let r2 = &s;
let r3 = &mut s; // 错误：不能同时有可变和不可变引用

// 解决方法：确保可变引用和不可变引用的作用域不重叠
let mut s = String::from("hello");
let r1 = &s;
let r2 = &s;
println!("{} and {}", r1, r2); // r1 和 r2 的作用域到这里结束
let r3 = &mut s; // 正确：r1 和 r2 的作用域已结束

// 2. 生命周期错误
// fn longest(x: &str, y: &str) -> &str { // 错误：缺少生命周期标注
//     if x.len() > y.len() {
//         x
//     } else {
//         y
//     }
// }

// 解决方法：添加生命周期标注
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

// 3. 移动错误
let s1 = String::from("hello");
let s2 = s1;
println!("{}", s1); // 错误：s1 的值已移动到 s2

// 解决方法：使用克隆或引用
let s1 = String::from("hello");
let s2 = s1.clone(); // 或 let s2 = &s1;
println!("{}", s1); // 正确
```

### 9.2 性能优化技巧

```rust
// 1. 避免不必要的克隆
// 不好的做法
fn process(s: String) {
    println!("{}", s);
}
let s = String::from("hello");
process(s.clone()); // 不必要的克隆

// 好的做法
fn process(s: &str) {
    println!("{}", s);
}
let s = String::from("hello");
process(&s); // 使用引用

// 2. 使用迭代器而不是索引访问
// 不好的做法
let v = vec![1, 2, 3, 4, 5];
for i in 0..v.len() {
    println!("{}", v[i]);
}

// 好的做法
let v = vec![1, 2, 3, 4, 5];
for item in &v {
    println!("{}", item);
}

// 3. 使用 String 的预分配
let mut s = String::with_capacity(1000); // 预分配空间
for i in 0..1000 {
    s.push_str("a");
}

// 4. 使用 Box<[T]> 代替 Vec<T> 存储固定大小的数据
let v: Vec<i32> = vec![1, 2, 3, 4, 5];
let b: Box<[i32]> = v.into_boxed_slice(); // 释放多余容量

// 5. 使用 release 模式编译
// cargo build --release
```

### 9.3 Rust 编码风格

```rust
// 1. 命名约定
struct UserData {} // 结构体使用 PascalCase
enum HttpStatus {} // 枚举使用 PascalCase

fn calculate_tax() {} // 函数使用 snake_case
let user_id = 42; // 变量使用 snake_case

const MAX_POINTS: u32 = 100_000; // 常量使用 SCREAMING_SNAKE_CASE

// 2. 代码格式化
// 使用 rustfmt 工具格式化代码
// rustfmt src/main.rs

// 3. 文档注释
/// 计算两个数的和
///
/// # Examples
///
/// ```
/// let sum = add(2, 3);
/// assert_eq!(sum, 5);
/// ```
fn add(a: i32, b: i32) -> i32 {
    a + b
}

// 4. 使用 clippy 进行代码检查
// cargo clippy
```

## 10. 实用 Crate 推荐

```rust
// 1. serde - 序列化和反序列化
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug)]
struct Point {
    x: i32,
    y: i32,
}

// 2. rand - 随机数生成
use rand::Rng;
let mut rng = rand::thread_rng();
let n: i32 = rng.gen_range(1..101); // 1-100 的随机数

// 3. tokio - 异步运行时
#[tokio::main]
async fn main() {
    println!("Hello, world!");
    let result = fetch_data().await;
    println!("{:?}", result);
}

async fn fetch_data() -> Result<String, Box<dyn std::error::Error>> {
    // 异步操作
    Ok(String::from("data"))
}

// 4. rayon - 并行计算
use rayon::prelude::*;

let v = vec![1, 2, 3, 4, 5];
let sum: i32 = v.par_iter().sum(); // 并行求和

// 5. clap - 命令行参数解析
use clap::{App, Arg};

let matches = App::new("My App")
    .version("1.0")
    .author("Author")
    .about("Does awesome things")
    .arg(Arg::with_name("config")
        .short("c")
        .long("config")
        .value_name("FILE")
        .help("Sets a custom config file")
        .takes_value(true))
    .get_matches();

if let Some(c) = matches.value_of("config") {
    println!("Value for config: {}", c);
}
```

希望这些补充内容能帮助你更好地理解 Rust 语言的核心概念和实践！如果有任何特定的问题，随时可以问我喵～