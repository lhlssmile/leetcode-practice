package main

import "fmt"

func differenceOfDistinctValues(grid [][]int) [][]int {
	m, n := len(grid), len(grid[0])
	ans := make([][]int, m)
	for i := range ans {
		ans[i] = make([]int, n)
	}

	for k := 1 - n; k < m; k++ {
		minJ := max(0, -k)
		maxJ := min(n-1, m-1-k)

		seen := make(map[int]bool)
		for j := minJ; j <= maxJ; j++ {
			i := k + j
			ans[i][j] = len(seen)
			seen[grid[i][j]] = true
		}

		seen = make(map[int]bool)
		for j := maxJ; j >= minJ; j-- {
			i := k + j
			ans[i][j] = abs(ans[i][j] - len(seen))
			seen[grid[i][j]] = true
		}
	}
	return ans
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}
func main() {
	grid := [][]int{
		{1, 2, 3},
		{3, 1, 5},
		{3, 2, 1},
	}
	res := differenceOfDistinctValues(grid)
	fmt.Println(res)
}
