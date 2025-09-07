'''
给你一个 m x n 的二进制网格 grid，其中：

grid[i][j] == 0 表示一个空格子。
grid[i][j] == 1 表示一面镜子。
一个机器人从网格的左上角 (0, 0) 出发，想要到达右下角 (m - 1, n - 1)。它只能向 右 或向 下 移动。如果机器人试图移入一个有镜子的格子，它会在进入该格子前被 反射：

如果它试图向 右 移动进入镜子，它会被转向 下 方，并移动到镜子正下方的格子里。
如果它试图向 下 移动进入镜子，它会被转向 右 方，并移动到镜子正右方的格子里。
如果这次反射会导致机器人移动到网格边界之外，则该路径被视为无效，不应被计数。

返回从 (0, 0) 到 (m - 1, n - 1) 不同的有效路径数量。

由于答案可能非常大，请将其返回对 109 + 7 取模 的结果。

注意：如果一次反射将机器人移动到一个有镜子的格子，机器人会立即再次被反射。这次反射的方向取决于它进入该镜子的方向：如果它是向右移动进入的，它将被转向下方；如果它是向下移动进入的，它将被转向右方。

 

示例 1:

输入： grid = [[0,1,0],[0,0,1],[1,0,0]]

输出： 5

解释：

编号	完整路径
1	(0, 0) → (0, 1) [M] → (1, 1) → (1, 2) [M] → (2, 2)
2	(0, 0) → (0, 1) [M] → (1, 1) → (2, 1) → (2, 2)
3	(0, 0) → (1, 0) → (1, 1) → (1, 2) [M] → (2, 2)
4	(0, 0) → (1, 0) → (1, 1) → (2, 1) → (2, 2)
5	(0, 0) → (1, 0) → (2, 0) [M] → (2, 1) → (2, 2)
[M] 表示机器人试图进入一个有镜子的格子但被反射了。

示例 2:

输入： grid = [[0,0],[0,0]]

输出： 2

解释：

编号	完整路径
1	(0, 0) → (0, 1) → (1, 1)
2	(0, 0) → (1, 0) → (1, 1)
示例 3:

输入： grid = [[0,1,1],[1,1,0]]

输出： 1

解释：

编号	完整路径
1	(0, 0) → (0, 1) [M] → (1, 1) [M] → (1, 2)
(0, 0) → (1, 0) [M] → (1, 1) [M] → (2, 1) 超出边界，因此是无效路径。
 

提示:

m == grid.length
n == grid[i].length
2 <= m, n <= 500
grid[i][j] 的值为 0 或 1。
grid[0][0] == grid[m - 1][n - 1] == 0©leetcode
'''

from typing import List


class Solution:
    def count_paths(self, grid: List[List[int]]):
        m, n = len(grid), len(grid[0])
        MOD = 10 ** 9 + 7
        
        # 使用记忆化搜索
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, j, direction):
            # direction: 0表示向右，1表示向下
            if i == m - 1 and j == n - 1:
                return 1
            
            result = 0
            
            # 尝试向右移动
            if j + 1 < n:
                ni, nj, ndir = move(i, j, 0)
                if ni != -1:  # 有效移动
                    result = (result + dfs(ni, nj, ndir)) % MOD
            
            # 尝试向下移动
            if i + 1 < m:
                ni, nj, ndir = move(i, j, 1)
                if ni != -1:  # 有效移动
                    result = (result + dfs(ni, nj, ndir)) % MOD
            
            return result
        
        def move(i, j, direction):
            # direction: 0向右，1向下
            if direction == 0:  # 向右
                next_j = j + 1
                if next_j >= n:
                    return -1, -1, -1
                
                if grid[i][next_j] == 0:  # 空格子
                    return i, next_j, 0
                else:  # 镜子，向右进入被反射向下
                    return reflect_move(i, next_j, 1)
            else:  # 向下
                next_i = i + 1
                if next_i >= m:
                    return -1, -1, -1
                
                if grid[next_i][j] == 0:  # 空格子
                    return next_i, j, 1
                else:  # 镜子，向下进入被反射向右
                    return reflect_move(next_i, j, 0)
        
        def reflect_move(i, j, new_direction):
            # 处理连续反射
            while True:
                if new_direction == 0:  # 向右
                    next_j = j + 1
                    if next_j >= n:
                        return -1, -1, -1
                    
                    if grid[i][next_j] == 0:  # 空格子
                        return i, next_j, 0
                    else:  # 又是镜子，继续反射
                        j = next_j
                        new_direction = 1  # 向右进入镜子，反射向下
                else:  # 向下
                    next_i = i + 1
                    if next_i >= m:
                        return -1, -1, -1
                    
                    if grid[next_i][j] == 0:  # 空格子
                        return next_i, j, 1
                    else:  # 又是镜子，继续反射
                        i = next_i
                        new_direction = 0  # 向下进入镜子，反射向右

        return dfs(0, 0, 0)


if __name__ == '__main__':
    s = Solution()
    
    # 测试用例1
    grid1 = [[0, 1, 0], [0, 0, 1], [1, 0, 0]]
    result1 = s.count_paths(grid1)
    print(f"测试用例1: {result1}, 预期: 5")
    
    # 测试用例2
    grid2 = [[0, 0], [0, 0]]
    result2 = s.count_paths(grid2)
    print(f"测试用例2: {result2}, 预期: 2")
    
    # 测试用例3
    grid3 = [[0, 1, 1], [1, 1, 0]]
    result3 = s.count_paths(grid3)
    print(f"测试用例3: {result3}, 预期: 1")
    
    # 验证结果
    if result1 == 5 and result2 == 2 and result3 == 1:
        print("\n✅ 所有测试用例通过！")
    else:
        print("\n❌ 有测试用例失败")



'''
test case 
[[0,1,0],[0,0,1],[1,0,0]]
[[0,0],[0,0]]
[[0,1,1],[1,1,0]]

预期结果
5
2
1
'''