'''
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。



示例 1：

输入：n = 12
输出：3
解释：12 = 4 + 4 + 4
示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9

提示：

1 <= n <= 104
'''

class Solution:
    def numSquares(self, n: int) -> int:
        # 使用Python @cache装饰器版本（更快！）
        return self.recursive_with_cache(n)
    
    def recursive_with_memo(self, n: int) -> int:
        """方法1: 递归 + 记忆化 (你的思路！)"""
        import math
        
        # 记忆化字典
        memo = {}
        
        def dfs(remaining):
            """递归函数：计算remaining需要的最少完全平方数个数"""
            # 基础情况
            if remaining == 0:
                return 0
            if remaining < 0:
                return float('inf')  # 不可能的情况
            
            # 记忆化检查
            if remaining in memo:
                return memo[remaining]
            
            # 找到所有可能的完全平方数
            max_sqrt = int(math.sqrt(remaining))  # 你提到的 log2 其实是 sqrt！
            min_count = float('inf')
            
            # 尝试所有可能的完全平方数：1², 2², 3², ..., max_sqrt²
            for i in range(1, max_sqrt + 1):
                square = i * i  # 1, 4, 9, 16, ...
                # 递归：用了一个square，还需要多少个？
                count = 1 + dfs(remaining - square)
                min_count = min(min_count, count)
            
            # 记忆化存储
            memo[remaining] = min_count
            return min_count
        
        return dfs(n)
    
    def recursive_with_cache(self, n: int) -> int:
        """方法1.5: 使用Python的@cache装饰器 (更简洁！)"""
        from functools import cache
        import math
        
        @cache  # 🚀 Python内置记忆化！
        def dfs(remaining):
            """递归函数：计算remaining需要的最少完全平方数个数"""
            # 基础情况
            if remaining == 0:
                return 0
            if remaining < 0:
                return float('inf')
            
            # 找到所有可能的完全平方数
            max_sqrt = int(math.sqrt(remaining))
            min_count = float('inf')
            
            # 尝试所有可能的完全平方数
            for i in range(1, max_sqrt + 1):
                square = i * i
                count = 1 + dfs(remaining - square)
                min_count = min(min_count, count)
            
            return min_count
        
        return dfs(n)
    
    def dp_solution(self, n: int) -> int:
        """方法2: 动态规划 (递推)"""
        # dp[i] 表示数字i需要的最少完全平方数个数
        dp = [float('inf')] * (n + 1)
        dp[0] = 0  # 0需要0个完全平方数
        
        # 从1到n逐个计算
        for i in range(1, n + 1):
            # 尝试所有可能的完全平方数
            j = 1
            while j * j <= i:
                square = j * j
                dp[i] = min(dp[i], dp[i - square] + 1)
                j += 1
        
        return dp[n]
    
    def bfs_solution(self, n: int) -> int:
        """方法3: BFS解法 (层序遍历)"""
        from collections import deque
        import math
        
        if n == 0:
            return 0
        
        # 预计算所有可能的完全平方数
        squares = []
        i = 1
        while i * i <= n:
            squares.append(i * i)
            i += 1
        
        # BFS
        queue = deque([n])
        visited = {n}
        level = 0
        
        while queue:
            level += 1
            size = len(queue)
            
            for _ in range(size):
                current = queue.popleft()
                
                # 尝试减去每个完全平方数
                for square in squares:
                    next_val = current - square
                    
                    if next_val == 0:
                        return level
                    
                    if next_val > 0 and next_val not in visited:
                        visited.add(next_val)
                        queue.append(next_val)
        
        return level


# 测试和解析
def test_and_explain():
    solution = Solution()
    
    # 测试用例
    test_cases = [12, 13, 1, 4, 7]
    
    print("=== 完全平方数问题详解 ===")
    print()
    
    for n in test_cases:
        result = solution.numSquares(n)
        print(f"n = {n}, 最少需要 {result} 个完全平方数")
        
        # 手动分析过程
        import math
        max_sqrt = int(math.sqrt(n))
        squares = [i*i for i in range(1, max_sqrt + 1)]
        print(f"  可用的完全平方数: {squares}")
        
        if n == 12:
            print(f"  分析: 12 = 4 + 4 + 4 (3个4)")
        elif n == 13:
            print(f"  分析: 13 = 4 + 9 (1个4 + 1个9)")
        print()
    
    print("=== 递归思路详解 ===")
    print("🎯 核心思想:")
    print("1. dfs(n) = 求n需要的最少完全平方数个数")
    print("2. 状态转移: dfs(n) = min(1 + dfs(n - square)) for all squares <= n")
    print("3. 记忆化: 避免重复计算相同的子问题")
    print()
    
    print("🔍 递归过程 (以n=13为例):")
    print("dfs(13):")
    print("  尝试 1²=1: 1 + dfs(12)")
    print("  尝试 2²=4: 1 + dfs(9)")
    print("  尝试 3²=9: 1 + dfs(4)")
    print("  取最小值")
    print()
    
    print("💡 记忆化的关键:")
    print("- memo[remaining] 存储remaining需要的最少个数")
    print("- 避免重复计算，提高效率")
    print("- 时间复杂度: O(n * sqrt(n))")
    print("- 空间复杂度: O(n)")
    print()
    
    print("🚀 三种方法对比:")
    print("1. 递归+记忆化: 思路直观，自顶向下")
    print("2. 动态规划: 效率高，自底向上")
    print("3. BFS: 层序遍历，保证最优解")


if __name__ == "__main__":
    test_and_explain()
        