from typing import List


class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        avgs = [-1] * len(nums)

        s = 0

        for i, x in enumerate(nums):
            s += x
            if i < 2 * k:
                continue
            avgs[i - k] = s // (k * 2 + 1)
            s -= nums[i - 2 * k]

        return avgs
