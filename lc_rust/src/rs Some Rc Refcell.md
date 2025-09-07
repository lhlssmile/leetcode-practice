# Rust 引用借用、Rc 和 RefCell 详解 🦀

## 目录
1. [基础概念](#基础概念)
2. [所有权系统](#所有权系统)
3. [引用和借用](#引用和借用)
4. [Rc智能指针](#rc智能指针)
5. [RefCell内部可变性](#refcell内部可变性)
6. [双向链表实战](#双向链表实战)
7. [常见陷阱和解决方案](#常见陷阱和解决方案)

## 基础概念

### 什么是所有权？

Rust的所有权系统是其内存安全的核心，每个值都有一个唯一的所有者：

```rust
// 基本所有权规则
fn ownership_basics() {
    let s1 = String::from("hello");  // s1 拥有字符串
    let s2 = s1;                     // 所有权转移给 s2
    // println!("{}", s1);          // 错误！s1 不再有效
    println!("{}", s2);             // 正确
}

// 函数调用中的所有权转移
fn takes_ownership(s: String) {
    println!("{}", s);
} // s 在这里被丢弃

fn gives_ownership() -> String {
    String::from("hello")
}

fn ownership_transfer() {
    let s1 = gives_ownership();      // 获得所有权
    let s2 = String::from("world");
    takes_ownership(s2);             // s2 的所有权被转移
    // println!("{}", s2);          // 错误！s2 不再有效
    println!("{}", s1);             // s1 仍然有效
}
```

## 所有权系统

### 三大规则

1. **每个值都有一个所有者**
2. **同时只能有一个所有者**
3. **当所有者离开作用域时，值被丢弃**

```rust
// 作用域和所有权
fn scope_example() {
    {                        // s 不在作用域内
        let s = "hello";     // s 进入作用域
        // 使用 s
    }                        // s 离开作用域，被丢弃
    
    let s1 = String::from("hello");
    let s2 = s1;            // s1 的值移动到 s2
    // s1 不再有效
    
    let x = 5;
    let y = x;              // 基本类型实现了 Copy trait，所以 x 仍然有效
    println!("x = {}, y = {}", x, y);
}
```

## 引用和借用

### 不可变引用

```rust
// 不可变引用允许你使用值但不获取其所有权
fn calculate_length(s: &String) -> usize {
    s.len()
} // s 离开作用域，但因为它不拥有引用的值，所以什么也不会发生

fn immutable_reference() {
    let s1 = String::from("hello");
    let len = calculate_length(&s1);  // &s1 创建一个指向 s1 的引用
    println!("'{}' 的长度是 {}.", s1, len);
    // s1 仍然有效，因为我们只是借用了它
}

// 多个不可变引用是允许的
fn multiple_immutable_refs() {
    let s = String::from("hello");
    let r1 = &s;  // 没问题
    let r2 = &s;  // 没问题
    let r3 = &s;  // 没问题
    println!("{}, {}, {}", r1, r2, r3);
}
```

### 可变引用

```rust
// 可变引用允许修改借用的值
fn change(some_string: &mut String) {
    some_string.push_str(", world");
}

fn mutable_reference() {
    let mut s = String::from("hello");
    change(&mut s);
    println!("{}", s);
}

// 可变引用的限制：同时只能有一个
fn mutable_reference_rules() {
    let mut s = String::from("hello");
    
    let r1 = &mut s;
    // let r2 = &mut s;  // 错误！不能同时有两个可变引用
    
    println!("{}", r1);
    
    // 在 r1 的作用域结束后，可以创建新的可变引用
    let r2 = &mut s;
    println!("{}", r2);
}

// 不能同时拥有可变和不可变引用
fn mixed_references() {
    let mut s = String::from("hello");
    
    let r1 = &s;      // 没问题
    let r2 = &s;      // 没问题
    // let r3 = &mut s;  // 错误！不能在有不可变引用时创建可变引用
    
    println!("{} and {}", r1, r2);
    // r1 和 r2 在这里不再使用
    
    let r3 = &mut s;  // 现在可以了
    println!("{}", r3);
}
```

### 悬垂引用（Dangling References）

```rust
// Rust 防止悬垂引用
// fn dangle() -> &String {     // 错误！
//     let s = String::from("hello");
//     &s  // 返回字符串 s 的引用
// } // s 离开作用域并被丢弃，其内存被释放

// 正确的做法：返回 String 本身
fn no_dangle() -> String {
    let s = String::from("hello");
    s  // 返回 s，所有权被转移
}
```

## Rc智能指针

### 什么是 Rc？

`Rc<T>` (Reference Counted) 允许多个所有者共享同一个数据：

```rust
use std::rc::Rc;

// 基本 Rc 使用
fn rc_basic() {
    let a = Rc::new(String::from("hello"));
    println!("引用计数: {}", Rc::strong_count(&a));  // 1
    
    let b = Rc::clone(&a);  // 增加引用计数，不是深拷贝
    println!("引用计数: {}", Rc::strong_count(&a));  // 2
    
    {
        let c = Rc::clone(&a);
        println!("引用计数: {}", Rc::strong_count(&a));  // 3
    }  // c 离开作用域，引用计数减 1
    
    println!("引用计数: {}", Rc::strong_count(&a));  // 2
}

// Rc 在数据结构中的应用
#[derive(Debug)]
struct Node {
    value: i32,
    children: Vec<Rc<Node>>,
}

fn rc_tree() {
    let leaf = Rc::new(Node {
        value: 3,
        children: vec![],
    });
    
    let branch = Rc::new(Node {
        value: 5,
        children: vec![Rc::clone(&leaf)],
    });
    
    let root = Rc::new(Node {
        value: 10,
        children: vec![Rc::clone(&branch), Rc::clone(&leaf)],
    });
    
    println!("leaf 引用计数: {}", Rc::strong_count(&leaf));  // 3
    println!("branch 引用计数: {}", Rc::strong_count(&branch));  // 2
}
```

### Rc 的限制

```rust
// Rc 只允许不可变访问
fn rc_limitations() {
    let data = Rc::new(vec![1, 2, 3]);
    let data1 = Rc::clone(&data);
    let data2 = Rc::clone(&data);
    
    // data.push(4);  // 错误！Rc 不允许可变访问
    
    // 只能读取数据
    println!("data: {:?}", data);
    println!("data1: {:?}", data1);
    println!("data2: {:?}", data2);
}
```

## RefCell内部可变性

### 什么是 RefCell？

`RefCell<T>` 提供内部可变性，允许在不可变引用存在时修改数据：

```rust
use std::cell::RefCell;

// 基本 RefCell 使用
fn refcell_basic() {
    let data = RefCell::new(vec![1, 2, 3]);
    
    // 借用可变引用
    data.borrow_mut().push(4);
    data.borrow_mut().push(5);
    
    // 借用不可变引用
    println!("data: {:?}", data.borrow());
}

// RefCell 的运行时借用检查
fn refcell_borrow_rules() {
    let data = RefCell::new(5);
    
    // 多个不可变借用是允许的
    let r1 = data.borrow();
    let r2 = data.borrow();
    println!("r1: {}, r2: {}", *r1, *r2);
    
    // 释放不可变借用
    drop(r1);
    drop(r2);
    
    // 现在可以获取可变借用
    let mut r3 = data.borrow_mut();
    *r3 += 10;
    println!("modified: {}", *r3);
    
    // 如果违反借用规则，会在运行时 panic
    // let r4 = data.borrow();  // panic！不能在有可变借用时创建不可变借用
}

// RefCell 与 Rc 结合使用
fn rc_refcell_combo() {
    let data = Rc::new(RefCell::new(vec![1, 2, 3]));
    let data1 = Rc::clone(&data);
    let data2 = Rc::clone(&data);
    
    // 现在可以通过任何一个 Rc 修改数据
    data1.borrow_mut().push(4);
    data2.borrow_mut().push(5);
    
    println!("final data: {:?}", data.borrow());
}
```

### 内部可变性模式

```rust
// 模拟一个需要内部可变性的场景
struct MockMessenger {
    sent_messages: RefCell<Vec<String>>,
}

impl MockMessenger {
    fn new() -> MockMessenger {
        MockMessenger {
            sent_messages: RefCell::new(vec![]),
        }
    }
    
    fn send(&self, message: &str) {  // 注意这里是 &self，不是 &mut self
        self.sent_messages.borrow_mut().push(String::from(message));
    }
    
    fn get_messages(&self) -> Vec<String> {
        self.sent_messages.borrow().clone()
    }
}

fn internal_mutability_pattern() {
    let messenger = MockMessenger::new();
    messenger.send("Hello");
    messenger.send("World");
    
    println!("Messages: {:?}", messenger.get_messages());
}
```

## 双向链表实战

现在让我们用刚才学到的知识来理解双向链表的实现：

```rust
use std::rc::Rc;
use std::cell::RefCell;

// 双向链表节点
#[derive(Debug)]
struct ListNode {
    val: i32,
    next: Option<Rc<RefCell<ListNode>>>,
    prev: Option<Rc<RefCell<ListNode>>>,
}

impl ListNode {
    fn new(val: i32) -> Rc<RefCell<Self>> {
        Rc::new(RefCell::new(ListNode {
            val,
            next: None,
            prev: None,
        }))
    }
}

// 双向链表
struct DoublyLinkedList {
    head: Option<Rc<RefCell<ListNode>>>,
    tail: Option<Rc<RefCell<ListNode>>>,
    size: usize,
}

impl DoublyLinkedList {
    fn new() -> Self {
        DoublyLinkedList {
            head: None,
            tail: None,
            size: 0,
        }
    }
    
    // 在头部添加节点
    fn push_front(&mut self, val: i32) {
        let new_node = ListNode::new(val);
        
        match self.head.take() {
            Some(old_head) => {
                // 设置新节点的 next 指向旧头节点
                new_node.borrow_mut().next = Some(Rc::clone(&old_head));
                // 设置旧头节点的 prev 指向新节点
                old_head.borrow_mut().prev = Some(Rc::clone(&new_node));
                // 更新头节点
                self.head = Some(new_node);
            }
            None => {
                // 链表为空，新节点既是头也是尾
                self.head = Some(Rc::clone(&new_node));
                self.tail = Some(new_node);
            }
        }
        
        self.size += 1;
    }
    
    // 在尾部添加节点
    fn push_back(&mut self, val: i32) {
        let new_node = ListNode::new(val);
        
        match self.tail.take() {
            Some(old_tail) => {
                // 设置新节点的 prev 指向旧尾节点
                new_node.borrow_mut().prev = Some(Rc::clone(&old_tail));
                // 设置旧尾节点的 next 指向新节点
                old_tail.borrow_mut().next = Some(Rc::clone(&new_node));
                // 更新尾节点
                self.tail = Some(new_node);
            }
            None => {
                // 链表为空，新节点既是头也是尾
                self.head = Some(Rc::clone(&new_node));
                self.tail = Some(new_node);
            }
        }
        
        self.size += 1;
    }
    
    // 从头部移除节点
    fn pop_front(&mut self) -> Option<i32> {
        self.head.take().map(|old_head| {
            let val = old_head.borrow().val;
            
            match old_head.borrow_mut().next.take() {
                Some(new_head) => {
                    // 新头节点的 prev 设为 None
                    new_head.borrow_mut().prev = None;
                    self.head = Some(new_head);
                }
                None => {
                    // 链表变空
                    self.tail = None;
                }
            }
            
            self.size -= 1;
            val
        })
    }
    
    // 遍历链表（从头到尾）
    fn iter_forward(&self) -> Vec<i32> {
        let mut result = Vec::new();
        let mut current = self.head.as_ref().map(|node| Rc::clone(node));
        
        while let Some(node) = current {
            result.push(node.borrow().val);
            current = node.borrow().next.as_ref().map(|next| Rc::clone(next));
        }
        
        result
    }
    
    // 遍历链表（从尾到头）
    fn iter_backward(&self) -> Vec<i32> {
        let mut result = Vec::new();
        let mut current = self.tail.as_ref().map(|node| Rc::clone(node));
        
        while let Some(node) = current {
            result.push(node.borrow().val);
            current = node.borrow().prev.as_ref().map(|prev| Rc::clone(prev));
        }
        
        result
    }
}

// 测试双向链表
fn test_doubly_linked_list() {
    let mut list = DoublyLinkedList::new();
    
    // 添加元素
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    
    println!("正向遍历: {:?}", list.iter_forward());   // [0, 1, 2, 3]
    println!("反向遍历: {:?}", list.iter_backward());  // [3, 2, 1, 0]
    
    // 移除元素
    println!("移除头部: {:?}", list.pop_front());      // Some(0)
    println!("正向遍历: {:?}", list.iter_forward());   // [1, 2, 3]
}
```

### 为什么需要 Rc<RefCell<T>>？

在双向链表中，我们需要：

1. **Rc**: 因为每个节点可能被多个地方引用（前一个节点的 next 和后一个节点的 prev）
2. **RefCell**: 因为我们需要在运行时修改节点的内容（设置 next 和 prev 指针）

```rust
// 解释为什么需要这种复杂的类型
fn why_rc_refcell() {
    // 创建三个节点
    let node1 = ListNode::new(1);
    let node2 = ListNode::new(2);
    let node3 = ListNode::new(3);
    
    // 建立连接：node1 <-> node2 <-> node3
    
    // node1.next = node2, node2.prev = node1
    node1.borrow_mut().next = Some(Rc::clone(&node2));
    node2.borrow_mut().prev = Some(Rc::clone(&node1));
    
    // node2.next = node3, node3.prev = node2
    node2.borrow_mut().next = Some(Rc::clone(&node3));
    node3.borrow_mut().prev = Some(Rc::clone(&node2));
    
    // 现在 node2 被三个地方引用：
    // 1. 变量 node2
    // 2. node1.next
    // 3. node3.prev
    println!("node2 引用计数: {}", Rc::strong_count(&node2));  // 3
    
    // 通过不同的路径访问 node2
    println!("直接访问: {}", node2.borrow().val);
    println!("通过 node1.next: {}", node1.borrow().next.as_ref().unwrap().borrow().val);
    println!("通过 node3.prev: {}", node3.borrow().prev.as_ref().unwrap().borrow().val);
}
```

## 常见陷阱和解决方案

### 1. 循环引用

```rust
use std::rc::{Rc, Weak};
use std::cell::RefCell;

// 危险：循环引用会导致内存泄漏
#[derive(Debug)]
struct Parent {
    children: RefCell<Vec<Rc<Child>>>,
}

#[derive(Debug)]
struct Child {
    parent: RefCell<Option<Rc<Parent>>>,  // 这会造成循环引用！
}

// 解决方案：使用 Weak 引用
#[derive(Debug)]
struct SafeParent {
    children: RefCell<Vec<Rc<SafeChild>>>,
}

#[derive(Debug)]
struct SafeChild {
    parent: RefCell<Option<Weak<SafeParent>>>,  // 使用 Weak 避免循环引用
}

fn avoid_cycles() {
    let parent = Rc::new(SafeParent {
        children: RefCell::new(vec![]),
    });
    
    let child = Rc::new(SafeChild {
        parent: RefCell::new(Some(Rc::downgrade(&parent))),
    });
    
    parent.children.borrow_mut().push(Rc::clone(&child));
    
    // 检查引用计数
    println!("parent 强引用计数: {}", Rc::strong_count(&parent));  // 1
    println!("parent 弱引用计数: {}", Rc::weak_count(&parent));    // 1
    println!("child 强引用计数: {}", Rc::strong_count(&child));    // 2
}
```

### 2. RefCell 运行时借用检查失败

```rust
// 危险：违反借用规则会导致 panic
fn borrow_check_panic() {
    let data = RefCell::new(5);
    
    let _r1 = data.borrow_mut();  // 获取可变借用
    // let _r2 = data.borrow();   // panic！不能在有可变借用时获取不可变借用
}

// 解决方案：使用 try_borrow
fn safe_borrow_check() {
    let data = RefCell::new(5);
    
    let _r1 = data.borrow_mut();
    
    match data.try_borrow() {
        Ok(_r2) => println!("成功获取不可变借用"),
        Err(_) => println!("无法获取不可变借用，已有可变借用存在"),
    }
}
```

### 3. 性能考虑

```rust
// Rc<RefCell<T>> 的性能开销
fn performance_considerations() {
    use std::time::Instant;
    
    // 直接访问
    let start = Instant::now();
    let mut vec = vec![1, 2, 3, 4, 5];
    for i in 0..1000000 {
        vec.push(i);
    }
    println!("直接访问耗时: {:?}", start.elapsed());
    
    // 通过 Rc<RefCell<T>> 访问
    let start = Instant::now();
    let vec_rc = Rc::new(RefCell::new(vec![1, 2, 3, 4, 5]));
    for i in 0..1000000 {
        vec_rc.borrow_mut().push(i);
    }
    println!("Rc<RefCell<T>> 访问耗时: {:?}", start.elapsed());
}
```

## 总结

### 何时使用什么？

| 场景 | 使用 | 原因 |
|------|------|------|
| 单一所有者，不需要修改 | `T` | 最简单，性能最好 |
| 单一所有者，需要修改 | `&mut T` | 编译时借用检查 |
| 多个所有者，不需要修改 | `Rc<T>` | 共享只读数据 |
| 多个所有者，需要修改 | `Rc<RefCell<T>>` | 共享可变数据 |
| 需要避免循环引用 | `Weak<T>` | 打破循环引用 |
| 线程间共享 | `Arc<T>` 或 `Arc<Mutex<T>>` | 线程安全 |

### 最佳实践

1. **优先使用借用而不是所有权转移**
2. **尽量避免 `Rc<RefCell<T>>`，除非确实需要**
3. **注意循环引用，使用 `Weak<T>` 打破循环**
4. **使用 `try_borrow` 避免运行时 panic**
5. **在性能敏感的代码中谨慎使用智能指针**

### 记忆口诀 🎯

- **借用不拥有，引用要小心** 📝
- **Rc 多主人，RefCell 内可变** 🔄
- **循环引用坏，Weak 来打破** 💔
- **编译时安全，运行时检查** ⚡

现在你应该对 Rust 的引用借用系统有了更深入的理解！记住，这些概念需要在实践中慢慢消化，多写代码多踩坑就会越来越熟练的喵~ 🐱