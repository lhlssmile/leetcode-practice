// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

package main

import (
	"fmt"
	"strconv"
	"strings"
)

// ListNode 双向链表节点
type ListNode struct {
	val  int
	prev *ListNode
	next *ListNode
}

// NewListNode 创建新节点
func NewListNode(val int) *ListNode {
	return &ListNode{
		val:  val,
		prev: nil,
		next: nil,
	}
}

// MyLinkedList 双向链表实现
type MyLinkedList struct {
	head *ListNode
	tail *ListNode
	size int
}

// Constructor 构造函数
func Constructor() MyLinkedList {
	head := NewListNode(0) // 哨兵头节点
	tail := NewListNode(0) // 哨兵尾节点
	head.next = tail
	tail.prev = head
	return MyLinkedList{
		head: head,
		tail: tail,
		size: 0,
	}
}

// Get 获取链表中第 index 个节点的值
func (this *MyLinkedList) Get(index int) int {
	if index < 0 || index >= this.size {
		return -1
	}
	
	cur := this.head.next
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	return cur.val
}

// AddAtHead 在链表第一个元素之前添加一个值为 val 的节点
func (this *MyLinkedList) AddAtHead(val int) {
	this.AddAtIndex(0, val)
}

// AddAtTail 将值为 val 的节点追加到链表的最后一个元素
func (this *MyLinkedList) AddAtTail(val int) {
	this.AddAtIndex(this.size, val)
}

// AddAtIndex 在链表中的第 index 个节点之前添加值为 val 的节点
func (this *MyLinkedList) AddAtIndex(index int, val int) {
	if index < 0 || index > this.size {
		return
	}
	
	pred := this.head
	for i := 0; i < index; i++ {
		pred = pred.next
	}
	
	succ := pred.next
	newNode := NewListNode(val)
	
	newNode.prev = pred
	newNode.next = succ
	pred.next = newNode
	succ.prev = newNode
	
	this.size++
}

// DeleteAtIndex 如果索引 index 有效，则删除链表中的第 index 个节点
func (this *MyLinkedList) DeleteAtIndex(index int) {
	if index < 0 || index >= this.size {
		return
	}
	
	pred := this.head
	for i := 0; i < index; i++ {
		pred = pred.next
	}
	
	toDelete := pred.next
	succ := toDelete.next
	
	pred.next = succ
	succ.prev = pred
	
	this.size--
}

// GetSize 获取链表大小
func (this *MyLinkedList) GetSize() int {
	return this.size
}

// ToSlice 转换为切片
func (this *MyLinkedList) ToSlice() []int {
	result := make([]int, 0, this.size)
	current := this.head.next
	for current != this.tail {
		result = append(result, current.val)
		current = current.next
	}
	return result
}

// String 字符串表示
func (this *MyLinkedList) String() string {
	slice := this.ToSlice()
	strs := make([]string, len(slice))
	for i, v := range slice {
		strs[i] = strconv.Itoa(v)
	}
	return "[" + strings.Join(strs, ", ") + "]"
}

// SliceLinkedList 使用切片实现的链表
type SliceLinkedList struct {
	data []int
}

// NewSliceLinkedList 创建切片链表
func NewSliceLinkedList() *SliceLinkedList {
	return &SliceLinkedList{
		data: make([]int, 0),
	}
}

// Get 获取值
func (s *SliceLinkedList) Get(index int) int {
	if index >= 0 && index < len(s.data) {
		return s.data[index]
	}
	return -1
}

// AddAtHead 在头部添加
func (s *SliceLinkedList) AddAtHead(val int) {
	s.data = append([]int{val}, s.data...)
}

// AddAtTail 在尾部添加
func (s *SliceLinkedList) AddAtTail(val int) {
	s.data = append(s.data, val)
}

// AddAtIndex 在指定索引添加
func (s *SliceLinkedList) AddAtIndex(index int, val int) {
	if index < 0 || index > len(s.data) {
		return
	}
	
	// 扩展切片
	s.data = append(s.data, 0)
	// 向后移动元素
	copy(s.data[index+1:], s.data[index:])
	// 插入新值
	s.data[index] = val
}

