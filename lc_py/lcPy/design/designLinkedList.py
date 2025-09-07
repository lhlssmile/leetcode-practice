# LeetCode 707: 设计链表
# 设计链表的实现。您可以选择使用单链表或双链表。

from typing import Optional, List, Any
from collections import deque
import weakref

class ListNode:
    """双向链表节点"""
    def __init__(self, val: int = 0):
        self.val = val
        self.prev: Optional['ListNode'] = None
        self.next: Optional['ListNode'] = None
    
    def __repr__(self):
        return f"ListNode({self.val})"

class MyLinkedList:
    """双向链表实现"""
    
    def __init__(self):
        """初始化链表，使用哨兵节点"""
        self.head = ListNode()  # 哨兵头节点
        self.tail = ListNode()  # 哨兵尾节点
        self.head.next = self.tail
        self.tail.prev = self.head
        self.size = 0
    
    def get(self, index: int) -> int:
        """获取链表中第 index 个节点的值"""
        if index < 0 or index >= self.size:
            return -1
        
        current = self.head.next
        for _ in range(index):
            current = current.next
        return current.val
    
    def addAtHead(self, val: int) -> None:
        """在链表第一个元素之前添加一个值为 val 的节点"""
        self.addAtIndex(0, val)
    
    def addAtTail(self, val: int) -> None:
        """将值为 val 的节点追加到链表的最后一个元素"""
        self.addAtIndex(self.size, val)
    
    def addAtIndex(self, index: int, val: int) -> None:
        """在链表中的第 index 个节点之前添加值为 val 的节点"""
        if index < 0 or index > self.size:
            return
        
        pred = self.head
        for _ in range(index):
            pred = pred.next
        
        succ = pred.next
        new_node = ListNode(val)
        
        new_node.prev = pred
        new_node.next = succ
        pred.next = new_node
        succ.prev = new_node
        
        self.size += 1
    
    def deleteAtIndex(self, index: int) -> None:
        """如果索引 index 有效，则删除链表中的第 index 个节点"""
        if index < 0 or index >= self.size:
            return
        
        pred = self.head
        for _ in range(index):
            pred = pred.next
        
        to_delete = pred.next
        succ = to_delete.next
        
        pred.next = succ
        succ.prev = pred
        
        self.size -= 1
    
    def __str__(self) -> str:
        """字符串表示"""
        result = []
        current = self.head.next
        while current != self.tail:
            result.append(str(current.val))
            current = current.next
        return f"[{', '.join(result)}]"
    
    def __len__(self) -> int:
        """返回链表长度"""
        return self.size
    
    def to_list(self) -> List[int]:
        """转换为Python列表"""
        result = []
        current = self.head.next
        while current != self.tail:
            result.append(current.val)
            current = current.next
        return result

class ListLinkedList:
    """使用Python列表实现的链表"""
    
    def __init__(self):
        self.data = []
    
    def get(self, index: int) -> int:
        if 0 <= index < len(self.data):
            return self.data[index]
        return -1
    
    def addAtHead(self, val: int) -> None:
        self.data.insert(0, val)
    
    def addAtTail(self, val: int) -> None:
        self.data.append(val)
    
    def addAtIndex(self, index: int, val: int) -> None:
        if 0 <= index <= len(self.data):
            self.data.insert(index, val)
    
    def deleteAtIndex(self, index: int) -> None:
        if 0 <= index < len(self.data):
            self.data.pop(index)
    
    def __str__(self) -> str:
        return str(self.data)

class DequeLinkedList:
    """使用collections.deque实现的链表"""
    
    def __init__(self):
        self.data = deque()
    
    def get(self, index: int) -> int:
        if 0 <= index < len(self.data):
            return self.data[index]
        return -1
    
    def addAtHead(self, val: int) -> None:
        self.data.appendleft(val)
    
    def addAtTail(self, val: int) -> None:
        self.data.append(val)
    
    def addAtIndex(self, index: int, val: int) -> None:
        if 0 <= index <= len(self.data):
            self.data.insert(index, val)
    
    def deleteAtIndex(self, index: int) -> None:
        if 0 <= index < len(self.data):
            del self.data[index]
    
    def __str__(self) -> str:
        return str(list(self.data))

class SinglyListNode:
    """单链表节点"""
    def __init__(self, val: int = 0):
        self.val = val
        self.next: Optional['SinglyListNode'] = None

