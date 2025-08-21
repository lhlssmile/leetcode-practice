package main

func isZeroArray(nums []int, queries [][]int) bool {
	n := len(nums)

	diff := make([]int, n+2)

	for _, q := range queries {
		diff[q[0]]++
		diff[q[1]+1]--
	}
	s := 0
	for i := range nums {
		s += diff[i]
		if s < nums[i] {
			return false
		}
	}
	return true
}

func main() {

}
