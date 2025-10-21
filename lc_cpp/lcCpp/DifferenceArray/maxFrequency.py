from collections import defaultdict
from typing import List


class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        cnt = defaultdict(int)
        diff = defaultdict(int)
        for x in nums:
            cnt[x] += 1
            diff[x]  # 把 x 插入 diff，以保证下面能遍历到 x
            diff[x - k] += 1  # 把 [x-k,x+k] 中的每个整数的出现次数都加一
            diff[x + k + 1] -= 1

        ans = sum_d = 0
        for x, d in sorted(diff.items()):
            sum_d += d
            ans = max(ans, min(sum_d, cnt[x] + numOperations))
        return ans


if __name__ == '__main__':
    nums = [1, 4, 5]
    k = 1
    op = 2
    s = Solution()
    print(s.maxFrequency(nums, k, op))