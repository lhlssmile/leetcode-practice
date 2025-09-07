# LeetCode 150: 逆波兰表达式求值
# 根据逆波兰表示法，求表达式的值

from typing import List

class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        st = []
        for c in tokens:
            if c in "+-*/":
                b = st.pop()  # 右操作数
                a = st.pop()  # 左操作数
                if c == "+":
                    st.append(a + b)
                elif c == "-":
                    st.append(a - b)
                elif c == "*":
                    st.append(a * b)
                else:  # 除法
                    # Python 的 // 对负数是向下取整，所以要特殊处理成"向零截断"
                    st.append(int(a / b))
            else:
                st.append(int(c))
        return st[-1]

# 函数式编程风格
def eval_rpn_functional(tokens: List[str]) -> int:
    from functools import reduce
    
    def process_token(stack, token):
        if token in "+-*/":
            b, a = stack[-1], stack[-2]
            stack = stack[:-2]
            if token == "+":
                return stack + [a + b]
            elif token == "-":
                return stack + [a - b]
            elif token == "*":
                return stack + [a * b]
            else:  # 除法
                return stack + [int(a / b)]
        else:
            return stack + [int(token)]
    
    return reduce(process_token, tokens, [])[-1]

# 使用字典映射操作符
def eval_rpn_dict(tokens: List[str]) -> int:
    stack = []
    operators = {
        '+': lambda a, b: a + b,
        '-': lambda a, b: a - b,
        '*': lambda a, b: a * b,
        '/': lambda a, b: int(a / b)
    }
    
    for token in tokens:
        if token in operators:
            b = stack.pop()
            a = stack.pop()
            stack.append(operators[token](a, b))
        else:
            stack.append(int(token))
    
    return stack[0]

def test_eval_rpn():
    print("=== 逆波兰表达式求值测试 ===")
    
    solution = Solution()
    
    # 测试用例
    test_cases = [
        (["2", "1", "+", "3", "*"], 9),  # ((2 + 1) * 3) = 9
        (["4", "13", "5", "/", "+"], 6),  # (4 + (13 / 5)) = 6
        (["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"], 22)  # 22
    ]
    
    for i, (tokens, expected) in enumerate(test_cases, 1):
        result1 = solution.evalRPN(tokens.copy())
        result2 = eval_rpn_functional(tokens.copy())
        result3 = eval_rpn_dict(tokens.copy())
        
        print(f"测试用例{i}: {tokens}")
        print(f"标准实现结果: {result1}")
        print(f"函数式实现结果: {result2}")
        print(f"字典映射实现结果: {result3}")
        print(f"期望结果: {expected}")
        print(f"所有实现正确: {all([result1 == expected, result2 == expected, result3 == expected])}")
        print()
    
    print("=== Python特性说明 ===")
    print("1. 动态类型: 无需声明变量类型")
    print("2. 列表: 内置的动态数组")
    print("3. 字典: 内置的哈希表")
    print("4. Lambda表达式: 匿名函数")
    print("5. 函数式编程: reduce和高阶函数")

if __name__ == "__main__":
    test_eval_rpn()

"""
Python实现特点:

1. **简洁语法**:
   - 动态类型系统
   - 简洁的条件语句
   - 内置数据结构

2. **函数式编程**:
   - reduce函数累积操作
   - lambda匿名函数
   - 高阶函数支持

3. **数据结构**:
   - 列表作为栈使用
   - 字典映射操作符
   - 灵活的数据操作

4. **内存管理**:
   - 自动垃圾回收
   - 引用计数
   - 无需手动内存管理

5. **标准库**:
   - typing模块类型提示
   - functools模块函数工具
   - 丰富的内置函数

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
"""