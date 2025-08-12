from typing import List


class Solution:
    def maxSubarraySumCircular(self, nums: List[int]) -> int:
        total, mx_sum, mi_sum, mx_en, mi_en = 0, nums[0], nums[0], 0, 0

        for v in nums:
            total += v
            mx_en = max(v, v + mx_en)
            mx_sum = max(mx_sum, mx_en)
            mi_en = min(v, v + mi_en)
            mi_sum = min(mi_sum, mi_en)
        return mx_sum if mx_sum < 0 else max(mx_sum, total - mi_sum)