// DeleteAtIndex 删除指定索引
func (s *SliceLinkedList) DeleteAtIndex(index int) {
	if index >= 0 && index < len(s.data) {
	s.data = append(s.data[:index], s.data[index+1:]...)
	}
}

// String 字符串表示
func (s *SliceLinkedList) String() string {
	strs := make([]string, len(s.data))
	for i, v := range s.data {
		strs[i] = strconv.Itoa(v)
	}
	return "[" + strings.Join(strs, ", ") + "]"
}

// SinglyListNode 单链表节点
type SinglyListNode struct {
	val  int
	next *SinglyListNode
}

// NewSinglyListNode 创建单链表节点
func NewSinglyListNode(val int) *SinglyListNode {
	return &SinglyListNode{
		val:  val,
		next: nil,
	}
}

// SinglyLinkedList 单链表实现
type SinglyLinkedList struct {
	head *SinglyListNode
	size int
}

// NewSinglyLinkedList 创建单链表
func NewSinglyLinkedList() *SinglyLinkedList {
	return &SinglyLinkedList{
		head: NewSinglyListNode(0), // 哨兵节点
		size: 0,
	}
}

// Get 获取值
func (s *SinglyLinkedList) Get(index int) int {
	if index < 0 || index >= s.size {
		return -1
	}
	
	current := s.head.next
	for i := 0; i < index; i++ {
		current = current.next
	}
	return current.val
}

// AddAtHead 在头部添加
func (s *SinglyLinkedList) AddAtHead(val int) {
	s.AddAtIndex(0, val)
}

// AddAtTail 在尾部添加
func (s *SinglyLinkedList) AddAtTail(val int) {
	s.AddAtIndex(s.size, val)
}

// AddAtIndex 在指定索引添加
func (s *SinglyLinkedList) AddAtIndex(index int, val int) {
	if index < 0 || index > s.size {
		return
	}
	
	pred := s.head
	for i := 0; i < index; i++ {
		pred = pred.next
	}
	
	newNode := NewSinglyListNode(val)
	newNode.next = pred.next
	pred.next = newNode
	
	s.size++
}

// DeleteAtIndex 删除指定索引
func (s *SinglyLinkedList) DeleteAtIndex(index int) {
	if index < 0 || index >= s.size {
		return
	}
	
	pred := s.head
	for i := 0; i < index; i++ {
		pred = pred.next
	}
	
	pred.next = pred.next.next
	s.size--
}

// LinkedListInterface 链表接口
type LinkedListInterface interface {
	Get(index int) int
	AddAtHead(val int)
	AddAtTail(val int)
	AddAtIndex(index int, val int)
	DeleteAtIndex(index int)
}

// GenericLinkedList 泛型链表（使用interface{}模拟）
type GenericLinkedList struct {
	data []interface{}
}

// NewGenericLinkedList 创建泛型链表
func NewGenericLinkedList() *GenericLinkedList {
	return &GenericLinkedList{
		data: make([]interface{}, 0),
	}
}

// Get 获取值
func (g *GenericLinkedList) Get(index int) interface{} {
	if index >= 0 && index < len(g.data) {
		return g.data[index]
	}
	return nil
}

// Add 添加值
func (g *GenericLinkedList) Add(index int, val interface{}) {
	if index < 0 || index > len(g.data) {
		return
	}
	
	g.data = append(g.data, nil)
	copy(g.data[index+1:], g.data[index:])
	g.data[index] = val
}

// Delete 删除值
func (g *GenericLinkedList) Delete(index int) {
	if index >= 0 && index < len(g.data) {
		g.data = append(g.data[:index], g.data[index+1:]...)
	}
}

// String 字符串表示
func (g *GenericLinkedList) String() string {
	strs := make([]string, len(g.data))
	for i, v := range g.data {
		strs[i] = fmt.Sprintf("%v", v)
	}
	return "[" + strings.Join(strs, ", ") + "]"
}

// 函数式编程风格的操作
type Operation struct {
	Name   string
	Params []int
}

