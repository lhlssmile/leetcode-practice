package main

import "fmt"

func countCompleteSubarrays(nums []int) (ans int) {
	n := len(nums)
	set := map[int]struct{}{}
	for _, x := range nums {
		set[x] = struct{}{}
	}
	m := len(set)
	freq := map[int]int{}
	left,right := 0,0
	for ; right < len(nums);right++ {
		freq[nums[right]]++
		for len(freq) == m {
			ans += n - right 
			freq[nums[left]]--
			if freq[nums[left]] == 0 {
				delete(freq,nums[left])
			}
			left++
		}
	}
	return 
}

func main() {
	nums := []int{1,3,1,2,2}
    res := countCompleteSubarrays(nums)
    fmt.Println(res)
}