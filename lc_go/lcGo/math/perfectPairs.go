package main

import "slices"

func perfectPairs(nums []int) int64 {

	for i, x := range nums {
		if nums[i] < 0 {
			nums[i] = -x
		}
	}
	slices.Sort(nums)

	ans, left := 0, 0

	for j, b := range nums {
		for nums[left]*2 < b {
			left++
		}
		ans += j - left
	}

	return int64(ans)
}

func main() {

}
