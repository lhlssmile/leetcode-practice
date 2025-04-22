package main

import "fmt"

func maxTripletValue(nums []int) (ans int64) {
	n := len(nums)

	maxDiff, maxVal := 0, 0

	for k := 0; k < n; k++ {
		ans = max(ans, (int64(maxDiff))*(int64(nums[k])))

		maxDiff = max(maxDiff, maxVal-nums[k])

		maxVal = max(maxVal, nums[k])
	}

	return
}

func main() {
	nums := []int{12, 6, 1, 2, 7}
	res := maxTripletValue(nums)
	fmt.Println(res)

}
