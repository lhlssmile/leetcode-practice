from typing import List


class Solution:
    def numsOfSubarrays(self, arr: List[int], k, threshold: int) -> int:

        s, ans = 0, 0
        for i, x in enumerate(arr):
            s += x

            if i < k - 1:
                continue

            if s >= threshold * k:
                ans += 1

            s -= arr[i - k + 1]

        return ans
