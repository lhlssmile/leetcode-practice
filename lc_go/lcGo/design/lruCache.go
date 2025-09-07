// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

package main

import (
	"fmt"
)

type Node struct {
	key, val   int
	prev, next *Node
}

type LRUCache struct {
	cap        int
	cache      map[int]*Node
	head, tail *Node
}

func Constructor(capacity int) LRUCache {
	head, tail := &Node{}, &Node{}
	head.next = tail
	tail.prev = head
	return LRUCache{
		cap:   capacity,
		cache: make(map[int]*Node),
		head:  head,
		tail:  tail,
	}
}

func (this *LRUCache) Get(key int) int {
	if node, ok := this.cache[key]; ok {
		this.moveToHead(node)
		return node.val
	}
	return -1
}

func (this *LRUCache) Put(key int, value int) {
	if node, ok := this.cache[key]; ok {
		node.val = value
		this.moveToHead(node)
	} else {
		node := &Node{key: key, val: value}
		this.cache[key] = node
		this.addToHead(node)
		if len(this.cache) > this.cap {
			removed := this.removeTail()
			delete(this.cache, removed.key)
		}
	}
}

func (this *LRUCache) addToHead(node *Node) {
	node.prev = this.head
	node.next = this.head.next
	this.head.next.prev = node
	this.head.next = node
}

func (this *LRUCache) removeNode(node *Node) {
	node.prev.next = node.next
	node.next.prev = node.prev
}

func (this *LRUCache) moveToHead(node *Node) {
	this.removeNode(node)
	this.addToHead(node)
}

func (this *LRUCache) removeTail() *Node {
	node := this.tail.prev
	this.removeNode(node)
	return node
}

// 使用切片的简化版本
type SimpleLRUCache struct {
	capacity int
	keys     []int
	values   map[int]int
}

func NewSimpleLRUCache(capacity int) *SimpleLRUCache {
	return &SimpleLRUCache{
		capacity: capacity,
		keys:     make([]int, 0),
		values:   make(map[int]int),
	}
}

func (this *SimpleLRUCache) Get(key int) int {
	if val, ok := this.values[key]; ok {
		// 移动到最前面
		for i, k := range this.keys {
			if k == key {
				// 删除当前位置
				this.keys = append(this.keys[:i], this.keys[i+1:]...)
				break
			}
		}
		// 插入到最前面
		this.keys = append([]int{key}, this.keys...)
		return val
	}
	return -1
}

func (this *SimpleLRUCache) Put(key int, value int) {
	if _, ok := this.values[key]; ok {
		// 更新值并移动到最前面
		this.values[key] = value
		for i, k := range this.keys {
			if k == key {
				// 删除当前位置
				this.keys = append(this.keys[:i], this.keys[i+1:]...)
				break
			}
		}
		// 插入到最前面
		this.keys = append([]int{key}, this.keys...)
	} else {
		// 新增
		if len(this.keys) >= this.capacity {
			// 移除最后一个
			lastKey := this.keys[len(this.keys)-1]
			this.keys = this.keys[:len(this.keys)-1]
			delete(this.values, lastKey)
		}
		// 插入到最前面
		this.keys = append([]int{key}, this.keys...)
		this.values[key] = value
	}
}

func testLRUCache() {
	fmt.Println("=== LRU缓存测试 ===")
	
	// 测试标准版本
	fmt.Println("\n--- 标准版本测试 ---")
	lru := Constructor(2)
	
	lru.Put(1, 1)
	lru.Put(2, 2)
	fmt.Printf("get(1): %d\n", lru.Get(1)) // 返回 1
	lru.Put(3, 3)                          // 该操作会使得关键字 2 作废
	fmt.Printf("get(2): %d\n", lru.Get(2)) // 返回 -1 (未找到)
	lru.Put(4, 4)                          // 该操作会使得关键字 1 作废
	fmt.Printf("get(1): %d\n", lru.Get(1)) // 返回 -1 (未找到)
	fmt.Printf("get(3): %d\n", lru.Get(3)) // 返回 3
	fmt.Printf("get(4): %d\n", lru.Get(4)) // 返回 4
	
	// 测试简化版本
	fmt.Println("\n--- 简化版本测试 ---")
	simpleLru := NewSimpleLRUCache(2)
	
	simpleLru.Put(1, 1)
	simpleLru.Put(2, 2)
	fmt.Printf("get(1): %d\n", simpleLru.Get(1)) // 返回 1
	simpleLru.Put(3, 3)                           // 该操作会使得关键字 2 作废
	fmt.Printf("get(2): %d\n", simpleLru.Get(2)) // 返回 -1 (未找到)
	simpleLru.Put(4, 4)                           // 该操作会使得关键字 1 作废
	fmt.Printf("get(1): %d\n", simpleLru.Get(1)) // 返回 -1 (未找到)
	fmt.Printf("get(3): %d\n", simpleLru.Get(3)) // 返回 3
	fmt.Printf("get(4): %d\n", simpleLru.Get(4)) // 返回 4
	
	fmt.Println("\n=== Go语言特性说明 ===")
	fmt.Println("1. 静态类型: 编译时类型检查")
	fmt.Println("2. 垃圾回收: 自动内存管理")
	fmt.Println("3. 指针: 高效的内存访问")
	fmt.Println("4. 切片和映射: 内置数据结构")
	fmt.Println("5. 方法接收者: 面向对象特性")
}

func main() {
	testLRUCache()
}

/*
Go语言实现特点:

1. **简洁语法**:
   - 简洁的语法结构
   - 类型推断
   - 无需分号

2. **内存管理**:
   - 垃圾回收器
   - 指针但无指针运算
   - 内存安全

3. **并发支持**:
   - goroutine轻量级线程
   - channel通信机制
   - 内置并发原语

4. **性能特点**:
   - 编译型语言
   - 快速编译
   - 高效执行

5. **标准库**:
   - 丰富的标准库
   - 内置数据结构
   - 网络编程支持

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/