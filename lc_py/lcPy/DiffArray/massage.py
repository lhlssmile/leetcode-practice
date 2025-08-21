from typing import List


class Solution:
    def massage(self, nums: List[int]) -> int:
        n = len(nums)

        if n == 0:
            return 0
        if n == 1:
            return nums[0]
        prev = nums[0]
        curr = max(prev, nums[1])

        for i in range(2, n):
            prev, curr = curr, max(curr, prev + nums[i])
        return curr

if __name__ == '__main__':
    s = Solution()
    nums = [1, 2, 3, 1]
    print(s.massage(nums))
