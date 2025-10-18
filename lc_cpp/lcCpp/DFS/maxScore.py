from collections import defaultdict
from functools import lru_cache, cache
from typing import List


class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        pos = defaultdict(list)
        for i, row in enumerate(grid):
            for x in row:
                pos[x].append(i)
        all_nums = sorted(pos)

        @cache
        def dfs(i, j: int) -> int:
            if i < 0: return 0
            # 不选
            res = dfs(i - 1, j)

            for k in pos[all_nums[i]]:
                if (j >> k & 1) == 0:
                    res = max(res, dfs(i - 1, j | 1 << k) + all_nums[i])
                return res if res else dfs(i - 1, j)
        return dfs(len(all_nums) - 1, 0)

if __name__ == '__main__':
    s = Solution()
    grid = [[8,7,6],[8,3,2]]
    print(s.maxScore(grid))