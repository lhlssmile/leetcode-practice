'''
生成括号问题 - 经典回溯算法

给定 n 对括号，生成所有有效的括号组合。

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例 2：
输入：n = 1
输出：["()"]

提示：
1 <= n <= 8
'''
from typing import List


class Solution:
    # 方法1：回溯算法 + 栈验证 (你的思路优化版)
    def generateParenthesis(self, n: int) -> List[str]:
        """
        🎯 核心思想：回溯 + 栈验证括号有效性
        
        你的思路很对！用栈来验证括号的有效性：
        - 遇到 '(' 就入栈
        - 遇到 ')' 就出栈（如果栈为空则无效）
        - 最终栈必须为空
        """
        ans = []
        path = []  # 当前构建的括号序列
        
        def dfs(i: int) -> None:
            # 剪枝：如果当前长度已经超过2n，直接返回
            if i == 2 * n:
                # 验证括号序列是否有效
                if is_valid(path):
                    ans.append(''.join(path))
                return
            
            # 选择 '('
            path.append('(')
            dfs(i + 1)
            path.pop()  # 回溯
            
            # 选择 ')'
            path.append(')')
            dfs(i + 1)
            path.pop()  # 回溯
        
        def is_valid(brackets: List[str]) -> bool:
            """验证括号序列是否有效"""
            stack = []
            for bracket in brackets:
                if bracket == '(':
                    stack.append(bracket)
                else:  # bracket == ')'
                    if not stack:
                        return False
                    stack.pop()
            return len(stack) == 0
        
        dfs(0)
        return ans
    
    # 方法2：优化回溯 - 边构建边验证 (推荐)
    def generateParenthesis_Optimized(self, n: int) -> List[str]:
        """
        🚀 优化思路：在构建过程中就进行剪枝
        
        关键观察：
        1. 左括号数量不能超过 n
        2. 右括号数量不能超过左括号数量
        3. 右括号数量不能超过 n
        """
        ans = []
        path = []
        
        def dfs(left_count: int, right_count: int) -> None:
            # 终止条件：生成了 n 对括号
            if left_count == n and right_count == n:
                ans.append(''.join(path))
                return
            
            # 剪枝 + 选择
            # 选择 '('：左括号数量不能超过 n
            if left_count < n:
                path.append('(')
                dfs(left_count + 1, right_count)
                path.pop()  # 回溯
            
            # 选择 ')'：右括号数量不能超过左括号数量
            if right_count < left_count:
                path.append(')')
                dfs(left_count, right_count + 1)
                path.pop()  # 回溯
        
        dfs(0, 0)
        return ans
    
    # 方法3：字符串拼接版本 (更简洁)
    def generateParenthesis_String(self, n: int) -> List[str]:
        """
        🎨 字符串版本：不用数组，直接拼接字符串
        """
        ans = []
        
        def dfs(current: str, left: int, right: int) -> None:
            # 终止条件
            if left == n and right == n:
                ans.append(current)
                return
            
            # 添加左括号
            if left < n:
                dfs(current + '(', left + 1, right)
            
            # 添加右括号
            if right < left:
                dfs(current + ')', left, right + 1)
        
        dfs('', 0, 0)
        return ans
    
    # 方法4：动态规划解法 (了解即可)
    def generateParenthesis_DP(self, n: int) -> List[str]:
        """
        💡 DP思路：f(n) = "(" + f(i) + ")" + f(n-1-i) for i in [0, n-1]
        
        例如 f(3) 可以分解为：
        - "(" + f(0) + ")" + f(2)
        - "(" + f(1) + ")" + f(1) 
        - "(" + f(2) + ")" + f(0)
        """
        if n == 0:
            return ['']
        
        ans = []
        for i in range(n):
            # 左边 i 对括号，右边 n-1-i 对括号
            for left in self.generateParenthesis_DP(i):
                for right in self.generateParenthesis_DP(n - 1 - i):
                    ans.append(f'({left}){right}')
        
        return ans


# 📚 回溯算法学习笔记
"""
🎯 回溯算法核心思想：

1. 什么是回溯？
   - 尝试所有可能的解决方案
   - 当发现当前路径不可行时，"回退"到上一步
   - 继续尝试其他可能性

2. 回溯三要素：
   - 选择：每一步有哪些选择？(本题：选 '(' 或 ')')
   - 约束：什么情况下选择无效？(本题：右括号不能超过左括号)
   - 目标：什么时候找到解？(本题：生成了 n 对括号)

3. 回溯模板：
   def backtrack(路径, 选择列表):
       if 满足结束条件:
           result.add(路径)
           return
       
       for 选择 in 选择列表:
           做选择
           backtrack(路径, 选择列表)
           撤销选择  # 这就是"回溯"

4. 本题的关键剪枝：
   - 左括号数量 <= n
   - 右括号数量 <= 左括号数量
   - 这样可以避免生成无效的括号序列

5. 时间复杂度：
   - 第 n 个卡特兰数：C_n = (2n)! / ((n+1)! * n!)
   - 约为 O(4^n / n^(3/2))
"""


# 🧪 测试函数
def test_generate_parenthesis():
    solution = Solution()
    
    test_cases = [
        (1, ["()"]),
        (2, ["(())", "()()"]),
        (3, ["((()))", "(()())", "(())()", "()(())", "()()()"])
    ]
    
    print("=== 生成括号测试 ===")
    
    for n, expected in test_cases:
        print(f"\nn = {n} (期望 {len(expected)} 种组合):")
        
        # 测试方法1：回溯 + 栈验证
        result1 = solution.generateParenthesis(n)
        result1.sort()
        print(f"  方法1 (回溯+栈): {result1}")
        
        # 测试方法2：优化回溯
        result2 = solution.generateParenthesis_Optimized(n)
        result2.sort()
        print(f"  方法2 (优化回溯): {result2}")
        
        # 测试方法3：字符串版本
        result3 = solution.generateParenthesis_String(n)
        result3.sort()
        print(f"  方法3 (字符串版): {result3}")
        
        # 验证结果
        expected_sorted = sorted(expected)
        if result1 == result2 == result3 == expected_sorted:
            print(f"  ✅ 所有方法结果一致且正确")
        else:
            print(f"  ❌ 结果不一致或错误")
            print(f"     期望: {expected_sorted}")


# 🎨 可视化回溯过程
def visualize_backtrack_process(n: int):
    print(f"\n=== 回溯过程可视化 (n={n}) ===")
    
    ans = []
    path = []
    step = [0]  # 用列表包装以便在内部函数中修改
    
    def dfs(left: int, right: int, depth: int = 0) -> None:
        step[0] += 1
        indent = "  " * depth
        print(f"{indent}步骤{step[0]}: path={''.join(path)}, left={left}, right={right}")
        
        # 终止条件
        if left == n and right == n:
            ans.append(''.join(path))
            print(f"{indent}✅ 找到解: {''.join(path)}")
            return
        
        # 选择 '('
        if left < n:
            print(f"{indent}尝试添加 '('")
            path.append('(')
            dfs(left + 1, right, depth + 1)
            path.pop()
            print(f"{indent}回溯，移除 '('")
        
        # 选择 ')'
        if right < left:
            print(f"{indent}尝试添加 ')'")
            path.append(')')
            dfs(left, right + 1, depth + 1)
            path.pop()
            print(f"{indent}回溯，移除 ')'")
    
    dfs(0, 0)
    print(f"\n最终结果: {ans}")
    return ans


if __name__ == '__main__':
    test_generate_parenthesis()
    
    # 可视化小例子
    print("\n" + "="*50)
    visualize_backtrack_process(2)