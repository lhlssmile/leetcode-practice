from collections import defaultdict
from typing import List

"""
LeetCode 2845: 统计趣味子数组 (Count Interesting Subarrays)
https://leetcode.cn/problems/count-interesting-subarrays/
"""

class Solution:
    """
    统计趣味子数组
    思路：前缀和 + 哈希表 + 模运算
    """
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        # 哈希表，存储 <前缀和 % modulo, 出现次数>
        # 使用 defaultdict 可以简化代码，不存在的 key 默认值为 0
        count = defaultdict(int)
        # 初始化，处理 l=0 的情况，空前缀和模 modulo 为 0
        count[0] = 1
        ans = 0
        prefix_sum = 0  # 当前的前缀和（满足 num % modulo == k 的元素个数）

        for num in nums:  # 遍历数组
            if num % modulo == k:  # 如果当前元素满足条件
                prefix_sum += 1  # 前缀和加 1

            # 计算我们需要的前一个前缀和模 modulo 的值
            # P[l] % modulo == (P[r+1] % modulo - k % modulo + modulo) % modulo
            need = (prefix_sum - k % modulo + modulo) % modulo

            # 查找哈希表中是否存在需要的 need 值
            # defaultdict 会自动处理 key 不存在的情况，返回 0
            ans += count[need]

            # 将当前的前缀和模 modulo 加入哈希表
            count[prefix_sum % modulo] += 1

        return ans

# --- 测试用例 ---
if __name__ == "__main__":
    solver = Solution()

    nums1 = [3, 1, 9, 6]
    modulo1 = 3
    k1 = 0
    print(solver.countInterestingSubarrays(nums1, modulo1, k1))  # 预期输出 2

    nums2 = [3, 2, 4]
    modulo2 = 2
    k2 = 1
    print(solver.countInterestingSubarrays(nums2, modulo2, k2))  # 预期输出 3