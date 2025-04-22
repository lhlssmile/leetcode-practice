package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

/*
*
Go 基础语法：
变量声明：var 或 :=。
指针：& 取地址，* 解引用，自动解引用简化操作。
结构体：struct 定义，{} 初始化。
循环和条件：只有 for，if 不需要括号。
代码风格：不写分号，gofmt 格式化。
*/
func sortList(head *ListNode) *ListNode {
	// 终止条件 空链表或者是 只有一个结点
	if head == nil || head.Next == nil {
		return head
	}
	slow, fast := head, head.Next

	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}
	mid := slow.Next
	slow.Next = nil

	left := sortList(head)
	right := sortList(mid)
	return merge(left, right)
}

func merge(l1 *ListNode, l2 *ListNode) *ListNode {
	//& 取地址 *解引用		ListNode{} 创建一个实例List node
	dummy := &ListNode{}
	tail := dummy

	for l1 != nil && l2 != nil {
		if l1.Val <= l2.Val {
			tail.Next = l1
			l1 = l1.Next
		} else {
			tail.Next = l2
			l2 = l2.Next
		}
		tail = tail.Next
	}
	if l1 != nil {
		tail.Next = l1
	}
	if l2 != nil {
		tail.Next = l2
	}
	//dummy.Next 相当于 (*dummy).Next
	return dummy.Next
}

func createList(arr []int) *ListNode {
	if len(arr) == 0 {
		return nil
	}
	var build func(index int) *ListNode
	build = func(index int) *ListNode {
		if index >= len(arr) {
			return nil
		}
		node := &ListNode{Val: arr[index]}
		node.Next = build(index + 1)
		return node
	}
	return build(0)
}
func printList(head *ListNode) {
	for head != nil {
		fmt.Printf("%d ", head.Val)
		head = head.Next
	}
	fmt.Println()
}
func main() {
	arr := []int{4, 2, 1, 3}
	head := createList(arr)

	sorted := sortList(head)
	printList(sorted) // 输出: 1 2 3 4
}

/**
var p *int	声明指针
x := 10
p := &x  // p 是 *int 类型，指向 x
*/
