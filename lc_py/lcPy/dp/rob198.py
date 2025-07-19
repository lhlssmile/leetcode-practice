from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        f0, f1 = 0, 0

        for num in nums:
            new_f = max(f1, f0 + num)
            f0, f1 = f1, new_f
        return f1
