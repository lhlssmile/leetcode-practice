from typing import List


class Solution:
    def subsequenceSumAfterCapping(self, nums: List[int], k: int) -> List[bool]:
        nums.sort()

        n = len(nums)
        ans = [False] * n
        f = [False] * (k + 1)
        f[0] = True  # 不选元素，和为 0

        i = 0
        for x in range(1, n + 1):
            # 增量地考虑所有恰好等于 x 的数
            # 小于 x 的数在之前的循环中已计算完毕，无需重复计算
            while i < n and nums[i] == x:
                for j in range(k, nums[i] - 1, -1):
                    f[j] = f[j] or f[j - nums[i]]  # 0-1 背包：不选 or 选
                i += 1

            # 枚举（从大于 x 的数中）选了 j 个 x
            for j in range(min(n - i, k // x) + 1):
                if f[k - j * x]:
                    ans[x - 1] = True
                    break
        return ans


if __name__ == '__main__':
    nums = [4, 3, 2, 4]
    k = 5
    s = Solution()
    print(s.subsequenceSumAfterCapping(nums, k))