class SinglyLinkedList:
    """单链表实现"""
    
    def __init__(self):
        self.head = SinglyListNode()  # 哨兵节点
        self.size = 0
    
    def get(self, index: int) -> int:
        if index < 0 or index >= self.size:
            return -1
        
        current = self.head.next
        for _ in range(index):
            current = current.next
        return current.val
    
    def addAtHead(self, val: int) -> None:
        self.addAtIndex(0, val)
    
    def addAtTail(self, val: int) -> None:
        self.addAtIndex(self.size, val)
    
    def addAtIndex(self, index: int, val: int) -> None:
        if index < 0 or index > self.size:
            return
        
        pred = self.head
        for _ in range(index):
            pred = pred.next
        
        new_node = SinglyListNode(val)
        new_node.next = pred.next
        pred.next = new_node
        
        self.size += 1
    
    def deleteAtIndex(self, index: int) -> None:
        if index < 0 or index >= self.size:
            return
        
        pred = self.head
        for _ in range(index):
            pred = pred.next
        
        pred.next = pred.next.next
        self.size -= 1

class FunctionalLinkedList:
    """函数式编程风格的链表"""
    
    def __init__(self):
        self.data = []
    
    def get(self, index: int) -> int:
        return self.data[index] if 0 <= index < len(self.data) else -1
    
    def addAtHead(self, val: int) -> None:
        self.data = [val] + self.data
    
    def addAtTail(self, val: int) -> None:
        self.data = self.data + [val]
    
    def addAtIndex(self, index: int, val: int) -> None:
        if 0 <= index <= len(self.data):
            self.data = self.data[:index] + [val] + self.data[index:]
    
    def deleteAtIndex(self, index: int) -> None:
        if 0 <= index < len(self.data):
            self.data = self.data[:index] + self.data[index + 1:]
    
    def __str__(self) -> str:
        return str(self.data)

class GenericLinkedList:
    """泛型链表实现"""
    
    def __init__(self, data_type: type = int):
        self.data_type = data_type
        self.data = []
    
    def get(self, index: int) -> Any:
        if 0 <= index < len(self.data):
            return self.data[index]
        return None
    
    def add(self, index: int, val: Any) -> None:
        if not isinstance(val, self.data_type):
            raise TypeError(f"Expected {self.data_type}, got {type(val)}")
        
        if 0 <= index <= len(self.data):
            self.data.insert(index, val)
    
    def delete(self, index: int) -> None:
        if 0 <= index < len(self.data):
            self.data.pop(index)
    
    def __str__(self) -> str:
        return f"{self.data_type.__name__}LinkedList{self.data}"

def linked_list_operations(operations: List[tuple]) -> List[Optional[int]]:
    """函数式操作链表"""
    obj = MyLinkedList()
    results = []
    
    for op, *params in operations:
        if op == "get":
            results.append(obj.get(params[0]))
        elif op == "addAtHead":
            obj.addAtHead(params[0])
            results.append(None)
        elif op == "addAtTail":
            obj.addAtTail(params[0])
            results.append(None)
        elif op == "addAtIndex":
            obj.addAtIndex(params[0], params[1])
            results.append(None)
        elif op == "deleteAtIndex":
            obj.deleteAtIndex(params[0])
            results.append(None)
        else:
            results.append(None)
    
    return results

