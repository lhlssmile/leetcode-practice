package main

import "math"

func findMaxAverage(nums []int, k int) (ans float64) {

	s := math.MinInt

	cs := 0

	for i, x := range nums {
		cs += x

		if i < k-1 {
			continue
		}

		s = max(cs, s)

		cs -= nums[i-k+1]
	}
	return float64(s) / float64(k)
}

func main() {

}
