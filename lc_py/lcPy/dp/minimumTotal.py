from typing import List


class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        if n == 1: return triangle[0][0]
        f = [0] * (n + 1)

        for row in reversed(triangle):
            for j in range(len(row)):
                f[j] = min(f[j], f[j + 1]) + row[j]
        return f[0]


if __name__ == '__main__':
    triangle = [[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]]
    s = Solution()
    s.minimumTotal(triangle)
