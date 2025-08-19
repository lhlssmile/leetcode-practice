from typing import List


class Solution:
    def minArraySum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        f = [0] * ( n + 1)
        prefix = [0] * (n + 1)
        mp = {0: 0}

        for i, x in enumerate(nums):
            prefix[i + 1] = prefix[i] + x

        total = prefix[n]

        for i in range(1, n + 1):
            rem = prefix[i] % k
            f[i] = f[i - 1]
            if rem in mp:
                f[i] = max(f[i], prefix[i] + mp[rem])

            if rem not in mp or mp[rem] < f[i] - prefix[i]:
                mp[rem] = f[i] - prefix[i]

        return total - f[n]


if __name__ == '__main__':
    s = Solution()
    s.minArraySum([3, 1, 4, 1, 5], 3)