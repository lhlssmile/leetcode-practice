'''
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。



示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：

输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"


提示：

1 <= s.length <= 30
s 由小写英文字母、数字和方括号 '[]' 组成
s 保证是一个 有效 的输入。
s 中所有整数的取值范围为 [1, 300]
'''

class Solution:
    def decodeString(self, s: str) -> str:
        """方法1: 栈解法 - 处理嵌套结构的经典方法"""
        # 数字栈：存储重复次数
        num_stack = []
        # 字符串栈：存储当前层的字符串
        str_stack = []
        # 当前数字和当前字符串
        current_num = 0
        current_str = ""
        
        for char in s:
            if char.isdigit():
                # 构建多位数字
                current_num = current_num * 10 + int(char)
            elif char == '[':
                # 遇到左括号，保存当前状态到栈中
                num_stack.append(current_num)
                str_stack.append(current_str)
                # 重置当前状态
                current_num = 0
                current_str = ""
            elif char == ']':
                # 遇到右括号，弹出栈顶进行解码
                repeat_times = num_stack.pop()
                prev_str = str_stack.pop()
                # 当前字符串重复指定次数，然后拼接到前一层字符串
                current_str = prev_str + current_str * repeat_times
            else:
                # 普通字符，直接添加到当前字符串
                current_str += char
        
        return current_str
    
    def decodeStringRecursive(self, s: str) -> str:
        """方法2: 递归解法 - 另一种思路"""
        def dfs(index):
            """返回 (解码后的字符串, 下一个处理位置)"""
            result = ""
            num = 0
            
            while index < len(s):
                char = s[index]
                
                if char.isdigit():
                    num = num * 10 + int(char)
                elif char == '[':
                    # 递归处理括号内的内容
                    sub_str, next_index = dfs(index + 1)
                    result += sub_str * num
                    num = 0
                    index = next_index
                elif char == ']':
                    # 返回当前层的结果
                    return result, index
                else:
                    # 普通字符
                    result += char
                
                index += 1
            
            return result, index
        
        return dfs(0)[0]
    
    def decodeStringDFS(self, s: str) -> str:
        """方法3: DFS + 指针 - 更直观的递归"""
        self.index = 0
        
        def dfs():
            result = ""
            num = 0
            
            while self.index < len(s):
                char = s[self.index]
                
                if char.isdigit():
                    num = num * 10 + int(char)
                elif char == '[':
                    self.index += 1  # 跳过 '['
                    sub_result = dfs()  # 递归处理
                    result += sub_result * num
                    num = 0
                elif char == ']':
                    return result
                else:
                    result += char
                
                self.index += 1
            
            return result
        
        return dfs()


if __name__ == "__main__":
    solution = Solution()
    
    print("=== 字符串解码问题 ===")
    
    # 测试用例
    test_cases = [
        "3[a]2[bc]",      # "aaabcbc"
        "3[a2[c]]",       # "accaccacc" (嵌套)
        "2[abc]3[cd]ef",  # "abcabccdcdcdef"
        "abc3[cd]xyz",    # "abccdcdcdxyz"
        "10[a]",          # 多位数字
    ]
    
    for i, test in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}: {test}")
        
        # 方法1: 栈解法
        result1 = solution.decodeString(test)
        print(f"栈解法: {result1}")
        
        # 方法2: 递归解法
        result2 = solution.decodeStringRecursive(test)
        print(f"递归解法: {result2}")
        
        # 方法3: DFS解法
        result3 = solution.decodeStringDFS(test)
        print(f"DFS解法: {result3}")
    
    print("\n=== 栈解法核心思想 ===")
    print("1. 用两个栈分别存储：")
    print("   - num_stack: 存储重复次数")
    print("   - str_stack: 存储当前层的字符串")
    print("2. 遇到 '[' 时：保存当前状态到栈，开始新的一层")
    print("3. 遇到 ']' 时：弹出栈顶，完成当前层的解码")
    print("4. 栈的特性完美匹配括号的嵌套结构")
    
    print("\n=== 嵌套处理示例: 3[a2[c]] ===")
    print("步骤分析:")
    print("1. 遇到 '3': current_num = 3")
    print("2. 遇到 '[': 保存 (3, '') 到栈，重置状态")
    print("3. 遇到 'a': current_str = 'a'")
    print("4. 遇到 '2': current_num = 2")
    print("5. 遇到 '[': 保存 (2, 'a') 到栈，重置状态")
    print("6. 遇到 'c': current_str = 'c'")
    print("7. 遇到 ']': 弹出 (2, 'a')，计算 'a' + 'c'*2 = 'acc'")
    print("8. 遇到 ']': 弹出 (3, '')，计算 '' + 'acc'*3 = 'accaccacc'")
    
    print("\n=== 三种方法对比 ===")
    print("栈解法:")
    print("  - 时间复杂度: O(n)")
    print("  - 空间复杂度: O(n)")
    print("  - 优点: 迭代实现，无递归开销，思路清晰")
    print("  - 缺点: 需要维护两个栈")
    
    print("\n递归解法:")
    print("  - 时间复杂度: O(n)")
    print("  - 空间复杂度: O(n) [递归栈]")
    print("  - 优点: 代码简洁，自然处理嵌套")
    print("  - 缺点: 递归开销，可能栈溢出")
    
    print("\nDFS解法:")
    print("  - 时间复杂度: O(n)")
    print("  - 空间复杂度: O(n) [递归栈]")
    print("  - 优点: 使用全局指针，更直观")
    print("  - 缺点: 修改了类的状态")
    
    print("\n=== 栈 vs 递归的本质 ===")
    print("- 栈是递归的迭代实现")
    print("- 递归的函数调用栈 ≈ 手动维护的栈")
    print("- 嵌套结构天然适合栈/递归处理")
    print("- 栈解法更适合处理深度嵌套（避免栈溢出）")
    print("- 递归解法代码更简洁易懂")
        
