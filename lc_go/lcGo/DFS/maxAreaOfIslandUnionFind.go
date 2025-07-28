package main

import "fmt"

// 并查集结构
type UnionFind struct {
	parent    []int  // 父节点数组
	size      []int  // 集合大小数组
	activated []bool // 节点是否被激活
	count     int    // 集合数量
}

// 初始化并查集
func NewUnionFind(n int) *UnionFind {
	uf := &UnionFind{
		parent:    make([]int, n),
		size:      make([]int, n),
		activated: make([]bool, n),
		count:     0,
	}

	// 初始化：每个节点的父节点是自己，大小为1
	for i := 0; i < n; i++ {
		uf.parent[i] = i
		uf.size[i] = 1
		uf.activated[i] = false // 初始都未激活
	}
	return uf
}

// 查找根节点（带路径压缩）
func (uf *UnionFind) Find(x int) int {
	if uf.parent[x] != x {
		// 路径压缩：将路径上所有节点直接连到根节点
		uf.parent[x] = uf.Find(uf.parent[x])
	}
	return uf.parent[x]
}

// 合并两个集合（按大小合并）
func (uf *UnionFind) Union(x, y int) {
	rootX := uf.Find(x)
	rootY := uf.Find(y)

	if rootX == rootY {
		return // 已经在同一个集合中
	}

	// 按大小合并：小树合并到大树上
	if uf.size[rootX] < uf.size[rootY] {
		rootX, rootY = rootY, rootX
	}

	uf.parent[rootY] = rootX
	uf.size[rootX] += uf.size[rootY]
	uf.count--
}

// 激活一个节点（将其加入并查集）
func (uf *UnionFind) Activate(x int) {
	if !uf.activated[x] {
		uf.activated[x] = true
		uf.count++
	}
}

// 获取集合大小
func (uf *UnionFind) GetSize(x int) int {
	return uf.size[uf.Find(x)]
}

// 获取最大集合大小
func (uf *UnionFind) GetMaxSize() int {
	maxSize := 0
	for i := 0; i < len(uf.size); i++ {
		// 只检查已激活且为根节点的节点
		if uf.activated[i] && uf.parent[i] == i {
			if uf.size[i] > maxSize {
				maxSize = uf.size[i]
			}
		}
	}
	return maxSize
}

// 使用并查集解决最大岛屿面积
func maxAreaOfIslandUF(grid [][]int) int {
	m, n := len(grid), len(grid[0])

	// 创建并查集
	uf := NewUnionFind(m * n)

	// 方向数组：上下左右
	directions := [][]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}

	// 坐标转换函数：(i,j) -> 一维索引
	getIndex := func(i, j int) int {
		return i*n + j
	}

	// 第一步：激活所有陆地格子
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if grid[i][j] == 1 {
				uf.Activate(getIndex(i, j))
			}
		}
	}

	// 第二步：合并相邻的陆地格子
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if grid[i][j] == 1 {
				currentIndex := getIndex(i, j)

				// 检查四个方向的相邻格子
				for _, dir := range directions {
					ni, nj := i+dir[0], j+dir[1]

					// 边界检查和陆地检查
					if ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] == 1 {
						neighborIndex := getIndex(ni, nj)
						uf.Union(currentIndex, neighborIndex)
					}
				}
			}
		}
	}

	// 第三步：找到最大的岛屿面积
	return uf.GetMaxSize()
}

// DFS方法（用于对比）
func maxAreaOfIslandA(grid [][]int) int {
	m, n := len(grid), len(grid[0])
	visited := make([][]bool, m)
	for i := 0; i < m; i++ {
		visited[i] = make([]bool, n)
	}

	directions := [][]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

	var dfs func(int, int) int
	dfs = func(i, j int) int {
		if i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j] {
			return 0
		}

		visited[i][j] = true
		area := 1

		for _, dir := range directions {
			newI, newJ := i+dir[0], j+dir[1]
			area += dfs(newI, newJ)
		}

		return area
	}

	ans := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if grid[i][j] == 1 && !visited[i][j] {
				currentArea := dfs(i, j)
				ans = max(ans, currentArea)
			}
		}
	}
	return ans
}

func main() {
	// 测试用例1：正常情况
	grid1 := [][]int{
		{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
		{0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
	}

	// 测试用例2：全为0的情况
	grid2 := [][]int{{0, 0, 0, 0, 0, 0, 0, 0}}

	fmt.Println("=== 测试用例1 ===")
	fmt.Println("DFS方法结果:", maxAreaOfIsland(grid1))
	fmt.Println("并查集方法结果:", maxAreaOfIslandUF(grid1))

	fmt.Println("\n=== 测试用例2（全为0）===")
	fmt.Println("DFS方法结果:", maxAreaOfIsland(grid2))
	fmt.Println("并查集方法结果:", maxAreaOfIslandUF(grid2))
}
