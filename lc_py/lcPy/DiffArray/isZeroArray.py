from typing import List


class Solution:
    def isZeroArray(self, nums: List[int], queries: List[List[int]]) -> bool:
        diff = [0] * (len(nums) + 2)

        for q1, q2 in queries:
            diff[q1] += 1
            diff[q2 + 1] -= 1

        s = 0

        for i in range(len(nums)):
            s += diff[i]
            if s < nums[i]:
                return False
        return True
