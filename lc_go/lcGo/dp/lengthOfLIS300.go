package main

import (
	"fmt"
	"sort"
)

func lengthOfLIS(nums []int) int {
	n := len(nums)
	if n == 0 {
		return 0
	}
	//create vector<int> size(n)
	dp := make([]int, n)
	for i := range dp {
		dp[i] = 1
	}
	maxLen := 1
	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] {
				dp[i] = max(dp[i], dp[j]+1)
			}
		}
		maxLen = max(maxLen, dp[i])
	}
	return maxLen
}

func lengthOfLISBinarySearch(nums []int) int {
	n := len(nums)
	if n == 0 {
		return 0
	}
	tails := []int{} // tails[i] 是长度为 i+1 的 LIS 末尾最小值
	for _, num := range nums {
		if len(tails) == 0 || num > tails[len(tails)-1] {
			tails = append(tails, num)
		} else {
			pos := sort.SearchInts(tails, num)
			tails[pos] = num
		}
	}
	return len(tails)
}

func main() {
	nums := []int{10, 9, 2, 5, 3, 7, 101, 18}
	res := lengthOfLISBinarySearch(nums)
	fmt.Println(res)
}
