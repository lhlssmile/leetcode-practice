package main

import "math"

func resultsArray(queries [][]int, k int) []int {
	ans := make([]int, len(queries))
	for i := 0; i < k-1; i++ {
		ans[i] = -1
	}
	n := len(queries)
	for i := k - 1; i < n; i++ {
		ans[i] = int(math.Abs(float64(queries[i][0])) + math.Abs(float64(queries[i][1])))
	}
	return ans
}
func abs(n int) int {
	if n < 0 {
		return -n
	}
	return n
}
func main() {

}
