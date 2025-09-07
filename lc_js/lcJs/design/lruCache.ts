// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

class Node {
    key: number;
    val: number;
    prev: Node | null;
    next: Node | null;
    
    constructor(key: number = 0, val: number = 0) {
        this.key = key;
        this.val = val;
        this.prev = null;
        this.next = null;
    }
}

class LRUCache {
    private cap: number;
    private cache: Map<number, Node>;
    private head: Node;
    private tail: Node;
    
    constructor(capacity: number) {
        this.cap = capacity;
        this.cache = new Map<number, Node>();
        this.head = new Node();
        this.tail = new Node();
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }
    
    private addToHead(node: Node): void {
        node.prev = this.head;
        node.next = this.head.next;
        this.head.next!.prev = node;
        this.head.next = node;
    }
    
    private removeNode(node: Node): void {
        node.prev!.next = node.next;
        node.next!.prev = node.prev;
    }
    
    private moveToHead(node: Node): void {
        this.removeNode(node);
        this.addToHead(node);
    }
    
    private removeTail(): Node {
        const node = this.tail.prev!;
        this.removeNode(node);
        return node;
    }
    
    get(key: number): number {
        const node = this.cache.get(key);
        if (node) {
            this.moveToHead(node);
            return node.val;
        }
        return -1;
    }
    
    put(key: number, value: number): void {
        const node = this.cache.get(key);
        if (node) {
            node.val = value;
            this.moveToHead(node);
        } else {
            const newNode = new Node(key, value);
            this.cache.set(key, newNode);
            this.addToHead(newNode);
            if (this.cache.size > this.cap) {
                const removed = this.removeTail();
                this.cache.delete(removed.key);
            }
        }
    }
}

// 泛型版本的LRU缓存
class GenericLRUCache<K, V> {
    private capacity: number;
    private cache: Map<K, V>;
    
    constructor(capacity: number) {
        this.capacity = capacity;
        this.cache = new Map<K, V>();
    }
    
    get(key: K): V | undefined {
        if (this.cache.has(key)) {
            const value = this.cache.get(key)!;
            // 删除后重新插入以更新顺序
            this.cache.delete(key);
            this.cache.set(key, value);
            return value;
        }
        return undefined;
    }
    
    put(key: K, value: V): void {
        if (this.cache.has(key)) {
            this.cache.delete(key);
        } else if (this.cache.size >= this.capacity) {
            // 删除最旧的（第一个）
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        this.cache.set(key, value);
    }
    
    has(key: K): boolean {
        return this.cache.has(key);
    }
    
    size(): number {
        return this.cache.size;
    }
    
    clear(): void {
        this.cache.clear();
    }
}

// 接口定义
interface ILRUCache<K, V> {
    get(key: K): V | undefined;
    put(key: K, value: V): void;
    has(key: K): boolean;
    size(): number;
    clear(): void;
}

// 实现接口的类
class TypedLRUCache<K, V> implements ILRUCache<K, V> {
    private capacity: number;
    private cache: Map<K, V>;
    
    constructor(capacity: number) {
        this.capacity = capacity;
        this.cache = new Map<K, V>();
    }
    
    get(key: K): V | undefined {
        if (this.cache.has(key)) {
            const value = this.cache.get(key)!;
            this.cache.delete(key);
            this.cache.set(key, value);
            return value;
        }
        return undefined;
    }
    
    put(key: K, value: V): void {
        if (this.cache.has(key)) {
            this.cache.delete(key);
        } else if (this.cache.size >= this.capacity) {
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        this.cache.set(key, value);
    }
    
    has(key: K): boolean {
        return this.cache.has(key);
    }
    
    size(): number {
        return this.cache.size;
    }
    
    clear(): void {
        this.cache.clear();
    }
}

// 类型别名
type CacheEntry<T> = {
    key: string;
    value: T;
    timestamp: number;
};

// 带过期时间的LRU缓存
class TTLLRUCache<T> {
    private capacity: number;
    private ttl: number;
    private cache: Map<string, CacheEntry<T>>;
    
