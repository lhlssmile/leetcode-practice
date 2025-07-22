'''
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

 

示例：

输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
 

提示：

1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 105
最多调用 2 * 105 次 get 和 put
'''
# 方法1：使用OrderedDict（最简洁）
from collections import OrderedDict

class LRUCache_OrderedDict:
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
            # 检查容量
            if len(self.cache) >= self.capacity:
                # 删除最久未使用的（第一个）
                self.cache.popitem(last=False)
            self.cache[key] = value

# 方法2：自定义双向链表 + 哈希表（经典实现）
class DLinkedNode:
    def __init__(self, key=0, value=0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class LRUCache_LinkedList:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}  # key -> node
        
        # 创建虚拟头尾节点
        self.head = DLinkedNode()
        self.tail = DLinkedNode()
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _add_node(self, node):
        """在头部添加节点"""
        node.prev = self.head
        node.next = self.head.next
        
        self.head.next.prev = node
        self.head.next = node
    
    def _remove_node(self, node):
        """移除节点"""
        prev_node = node.prev
        next_node = node.next
        
        prev_node.next = next_node
        next_node.prev = prev_node
    
    def _move_to_head(self, node):
        """移动节点到头部"""
        self._remove_node(node)
        self._add_node(node)
    
    def _pop_tail(self):
        """删除尾部节点"""
        last_node = self.tail.prev
        self._remove_node(last_node)
        return last_node
    
    def get(self, key: int) -> int:
        node = self.cache.get(key)
        if node:
            # 移动到头部
            self._move_to_head(node)
            return node.value
        return -1
    
    def put(self, key: int, value: int) -> None:
        node = self.cache.get(key)
        
        if node:
            # 更新值并移动到头部
            node.value = value
            self._move_to_head(node)
        else:
            new_node = DLinkedNode(key, value)
            
            if len(self.cache) >= self.capacity:
                # 删除尾部节点
                tail = self._pop_tail()
                del self.cache[tail.key]
            
            # 添加新节点
            self.cache[key] = new_node
            self._add_node(new_node)

# 方法3：使用collections.deque（你提到的方案）
from collections import deque

class LRUCache_Deque:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}  # key -> value
        self.order = deque()  # 存储key的使用顺序
    
    def get(self, key: int) -> int:
        if key in self.cache:
            # 更新使用顺序
            self.order.remove(key)  # O(n) 操作！
            self.order.append(key)
            return self.cache[key]
        return -1
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # 更新值和顺序
            self.cache[key] = value
            self.order.remove(key)  # O(n) 操作！
            self.order.append(key)
        else:
            if len(self.cache) >= self.capacity:
                # 删除最久未使用的
                oldest = self.order.popleft()
                del self.cache[oldest]
            
            self.cache[key] = value
            self.order.append(key)

# 主类（推荐使用OrderedDict）
class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key: int) -> int:
        if key in self.cache:
            self.cache.move_to_end(key)
            return self.cache[key]
        return -1
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache[key] = value
            self.cache.move_to_end(key)
        else:
            if len(self.cache) >= self.capacity:
                self.cache.popitem(last=False)
            self.cache[key] = value

if __name__ == '__main__':
    # 测试用例
    print("=== LRU缓存测试 ===")
    
    # 测试OrderedDict实现
    print("\n1. OrderedDict实现:")
    lru1 = LRUCache_OrderedDict(2)
    lru1.put(1, 1)
    lru1.put(2, 2)
    print(f"get(1): {lru1.get(1)}")  # 返回 1
    lru1.put(3, 3)  # 该操作会使得关键字 2 作废
    print(f"get(2): {lru1.get(2)}")  # 返回 -1 (未找到)
    lru1.put(4, 4)  # 该操作会使得关键字 1 作废
    print(f"get(1): {lru1.get(1)}")  # 返回 -1 (未找到)
    print(f"get(3): {lru1.get(3)}")  # 返回 3
    print(f"get(4): {lru1.get(4)}")  # 返回 4
    
    # 测试双向链表实现
    print("\n2. 双向链表实现:")
    lru2 = LRUCache_LinkedList(2)
    lru2.put(1, 1)
    lru2.put(2, 2)
    print(f"get(1): {lru2.get(1)}")  # 返回 1
    lru2.put(3, 3)
    print(f"get(2): {lru2.get(2)}")  # 返回 -1
    lru2.put(4, 4)
    print(f"get(1): {lru2.get(1)}")  # 返回 -1
    print(f"get(3): {lru2.get(3)}")  # 返回 3
    print(f"get(4): {lru2.get(4)}")  # 返回 4
    
    # 测试Deque实现（注意：这个实现不是真正的O(1)）
    print("\n3. Deque实现（注意：remove操作是O(n)）:")
    lru3 = LRUCache_Deque(2)
    lru3.put(1, 1)
    lru3.put(2, 2)
    print(f"get(1): {lru3.get(1)}")  # 返回 1
    lru3.put(3, 3)
    print(f"get(2): {lru3.get(2)}")  # 返回 -1
    lru3.put(4, 4)
    print(f"get(1): {lru3.get(1)}")  # 返回 -1
    print(f"get(3): {lru3.get(3)}")  # 返回 3
    print(f"get(4): {lru3.get(4)}")  # 返回 4

