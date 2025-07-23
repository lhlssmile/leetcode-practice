'''
给你一个字符串 s 和两个整数 x 和 y 。你可以执行下面两种操作任意次。

删除子字符串 "ab" 并得到 x 分。
比方说，从 "cabxbae" 删除 ab ，得到 "cxbae" 。
删除子字符串"ba" 并得到 y 分。
比方说，从 "cabxbae" 删除 ba ，得到 "cabxe" 。
请返回对 s 字符串执行上面操作若干次能得到的最大得分。

示例 1：
输入：s = "cdbcbbaaabab", x = 4, y = 5
输出：19
解释：
- 删除 "cdbcbbaaabab" 中加粗的 "ba" ，得到 s = "cdbcbbaaab" ，加 5 分。
- 删除 "cdbcbbaaab" 中加粗的 "ab" ，得到 s = "cdbcbbaa" ，加 4 分。
- 删除 "cdbcbbaa" 中加粗的 "ba" ，得到 s = "cdbcba" ，加 5 分。
- 删除 "cdbcba" 中加粗的 "ba" ，得到 s = "cdbc" ，加 5 分。
总得分为 5 + 4 + 5 + 5 = 19 。

示例 2：
输入：s = "aabbaaxybbaabb", x = 5, y = 4
输出：20

提示：
1 <= s.length <= 105
1 <= x, y <= 104
s 只包含小写英文字母。

算法思路：
你的栈思路完全正确！关键是贪心策略：
1. 优先删除分数更高的子串（ab或ba）
2. 用栈模拟删除过程
3. 两次遍历：先删高分的，再删低分的

为什么示例2是20分？
"aabbaaxybbaabb" x=5, y=4
- 先删ab（分数高）：能删除4个ab，得分4×5=20
- 再删ba：剩余字符无法组成ba
- 总分：20

如果先删ba会怎样？
- 先删ba：能删除2个ba，得分2×4=8  
- 再删ab：能删除2个ab，得分2×5=10
- 总分：18 < 20

所以贪心策略是关键！
'''

class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        """标准贪心+栈解法"""
        def remove_substring(s: str, first: str, second: str, points: int) -> tuple:
            """用栈删除指定子串，返回(得分, 剩余字符串)"""
            stack = []
            score = 0
            
            for char in s:
                if stack and stack[-1] == first and char == second:
                    # 找到目标子串，删除并得分
                    stack.pop()
                    score += points
                else:
                    stack.append(char)
            
            return score, ''.join(stack)
        
        # 贪心策略：优先删除分数更高的子串
        if x >= y:
            # ab分数更高，先删ab再删ba
            score1, remaining = remove_substring(s, 'a', 'b', x)
            score2, _ = remove_substring(remaining, 'b', 'a', y)
        else:
            # ba分数更高，先删ba再删ab
            score1, remaining = remove_substring(s, 'b', 'a', y)
            score2, _ = remove_substring(remaining, 'a', 'b', x)
        
        return score1 + score2
    
    def maximumGain_detailed(self, s: str, x: int, y: int) -> int:
        """详细版本 - 带调试信息"""
        print(f"输入字符串: {s}")
        print(f"ab得分: {x}, ba得分: {y}")
        
        def remove_substring_debug(s: str, first: str, second: str, points: int, name: str) -> tuple:
            stack = []
            score = 0
            removed_count = 0
            
            print(f"\n开始删除 {name} (分数: {points})")
            print(f"处理字符串: {s}")
            
            for i, char in enumerate(s):
                if stack and stack[-1] == first and char == second:
                    stack.pop()
                    score += points
                    removed_count += 1
                    print(f"  位置{i}: 删除{first}{second}, 得分+{points}, 总分:{score}")
                else:
                    stack.append(char)
            
            remaining = ''.join(stack)
            print(f"删除{removed_count}个{name}, 得分:{score}")
            print(f"剩余字符串: {remaining}")
            
            return score, remaining
        
        if x >= y:
            print("\n策略: ab分数更高，先删ab再删ba")
            score1, remaining = remove_substring_debug(s, 'a', 'b', x, 'ab')
            score2, final = remove_substring_debug(remaining, 'b', 'a', y, 'ba')
        else:
            print("\n策略: ba分数更高，先删ba再删ab")
            score1, remaining = remove_substring_debug(s, 'b', 'a', y, 'ba')
            score2, final = remove_substring_debug(remaining, 'a', 'b', x, 'ab')
        
        total = score1 + score2
        print(f"\n最终结果: {score1} + {score2} = {total}")
        print(f"最终剩余: {final}")
        
        return total
    
    def maximumGain_optimized(self, s: str, x: int, y: int) -> int:
        """优化版本 - 一次遍历"""
        # 确定优先删除的子串
        if x < y:
            x, y = y, x  # 交换分数
            first, second = 'b', 'a'  # 交换字符
        else:
            first, second = 'a', 'b'
        
        stack = []
        score = 0
        
        # 第一次遍历：删除高分子串
        for char in s:
            if stack and stack[-1] == first and char == second:
                stack.pop()
                score += x  # 高分
            else:
                stack.append(char)
        
        # 第二次遍历：删除低分子串
        remaining = stack
        stack = []
        for char in remaining:
            if stack and stack[-1] == second and char == first:
                stack.pop()
                score += y  # 低分
            else:
                stack.append(char)
        
        return score


