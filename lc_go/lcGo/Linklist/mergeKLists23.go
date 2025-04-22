package main

import "fmt"

// no need to declare again
//type ListNode struct {
//	Val int
//	Next *ListNode
//}

func mergeTwoLists(l1, l2 *ListNode) *ListNode {
	if l1 == nil {
		return l2
	}
	if l2 == nil {
		return l1
	}
	if l1.Val < l2.Val {
		l1.Next = mergeTwoLists(l1.Next, l2)
		return l1
	}
	l2.Next = mergeTwoLists(l1, l2.Next)
	return l2
}

func mergeKLists(lists []*ListNode) *ListNode {
	if len(lists) == 0 {
		return nil
	}
	return mergeK(lists, 0, len(lists)-1)
}

func mergeK(lists []*ListNode, left, right int) *ListNode {
	if left == right {
		return lists[left]
	}
	mid := left + (right-left)/2
	l1 := mergeK(lists, left, mid)
	l2 := mergeK(lists, mid+1, right)
	return mergeTwoLists(l1, l2)
}

//func createList(vals []int) *ListNode {
//	dummy := &ListNode{}
//	tail := dummy
//
//	for _,v := range vals{
//		tail.Next = &ListNode{Val: v}
//		tail = tail.Next
//	}
//	return dummy.Next
//}

func main() {
	lists := []*ListNode{
		createList([]int{1, 4, 5}),
		createList([]int{1, 3, 4}),
		createList([]int{2, 6}),
	}
	res := mergeKLists(lists)
	for res != nil {
		fmt.Println(res.Val, " ")
		res = res.Next
	}
}
