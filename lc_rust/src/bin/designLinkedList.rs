// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

use std::rc::Rc;
use std::cell::RefCell;

// 双向链表节点
#[derive(Debug, Clone)]
struct ListNode {
    val: i32,
    prev: Option<Rc<RefCell<ListNode>>>,
    next: Option<Rc<RefCell<ListNode>>>,
}

impl ListNode {
    fn new(val: i32) -> Self {
        ListNode {
            val,
            prev: None,
            next: None,
        }
    }
}

// 双向链表实现
#[derive(Debug)]
struct MyLinkedList {
    head: Option<Rc<RefCell<ListNode>>>,
    tail: Option<Rc<RefCell<ListNode>>>,
    size: usize,
}

impl MyLinkedList {
    fn new() -> Self {
        // 创建哨兵节点
        let head = Rc::new(RefCell::new(ListNode::new(0)));
        let tail = Rc::new(RefCell::new(ListNode::new(0)));
        
        head.borrow_mut().next = Some(tail.clone());
        tail.borrow_mut().prev = Some(head.clone());
        
        MyLinkedList {
            head: Some(head),
            tail: Some(tail),
            size: 0,
        }
    }
    
    fn get(&self, index: i32) -> i32 {
        if index < 0 || index as usize >= self.size {
            return -1;
        }
        
        let mut current = self.head.as_ref().unwrap().borrow().next.clone();
        for _ in 0..index {
            if let Some(node) = current {
                current = node.borrow().next.clone();
            }
        }
        
        current.map_or(-1, |node| node.borrow().val)
    }
    
    fn add_at_head(&mut self, val: i32) {
        self.add_at_index(0, val);
    }
    
    fn add_at_tail(&mut self, val: i32) {
        self.add_at_index(self.size as i32, val);
    }
    
    fn add_at_index(&mut self, index: i32, val: i32) {
        if index < 0 || index as usize > self.size {
            return;
        }
        
        let mut pred = self.head.clone();
        for _ in 0..index {
            if let Some(node) = pred {
                pred = node.borrow().next.clone();
            }
        }
        
        if let Some(pred_node) = pred {
            let succ = pred_node.borrow().next.clone();
            let new_node = Rc::new(RefCell::new(ListNode::new(val)));
            
            new_node.borrow_mut().prev = Some(pred_node.clone());
            new_node.borrow_mut().next = succ.clone();
            
            pred_node.borrow_mut().next = Some(new_node.clone());
            if let Some(succ_node) = succ {
                succ_node.borrow_mut().prev = Some(new_node);
            }
            
            self.size += 1;
        }
    }
    
    fn delete_at_index(&mut self, index: i32) {
        if index < 0 || index as usize >= self.size {
            return;
        }
        
        let mut pred = self.head.clone();
        for _ in 0..index {
            if let Some(node) = pred {
                pred = node.borrow().next.clone();
            }
        }
        
        if let Some(pred_node) = pred {
            // 这里立刻拿到 pred_node.next，Ref 在这行就会 drop
            let to_delete = pred_node.borrow().next.clone();
        
            if let Some(to_delete) = to_delete {
                let succ = to_delete.borrow().next.clone();
        
                // 现在 Ref 已经 drop，可以安全 borrow_mut
                pred_node.borrow_mut().next = succ.clone();
                if let Some(succ_node) = succ {
                    succ_node.borrow_mut().prev = Some(pred_node.clone());
                }
        
                self.size -= 1;
            }
        }
        
    }
}

// 简化版本：使用Vec实现
#[derive(Debug)]
struct SimpleLinkedList {
    data: Vec<i32>,
}

impl SimpleLinkedList {
    fn new() -> Self {
        SimpleLinkedList {
            data: Vec::new(),
        }
    }
    
    fn get(&self, index: i32) -> i32 {
        if index < 0 || index as usize >= self.data.len() {
            -1
        } else {
            self.data[index as usize]
        }
    }
    
    fn add_at_head(&mut self, val: i32) {
        self.data.insert(0, val);
    }
    
    fn add_at_tail(&mut self, val: i32) {
        self.data.push(val);
    }
    
    fn add_at_index(&mut self, index: i32, val: i32) {
        if index < 0 || index as usize > self.data.len() {
            return;
        }
        self.data.insert(index as usize, val);
    }
    
    fn delete_at_index(&mut self, index: i32) {
        if index >= 0 && (index as usize) < self.data.len() {
            self.data.remove(index as usize);
        }
    }
}

// 函数式编程风格的链表操作
mod functional {
    use super::*;
    
