from typing import List      
class Solution:
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:
        ans, precnt, cnt, n = 0, 0, 0, len(nums)

        for i, x in enumerate(nums):
            cnt += 1
            if i == n - 1 or x >= nums[i + 1]:
                ans = max(cnt // 2, min(cnt, precnt), ans)
                precnt = cnt
                cnt = 0
        return ans


if __name__ == "__main__":
    s = Solution()
    nums = [2,5,7,8,9,2,3,4,3,1]
    print(s.maxIncreasingSubarrays(nums))