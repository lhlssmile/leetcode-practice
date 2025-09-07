# LeetCode 146: LRU缓存
# 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

class Node:
    def __init__(self, key=0, val=0):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.cache = {}
        self.head = Node()
        self.tail = Node()
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def add_to_head(self, node):
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node
    
    def remove_node(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev
    
    def move_to_head(self, node):
        self.remove_node(node)
        self.add_to_head(node)
    
    def remove_tail(self):
        node = self.tail.prev
        self.remove_node(node)
        return node
    
    def get(self, key: int) -> int:
        if key in self.cache:
            node = self.cache[key]
            self.move_to_head(node)
            return node.val
        return -1
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            node = self.cache[key]
            node.val = value
            self.move_to_head(node)
        else:
            node = Node(key, value)
            self.cache[key] = node
            self.add_to_head(node)
            if len(self.cache) > self.cap:
                removed = self.remove_tail()
                del self.cache[removed.key]

# 使用collections.OrderedDict的简化版本
from collections import OrderedDict

class SimpleLRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key: int) -> int:
        if key in self.cache:
            # 移动到末尾（最近使用）
            self.cache.move_to_end(key)
            return self.cache[key]
        return -1
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # 更新值并移动到末尾
            self.cache[key] = value
            self.cache.move_to_end(key)
        else:
            # 新增
            if len(self.cache) >= self.capacity:
                # 移除最旧的（第一个）
                self.cache.popitem(last=False)
            self.cache[key] = value

def test_lru_cache():
    print("=== LRU缓存测试 ===")
    
    # 测试标准版本
    print("\n--- 标准版本测试 ---")
    lru = LRUCache(2)
    
    lru.put(1, 1)
    lru.put(2, 2)
    print(f"get(1): {lru.get(1)}")  # 返回 1
    lru.put(3, 3)  # 该操作会使得关键字 2 作废
    print(f"get(2): {lru.get(2)}")  # 返回 -1 (未找到)
    lru.put(4, 4)  # 该操作会使得关键字 1 作废
    print(f"get(1): {lru.get(1)}")  # 返回 -1 (未找到)
    print(f"get(3): {lru.get(3)}")  # 返回 3
    print(f"get(4): {lru.get(4)}")  # 返回 4
    
    # 测试简化版本
    print("\n--- 简化版本测试 ---")
    simple_lru = SimpleLRUCache(2)
    
    simple_lru.put(1, 1)
    simple_lru.put(2, 2)
    print(f"get(1): {simple_lru.get(1)}")  # 返回 1
    simple_lru.put(3, 3)  # 该操作会使得关键字 2 作废
    print(f"get(2): {simple_lru.get(2)}")  # 返回 -1 (未找到)
    simple_lru.put(4, 4)  # 该操作会使得关键字 1 作废
    print(f"get(1): {simple_lru.get(1)}")  # 返回 -1 (未找到)
    print(f"get(3): {simple_lru.get(3)}")  # 返回 3
    print(f"get(4): {simple_lru.get(4)}")  # 返回 4
    
    print("\n=== Python特性说明 ===")
    print("1. 动态类型: 无需声明变量类型")
    print("2. 字典: 内置哈希表实现")
    print("3. 面向对象: 类和方法")
    print("4. 内存管理: 自动垃圾回收")
    print("5. OrderedDict: 保持插入顺序的字典")

if __name__ == "__main__":
    test_lru_cache()

"""
Python实现特点:

1. **简洁语法**:
   - 动态类型系统
   - 简洁的类定义
   - 内置数据结构

2. **内存管理**:
   - 自动垃圾回收
   - 引用计数
   - 无需手动内存管理

3. **数据结构**:
   - 内置字典（哈希表）
   - OrderedDict保持顺序
   - 灵活的对象系统

4. **面向对象**:
   - 类和继承
   - 方法和属性
   - 动态属性添加

5. **标准库**:
   - collections模块
   - 丰富的内置函数
   - 第三方库生态

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
"""