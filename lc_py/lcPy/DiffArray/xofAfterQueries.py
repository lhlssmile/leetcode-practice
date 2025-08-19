from functools import reduce
from math import isqrt
from operator import xor
from typing import List

MOD = 1_000_000_007


class Solution:
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)

        B = isqrt(len(queries))

        diff = [None] * B
        has = [None] * B

        for l, r, k, v in queries:
            if k < B:
                if not diff[k]:
                    diff[k] = [1] * (n + k)
                    has[k] = [False] * k
                has[k][l % k] = True
                diff[k][l] = diff[k][l] * v % MOD
                r = r - (r - l) % k + k
                diff[k][r] = diff[k][r] * pow(v, -1, MOD) % MOD
            else:
                for i in range(l, r + 1, k):
                    nums[i] = nums[i] * v % MOD
        for k, d in enumerate(diff):
            if not d:
                continue
            for start, b in enumerate(has[k]):
                if not b:
                    continue
                mul_d = 1

                for i in range(start, n, k):
                    mul_d = mul_d * d[i] % MOD
                    nums[i] = nums[i] * mul_d % MOD
        return reduce(xor, nums)


if __name__ == '__main__':
    s = Solution()
    nums = [798, 364, 542, 363]
    queries = [[0, 3, 2, 18], [2, 2, 1, 16], [1, 3, 1, 18], [2, 2, 4, 3], [1, 2, 2, 10], [0, 2, 4, 6], [2, 3, 1, 3],
               [2, 3, 2, 19], [3, 3, 4, 15],
               [3, 3, 3, 16], [0, 2, 3, 2], [0, 1, 3, 18], [1, 2, 3, 12], [1, 3, 1, 3], [3, 3, 4, 5], [3, 3, 1, 8],
               [3, 3, 3, 12]]
    s.xorAfterQueries(nums, queries)
