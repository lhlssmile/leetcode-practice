// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

use std::collections::HashMap;
use std::ptr::NonNull;
use std::cell::RefCell;
use std::rc::Rc;

// 使用Rc<RefCell<>>的安全版本
#[derive(Debug)]
struct Node {
    key: i32,
    val: i32,
    prev: Option<Rc<RefCell<Node>>>,
    next: Option<Rc<RefCell<Node>>>,
}

impl Node {
    fn new(key: i32, val: i32) -> Rc<RefCell<Self>> {
        Rc::new(RefCell::new(Node {
            key,
            val,
            prev: None,
            next: None,
        }))
    }
}

#[derive(Debug)]
struct LRUCache {
    capacity: usize,
    cache: HashMap<i32, Rc<RefCell<Node>>>,
    head: Rc<RefCell<Node>>,
    tail: Rc<RefCell<Node>>,
}

impl LRUCache {
    fn new(capacity: i32) -> Self {
        let head = Node::new(0, 0);
        let tail = Node::new(0, 0);
        
        head.borrow_mut().next = Some(tail.clone());
        tail.borrow_mut().prev = Some(head.clone());
        
        LRUCache {
            capacity: capacity as usize,
            cache: HashMap::new(),
            head,
            tail,
        }
    }
    
    fn get(&mut self, key: i32) -> i32 {
        if let Some(node) = self.cache.get(&key) {
            let val = node.borrow().val;
            self.move_to_head(node.clone());
            val
        } else {
            -1
        }
    }
    
    fn put(&mut self, key: i32, value: i32) {
        if let Some(node) = self.cache.get(&key) {
            node.borrow_mut().val = value;
            self.move_to_head(node.clone());
        } else {
            let node = Node::new(key, value);
            self.cache.insert(key, node.clone());
            self.add_to_head(node);
            
            if self.cache.len() > self.capacity {
                let removed = self.remove_tail();
                self.cache.remove(&removed.borrow().key);
            }
        }
    }
    
    fn add_to_head(&mut self, node: Rc<RefCell<Node>>) {
        let head_next = self.head.borrow().next.clone();
        
        node.borrow_mut().prev = Some(self.head.clone());
        node.borrow_mut().next = head_next.clone();
        
        if let Some(next) = head_next {
            next.borrow_mut().prev = Some(node.clone());
        }
        self.head.borrow_mut().next = Some(node);
    }
    
    fn remove_node(&mut self, node: Rc<RefCell<Node>>) {
        let prev = node.borrow().prev.clone();
        let next = node.borrow().next.clone();
        
        if let Some(ref prev_node) = prev {
            prev_node.borrow_mut().next = next.clone();
        }
        if let Some(ref next_node) = next {
            next_node.borrow_mut().prev = prev.clone();
        }
    }
    
    fn move_to_head(&mut self, node: Rc<RefCell<Node>>) {
        self.remove_node(node.clone());
        self.add_to_head(node);
    }
    
    fn remove_tail(&mut self) -> Rc<RefCell<Node>> {
        let tail_prev = self.tail.borrow().prev.clone().unwrap();
        self.remove_node(tail_prev.clone());
        tail_prev
    }
}

// 使用Vec的简化版本
#[derive(Debug)]
struct SimpleLRUCache {
    capacity: usize,
    keys: Vec<i32>,
    values: HashMap<i32, i32>,
}

impl SimpleLRUCache {
    fn new(capacity: i32) -> Self {
        SimpleLRUCache {
            capacity: capacity as usize,
            keys: Vec::new(),
            values: HashMap::new(),
        }
    }
    
    fn get(&mut self, key: i32) -> i32 {
        if let Some(&value) = self.values.get(&key) {
            // 移动到最前面
            if let Some(pos) = self.keys.iter().position(|&x| x == key) {
                self.keys.remove(pos);
                self.keys.insert(0, key);
            }
            value
        } else {
            -1
        }
    }
    
    fn put(&mut self, key: i32, value: i32) {
        if self.values.contains_key(&key) {
            // 更新值并移动到最前面
            self.values.insert(key, value);
            if let Some(pos) = self.keys.iter().position(|&x| x == key) {
                self.keys.remove(pos);
                self.keys.insert(0, key);
            }
        } else {
            // 新增
            if self.keys.len() >= self.capacity {
                // 移除最后一个
                if let Some(last_key) = self.keys.pop() {
                    self.values.remove(&last_key);
                }
            }
            self.keys.insert(0, key);
            self.values.insert(key, value);
        }
    }
}

fn main() {
    println!("=== LRU缓存测试 ===");
    
    // 测试标准版本
    println!("\n--- 标准版本测试 ---");
    let mut lru = LRUCache::new(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    println!("get(1): {}", lru.get(1)); // 返回 1
    lru.put(3, 3); // 该操作会使得关键字 2 作废
    println!("get(2): {}", lru.get(2)); // 返回 -1 (未找到)
    lru.put(4, 4); // 该操作会使得关键字 1 作废
    println!("get(1): {}", lru.get(1)); // 返回 -1 (未找到)
    println!("get(3): {}", lru.get(3)); // 返回 3
    println!("get(4): {}", lru.get(4)); // 返回 4
    
    // 测试简化版本
    println!("\n--- 简化版本测试 ---");
    let mut simple_lru = SimpleLRUCache::new(2);
    
    simple_lru.put(1, 1);
    simple_lru.put(2, 2);
    println!("get(1): {}", simple_lru.get(1)); // 返回 1
    simple_lru.put(3, 3); // 该操作会使得关键字 2 作废
    println!("get(2): {}", simple_lru.get(2)); // 返回 -1 (未找到)
    simple_lru.put(4, 4); // 该操作会使得关键字 1 作废
    println!("get(1): {}", simple_lru.get(1)); // 返回 -1 (未找到)
    println!("get(3): {}", simple_lru.get(3)); // 返回 3
    println!("get(4): {}", simple_lru.get(4)); // 返回 4
    
    println!("\n=== Rust特性说明 ===");
    println!("1. Rc<RefCell<>>: 内部可变性和共享所有权");
    println!("2. HashMap: 高效的键值存储");
    println!("3. Option类型: 安全的空值处理");
    println!("4. 借用检查: 内存安全保证");
    println!("5. 模式匹配: if let语法");
}

/*
Rust实现特点:

1. **内存安全**:
   - 使用Rc<RefCell<>>实现共享可变引用
   - 避免空指针和悬垂指针
   - 编译时内存安全检查

2. **所有权系统**:
   - 明确的所有权转移
   - 借用检查器防止数据竞争
   - 零成本抽象

3. **类型系统**:
   - Option类型处理可能为空的值
   - 强类型系统防止类型错误
   - 模式匹配提供安全的解构

4. **性能优化**:
   - 零成本抽象
   - 编译时优化
   - 无垃圾回收开销

5. **错误处理**:
   - Result类型处理可能失败的操作
   - 强制错误处理
   - 无异常机制

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/