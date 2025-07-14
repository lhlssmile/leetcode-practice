package main

import "fmt"

type ListNode_ struct {
	val  int
	next *ListNode_
}

func getDecimalValue(head *ListNode) int {
	ans := 0

	for head != nil {
		ans = ans*2 + head.Val
		head = head.Next
	}
	return ans
}

func main() {

	fmt.Println(createList([]int{1, 0, 1}))
}
