'''
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

示例 1：
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1

示例 2：
输入：coins = [2], amount = 3
输出：-1

示例 3：
输入：coins = [1], amount = 0
输出：0
'''
from typing import List


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        # 方法1：递归 + 记忆化（自顶向下）
        memo = {}
        
        def dfs(remaining: int) -> int:
            # 基础情况
            if remaining == 0:
                return 0
            if remaining < 0:
                return float('inf')  # 无效状态
            
            # 记忆化
            if remaining in memo:
                return memo[remaining]
            
            # 尝试每种硬币
            min_coins = float('inf')
            for coin in coins:
                if coin <= remaining:
                    result = dfs(remaining - coin)
                    if result != float('inf'):
                        min_coins = min(min_coins, result + 1)
            
            memo[remaining] = min_coins
            return min_coins
        
        result = dfs(amount)
        return result if result != float('inf') else -1
    
    # 方法2：纯递归（会超时，仅供理解）
    def coinChangeRecursive(self, coins: List[int], amount: int) -> int:
        def dfs(remaining: int) -> int:
            # 基础情况
            if remaining == 0:
                return 0
            if remaining < 0:
                return float('inf')
            
            # 尝试每种硬币
            min_coins = float('inf')
            for coin in coins:
                if coin <= remaining:
                    result = dfs(remaining - coin)
                    if result != float('inf'):
                        min_coins = min(min_coins, result + 1)
            
            return min_coins
        
        result = dfs(amount)
        return result if result != float('inf') else -1
    
    # 方法3：动态规划（自底向上）
    def coinChangeDP(self, coins: List[int], amount: int) -> int:
        # dp[i] 表示凑成金额 i 所需的最少硬币数
        dp = [float('inf')] * (amount + 1)
        dp[0] = 0  # 凑成0元需要0个硬币
        
        for i in range(1, amount + 1):
            for coin in coins:
                if coin <= i:
                    dp[i] = min(dp[i], dp[i - coin] + 1)
        
        return dp[amount] if dp[amount] != float('inf') else -1


if __name__ == "__main__":
    s = Solution()
    
    # 测试用例
    test_cases = [
        ([1, 2, 5], 11),  # 期望输出: 3
        ([2], 3),         # 期望输出: -1
        ([1], 0),         # 期望输出: 0
        ([1, 3, 4], 6),   # 期望输出: 2 (3+3)
    ]
    
    for coins, amount in test_cases:
        print(f"\n=== 测试: coins={coins}, amount={amount} ===")
        print(f"递归+记忆化: {s.coinChange(coins, amount)}")
        print(f"动态规划: {s.coinChangeDP(coins, amount)}")
        # print(f"纯递归: {s.coinChangeRecursive(coins, amount)}")  # 大数据会超时