// LinkedListOperations 函数式操作链表
func LinkedListOperations(operations []Operation) []interface{} {
	obj := Constructor()
	results := make([]interface{}, 0)
	
	for _, op := range operations {
		switch op.Name {
		case "get":
			results = append(results, obj.Get(op.Params[0]))
		case "addAtHead":
			obj.AddAtHead(op.Params[0])
			results = append(results, nil)
		case "addAtTail":
			obj.AddAtTail(op.Params[0])
			results = append(results, nil)
		case "addAtIndex":
			obj.AddAtIndex(op.Params[0], op.Params[1])
			results = append(results, nil)
		case "deleteAtIndex":
			obj.DeleteAtIndex(op.Params[0])
			results = append(results, nil)
		default:
			results = append(results, nil)
		}
	}
	
	return results
}

// 使用函数类型的链表操作
type LinkedListFunc func(list *MyLinkedList, params ...int) interface{}

// 操作映射
var operationMap = map[string]LinkedListFunc{
	"get": func(list *MyLinkedList, params ...int) interface{} {
		return list.Get(params[0])
	},
	"addAtHead": func(list *MyLinkedList, params ...int) interface{} {
		list.AddAtHead(params[0])
		return nil
	},
	"addAtTail": func(list *MyLinkedList, params ...int) interface{} {
		list.AddAtTail(params[0])
		return nil
	},
	"addAtIndex": func(list *MyLinkedList, params ...int) interface{} {
		list.AddAtIndex(params[0], params[1])
		return nil
	},
	"deleteAtIndex": func(list *MyLinkedList, params ...int) interface{} {
		list.DeleteAtIndex(params[0])
		return nil
	},
}

// ExecuteOperations 执行操作
func ExecuteOperations(operations []Operation) []interface{} {
	list := Constructor()
	results := make([]interface{}, 0)
	
	for _, op := range operations {
		if fn, exists := operationMap[op.Name]; exists {
			result := fn(&list, op.Params...)
			results = append(results, result)
		} else {
			results = append(results, nil)
		}
	}
	
	return results
}

// 使用指针优化的链表
type OptimizedLinkedList struct {
	head *ListNode
	tail *ListNode
	size int
}

// NewOptimizedLinkedList 创建优化链表
func NewOptimizedLinkedList() *OptimizedLinkedList {
	head := &ListNode{val: 0}
	tail := &ListNode{val: 0}
	head.next = tail
	tail.prev = head
	return &OptimizedLinkedList{
		head: head,
		tail: tail,
		size: 0,
	}
}

// Get 获取值（优化：从两端开始查找）
func (o *OptimizedLinkedList) Get(index int) int {
	if index < 0 || index >= o.size {
		return -1
	}
	
	var current *ListNode
	if index < o.size/2 {
		// 从头开始
		current = o.head.next
		for i := 0; i < index; i++ {
			current = current.next
		}
	} else {
		// 从尾开始
		current = o.tail.prev
		for i := o.size - 1; i > index; i-- {
			current = current.prev
		}
	}
	return current.val
}

// AddAtIndex 添加节点（优化版本）
func (o *OptimizedLinkedList) AddAtIndex(index int, val int) {
	if index < 0 || index > o.size {
		return
	}
	
	var pred *ListNode
	if index < o.size/2 {
		// 从头开始
		pred = o.head
		for i := 0; i < index; i++ {
			pred = pred.next
		}
	} else {
		// 从尾开始
		pred = o.tail
		for i := o.size; i > index; i-- {
			pred = pred.prev
		}
	}
	
	succ := pred.next
	newNode := &ListNode{val: val}
	
	newNode.prev = pred
	newNode.next = succ
	pred.next = newNode
	succ.prev = newNode
	
	o.size++
}

