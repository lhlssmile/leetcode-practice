// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

class Node {
    constructor(key = 0, val = 0) {
        this.key = key;
        this.val = val;
        this.prev = null;
        this.next = null;
    }
}

class LRUCache {
    constructor(capacity) {
        this.cap = capacity;
        this.cache = new Map();
        this.head = new Node();
        this.tail = new Node();
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }
    
    addToHead(node) {
        node.prev = this.head;
        node.next = this.head.next;
        this.head.next.prev = node;
        this.head.next = node;
    }
    
    removeNode(node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }
    
    moveToHead(node) {
        this.removeNode(node);
        this.addToHead(node);
    }
    
    removeTail() {
        const node = this.tail.prev;
        this.removeNode(node);
        return node;
    }
    
    get(key) {
        if (this.cache.has(key)) {
            const node = this.cache.get(key);
            this.moveToHead(node);
            return node.val;
        }
        return -1;
    }
    
    put(key, value) {
        if (this.cache.has(key)) {
            const node = this.cache.get(key);
            node.val = value;
            this.moveToHead(node);
        } else {
            const node = new Node(key, value);
            this.cache.set(key, node);
            this.addToHead(node);
            if (this.cache.size > this.cap) {
                const removed = this.removeTail();
                this.cache.delete(removed.key);
            }
        }
    }
}

// 使用Map的简化版本（Map保持插入顺序）
class SimpleLRUCache {
    constructor(capacity) {
        this.capacity = capacity;
        this.cache = new Map();
    }
    
    get(key) {
        if (this.cache.has(key)) {
            const value = this.cache.get(key);
            // 删除后重新插入以更新顺序
            this.cache.delete(key);
            this.cache.set(key, value);
            return value;
        }
        return -1;
    }
    
    put(key, value) {
        if (this.cache.has(key)) {
            // 删除后重新插入以更新顺序
            this.cache.delete(key);
        } else if (this.cache.size >= this.capacity) {
            // 删除最旧的（第一个）
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        this.cache.set(key, value);
    }
}

// 函数式编程风格的实现
const createLRUCache = (capacity) => {
    let cache = new Map();
    
    const get = (key) => {
        if (cache.has(key)) {
            const value = cache.get(key);
            cache.delete(key);
            cache.set(key, value);
            return value;
        }
        return -1;
    };
    
    const put = (key, value) => {
        if (cache.has(key)) {
            cache.delete(key);
        } else if (cache.size >= capacity) {
            const firstKey = cache.keys().next().value;
            cache.delete(firstKey);
        }
        cache.set(key, value);
    };
    
    return { get, put };
};

function testLRUCache() {
    console.log("=== LRU缓存测试 ===");
    
    // 测试标准版本
    console.log("\n--- 标准版本测试 ---");
    const lru = new LRUCache(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    console.log(`get(1): ${lru.get(1)}`); // 返回 1
    lru.put(3, 3); // 该操作会使得关键字 2 作废
    console.log(`get(2): ${lru.get(2)}`); // 返回 -1 (未找到)
    lru.put(4, 4); // 该操作会使得关键字 1 作废
    console.log(`get(1): ${lru.get(1)}`); // 返回 -1 (未找到)
    console.log(`get(3): ${lru.get(3)}`); // 返回 3
    console.log(`get(4): ${lru.get(4)}`); // 返回 4
    
    // 测试简化版本
    console.log("\n--- 简化版本测试 ---");
    const simpleLru = new SimpleLRUCache(2);
    
    simpleLru.put(1, 1);
    simpleLru.put(2, 2);
    console.log(`get(1): ${simpleLru.get(1)}`); // 返回 1
    simpleLru.put(3, 3); // 该操作会使得关键字 2 作废
    console.log(`get(2): ${simpleLru.get(2)}`); // 返回 -1 (未找到)
    simpleLru.put(4, 4); // 该操作会使得关键字 1 作废
    console.log(`get(1): ${simpleLru.get(1)}`); // 返回 -1 (未找到)
    console.log(`get(3): ${simpleLru.get(3)}`); // 返回 3
    console.log(`get(4): ${simpleLru.get(4)}`); // 返回 4
    
    // 测试函数式版本
    console.log("\n--- 函数式版本测试 ---");
    const funcLru = createLRUCache(2);
    
    funcLru.put(1, 1);
    funcLru.put(2, 2);
    console.log(`get(1): ${funcLru.get(1)}`); // 返回 1
    funcLru.put(3, 3); // 该操作会使得关键字 2 作废
    console.log(`get(2): ${funcLru.get(2)}`); // 返回 -1 (未找到)
    funcLru.put(4, 4); // 该操作会使得关键字 1 作废
    console.log(`get(1): ${funcLru.get(1)}`); // 返回 -1 (未找到)
    console.log(`get(3): ${funcLru.get(3)}`); // 返回 3
    console.log(`get(4): ${funcLru.get(4)}`); // 返回 4
    
    console.log("\n=== JavaScript特性说明 ===");
    console.log("1. 动态类型: 运行时类型检查");
    console.log("2. 原型链: 基于原型的继承");
    console.log("3. 闭包: 函数式编程支持");
    console.log("4. Map对象: 键值对集合");
    console.log("5. ES6类: 面向对象语法糖");
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { LRUCache, SimpleLRUCache, createLRUCache, testLRUCache };
}

// 浏览器环境直接运行
if (typeof window !== 'undefined') {
    testLRUCache();
}

// Node.js环境运行
if (typeof require !== 'undefined' && require.main === module) {
    testLRUCache();
}

/*
JavaScript实现特点:

1. **动态特性**:
   - 动态类型系统
   - 运行时类型检查
   - 灵活的对象操作

2. **函数式编程**:
   - 一等函数
   - 闭包支持
   - 高阶函数

3. **面向对象**:
   - 基于原型的继承
   - ES6类语法
   - 方法链调用

4. **内置数据结构**:
   - Map保持插入顺序
   - 弱引用支持
   - 丰富的数组方法

5. **异步编程**:
   - Promise/async-await
   - 事件循环
   - 非阻塞I/O

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/