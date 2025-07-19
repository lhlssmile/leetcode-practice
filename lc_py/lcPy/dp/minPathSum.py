'''
给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。



示例 1：


输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。
示例 2：

输入：grid = [[1,2,3],[4,5,6]]
输出：12


提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 200
'''
from functools import cache
from typing import List


class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        @cache
        def dfs(i: int, j: int) -> int:
            """递归函数：从(i,j)到右下角的最小路径和"""
            # 边界情况：到达右下角
            if i == m - 1 and j == n - 1:
                return grid[i][j]
            
            # 边界情况：超出边界，返回无穷大
            if i >= m or j >= n:
                return float('inf')
            
            # 递归：只能向右或向下
            # 当前格子值 + min(向右走, 向下走)
            right = dfs(i, j + 1)  # 向右走
            down = dfs(i + 1, j)   # 向下走
            
            return grid[i][j] + min(right, down)
        
        # 从左上角(0,0)开始
        return dfs(0, 0)
    
    def minPathSumDP(self, grid: List[List[int]]) -> int:
        """方法2: 动态规划 (递推)"""
        m, n = len(grid), len(grid[0])
        
        # dp[i][j] 表示从(0,0)到(i,j)的最小路径和
        dp = [[0] * n for _ in range(m)]
        
        # 初始化起点
        dp[0][0] = grid[0][0]
        
        # 初始化第一行（只能从左边来）
        for j in range(1, n):
            dp[0][j] = dp[0][j-1] + grid[0][j]
        
        # 初始化第一列（只能从上边来）
        for i in range(1, m):
            dp[i][0] = dp[i-1][0] + grid[i][0]
        
        # 填充其他位置
        for i in range(1, m):
            for j in range(1, n):
                # 从上边或左边来，选择较小的
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
        
        return dp[m-1][n-1]
    
    def minPathSumOptimized(self, grid: List[List[int]]) -> int:
        """方法3: 空间优化版本 (只用一行)"""
        m, n = len(grid), len(grid[0])
        
        # 只需要一行的空间
        dp = [0] * n
        
        # 初始化第一行
        dp[0] = grid[0][0]
        for j in range(1, n):
            dp[j] = dp[j-1] + grid[0][j]
        
        # 逐行更新
        for i in range(1, m):
            # 更新第一列
            dp[0] += grid[i][0]
            
            # 更新其他列
            for j in range(1, n):
                dp[j] = grid[i][j] + min(dp[j], dp[j-1])
        
        return dp[n-1]


if __name__ == "__main__":
    # 测试用例
    grid = [[1,3,1],[1,5,1],[4,2,1]]
    solution = Solution()
    
    print("=== 最小路径和问题 ===")
    print(f"输入网格: {grid}")
    print()
    
    # 方法1: 递归 + 记忆化
    result1 = solution.minPathSum(grid)
    print(f"方法1 (递归+记忆化): {result1}")
    
    # 方法2: 动态规划
    result2 = solution.minPathSumDP(grid)
    print(f"方法2 (动态规划): {result2}")
    
    # 方法3: 空间优化
    result3 = solution.minPathSumOptimized(grid)
    print(f"方法3 (空间优化): {result3}")
    
    print("\n=== 递归思路分析 ===")
    print("1. 递归函数定义: dfs(i, j) = 从(i,j)到右下角的最小路径和")
    print("2. 边界条件:")
    print("   - 到达右下角: 返回 grid[i][j]")
    print("   - 超出边界: 返回 float('inf')")
    print("3. 状态转移:")
    print("   - dfs(i,j) = grid[i][j] + min(dfs(i,j+1), dfs(i+1,j))")
    print("4. 记忆化: @cache 自动缓存避免重复计算")
    
    print("\n=== 递归过程示例 (3x3网格) ===")
    print("dfs(0,0) = 1 + min(dfs(0,1), dfs(1,0))")
    print("dfs(0,1) = 3 + min(dfs(0,2), dfs(1,1))")
    print("dfs(0,2) = 1 + min(dfs(0,3), dfs(1,2))")
    print("dfs(0,3) = inf (超出边界)")
    print("dfs(1,2) = 1 + min(dfs(1,3), dfs(2,2))")
    print("dfs(2,2) = 1 (到达终点)")
    print("...")
    
    print("\n=== 三种方法对比 ===")
    print("递归+记忆化:")
    print("  - 时间复杂度: O(m*n)")
    print("  - 空间复杂度: O(m*n) [递归栈 + 缓存]")
    print("  - 优点: 思路直观，自顶向下")
    print("  - 缺点: 递归栈开销")
    
    print("\n动态规划:")
    print("  - 时间复杂度: O(m*n)")
    print("  - 空间复杂度: O(m*n)")
    print("  - 优点: 自底向上，无递归开销")
    print("  - 缺点: 需要理解状态转移")
    
    print("\n空间优化:")
    print("  - 时间复杂度: O(m*n)")
    print("  - 空间复杂度: O(n)")
    print("  - 优点: 空间最优")
    print("  - 缺点: 代码稍复杂")
    
    print("\n=== 记忆化的精髓 ===")
    print("- 避免重复计算相同子问题")
    print("- 将指数时间复杂度优化到多项式")
    print("- @cache装饰器自动管理缓存")
    print("- 递归 + 记忆化 = 动态规划的另一种实现")
    
    print("\n=== 递归思维要点 ===")
    print("1. 明确递归函数的含义")
    print("2. 找到递归的边界条件")
    print("3. 确定状态转移方程")
    print("4. 加上记忆化避免重复计算")
    print("5. 递归是自顶向下的思考方式，更符合人的直觉")