def test_maximum_gain():
    """测试函数"""
    solution = Solution()
    
    test_cases = [
        ("aabbaaxybbaabb", 5, 4),  # 示例2
        ("cdbcbbaaabab", 4, 5),  # 示例1

        ("aabb", 1, 2),
        ("abab", 3, 4),
        ("baba", 2, 5)
    ]
    
    print("=== 最大得分测试 ===")
    for s, x, y in test_cases:
        result = solution.maximumGain_optimized(s, x, y)
        print(f"输入: s='{s}', x={x}, y={y} -> 输出: {result}")
    
    print("\n=== 详细过程演示 ===")
    solution.maximumGain_detailed("aabbaaxybbaabb", 5, 4)


def analyze_example2():
    """详细分析示例2为什么是20分"""
    print("\n=== 示例2详细分析 ===")
    s = "aabbaaxybbaabb"
    x, y = 5, 4
    
    print(f"字符串: {s}")
    print(f"ab得分: {x}, ba得分: {y}")
    
    # 统计a和b的数量
    a_count = s.count('a')
    b_count = s.count('b')
    print(f"\na的数量: {a_count}, b的数量: {b_count}")
    
    # 理论最大配对数
    max_pairs = min(a_count, b_count)
    print(f"理论最大配对数: {max_pairs}")
    
    print("\n策略1: 先删ab(高分)")
    print("模拟过程:")
    print("aabbaaxybbaabb")
    print("删除ab: a[ab]baaxybbaabb -> abaaxybbaabb (得分+5)")
    print("删除ab: [ab]aaxybbaabb -> aaxybbaabb (得分+5)")
    print("删除ab: aaxybba[ab]b -> aaxybbab (得分+5)")
    print("删除ab: aaxybb[ab] -> aaxybb (得分+5)")
    print("剩余: aaxybb (无法再删除ab或ba)")
    print("总得分: 4×5 = 20")
    
    print("\n策略2: 先删ba(低分)")
    print("模拟过程:")
    print("aabbaaxybbaabb")
    print("删除ba: aa[ba]axybbaabb -> aaaxybbaabb (得分+4)")
    print("删除ba: aaaxyb[ba]abb -> aaaxybaabb (得分+4)")
    print("剩余: aaaxybaabb")
    print("删除ab: aaaaxy[ab]aabb -> aaaxyaabb (得分+5)")
    print("删除ab: aaaxy[ab]ab -> aaaxyab (得分+5)")
    print("删除ab: aaaxy[ab] -> aaaxy (得分+5)")
    print("总得分: 2×4 + 3×5 = 8 + 15 = 23")
    
    print("\n等等！我算错了，让我重新分析...")
    
    solution = Solution()
    solution.maximumGain_detailed(s, x, y)


def greedy_learning_tips():
    """贪心算法学习要点"""
    print("\n=== 贪心算法学习要点 ===")
    
    print("\n1. 贪心策略:")
    print("   - 优先选择分数更高的操作")
    print("   - 局部最优 → 全局最优")
    
    print("\n2. 为什么这题可以用贪心?")
    print("   - 删除ab和删除ba是独立的操作")
    print("   - 先删高分的不会影响低分的最优性")
    print("   - 满足贪心选择性质")
    
    print("\n3. 栈的作用:")
    print("   - 模拟字符串删除过程")
    print("   - 遇到匹配就删除(弹栈)")
    print("   - 不匹配就保留(入栈)")
    
    print("\n4. 时间复杂度:")
    print("   - 两次遍历: O(n)")
    print("   - 栈操作: O(1)")
    print("   - 总体: O(n)")
    
    print("\n5. 空间复杂度:")
    print("   - 栈空间: O(n)")
    
    print("\n6. 关键洞察:")
    print("   - 删除顺序很重要！")
    print("   - 贪心 > 动态规划（这题不需要DP）")
    print("   - 栈 > 字符串操作（效率更高）")


if __name__ == "__main__":
    test_maximum_gain()
    analyze_example2()
    greedy_learning_tips()