def test_design_linked_list():
    """测试设计链表"""
    print("=== 设计链表测试 ===")
    
    # 测试双向链表实现
    print("\n--- 双向链表实现测试 ---")
    linked_list = MyLinkedList()
    
    linked_list.addAtHead(7)
    linked_list.addAtHead(2)
    linked_list.addAtHead(1)
    print(f"添加头部元素后: {linked_list}")
    
    linked_list.addAtIndex(3, 0)
    print(f"在索引3添加0后: {linked_list}")
    
    linked_list.deleteAtIndex(2)
    print(f"删除索引2后: {linked_list}")
    
    linked_list.addAtHead(6)
    print(f"添加头部6后: {linked_list}")
    
    linked_list.addAtTail(4)
    print(f"添加尾部4后: {linked_list}")
    
    print(f"获取索引5: {linked_list.get(5)}")  # -1
    print(f"获取索引3: {linked_list.get(3)}")  # 0
    print(f"获取索引2: {linked_list.get(2)}")  # 2
    print(f"获取索引0: {linked_list.get(0)}")  # 6
    
    linked_list.deleteAtIndex(0)
    print(f"删除索引0后，获取索引0: {linked_list.get(0)}")  # 1
    
    # 测试列表实现
    print("\n--- 列表实现测试 ---")
    list_impl = ListLinkedList()
    list_impl.addAtHead(1)
    list_impl.addAtTail(3)
    list_impl.addAtIndex(1, 2)
    print(f"列表实现操作后: {list_impl}")
    print(f"获取索引1: {list_impl.get(1)}")  # 2
    
    list_impl.deleteAtIndex(1)
    print(f"删除索引1后: {list_impl}")
    print(f"获取索引1: {list_impl.get(1)}")  # 3
    
    # 测试deque实现
    print("\n--- Deque实现测试 ---")
    deque_impl = DequeLinkedList()
    deque_impl.addAtHead(1)
    deque_impl.addAtTail(3)
    deque_impl.addAtIndex(1, 2)
    print(f"Deque实现操作后: {deque_impl}")
    print(f"获取索引1: {deque_impl.get(1)}")  # 2
    
    # 测试单链表实现
    print("\n--- 单链表实现测试 ---")
    singly_list = SinglyLinkedList()
    singly_list.addAtHead(1)
    singly_list.addAtTail(3)
    singly_list.addAtIndex(1, 2)
    print(f"单链表实现操作后: [1, 2, 3]")
    print(f"获取索引1: {singly_list.get(1)}")  # 2
    
    # 测试函数式实现
    print("\n--- 函数式实现测试 ---")
    func_list = FunctionalLinkedList()
    func_list.addAtHead(1)
    func_list.addAtTail(3)
    func_list.addAtIndex(1, 2)
    print(f"函数式实现操作后: {func_list}")
    print(f"获取索引1: {func_list.get(1)}")  # 2
    
    # 测试泛型实现
    print("\n--- 泛型实现测试 ---")
    str_list = GenericLinkedList(str)
    str_list.add(0, "Hello")
    str_list.add(1, "World")
    print(f"泛型实现(字符串): {str_list}")
    print(f"获取索引0: {str_list.get(0)}")  # Hello
    
    # 测试函数式操作
    print("\n--- 函数式操作测试 ---")
    operations = [
        ("addAtHead", 7),
        ("addAtHead", 2),
        ("addAtHead", 1),
        ("addAtIndex", 3, 0),
        ("deleteAtIndex", 2),
        ("addAtHead", 6),
        ("addAtTail", 4),
        ("get", 4),
        ("addAtHead", 4),
        ("addAtIndex", 5, 0),
        ("addAtHead", 6),
    ]
    
    results = linked_list_operations(operations)
    print(f"函数式操作结果: {results}")
    
    # 性能比较
    print("\n--- 性能特性比较 ---")
    print("双向链表: 插入删除O(1)，查找O(n)")
    print("列表实现: 尾部操作O(1)，其他O(n)")
    print("Deque实现: 两端操作O(1)，中间O(n)")
    print("单链表: 插入删除O(1)，查找O(n)")
    
    print("\n=== Python特性说明 ===")
    print("1. 动态类型: 运行时类型检查")
    print("2. 自动垃圾回收: 无需手动内存管理")
    print("3. 列表和deque: 高效的内置数据结构")
    print("4. 类型提示: 增强代码可读性")
    print("5. 魔术方法: __str__, __len__等特殊方法")
    print("6. 函数式编程: 支持函数式操作")

if __name__ == "__main__":
    test_design_linked_list()

"""
Python实现特点:

1. **动态类型系统**:
   - 运行时类型检查
   - 类型提示增强可读性
   - 灵活的数据处理

2. **自动内存管理**:
   - 垃圾回收机制
   - 引用计数
   - 无需手动释放内存

3. **丰富的内置数据结构**:
   - list动态数组
   - deque双端队列
   - 高效的操作方法

4. **面向对象特性**:
   - 类和继承
   - 魔术方法
   - 属性装饰器

5. **函数式编程**:
   - 高阶函数
   - Lambda表达式
   - 列表推导式

6. **代码简洁性**:
   - 简洁的语法
   - 强大的标准库
   - 易于阅读和维护

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
"""