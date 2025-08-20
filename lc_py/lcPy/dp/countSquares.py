from typing import List


class Solution:
    def countSquares(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        # ans = 0
        # for i in range(m):
        #     for j in range(n):
        #         if matrix[i][j] == 1:
        #             if i > 0 and j > 0:
        #                 matrix[i][j] = min(matrix[i - 1][j], matrix[i - 1][j - 1], matrix[i][j - 1]) + 1
        #             ans += matrix[i][j]
        # return ans
        prev = [0] * (n + 1)
        curr = [0] * (n + 1)
        cnt = 0
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == 0:
                    curr[j + 1] = 0
                    continue
                curr[j + 1] = min(curr[j], prev[j], prev[j + 1]) + 1
                cnt += curr[j + 1]
            prev, curr = curr, prev

        return cnt

