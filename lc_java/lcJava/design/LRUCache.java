// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

package design;

import java.util.*;

class Node {
    int key, val;
    Node prev, next;
    
    public Node() {}
    
    public Node(int key, int val) {
        this.key = key;
        this.val = val;
    }
}

public class LRUCache {
    private int cap;
    private Map<Integer, Node> cache;
    private Node head, tail;
    
    public LRUCache(int capacity) {
        cap = capacity;
        cache = new HashMap<>();
        head = new Node();
        tail = new Node();
        head.next = tail;
        tail.prev = head;
    }
    
    private void addToHead(Node node) {
        node.prev = head;
        node.next = head.next;
        head.next.prev = node;
        head.next = node;
    }
    
    private void removeNode(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }
    
    private void moveToHead(Node node) {
        removeNode(node);
        addToHead(node);
    }
    
    private Node removeTail() {
        Node node = tail.prev;
        removeNode(node);
        return node;
    }
    
    public int get(int key) {
        Node node = cache.get(key);
        if (node != null) {
            moveToHead(node);
            return node.val;
        }
        return -1;
    }
    
    public void put(int key, int value) {
        Node node = cache.get(key);
        if (node != null) {
            node.val = value;
            moveToHead(node);
        } else {
            Node newNode = new Node(key, value);
            cache.put(key, newNode);
            addToHead(newNode);
            if (cache.size() > cap) {
                Node removed = removeTail();
                cache.remove(removed.key);
            }
        }
    }
    
    // 使用LinkedHashMap的简化版本
    static class SimpleLRUCache extends LinkedHashMap<Integer, Integer> {
        private int capacity;
        
        public SimpleLRUCache(int capacity) {
            super(capacity, 0.75f, true);
            this.capacity = capacity;
        }
        
        public int get(int key) {
            return super.getOrDefault(key, -1);
        }
        
        public void put(int key, int value) {
            super.put(key, value);
        }
        
        @Override
        protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
            return size() > capacity;
        }
    }
    
    public static void testLRUCache() {
        System.out.println("=== LRU缓存测试 ===");
        
        // 测试标准版本
        System.out.println("\n--- 标准版本测试 ---");
        LRUCache lru = new LRUCache(2);
        
        lru.put(1, 1);
        lru.put(2, 2);
        System.out.println("get(1): " + lru.get(1)); // 返回 1
        lru.put(3, 3); // 该操作会使得关键字 2 作废
        System.out.println("get(2): " + lru.get(2)); // 返回 -1 (未找到)
        lru.put(4, 4); // 该操作会使得关键字 1 作废
        System.out.println("get(1): " + lru.get(1)); // 返回 -1 (未找到)
        System.out.println("get(3): " + lru.get(3)); // 返回 3
        System.out.println("get(4): " + lru.get(4)); // 返回 4
        
        // 测试简化版本
        System.out.println("\n--- 简化版本测试 ---");
        SimpleLRUCache simpleLru = new SimpleLRUCache(2);
        
        simpleLru.put(1, 1);
        simpleLru.put(2, 2);
        System.out.println("get(1): " + simpleLru.get(1)); // 返回 1
        simpleLru.put(3, 3); // 该操作会使得关键字 2 作废
        System.out.println("get(2): " + simpleLru.get(2)); // 返回 -1 (未找到)
        simpleLru.put(4, 4); // 该操作会使得关键字 1 作废
        System.out.println("get(1): " + simpleLru.get(1)); // 返回 -1 (未找到)
        System.out.println("get(3): " + simpleLru.get(3)); // 返回 3
        System.out.println("get(4): " + simpleLru.get(4)); // 返回 4
        
        System.out.println("\n=== Java特性说明 ===");
        System.out.println("1. 面向对象: 类、继承、封装");
        System.out.println("2. 泛型: 类型安全的集合");
        System.out.println("3. 垃圾回收: 自动内存管理");
        System.out.println("4. HashMap: 高效的哈希表实现");
        System.out.println("5. LinkedHashMap: 保持插入顺序的哈希表");
    }
    
    public static void main(String[] args) {
        testLRUCache();
    }
}

/*
Java实现特点:

1. **面向对象**:
   - 强类型系统
   - 类和接口
   - 继承和多态

2. **内存管理**:
   - 自动垃圾回收
   - 堆内存管理
   - 引用类型

3. **集合框架**:
   - HashMap高效哈希表
   - LinkedHashMap保持顺序
   - 泛型提供类型安全

4. **平台无关**:
   - JVM虚拟机
   - 字节码执行
   - 跨平台兼容

5. **企业级特性**:
   - 强大的标准库
   - 丰富的第三方框架
   - 成熟的生态系统

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/