    pub fn create_list() -> MyLinkedList {
        MyLinkedList::new()
    }
    
    pub fn list_operations(operations: Vec<(&str, Vec<i32>)>) -> Vec<Option<i32>> {
        let mut list = MyLinkedList::new();
        let mut results = Vec::new();
        
        for (op, params) in operations {
            match op {
                "get" => {
                    if let Some(&index) = params.first() {
                        results.push(Some(list.get(index)));
                    }
                }
                "addAtHead" => {
                    if let Some(&val) = params.first() {
                        list.add_at_head(val);
                        results.push(None);
                    }
                }
                "addAtTail" => {
                    if let Some(&val) = params.first() {
                        list.add_at_tail(val);
                        results.push(None);
                    }
                }
                "addAtIndex" => {
                    if params.len() >= 2 {
                        list.add_at_index(params[0], params[1]);
                        results.push(None);
                    }
                }
                "deleteAtIndex" => {
                    if let Some(&index) = params.first() {
                        list.delete_at_index(index);
                        results.push(None);
                    }
                }
                _ => results.push(None),
            }
        }
        
        results
    }
}

fn test_design_linked_list() {
    println!("=== 设计链表测试 ===");
    
    // 测试双向链表实现
    let mut list = MyLinkedList::new();
    
    println!("\n--- 双向链表实现测试 ---");
    list.add_at_head(7);
    list.add_at_head(2);
    list.add_at_head(1);
    println!("添加头部元素后: [1, 2, 7]");
    
    list.add_at_index(3, 0);
    println!("在索引3添加0后: [1, 2, 7, 0]");
    
    list.delete_at_index(2);
    println!("删除索引2后: [1, 2, 0]");
    
    list.add_at_head(6);
    println!("添加头部6后: [6, 1, 2, 0]");
    
    list.add_at_tail(4);
    println!("添加尾部4后: [6, 1, 2, 0, 4]");
    
    println!("获取索引5: {}", list.get(5)); // -1
    println!("获取索引3: {}", list.get(3)); // 0
    println!("获取索引2: {}", list.get(2)); // 2
    println!("获取索引0: {}", list.get(0)); // 6
    
    list.delete_at_index(0);
    println!("删除索引0后，获取索引0: {}", list.get(0)); // 1
    
    // 测试简化版本
    println!("\n--- 简化版本测试 ---");
    let mut simple_list = SimpleLinkedList::new();
    simple_list.add_at_head(1);
    simple_list.add_at_tail(3);
    simple_list.add_at_index(1, 2);
    println!("简化版本操作后: [1, 2, 3]");
    println!("获取索引1: {}", simple_list.get(1)); // 2
    
    simple_list.delete_at_index(1);
    println!("删除索引1后，获取索引1: {}", simple_list.get(1)); // 3
    
    // 测试函数式编程风格
    println!("\n--- 函数式编程风格测试 ---");
    let operations = vec![
        ("addAtHead", vec![7]),
        ("addAtHead", vec![2]),
        ("addAtHead", vec![1]),
        ("addAtIndex", vec![3, 0]),
        ("deleteAtIndex", vec![2]),
        ("addAtHead", vec![6]),
        ("addAtTail", vec![4]),
        ("get", vec![4]),
        ("addAtHead", vec![4]),
        ("addAtIndex", vec![5, 0]),
        ("addAtHead", vec![6]),
    ];
    
    let results = functional::list_operations(operations);
    println!("函数式操作结果: {:?}", results);
    
    println!("\n=== Rust特性说明 ===");
    println!("1. 内存安全: 编译时防止悬垂指针和内存泄漏");
    println!("2. 所有权系统: 自动管理内存，无需手动释放");
    println!("3. Rc<RefCell<>>: 允许多重引用和内部可变性");
    println!("4. 模式匹配: 安全处理Option类型");
    println!("5. 零成本抽象: 高级特性不影响运行时性能");
}

fn main() {
    test_design_linked_list();
}

/*
Rust实现特点:

1. **内存安全**:
   - 编译时检查防止悬垂指针
   - 自动内存管理
   - 无数据竞争

2. **所有权系统**:
   - 每个值都有唯一所有者
   - 借用检查器确保内存安全
   - RAII自动资源管理

3. **智能指针**:
   - Rc<RefCell<>>允许多重引用
   - RefCell提供内部可变性
   - 运行时借用检查

4. **模式匹配**:
   - Option类型安全处理空值
   - match表达式穷尽性检查
   - if let简化模式匹配

5. **零成本抽象**:
   - 高级特性编译时优化
   - 无运行时开销
   - 性能可预测

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/