package main

import "fmt"

func numIslands(grid [][]byte) int {
	m, n := len(grid), len(grid[0])
	ans := 0

	var dfs func(i, j int)
	dfs = func(i, j int) {
		if i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1' {
			return
		}
		grid[i][j] = '2' // 标记已访问
		dfs(i, j-1)      // 左
		dfs(i, j+1)      // 右
		dfs(i+1, j)      // 下
		dfs(i-1, j)      // 上
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if grid[i][j] == '1' {
				dfs(i, j)
				ans++
			}
		}
	}
	return ans
}

func main() {
	grid := [][]byte{
		{'1', '1', '1', '1', '0'},
		{'1', '1', '0', '1', '0'},
		{'1', '1', '0', '0', '0'},
		{'0', '0', '0', '0', '0'},
	}
	result := numIslands(grid)
	fmt.Println(result) // 输出 1
}
