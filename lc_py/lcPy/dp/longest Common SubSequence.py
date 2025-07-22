'''
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。



示例 1：

输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace" ，它的长度为 3 。
示例 2：

输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。
示例 3：

输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。


提示：

1 <= text1.length, text2.length <= 1000
text1 和 text2 仅由小写英文字符组成。
'''

class Solution:
    # 方法1：递归 + 记忆化 (自顶向下)
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        # 记忆化字典
        memo = {}
        
        def dfs(i, j):
            # 边界条件：任一字符串到头了
            if i < 0 or j < 0:
                return 0
            
            # 记忆化：避免重复计算
            if (i, j) in memo:
                return memo[(i, j)]
            
            # 核心逻辑：倒着比较
            if text1[i] == text2[j]:
                # 字符相同：当前字符+剩余部分的LCS
                result = 1 + dfs(i-1, j-1)
            else:
                # 字符不同：取两种情况的最大值
                result = max(dfs(i-1, j), dfs(i, j-1))
            
            memo[(i, j)] = result
            return result
        
        # 从最后一个字符开始比较
        return dfs(len(text1)-1, len(text2)-1)
    
    # 方法2：标准DP (自底向上) - 推荐面试使用
    def longestCommonSubsequence_DP(self, text1: str, text2: str) -> int:
        m, n = len(text1), len(text2)
        
        # dp[i][j] 表示 text1[0:i] 和 text2[0:j] 的LCS长度
        # 注意：这里用的是前i个字符，所以需要 (m+1) x (n+1) 的表
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        # 填表：从前往后 (自底向上)
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if text1[i-1] == text2[j-1]:  # 注意索引偏移
                    # 字符相同：继承左上角的值 + 1
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    # 字符不同：取上方和左方的最大值
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
        
        return dp[m][n]
    
    # 方法3：空间优化DP - 面试加分项
    def longestCommonSubsequence_Optimized(self, text1: str, text2: str) -> int:
        m, n = len(text1), len(text2)
        
        # 只用两行空间：上一行和当前行
        prev = [0] * (n + 1)  # 上一行
        curr = [0] * (n + 1)  # 当前行
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if text1[i-1] == text2[j-1]:
                    # 字符相同：用上一行的左上角值 + 1
                    curr[j] = prev[j-1] + 1
                else:
                    # 字符不同：取上方(prev[j])和左方(curr[j-1])的最大值
                    curr[j] = max(prev[j], curr[j-1])
            
            # 交换行：当前行变成上一行，准备处理下一行
            prev, curr = curr, prev
        
        return prev[n]

# 📚 LCS学习笔记 - 三种解法对比
"""
🎯 最长公共子序列 (Longest Common Subsequence) 学习指南

1. 问题本质：
   - 在两个字符串中找到最长的公共子序列
   - 子序列：可以不连续，但要保持相对顺序
   - 例："ace" 是 "abcde" 的子序列

2. 核心思路：
   - 比较两个字符串的字符
   - 相同：LCS长度 +1，继续比较剩余部分
   - 不同：分别尝试跳过其中一个字符，取最大值

3. 状态转移方程：
   dp[i][j] = {
       dp[i-1][j-1] + 1,           if text1[i-1] == text2[j-1]
       max(dp[i-1][j], dp[i][j-1]), if text1[i-1] != text2[j-1]
   }

4. 三种解法比较：
   方法1 - 递归+记忆化：
   ✅ 思路直观，容易理解
   ✅ 自顶向下，符合人类思维
   ❌ 递归深度可能很大
   
   方法2 - 标准DP：
   ✅ 经典解法，面试常考
   ✅ 自底向上，避免递归
   ✅ 易于理解和实现
   ❌ 空间复杂度 O(m*n)
   
   方法3 - 空间优化DP：
   ✅ 空间复杂度降到 O(n)
   ✅ 面试加分项
   ❌ 稍微复杂一些

5. 记忆技巧：
   - "相同就加1，不同就取max"
   - DP表格的含义：dp[i][j] = 前i个字符 vs 前j个字符的LCS
   - 边界：空字符串的LCS为0
"""

# 🧪 测试所有方法
def test_all_methods():
    solution = Solution()
    
    # 测试用例
    test_cases = [
        ("abcde", "ace", 3),
        ("abc", "abc", 3), 
        ("abc", "def", 0),
        ("bl", "yby", 1),
        ("ezupkr", "ubmrapg", 2)  # 复杂一点的例子
    ]
    
    print("=== LCS 三种方法测试对比 ===")
    
    for text1, text2, expected in test_cases:
        print(f"\n测试: '{text1}' vs '{text2}' (期望: {expected})")
        
        # 方法1：递归+记忆化
        result1 = solution.longestCommonSubsequence(text1, text2)
        print(f"  方法1 (递归+记忆化): {result1}")
        
        # 方法2：标准DP
        result2 = solution.longestCommonSubsequence_DP(text1, text2)
        print(f"  方法2 (标准DP):     {result2}")
        
        # 方法3：空间优化DP
        result3 = solution.longestCommonSubsequence_Optimized(text1, text2)
        print(f"  方法3 (空间优化):   {result3}")
        
        # 验证结果一致性
        if result1 == result2 == result3 == expected:
            print(f"  ✅ 所有方法结果一致且正确")
        else:
            print(f"  ❌ 结果不一致或错误")

# 📊 DP过程可视化 (帮助理解)
def visualize_dp_process(text1: str, text2: str):
    print(f"\n=== DP过程可视化: '{text1}' vs '{text2}' ===")
    
    m, n = len(text1), len(text2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 填表过程
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i-1] == text2[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
                print(f"  ({i},{j}): '{text1[i-1]}' == '{text2[j-1]}' → dp[{i}][{j}] = {dp[i][j]}")
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                print(f"  ({i},{j}): '{text1[i-1]}' != '{text2[j-1]}' → dp[{i}][{j}] = max({dp[i-1][j]}, {dp[i][j-1]}) = {dp[i][j]}")
    
    # 打印最终DP表
    print("\n最终DP表:")
    print("    ", end="")
    for j in range(n + 1):
        if j == 0:
            print("ε", end="   ")
        else:
            print(f"{text2[j-1]}", end="   ")
    print()
    
    for i in range(m + 1):
        if i == 0:
            print("ε ", end=" ")
        else:
            print(f"{text1[i-1]} ", end=" ")
        for j in range(n + 1):
            print(f"{dp[i][j]}", end="   ")
        print()
    
    return dp[m][n]

if __name__ == "__main__":
    test_all_methods()
    
    # 可视化一个简单例子
    result = visualize_dp_process("abc", "ac")
    print(f"\n最终结果: {result}")
