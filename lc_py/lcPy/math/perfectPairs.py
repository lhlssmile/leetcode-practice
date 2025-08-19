from typing import List


class Solution:
    def perfectPairs(self, nums: List[int]) -> int:

        for i, x in enumerate(nums):
            nums[i] = abs(x)

        nums.sort()
        ans = left = 0

        for j, b in enumerate(nums):
            while nums[left] * 2 < abs(b):
                left += 1
            ans += j - left

        return ans


if __name__ == '__main__':
    s = Solution()
    s.perfectPairs([0, 1, 2, 3])