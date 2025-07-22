'''
给你一个正整数 n。请判断 n 是否可以被以下两值之和 整除：

n 的数字和（即其各个位数之和）。

n 的数字积（即其各个位数之积）。

如果 n 能被该和整除，返回 true；否则，返回 false。©leetcode
'''
class Solution:
    def checkDivisibility(self, n: int) -> bool:
        s_n = str(n)
        
        # 计算数字和
        digit_sum = sum(int(digit) for digit in s_n)
        
        # 计算数字积
        digit_product = 1
        for digit in s_n:
            digit_product *= int(digit)
        
        # 判断n是否能被(数字和 + 数字积)整除
        return n % (digit_sum + digit_product) == 0


# 测试用例
if __name__ == "__main__":
    solution = Solution()
    
    # 测试案例
    test_cases = [12, 36, 108, 102]
    
    for num in test_cases:
        result = solution.checkDivisibility(num)
        print(f"n={num}: {result}")
        
        # 详细计算过程
        s_n = str(num)
        digit_sum = sum(int(d) for d in s_n)
        digit_product = 1
        for d in s_n:
            digit_product *= int(d)
        total = digit_sum + digit_product
        print(f"  数字和: {digit_sum}, 数字积: {digit_product}, 和: {total}, {num} % {total} = {num % total}")
        print()

