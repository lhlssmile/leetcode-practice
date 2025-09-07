class Solution:
    def removeKdigits(self, num: str, k: int) -> str:
        stack = []
        
        for digit in num:
            # 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
            while stack and k > 0 and stack[-1] > digit:
                stack.pop()
                k -= 1
            stack.append(digit)
        
        # 如果还没删完，从后面删
        while k > 0 and stack:
            stack.pop()
            k -= 1
        
        # 去掉前导零
        result = ''.join(stack).lstrip('0')
        return result if result else '0'

# 函数式版本（使用更多Python特性）
def removeKdigits_functional(num: str, k: int) -> str:
    from functools import reduce
    
    def process_digit(acc, digit):
        stack, remaining_k = acc
        # 移除比当前数字大的栈顶元素
        while stack and remaining_k > 0 and stack[-1] > digit:
            stack.pop()
            remaining_k -= 1
        stack.append(digit)
        return stack, remaining_k
    
    # 使用reduce处理每个数字
    stack, k = reduce(process_digit, num, ([], k))
    
    # 如果还有剩余删除次数，从后面删除
    stack = stack[:len(stack) - k] if k > 0 else stack
    
    # 去掉前导零并返回结果
    result = ''.join(stack).lstrip('0')
    return result or '0'

def main():
    sol = Solution()
    
    # 测试用例
    test_cases = [
        ("12345", 2),
        ("1432219", 3),  # "1219"
        ("10200", 1),    # "200"
        ("10", 2),       # "0"
        ("9", 1),        # "0"
        ("112", 1),      # "11"
    ]
    
    print("=== 标准版本 ===")
    for num, k in test_cases:
        result = sol.removeKdigits(num, k)
        print(f"removeKdigits('{num}', {k}) = '{result}'")
    
    print("\n=== 函数式版本 ===")
    for num, k in test_cases:
        result = removeKdigits_functional(num, k)
        print(f"removeKdigits_functional('{num}', {k}) = '{result}'")

if __name__ == "__main__":
    main()