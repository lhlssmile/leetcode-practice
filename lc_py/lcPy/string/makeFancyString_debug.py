'''
LeetCode 1957. 删除字符使字符串变好

给你一个字符串 s ，如果一个字符 连续 出现三次或者更多，就删除该字符，直到它的出现次数不超过两次。
请你返回删除后的最终字符串。题目保证答案是 唯一 的。

示例 1：
输入：s = "leeetcode"
输出："leetcode"
解释：从左到右，我们可以删除第 4 个 'e' ，得到 "leetcode" 。
没有其他需要删除的字符。

示例 2：
输入：s = "aaabaaaa"
输出："aabaa"
解释：从左到右，我们可以删除第 3 个 'a' ，得到 "aabaaaa" 。
接下来我们可以删除第 6 个 'a' ，得到 "aabaa" 。
没有其他需要删除的字符。

示例 3：
输入：s = "aab"
输出："aab"
解释：没有需要删除的字符。
'''

class Solution:
    def makeFancyString(self, s: str) -> str:
        ans = []
        cnt = 0
        
        for i, ch in enumerate(s):
            cnt += 1
            if cnt < 3:
                ans.append(ch)
            if i < len(s) - 1 and ch != s[i + 1]:
                cnt = 0
        return ''.join(ans)

class SolutionDebug(Solution):
    def makeFancyString_debug(self, s: str) -> str:
        """带调试信息的版本"""
        print(f"\n=== 调试 makeFancyString('{s}') ===")
        print(f"输入字符串长度: {len(s)}")
        print(f"字符串: {s}")
        print(f"索引:   {''.join(str(i%10) for i in range(len(s)))}")
        print()
        
        ans = []
        cnt = 0
        
        for i, ch in enumerate(s):
            print(f"步骤 {i+1}: 处理字符 '{ch}' (索引 {i})")
            
            # 更新计数
            cnt += 1
            print(f"  当前连续字符计数: {cnt}")
            
            # 判断是否添加字符
            if cnt < 3:
                ans.append(ch)
                print(f"  ✅ 计数 < 3，添加字符 '{ch}'")
                print(f"  当前结果: {''.join(ans)}")
            else:
                print(f"  ❌ 计数 >= 3，跳过字符 '{ch}'")
                print(f"  当前结果: {''.join(ans)}")
            
            # 检查是否需要重置计数
            if i < len(s) - 1 and ch != s[i + 1]:
                print(f"  🔄 下一个字符 '{s[i+1]}' 不同，重置计数")
                cnt = 0
            elif i < len(s) - 1:
                print(f"  ➡️  下一个字符 '{s[i+1]}' 相同，继续计数")
            else:
                print(f"  🏁 已到达字符串末尾")
            
            print()
        
        result = ''.join(ans)
        print(f"=== 最终结果: '{result}' ===")
        print(f"原长度: {len(s)}, 新长度: {len(result)}")
        return result

def test_cases():
    """测试用例"""
    solution = SolutionDebug()
    
    test_cases = [
        "leeetcode",
        "aaabaaaa", 
        "aab",
        "aaaa",
        "abcdef",
        "aabbcc",
        "aaabbbccc"
    ]
    
    print("🧪 LeetCode 本地调试示例 - makeFancyString")
    print("=" * 60)
    
    for i, test_case in enumerate(test_cases, 1):
        print(f"\n📝 测试用例 {i}: '{test_case}'")
        
        # 普通版本结果
        normal_result = solution.makeFancyString(test_case)
        print(f"普通版本结果: '{normal_result}'")
        
        # 调试版本
        debug_result = solution.makeFancyString_debug(test_case)
        
        # 验证结果一致性
        if normal_result == debug_result:
            print("✅ 结果一致")
        else:
            print("❌ 结果不一致！")
        
        print("-" * 60)

def step_by_step_example():
    """逐步分析示例"""
    print("\n🔍 逐步分析算法思路")
    print("=" * 40)
    
    print("\n算法核心思想:")
    print("1. 遍历字符串，维护连续相同字符的计数")
    print("2. 如果计数 < 3，则保留字符")
    print("3. 如果计数 >= 3，则跳过字符")
    print("4. 当遇到不同字符时，重置计数")
    
    print("\n关键变量:")
    print("- ans: 存储结果的列表")
    print("- cnt: 当前连续相同字符的计数")
    print("- ch: 当前处理的字符")
    print("- i: 当前字符的索引")
    
    print("\n边界条件:")
    print("- 字符串为空")
    print("- 字符串长度为1或2")
    print("- 所有字符都相同")
    print("- 没有连续超过2个的字符")

def performance_analysis():
    """性能分析"""
    print("\n⚡ 性能分析")
    print("=" * 30)
    print("时间复杂度: O(n) - 需要遍历整个字符串一次")
    print("空间复杂度: O(n) - 最坏情况下需要存储所有字符")
    print("\n优化点:")
    print("- 使用列表而不是字符串拼接，避免重复创建字符串")
    print("- 一次遍历完成，没有嵌套循环")
    print("- 及时重置计数器，避免不必要的计算")

if __name__ == '__main__':
    # 运行测试用例
    test_cases()
    
    # 逐步分析
    step_by_step_example()
    
    # 性能分析
    performance_analysis()
    
    print("\n🎯 调试技巧总结:")
    print("1. 添加详细的打印语句，显示每一步的状态")
    print("2. 可视化数据结构的变化过程")
    print("3. 验证边界条件和特殊情况")
    print("4. 对比普通版本和调试版本的结果")
    print("5. 分析时间和空间复杂度")