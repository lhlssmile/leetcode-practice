'''
给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。



示例 1：

输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
示例 2：

输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
示例 3：

输入：s = ""
输出：0


提示：

0 <= s.length <= 3 * 104
s[i] 为 '(' 或 ')'
'''
from functools import cache


class Solution:
    # 方法1：动态规划（经典解法）
    def longestValidParentheses(self, s: str) -> int:
        if not s:
            return 0
        
        n = len(s)
        # dp[i] 表示以 s[i] 结尾的最长有效括号长度
        dp = [0] * n
        max_len = 0
        
        for i in range(1, n):
            if s[i] == ')':
                if s[i-1] == '(':
                    # 情况1: ...() 形式
                    dp[i] = (dp[i-2] if i >= 2 else 0) + 2
                elif dp[i-1] > 0:
                    # 情况2: ...)) 形式，需要检查匹配的左括号
                    match_pos = i - dp[i-1] - 1
                    if match_pos >= 0 and s[match_pos] == '(':
                        dp[i] = dp[i-1] + 2 + (dp[match_pos-1] if match_pos > 0 else 0)
                
                max_len = max(max_len, dp[i])
        
        return max_len
    
    # 方法2：栈解法（直观易懂）
    def longestValidParenthesesStack(self, s: str) -> int:
        if not s:
            return 0
        
        stack = [-1]  # 栈底放-1作为基准
        max_len = 0
        
        for i, char in enumerate(s):
            if char == '(':
                stack.append(i)
            else:  # char == ')'
                stack.pop()
                if not stack:
                    # 栈空了，说明当前右括号无法匹配
                    stack.append(i)
                else:
                    # 计算当前有效括号长度
                    max_len = max(max_len, i - stack[-1])
        
        return max_len
    
    # 方法3：递归+记忆化（你提到的思路）
    def longestValidParenthesesMemo(self, s: str) -> int:
        if not s:
            return 0
        
        n = len(s)
        
        @cache
        def dfs(i: int) -> int:
            """返回以位置i结尾的最长有效括号长度"""
            if i <= 0:
                return 0
            
            if s[i] == '(':
                return 0  # 左括号结尾不可能形成有效括号
            
            # s[i] == ')'
            if s[i-1] == '(':
                # 情况1: ...() 形式
                return (dfs(i-2) if i >= 2 else 0) + 2
            else:
                # 情况2: ...)) 形式
                prev_len = dfs(i-1)
                if prev_len > 0:
                    match_pos = i - prev_len - 1
                    if match_pos >= 0 and s[match_pos] == '(':
                        return prev_len + 2 + (dfs(match_pos-1) if match_pos > 0 else 0)
            
            return 0
        
        # 计算所有位置的最大值
        return max(dfs(i) for i in range(n))
    
    # 方法4：双向扫描（O(1)空间复杂度）
    def longestValidParenthesesTwoPass(self, s: str) -> int:
        if not s:
            return 0
        
        def scan(s, left_char, right_char):
            left = right = max_len = 0
            for char in s:
                if char == left_char:
                    left += 1
                else:
                    right += 1
                
                if left == right:
                    max_len = max(max_len, 2 * right)
                elif right > left:
                    left = right = 0
            
            return max_len
        
        # 从左到右扫描
        left_to_right = scan(s, '(', ')')
        # 从右到左扫描
        right_to_left = scan(s[::-1], ')', '(')
        
        return max(left_to_right, right_to_left)


# 测试代码
def test_solutions():
    solution = Solution()
    
    test_cases = [
        "((()))",   # 期望输出: 6
        ")()()))",# 期望输出: 4
        "(()",      # 期望输出: 2
        ")()())",   # 期望输出: 4
        "",         # 期望输出: 0
        "()(()",    # 期望输出: 2
        "()(())",   # 期望输出: 6

        "(()())",   # 期望输出: 6
    ]
    
    print("=== 最长有效括号测试 ===")
    
    for i, s in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}: '{s}'")
        
        result1 = solution.longestValidParentheses(s)
        result2 = solution.longestValidParenthesesStack(s)
        result3 = solution.longestValidParenthesesMemo(s)
        result4 = solution.longestValidParenthesesTwoPass(s)
        
        print(f"  动态规划: {result1}")
        print(f"  栈解法: {result2}")
        print(f"  递归记忆化: {result3}")
        print(f"  双向扫描: {result4}")
        
        # 验证结果一致性
        if result1 == result2 == result3 == result4:
            print(f"  ✓ 所有方法结果一致: {result1}")
        else:
            print(f"  ✗ 结果不一致！")


if __name__ == "__main__":
    test_solutions()


"""
=== 最长有效括号问题解法分析 ===

【问题核心】
找出字符串中最长的有效（格式正确且连续）括号子串长度

【四种解法对比】

1. 动态规划（经典推荐）
   思路：dp[i] = 以位置i结尾的最长有效括号长度
   状态转移：
   - s[i] == '(' : dp[i] = 0
   - s[i] == ')' and s[i-1] == '(' : dp[i] = dp[i-2] + 2
   - s[i] == ')' and s[i-1] == ')' : 需要找匹配的左括号
   时间复杂度：O(n)
   空间复杂度：O(n)
   优点：思路清晰，易于理解和实现

2. 栈解法（直观易懂）
   思路：用栈记录未匹配的括号位置
   - 栈底始终保持-1作为基准
   - 遇到'('压入位置，遇到')'弹出并计算长度
   时间复杂度：O(n)
   空间复杂度：O(n)
   优点：直观，容易想到
   缺点：需要额外栈空间

3. 递归+记忆化（你的思路）
   思路：从右往左递归，记忆化避免重复计算
   - dfs(i) = 以位置i结尾的最长有效括号长度
   - 利用@cache装饰器自动记忆化
   时间复杂度：O(n)
   空间复杂度：O(n)
   优点：递归思路自然，记忆化优化性能
   缺点：递归深度可能较大

4. 双向扫描（空间最优）
   思路：分别从左到右和从右到左扫描
   - 左到右：处理右括号过多的情况
   - 右到左：处理左括号过多的情况
   时间复杂度：O(n)
   空间复杂度：O(1)
   优点：空间复杂度最优
   缺点：需要两次扫描，思路较复杂

【关键技巧】

1. 状态定义
   - 以某位置结尾的最长长度（而非以某位置开始）
   - 这样可以利用前面的计算结果

2. 边界处理
   - 空字符串返回0
   - 左括号结尾的子串长度为0
   - 注意数组越界检查

3. 匹配策略
   - 只有右括号能结束有效括号串
   - 需要向前查找对应的左括号
   - 连续的有效括号可以合并

【复杂度分析】
所有方法时间复杂度都是O(n)，但空间复杂度不同：
- 动态规划、栈解法、递归记忆化：O(n)
- 双向扫描：O(1)

【算法选择建议】
1. 面试推荐：动态规划（思路清晰，易于解释）
2. 空间受限：双向扫描
3. 理解括号匹配：栈解法
4. 喜欢递归：递归+记忆化

【扩展思考】
1. 如果要求返回最长有效括号子串本身？
2. 如果括号类型增加（如[]、{}）？
3. 如果要求所有有效括号子串？
4. 动态规划的状态还可以怎么定义？

你提到的"倒着往回写"和"右括号匹配左括号"的思路是正确的！
递归+记忆化确实是一个很好的解法，特别适合理解问题的本质。
"""
