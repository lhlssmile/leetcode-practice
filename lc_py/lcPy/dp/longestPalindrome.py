'''
给你一个字符串 s，找到 s 中最长的 回文 子串。

示例 1：
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。

示例 2：
输入：s = "cbbd"
输出："bb"

提示：
1 <= s.length <= 1000
s 仅由数字和英文字母组成

算法思路：
这个问题确实和分割回文串有相似性！都需要判断子串是否为回文。
区别在于：
- 分割回文串：找到所有可能的回文分割方案（回溯）
- 最长回文子串：找到最长的回文子串（动态规划）

动态规划解法：
1. 状态定义：dp[i][j] 表示 s[i:j+1] 是否为回文串
2. 状态转移：
   - 如果 s[i] == s[j]：
     - 当 j - i <= 2 时，dp[i][j] = True（长度为1或2的相同字符）
     - 当 j - i > 2 时，dp[i][j] = dp[i+1][j-1]
   - 如果 s[i] != s[j]：dp[i][j] = False
3. 遍历顺序：按长度从小到大遍历
'''

class Solution:
    def longestPalindrome(self, s: str) -> str:
        """标准动态规划解法 - 不空间优化版本"""
        if not s:
            return ""
        
        n = len(s)
        # dp[i][j] 表示 s[i:j+1] 是否为回文串
        dp = [[False] * n for _ in range(n)]
        
        start = 0  # 最长回文子串的起始位置
        max_len = 1  # 最长回文子串的长度
        
        # 所有长度为1的子串都是回文
        for i in range(n):
            dp[i][i] = True
        
        # 检查长度为2的子串
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                dp[i][i + 1] = True
                start = i
                max_len = 2
        
        # 检查长度为3及以上的子串
        for length in range(3, n + 1):  # 子串长度
            for i in range(n - length + 1):  # 起始位置
                j = i + length - 1  # 结束位置
                
                # 状态转移方程
                if s[i] == s[j] and dp[i + 1][j - 1]:
                    dp[i][j] = True
                    start = i
                    max_len = length
        
        return s[start:start + max_len]
    
    def longestPalindrome_detailed(self, s: str) -> str:
        """详细版本 - 带调试信息"""
        if not s:
            return ""
        
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        
        start = 0
        max_len = 1
        
        print(f"输入字符串: {s}")
        print(f"字符串长度: {n}")
        print("\n=== 动态规划过程 ===")
        
        # 长度为1
        for i in range(n):
            dp[i][i] = True
        print("长度为1的回文串已标记")
        
        # 长度为2
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                dp[i][i + 1] = True
                start = i
                max_len = 2
                print(f"找到长度为2的回文串: {s[i:i+2]}")
        
        # 长度为3及以上
        for length in range(3, n + 1):
            print(f"\n检查长度为{length}的子串:")
            for i in range(n - length + 1):
                j = i + length - 1
                
                if s[i] == s[j] and dp[i + 1][j - 1]:
                    dp[i][j] = True
                    start = i
                    max_len = length
                    print(f"  找到回文串: {s[i:j+1]}")
        
        result = s[start:start + max_len]
        print(f"\n最长回文子串: {result}")
        return result


def test_longest_palindrome():
    """测试函数"""
    solution = Solution()
    
    test_cases = [
        "babad",
        "cbbd", 
        "a",
        "ac",
        "racecar",
        "abcdef",
        "aabbaa"
    ]
    
    print("=== 最长回文子串测试 ===")
    for s in test_cases:
        result = solution.longestPalindrome(s)
        print(f"输入: '{s}' -> 输出: '{result}'")
    
    print("\n=== 详细过程演示 ===")
    solution.longestPalindrome_detailed("babad")


def visualize_dp_table(s: str):
    """可视化DP表格"""
    if not s:
        return
    
    n = len(s)
    dp = [[False] * n for _ in range(n)]
    
    # 填充DP表格
    for i in range(n):
        dp[i][i] = True
    
    for i in range(n - 1):
        if s[i] == s[i + 1]:
            dp[i][i + 1] = True
    
    for length in range(3, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            if s[i] == s[j] and dp[i + 1][j - 1]:
                dp[i][j] = True
    
    # 打印DP表格
    print(f"\n=== DP表格可视化 (字符串: {s}) ===")
    print("   ", end="")
    for j in range(n):
        print(f"{j:3}", end="")
    print()
    
    for i in range(n):
        print(f"{i:2} ", end="")
        for j in range(n):
            if j < i:
                print("  .", end="")
            else:
                print(f"{dp[i][j]:3}", end="")
        print(f"  ({s[i]})")
    
    print("\n说明: True表示s[i:j+1]是回文串")


def compare_with_partition():
    """对比最长回文子串和分割回文串的异同"""
    print("\n=== 最长回文子串 vs 分割回文串 ===")
    print("\n相似点:")
    print("1. 都需要判断子串是否为回文")
    print("2. 都可以用动态规划预处理回文判断")
    print("3. 都涉及字符串的子串操作")
    
    print("\n不同点:")
    print("| 方面           | 最长回文子串        | 分割回文串           |")
    print("|----------------|-------------------|-------------------|")
    print("| 目标           | 找最长的回文子串     | 找所有回文分割方案    |")
    print("| 算法           | 动态规划           | 回溯算法             |")
    print("| 返回值         | 一个字符串         | 字符串列表的列表      |")
    print("| 时间复杂度     | O(n²)             | O(2^n)              |")
    print("| 空间复杂度     | O(n²)             | O(n²) + 递归栈       |")
    
    print("\n核心思想:")
    print("- 最长回文子串: 在所有回文子串中找最长的")
    print("- 分割回文串: 将字符串分割成若干回文子串")


def dp_learning_tips():
    """动态规划学习要点"""
    print("\n=== 最长回文子串 DP 学习要点 ===")
    
    print("\n1. 状态定义:")
    print("   dp[i][j] = s[i:j+1] 是否为回文串")
    
    print("\n2. 状态转移:")
    print("   if s[i] == s[j]:")
    print("       if j - i <= 2: dp[i][j] = True")
    print("       else: dp[i][j] = dp[i+1][j-1]")
    print("   else:")
    print("       dp[i][j] = False")
    
    print("\n3. 遍历顺序:")
    print("   按子串长度从小到大遍历")
    print("   确保计算dp[i][j]时，dp[i+1][j-1]已经计算过")
    
    print("\n4. 边界条件:")
    print("   - 长度为1: 都是回文")
    print("   - 长度为2: 两字符相同则为回文")
    
    print("\n5. 优化技巧:")
    print("   - 中心扩展法: O(n²)时间，O(1)空间")
    print("   - Manacher算法: O(n)时间复杂度")
    
    print("\n6. 常见错误:")
    print("   - 遍历顺序错误")
    print("   - 边界条件处理不当")
    print("   - 状态转移方程理解错误")


if __name__ == "__main__":
    test_longest_palindrome()
    visualize_dp_table("babad")
    compare_with_partition()
    dp_learning_tips()