    constructor(capacity: number, ttl: number = 60000) {
        this.capacity = capacity;
        this.ttl = ttl;
        this.cache = new Map<string, CacheEntry<T>>();
    }
    
    get(key: string): T | undefined {
        const entry = this.cache.get(key);
        if (entry) {
            if (Date.now() - entry.timestamp > this.ttl) {
                this.cache.delete(key);
                return undefined;
            }
            // 更新访问时间并移动到最后
            entry.timestamp = Date.now();
            this.cache.delete(key);
            this.cache.set(key, entry);
            return entry.value;
        }
        return undefined;
    }
    
    put(key: string, value: T): void {
        const entry: CacheEntry<T> = {
            key,
            value,
            timestamp: Date.now()
        };
        
        if (this.cache.has(key)) {
            this.cache.delete(key);
        } else if (this.cache.size >= this.capacity) {
            const firstKey = this.cache.keys().next().value;
            this.cache.delete(firstKey);
        }
        
        this.cache.set(key, entry);
    }
}

function testLRUCache(): void {
    console.log("=== LRU缓存测试 ===");
    
    // 测试标准版本
    console.log("\n--- 标准版本测试 ---");
    const lru: LRUCache = new LRUCache(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    console.log(`get(1): ${lru.get(1)}`); // 返回 1
    lru.put(3, 3); // 该操作会使得关键字 2 作废
    console.log(`get(2): ${lru.get(2)}`); // 返回 -1 (未找到)
    lru.put(4, 4); // 该操作会使得关键字 1 作废
    console.log(`get(1): ${lru.get(1)}`); // 返回 -1 (未找到)
    console.log(`get(3): ${lru.get(3)}`); // 返回 3
    console.log(`get(4): ${lru.get(4)}`); // 返回 4
    
    // 测试泛型版本
    console.log("\n--- 泛型版本测试 ---");
    const genericLru: GenericLRUCache<string, number> = new GenericLRUCache<string, number>(2);
    
    genericLru.put("a", 1);
    genericLru.put("b", 2);
    console.log(`get("a"): ${genericLru.get("a")}`); // 返回 1
    genericLru.put("c", 3); // 该操作会使得关键字 "b" 作废
    console.log(`get("b"): ${genericLru.get("b")}`); // 返回 undefined
    
    // 测试TTL版本
    console.log("\n--- TTL版本测试 ---");
    const ttlLru: TTLLRUCache<string> = new TTLLRUCache<string>(2, 1000);
    
    ttlLru.put("key1", "value1");
    console.log(`get("key1"): ${ttlLru.get("key1")}`); // 返回 "value1"
    
    console.log("\n=== TypeScript特性说明 ===");
    console.log("1. 静态类型: 编译时类型检查");
    console.log("2. 泛型: 类型安全的代码复用");
    console.log("3. 接口: 契约定义");
    console.log("4. 类型别名: 复杂类型简化");
    console.log("5. 可选属性: 灵活的类型定义");
}

// 导出
export {
    LRUCache,
    GenericLRUCache,
    TypedLRUCache,
    TTLLRUCache,
    ILRUCache,
    CacheEntry,
    testLRUCache
};

// 默认导出
export default LRUCache;

// 如果在Node.js环境中直接运行
if (typeof require !== 'undefined' && require.main === module) {
    testLRUCache();
}

/*
TypeScript实现特点:

1. **静态类型系统**:
   - 编译时类型检查
   - 类型推断
   - 严格的类型安全

2. **面向对象特性**:
   - 类和接口
   - 继承和多态
   - 访问修饰符

3. **泛型编程**:
   - 类型参数
   - 约束泛型
   - 类型安全的代码复用

4. **高级类型**:
   - 联合类型
   - 交叉类型
   - 条件类型

5. **模块系统**:
   - ES6模块
   - 命名空间
   - 声明合并

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/