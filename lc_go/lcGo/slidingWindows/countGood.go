package main

import "fmt"

func countGood(nums []int, k int) (ans int64) {
	freq := map[int]int{}
	pairCount, left := 0, 0

	for _, x := range nums {

		pairCount += freq[x]
		freq[x]++

		for pairCount >= k {
			freq[nums[left]]--
			pairCount -= freq[nums[left]]
			left++
		}
		ans += int64(left)
	}
	return
}

func main() {
	nums := []int{3, 1, 4, 3, 2, 2, 4}
	k := 2
	res := countGood(nums, k)
	fmt.Println(res)
}
