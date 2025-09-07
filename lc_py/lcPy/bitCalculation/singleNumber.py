from typing import List

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        """位运算解法 - 统计每位1的个数"""
        ans = 0
        for i in range(32):
            cnt1 = 0
            for x in nums:
                cnt1 += (x >> i) & 1
            ans |= (cnt1 % 3) << i
        return ans
    
    def singleNumberStateMachine(self, nums: List[int]) -> int:
        """状态机解法"""
        ones = twos = 0
        for num in nums:
            ones = (ones ^ num) & ~twos
            twos = (twos ^ num) & ~ones
        return ones
    
    def singleNumberFunctional(self, nums: List[int]) -> int:
        """函数式编程解法"""
        from functools import reduce
        
        def count_bits(nums, bit_pos):
            return sum((x >> bit_pos) & 1 for x in nums)
        
        return reduce(lambda ans, i: ans | ((count_bits(nums, i) % 3) << i), 
                     range(32), 0)

def test():
    sol = Solution()
    assert sol.singleNumber([2, 2, 3, 2]) == 3
    assert sol.singleNumber([0, 1, 0, 1, 0, 1, 99]) == 99
    print("All tests passed!")

if __name__ == "__main__":
    test()