class CountSubarrays2302:
    def countSubarrays(self, nums: list[int], k: int) -> int:
        n = len(nums)
        left = 0
        prefix_sum = 0
        ans = 0

        for right in range(n):
            prefix_sum += nums[right]
            while left <= right and prefix_sum * (right - left + 1) >= k:
                prefix_sum -= nums[left]
                left += 1
            ans += right - left + 1

        return ans

# 测试
sol = Solution()
nums = [2, 1, 4, 3, 5]
k = 10
print(sol.CountSubarrays2302(nums, k))
