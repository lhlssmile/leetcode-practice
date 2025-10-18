from functools import lru_cache
from typing import List


class Solution:
    def maxStudents(self, seats: List[List[str]]) -> int:
        m, n = len(seats), len(seats[0])

        # 每行哪些位置能坐人（可用座位 = 1）
        valid_mask = [0] * m
        for i in range(m):
            mask = 0
            for j in range(n):
                if seats[i][j] == '.':
                    mask |= (1 << j)
            valid_mask[i] = mask

        # 预处理：这一行的所有合法状态 + 对应人数
        row_states = []
        state_count = {}
        for i in range(m):
            states = []
            for mask in range(1 << n):
                # 不能坐坏座位 & 不能有相邻学生
                if (mask & ~valid_mask[i]) == 0 and (mask & (mask << 1)) == 0:
                    states.append(mask)
                    state_count[mask] = bin(mask).count("1")
            row_states.append(states)

        @lru_cache(None)
        def dfs(row: int, prev_mask: int) -> int:
            """返回从 row 行开始往下能安排的最大学生数"""
            if row == m:
                return 0
            ans = 0
            for mask in row_states[row]:
                # 跨行冲突判定：mask vs prev_mask
                if (mask << 1 & prev_mask) == 0 and (mask >> 1 & prev_mask) == 0:
                    ans = max(ans, state_count[mask] + dfs(row + 1, mask))
            return ans

        return dfs(0, 0)
