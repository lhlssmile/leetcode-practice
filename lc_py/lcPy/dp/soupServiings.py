from functools import cache

import cachetools


class Solution:
    def soupServings(self, n: int) -> float:
        if n >= 5000:
            return 1.0

        operations = [
            (100, 0), (75, 25), (50, 50), (25, 75)
        ]
        @cache
        def dfs(a: int, b: int) -> float:
            if a <= 0 and b <= 0: return 0.5
            if a <= 0: return 1.0
            if b <= 0: return 0.0
            prob = 0.0

            for da, db in operations:
                new_a, new_b = a - da, b - db
                prob += 0.25 * dfs(new_a, new_b)
            return prob
        return dfs(n, n)

    def soupServingsDP(self, n: int) -> float:
        if n >= 5000: return 1.0

        n = (n + 24) // 25
        dp = [[0.0] * (n + 1) for _ in range(n + 1)]

        dp[0][0] = 0.5

        for a in range(1, n + 1):
            dp[a][0] = 0.0
        for b in range(1, n + 1):
            dp[0][b] = 1.0

        for a in range(1, n + 1):
            for b in range(1, n + 1):
                dp[a][b] = 0.25 * (
                        dp[max(0, a - 4)][b] +
                        dp[max(0, a - 3)][max(0, b - 1)] +
                        dp[max(0, a - 2)][max(0, b - 2)] +
                        dp[max(0, a - 1)][max(0, b - 3)]
                )
        return dp[n][n]