package main

import "fmt"

func maxSlidingWindow(nums []int, k int) (res []int) {
	n := len(nums)
	if n < k {
		maxVal := nums[0]
		for i := 1; i < n; i++ {
			maxVal = max(maxVal, nums[i])
		}
		res = append(res, maxVal)
		return
	}
	dq := []int{} //用slice模拟deque
	for i := 0; i < k; i++ {
		for len(dq) > 0 && nums[dq[len(dq)-1]] < nums[i] {
			dq = dq[:len(dq)-1] //队尾出队
		}
		dq = append(dq, i)
	}
	res = append(res, nums[dq[0]])
	for i := k; i < n; i++ {
		if len(dq) > 0 && dq[0] <= i-k {
			dq = dq[1:]
		}
		for len(dq) > 0 && nums[dq[len(dq)-1]] < nums[i] {
			dq = dq[:len(dq)-1]
		}
		dq = append(dq, i)
		res = append(res, nums[dq[0]])
	}
	return
}

func main() {
	nums := []int{1, 3, -1, -3, 5, 3, 6, 7}
	k := 3
	res := maxSlidingWindow(nums, k)
	fmt.Println(res)
}