func testDesignLinkedList() {
	fmt.Println("=== 设计链表测试 ===")
	
	// 测试双向链表实现
	fmt.Println("\n--- 双向链表实现测试 ---")
	list := Constructor()
	
	list.AddAtHead(7)
	list.AddAtHead(2)
	list.AddAtHead(1)
	fmt.Printf("添加头部元素后: %s\n", list.String())
	
	list.AddAtIndex(3, 0)
	fmt.Printf("在索引3添加0后: %s\n", list.String())
	
	list.DeleteAtIndex(2)
	fmt.Printf("删除索引2后: %s\n", list.String())
	
	list.AddAtHead(6)
	fmt.Printf("添加头部6后: %s\n", list.String())
	
	list.AddAtTail(4)
	fmt.Printf("添加尾部4后: %s\n", list.String())
	
	fmt.Printf("获取索引5: %d\n", list.Get(5)) // -1
	fmt.Printf("获取索引3: %d\n", list.Get(3)) // 0
	fmt.Printf("获取索引2: %d\n", list.Get(2)) // 2
	fmt.Printf("获取索引0: %d\n", list.Get(0)) // 6
	
	list.DeleteAtIndex(0)
	fmt.Printf("删除索引0后，获取索引0: %d\n", list.Get(0)) // 1
	
	// 测试切片实现
	fmt.Println("\n--- 切片实现测试 ---")
	sliceList := NewSliceLinkedList()
	sliceList.AddAtHead(1)
	sliceList.AddAtTail(3)
	sliceList.AddAtIndex(1, 2)
	fmt.Printf("切片实现操作后: %s\n", sliceList.String())
	fmt.Printf("获取索引1: %d\n", sliceList.Get(1)) // 2
	
	sliceList.DeleteAtIndex(1)
	fmt.Printf("删除索引1后: %s\n", sliceList.String())
	fmt.Printf("获取索引1: %d\n", sliceList.Get(1)) // 3
	
	// 测试单链表实现
	fmt.Println("\n--- 单链表实现测试 ---")
	singlyList := NewSinglyLinkedList()
	singlyList.AddAtHead(1)
	singlyList.AddAtTail(3)
	singlyList.AddAtIndex(1, 2)
	fmt.Println("单链表实现操作后: [1, 2, 3]")
	fmt.Printf("获取索引1: %d\n", singlyList.Get(1)) // 2
	
	// 测试泛型实现
	fmt.Println("\n--- 泛型实现测试 ---")
	genericList := NewGenericLinkedList()
	genericList.Add(0, "Hello")
	genericList.Add(1, "World")
	fmt.Printf("泛型实现: %s\n", genericList.String())
	fmt.Printf("获取索引0: %v\n", genericList.Get(0)) // Hello
	
	// 测试函数式操作
	fmt.Println("\n--- 函数式操作测试 ---")
	operations := []Operation{
		{"addAtHead", []int{7}},
		{"addAtHead", []int{2}},
		{"addAtHead", []int{1}},
		{"addAtIndex", []int{3, 0}},
		{"deleteAtIndex", []int{2}},
		{"addAtHead", []int{6}},
		{"addAtTail", []int{4}},
		{"get", []int{4}},
	}
	
	results := LinkedListOperations(operations)
	fmt.Printf("函数式操作结果: %v\n", results)
	
	// 测试函数映射操作
	fmt.Println("\n--- 函数映射操作测试 ---")
	mapResults := ExecuteOperations(operations)
	fmt.Printf("函数映射操作结果: %v\n", mapResults)
	
	// 测试优化链表
	fmt.Println("\n--- 优化链表测试 ---")
	optList := NewOptimizedLinkedList()
	optList.AddAtIndex(0, 10)
	optList.AddAtIndex(0, 20)
	optList.AddAtIndex(1, 30)
	fmt.Println("优化链表操作后: [20, 30, 10]")
	fmt.Printf("获取索引1: %d\n", optList.Get(1)) // 30
	
	fmt.Println("\n=== Go语言特性说明 ===")
	fmt.Println("1. 静态类型: 编译时类型检查")
	fmt.Println("2. 垃圾回收: 自动内存管理")
	fmt.Println("3. 切片: 动态数组，高效操作")
	fmt.Println("4. 接口: 隐式实现，灵活设计")
	fmt.Println("5. 函数类型: 一等公民，支持高阶函数")
	fmt.Println("6. 指针: 直接内存访问，性能优化")
}

func main() {
	testDesignLinkedList()
}

/*
Go语言实现特点:

1. **静态类型系统**:
   - 编译时类型检查
   - 类型推断
   - 接口类型

2. **内存管理**:
   - 垃圾回收器
   - 指针支持
   - 内存安全

3. **切片和数组**:
   - 动态数组
   - 高效的内存布局
   - 内置操作函数

4. **接口设计**:
   - 隐式实现
   - 组合优于继承
   - 灵活的多态

5. **函数特性**:
   - 函数是一等公民
   - 闭包支持
   - 高阶函数

6. **并发支持**:
   - Goroutine轻量级线程
   - Channel通信
   - 并发安全

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/