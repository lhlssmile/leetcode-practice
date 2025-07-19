'''
给你一个 m x n 的矩阵 grid 和一个正整数 k。一个 岛屿 是由 正 整数（表示陆地）组成的，并且陆地间 四周 连通（水平或垂直）。

一个岛屿的总价值是该岛屿中所有单元格的值之和。

返回总价值可以被 k 整除 的岛屿数量。

 

示例 1:


输入: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5

输出: 2

解释:

网格中包含四个岛屿。蓝色高亮显示的岛屿的总价值可以被 5 整除，而红色高亮显示的岛屿则不能。

示例 2:


输入: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3

输出: 6

解释:

网格中包含六个岛屿，每个岛屿的总价值都可以被 3 整除。

 

提示:

m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
0 <= grid[i][j] <= 106
1 <= k < = 106©leetcode

'''
from typing import List


class Solution:
    def countIslands(self, grid: List[List[int]], k: int) -> int:
        """递归DFS解法 - 统计总价值能被k整除的岛屿数量"""
        if not grid or not grid[0]:
            return 0
        
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        count = 0
        
        def dfs(i, j):
            """递归DFS遍历岛屿，返回岛屿的总价值"""
            # 边界条件：越界或已访问或为水域(0)
            if i < 0 or i >= m or j < 0 or j >= n or visited[i][j] or grid[i][j] == 0:
                return 0
            
            # 标记为已访问
            visited[i][j] = True
            
            # 当前格子的价值
            current_value = grid[i][j]
            
            # 递归遍历四个方向，累加岛屿总价值
            total_value = current_value
            total_value += dfs(i-1, j)  # 上
            total_value += dfs(i+1, j)  # 下
            total_value += dfs(i, j-1)  # 左
            total_value += dfs(i, j+1)  # 右
            
            return total_value
        
        # 遍历整个网格
        for i in range(m):
            for j in range(n):
                # 发现未访问的陆地，开始DFS
                if not visited[i][j] and grid[i][j] > 0:
                    island_value = dfs(i, j)
                    # 检查岛屿总价值是否能被k整除
                    if island_value % k == 0:
                        count += 1
        
        return count


if __name__ == "__main__":
    solution = Solution()
    
    print("=== 岛屿计数问题 ===")
    
    # 测试用例
    test_cases = [
        {
            "grid": [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], 
            "k": 5,
            "expected": 2
        },
        {
            "grid": [[3,0,3,0], [0,3,0,3], [3,0,3,0]], 
            "k": 3,
            "expected": 6
        },
        {
            "grid": [[1,2,3],[4,5,6]], 
            "k": 7,
            "expected": 0
        }
    ]
    
    for i, test in enumerate(test_cases, 1):
        grid = test["grid"]
        k = test["k"]
        expected = test["expected"]
        
        result = solution.countIslands(grid, k)
        
        print(f"\n测试用例 {i}:")
        print(f"网格: {grid}")
        print(f"k = {k}")
        print(f"结果: {result}")
        print(f"期望: {expected}")
        print(f"状态: {'✓ 通过' if result == expected else '✗ 失败'}")
    
    print("\n=== 递归DFS核心思路 ===")
    print("1. 遍历网格，找到未访问的陆地(>0)")
    print("2. 对每个岛屿使用DFS递归计算总价值")
    print("3. DFS递归逻辑:")
    print("   - 边界条件: 越界/已访问/水域 返回0")
    print("   - 标记当前位置为已访问")
    print("   - 递归遍历四个方向，累加价值")
    print("4. 检查岛屿总价值是否能被k整除")
    print("5. 统计符合条件的岛屿数量")
    
    print("\n=== 递归要点 ===")
    print("- 函数定义: dfs(i,j) 返回从(i,j)开始的岛屿总价值")
    print("- 边界条件: 越界、已访问、水域")
    print("- 状态转移: 当前值 + 四个方向的递归结果")
    print("- 避免重复: 使用visited数组标记")
    print("- 时间复杂度: O(m*n)")
    print("- 空间复杂度: O(m*n) 递归栈+visited数组")
        