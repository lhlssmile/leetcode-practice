package main

import "slices"

func countPairs(nums []int, target int) (ans int) {
	slices.Sort(nums)
	i, j := 0, len(nums)-1
	for i < j {
		if nums[i]+nums[j] < target {
			ans += j - i
			i++
		} else {
			j--
		}
	}
	return
}

func main() {

}
