# 力扣第583题：两个字符串的删除操作
# 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

from typing import List, Tuple

class Solution:
    # 方法一：基于最长公共子序列(LCS)的解法
    # 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    def minDistanceLCS(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        
        # 创建LCS矩阵
        lcs = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    lcs[i][j] = lcs[i - 1][j - 1] + 1
                else:
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1])
        
        # 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
        return m + n - 2 * lcs[m][n]
    
    # 方法二：直接使用动态规划
    # 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        
        # 创建DP矩阵
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        # 初始化
        for i in range(m + 1):
            dp[i][0] = i  # 删除 word1 的前 i 个字符
        for j in range(n + 1):
            dp[0][j] = j  # 删除 word2 的前 j 个字符
        
        # 动态规划
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]  # 字符相同，无需删除
                else:
                    dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1)  # 删除一个字符
        
        return dp[m][n]

# 测试函数
def test_solution():
    solution = Solution()
    
    # 测试用例
    test_cases = [
        ("sea", "eat"),           # 期望输出: 2
        ("leetcode", "etco"),     # 期望输出: 4
        ("", "a"),                 # 期望输出: 1
        ("a", ""),                 # 期望输出: 1
        ("intention", "execution") # 期望输出: 8
    ]
    
    for word1, word2 in test_cases:
        print(f'Word1: "{word1}", Word2: "{word2}"')
        print(f'方法一 (LCS): {solution.minDistanceLCS(word1, word2)}')
        print(f'方法二 (DP): {solution.minDistance(word1, word2)}')
        print("-------------------")

if __name__ == "__main__":
    test_solution()