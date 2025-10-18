from functools import cache
from typing import List


class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        n = len(nums)
        total = sum(nums)
        nums.sort()
        for k in range(1, n):
            if total * k % n != 0:
                continue
            target = total * k // n

            @cache
            def dfs(index, currSum, count):
                if count == k:
                    return currSum == target
                if index == n:
                    return False

                if count + (n - index) < k:
                    return False

                if dfs(index + 1, currSum + nums[index], count + 1):
                    return True
                if dfs(index + 1, currSum, count):
                    return True
                return False

            if dfs(0, 0, 0):
                return True
        return False


if __name__ == '__main__':
    nums = [1, 2, 3, 4, 5, 6, 7, 8]
    s = Solution()
    s.splitArraySameAverage(nums)