"""
=== LRU缓存算法分析与解题思路 ===

【题目核心】
LRU (Least Recently Used) 最近最少使用缓存淘汰算法
- 当缓存满时，删除最久未使用的数据
- 要求get和put操作都是O(1)时间复杂度

【关键洞察】
要实现O(1)的get和put，需要：
1. O(1)查找：哈希表
2. O(1)插入/删除：双向链表
3. O(1)移动到最新位置：双向链表的节点移动

【三种实现方案对比】

1. OrderedDict实现（推荐）
   核心思想：Python内置的有序字典，底层就是hash+双向链表
   优点：
   - 代码简洁，易于理解和维护
   - 性能优秀，底层C实现
   - move_to_end()和popitem()都是O(1)
   缺点：
   - 依赖Python特定库
   - 面试时可能要求手动实现
   时间复杂度：get O(1), put O(1)
   空间复杂度：O(capacity)

2. 自定义双向链表+哈希表（经典）
   核心思想：
   - 哈希表：key -> 链表节点，实现O(1)查找
   - 双向链表：维护使用顺序，头部=最新，尾部=最旧
   - 虚拟头尾节点：简化边界处理
   优点：
   - 完全自主实现，面试友好
   - 真正的O(1)操作
   - 逻辑清晰，易于扩展
   缺点：
   - 代码量大，容易出错
   - 需要仔细处理指针操作
   时间复杂度：get O(1), put O(1)
   空间复杂度：O(capacity)

3. Deque+哈希表实现（不推荐）
   核心思想：
   - 哈希表：key -> value
   - deque：维护key的使用顺序
   优点：
   - 思路直观，容易想到
   - 利用现有数据结构
   缺点：
   - deque.remove()是O(n)操作！
   - 不满足题目O(1)要求
   - 性能差，不适用于大数据
   时间复杂度：get O(n), put O(n)  # 因为remove操作
   空间复杂度：O(capacity)

【为什么Deque方案不是真正的O(1)？】
你的直觉很对，deque确实可以O(1)地在两端插入删除。
但LRU的关键问题是：当访问中间某个元素时，需要将它移动到"最新"位置。
- deque.remove(key)需要遍历整个deque找到key，这是O(n)操作
- 这就是为什么需要双向链表：可以直接通过节点指针O(1)删除任意位置的节点

【LRU与操作系统的关系】
是的！这确实是OS中的经典算法：
- 页面置换算法：当物理内存满时，选择最久未使用的页面换出
- 缓存管理：CPU缓存、文件系统缓存等都使用LRU策略
- 数据库缓冲池：MySQL的InnoDB引擎使用改进的LRU算法

【关键技巧总结】
1. 数据结构选择：
   - 单独的哈希表：查找O(1)，但无法维护顺序
   - 单独的链表：有序，但查找O(n)
   - 组合使用：哈希表+双向链表 = 查找O(1) + 有序O(1)

2. 双向链表的优势：
   - 可以O(1)删除任意节点（如果有节点指针）
   - 可以O(1)在任意位置插入
   - 虚拟头尾节点简化边界处理

3. 设计模式：
   - 头部 = 最新使用
   - 尾部 = 最久未使用
   - 访问时移动到头部
   - 淘汰时删除尾部

【复杂度分析】
最优解法（OrderedDict或自定义双向链表）：
- 时间复杂度：O(1) for both get and put
- 空间复杂度：O(capacity)
- 实际应用中OrderedDict性能更好（C实现）

【扩展思考】
1. LFU (Least Frequently Used)：需要额外维护访问频率
2. 时间窗口LRU：结合时间戳的改进版本
3. 分布式LRU：多机环境下的缓存一致性
4. 近似LRU：用更简单的数据结构实现近似效果

【面试建议】
1. 先说思路：hash+双向链表的组合
2. 画图解释：展示节点移动过程
3. 代码实现：推荐自定义双向链表（展示基础功底）
4. 优化讨论：提到OrderedDict的存在
5. 扩展应用：联系操作系统和数据库
"""