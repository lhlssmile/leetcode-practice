package main

import "fmt"

func countSubarrays(nums []int, k int64) (ans int64) {
	n := len(nums)
	left, prefixSum := 0, int64(0)

	for right := range nums[:n] {
		prefixSum += int64(nums[right])

		for left <= right && prefixSum*int64(right-left+1) >= k {
			prefixSum -= int64(nums[left])
			left++
		}

		ans += int64(right - left + 1)
	}
	return ans
}

func main() {
	nums := []int{2, 1, 4, 3, 5}
	k := int64(10)
	res := countSubarrays(nums, k)
	fmt.Println(res)
}
