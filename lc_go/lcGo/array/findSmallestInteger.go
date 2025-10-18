package main

import "fmt"

func findSmallestInteger(nums []int, m int) int {
	var mex int
	cnt := map[int]int{}

	for _, x := range nums {
		cnt[(x%m+m)%m]++
	}
	for cnt[mex%m] > 0 {
		cnt[mex%m]--
		mex++
	}
	return mex
}

func main() {
	nums := []int{1, -10, 7, 13, 6, 8}
	m := 5
	fmt.Println(findSmallestInteger(nums, m))
}
