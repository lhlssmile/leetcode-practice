'''

给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。



示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]


提示：

1 <= s.length <= 16
s 仅由小写英文字母组成
'''
from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        """回文串分割 - 回溯算法"""
        ans = []
        path = []
        
        def is_palindrome(substr: str) -> bool:
            """判断字符串是否为回文"""
            return substr == substr[::-1]
        
        def backtrack(start: int):
            # 递归终止条件：已经处理完整个字符串
            if start == len(s):
                ans.append(path[:])  # 深拷贝当前路径
                return
            
            # 尝试所有可能的分割点
            for end in range(start + 1, len(s) + 1):
                substr = s[start:end]  # 当前子串
                
                if is_palindrome(substr):  # 如果是回文串
                    path.append(substr)    # 选择：加入路径
                    backtrack(end)         # 递归：处理剩余部分
                    path.pop()             # 撤销：回溯
        
        backtrack(0)
        return ans
    
    def partition_optimized(self, s: str) -> List[List[str]]:
        """优化版本：预处理回文判断"""
        n = len(s)
        # 预处理：dp[i][j] 表示 s[i:j+1] 是否为回文
        dp = [[False] * n for _ in range(n)]
        
        # 填充dp表
        for i in range(n):
            dp[i][i] = True  # 单个字符是回文
        
        for length in range(2, n + 1):  # 长度从2开始
            for i in range(n - length + 1):
                j = i + length - 1
                if s[i] == s[j]:
                    if length == 2 or dp[i + 1][j - 1]:
                        dp[i][j] = True
        
        ans = []
        path = []
        
        def backtrack(start: int):
            if start == n:
                ans.append(path[:])
                return
            
            for end in range(start, n):
                if dp[start][end]:  # 使用预处理的结果
                    path.append(s[start:end + 1])
                    backtrack(end + 1)
                    path.pop()
        
        backtrack(0)
        return ans


def test_partition():
    """测试函数"""
    solution = Solution()
    
    # 测试用例1
    s1 = "aab"
    result1 = solution.partition(s1)
    print(f"输入: {s1}")
    print(f"输出: {result1}")
    print(f"预期: [['a','a','b'],['aa','b']]")
    print()
    
    # 测试用例2
    s2 = "raceacar"
    result2 = solution.partition(s2)
    print(f"输入: {s2}")
    print(f"输出: {result2}")
    print()
    
    # 测试优化版本
    result3 = solution.partition_optimized(s1)
    result4 = solution.partition_optimized(s2)
    print(f"优化版本结果: {result3}")
    

def visualize_backtrack_process():
    """可视化回溯过程"""
    print("=== 回溯过程可视化 (s='aab') ===")
    s = "aab"
    path = []
    
    def backtrack_with_print(start: int, depth: int = 0):
        indent = "  " * depth
        print(f"{indent}进入 backtrack({start}), 当前路径: {path}")
        
        if start == len(s):
            print(f"{indent}✓ 找到一个解: {path}")
            return
        
        for end in range(start + 1, len(s) + 1):
            substr = s[start:end]
            is_pal = substr == substr[::-1]
            print(f"{indent}尝试子串 '{substr}' (索引{start}:{end}) - 回文: {is_pal}")
            
            if is_pal:
                path.append(substr)
                print(f"{indent}→ 选择 '{substr}', 路径变为: {path}")
                backtrack_with_print(end, depth + 1)
                path.pop()
                print(f"{indent}← 撤销 '{substr}', 路径恢复为: {path}")
    
    backtrack_with_print(0)


# 回溯算法学习要点
def backtrack_learning_tips():
    """
    回文串分割 - 回溯算法学习要点：
    
    1. 问题分析：
       - 需要找到所有可能的分割方案
       - 每个子串都必须是回文
       - 典型的"组合"问题
    
    2. 回溯三要素：
       - 选择：当前位置可以分割出哪些回文子串
       - 约束：子串必须是回文
       - 目标：分割完整个字符串
    
    3. 递归函数设计：
       def backtrack(start):  # start表示当前处理的起始位置
           if start == len(s):  # 终止条件
               收集答案
           for end in range(start+1, len(s)+1):  # 尝试所有分割点
               if is_palindrome(s[start:end]):  # 约束检查
                   做选择
                   递归
                   撤销选择
    
    4. 优化技巧：
       - 预处理回文判断（动态规划）
       - 时间复杂度：O(2^n * n) -> O(2^n)
       - 空间复杂度：O(n^2) 用于存储dp表
    
    5. 常见错误：
       - 忘记深拷贝路径：ans.append(path[:]) 而不是 ans.append(path)
       - 返回类型错误：应该是 List[List[str]] 而不是 List[List[int]]
       - 边界处理：range(start+1, len(s)+1) 注意+1
    """
    pass


if __name__ == "__main__":
    test_partition()
    print("\n" + "="*50 + "\n")
    visualize_backtrack_process()