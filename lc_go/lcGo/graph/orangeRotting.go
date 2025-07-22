package main

import (
	"fmt"
)

// orangeRotting 腐烂的橘子 - 多源BFS解法
func orangeRotting(grid [][]int) int {
	if len(grid) == 0 || len(grid[0]) == 0 {
		return 0
	}

	rows, cols := len(grid), len(grid[0])
	queue := make([][2]int, 0) // 存储腐烂橘子的位置 [row, col]
	freshCount := 0            // 新鲜橘子数量

	// 1. 初始化：找到所有腐烂橘子，统计新鲜橘子
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] == 2 {
				queue = append(queue, [2]int{i, j}) // 腐烂橘子入队
			} else if grid[i][j] == 1 {
				freshCount++ // 统计新鲜橘子
			}
		}
	}

	// 如果没有新鲜橘子，直接返回0
	if freshCount == 0 {
		return 0
	}

	// 四个方向：上下左右
	directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
	minutes := 0

	// 2. BFS 多源扩散
	for len(queue) > 0 {
		// 当前轮次的腐烂橘子数量
		size := len(queue)

		// 处理当前轮次的所有腐烂橘子
		for i := 0; i < size; i++ {
			current := queue[0]
			queue = queue[1:] // 出队
			x, y := current[0], current[1]

			// 向四个方向扩散
			for _, dir := range directions {
				nx, ny := x+dir[0], y+dir[1]

				// 检查边界和是否为新鲜橘子
				if nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1 {
					grid[nx][ny] = 2                        // 变腐烂
					freshCount--                            // 新鲜橘子数量减1
					queue = append(queue, [2]int{nx, ny})   // 新腐烂的橘子入队
				}
			}
		}

		// 如果这轮有橘子腐烂，时间+1
		if len(queue) > 0 {
			minutes++
		}
	}

	// 3. 检查是否还有新鲜橘子
	if freshCount == 0 {
		return minutes
	}
	return -1
}

// 测试函数
func testOrangeRotting() {
	fmt.Println("=== 腐烂的橘子 Go版本测试 ===")

	// 测试用例1
	grid1 := [][]int{
		{2, 1, 1},
		{1, 1, 0},
		{0, 1, 1},
	}
	result1 := orangeRotting(grid1)
	fmt.Printf("测试1: [[2,1,1],[1,1,0],[0,1,1]] -> %d (期望: 4)\n", result1)

	// 测试用例2
	grid2 := [][]int{
		{2, 1, 1},
		{0, 1, 1},
		{1, 0, 1},
	}
	result2 := orangeRotting(grid2)
	fmt.Printf("测试2: [[2,1,1],[0,1,1],[1,0,1]] -> %d (期望: -1)\n", result2)

	// 测试用例3
	grid3 := [][]int{{0, 2}}
	result3 := orangeRotting(grid3)
	fmt.Printf("测试3: [[0,2]] -> %d (期望: 0)\n", result3)

	// 测试用例4：多个初始腐烂橘子
	grid4 := [][]int{
		{2, 1, 1},
		{1, 1, 1},
		{1, 1, 2},
	}
	result4 := orangeRotting(grid4)
	fmt.Printf("测试4: [[2,1,1],[1,1,1],[1,1,2]] -> %d (期望: 2)\n", result4)
}

// 带调试信息的版本
func orangeRottingDebug(grid [][]int) int {
	if len(grid) == 0 || len(grid[0]) == 0 {
		return 0
	}

	rows, cols := len(grid), len(grid[0])
	queue := make([][2]int, 0)
	freshCount := 0

	fmt.Println("初始状态:")
	printGrid(grid)

	// 初始化
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] == 2 {
				queue = append(queue, [2]int{i, j})
				fmt.Printf("找到初始腐烂橘子: (%d, %d)\n", i, j)
			} else if grid[i][j] == 1 {
				freshCount++
			}
		}
	}

	fmt.Printf("初始新鲜橘子数量: %d\n", freshCount)

	if freshCount == 0 {
		return 0
	}

	directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
	minutes := 0

	for len(queue) > 0 {
		size := len(queue)
		fmt.Printf("\n第%d分钟，处理%d个腐烂橘子:\n", minutes+1, size)

		for i := 0; i < size; i++ {
			current := queue[0]
			queue = queue[1:]
			x, y := current[0], current[1]

			for _, dir := range directions {
				nx, ny := x+dir[0], y+dir[1]

				if nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1 {
					grid[nx][ny] = 2
					freshCount--
					queue = append(queue, [2]int{nx, ny})
					fmt.Printf("  (%d,%d) -> (%d,%d) 腐烂\n", x, y, nx, ny)
				}
			}
		}

		if len(queue) > 0 {
			minutes++
			fmt.Printf("第%d分钟后状态:\n", minutes)
			printGrid(grid)
			fmt.Printf("剩余新鲜橘子: %d\n", freshCount)
		}
	}

	if freshCount == 0 {
		return minutes
	}
	return -1
}

// 打印网格
func printGrid(grid [][]int) {
	for _, row := range grid {
		for _, cell := range row {
			fmt.Printf("%d ", cell)
		}
		fmt.Println()
	}
}

// 调试测试
func debugTest() {
	fmt.Println("\n=== 调试模式测试 ===")
	grid := [][]int{
		{2, 1, 1},
		{1, 1, 1},
		{1, 1, 2},
	}
	result := orangeRottingDebug(grid)
	fmt.Printf("\n最终结果: %d 分钟\n", result)
}

func main() {
	testOrangeRotting()
	debugTest()
}
