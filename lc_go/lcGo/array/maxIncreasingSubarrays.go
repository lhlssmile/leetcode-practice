package main


import "fmt"


func maxIncreasingSubarrays(nums []int) int {
	ans, n, cnt, precnt := 0, len(nums), 0, 0

	for i, x := range nums {
		if i == n - 1 || x >= nums[i + 1] {
			ans = max(cnt / 2, min(cnt, precnt), ans)
			precnt = cnt
			cnt = 0
		}
	}

	return ans
}
func min (a, b int) int {
	if a < b {return a}
	return b
}
func max(a, b, c int) int {
	if a < b {a = b}
	if a < c {a = c}
	return a
}
func main() {
	nums := []int{2, 5, 7, 8, 9, 2, 3, 4, 3, 1}
	fmt.Println(maxIncreasingSubarrays(nums))
}