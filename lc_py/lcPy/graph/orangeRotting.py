from typing import List
from collections import deque

class Solution:
    def orangeRotting(self, grid: List[List[int]]) -> int:
        if not grid or not grid[0]:
            return 0
        
        rows, cols = len(grid), len(grid[0])
        queue = deque()  # 存储腐烂橘子的位置
        fresh_count = 0  # 新鲜橘子数量
        
        # 1. 初始化：找到所有腐烂橘子，统计新鲜橘子
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 2:
                    queue.append((i, j))  # 腐烂橘子入队
                elif grid[i][j] == 1:
                    fresh_count += 1  # 统计新鲜橘子
        
        # 如果没有新鲜橘子，直接返回0
        if fresh_count == 0:
            return 0
        
        # 四个方向：上下左右
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        minutes = 0
        
        # 2. BFS 多源扩散
        while queue:
            # 当前轮次的腐烂橘子数量
            size = len(queue)
            
            # 处理当前轮次的所有腐烂橘子
            for _ in range(size):
                x, y = queue.popleft()
                
                # 向四个方向扩散
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    
                    # 检查边界和是否为新鲜橘子
                    if (0 <= nx < rows and 0 <= ny < cols and 
                        grid[nx][ny] == 1):
                        
                        grid[nx][ny] = 2  # 变腐烂
                        fresh_count -= 1  # 新鲜橘子数量减1
                        queue.append((nx, ny))  # 新腐烂的橘子入队
            
            # 如果这轮有橘子腐烂，时间+1
            if queue:
                minutes += 1
        
        # 3. 检查是否还有新鲜橘子
        return minutes if fresh_count == 0 else -1

# 🧪 测试用例
def test_orangeRotting():
    solution = Solution()
    
    # 测试用例1
    grid1 = [[2,1,1],[1,1,0],[0,1,1]]
    print(f"测试1: {grid1} -> {solution.orangeRotting(grid1)}")  # 输出: 4
    
    # 测试用例2
    grid2 = [[2,1,1],[0,1,1],[1,0,1]]
    print(f"测试2: {grid2} -> {solution.orangeRotting(grid2)}")  # 输出: -1
    
    # 测试用例3
    grid3 = [[0,2]]
    print(f"测试3: {grid3} -> {solution.orangeRotting(grid3)}")  # 输出: 0

if __name__ == "__main__":
    test_orangeRotting()
