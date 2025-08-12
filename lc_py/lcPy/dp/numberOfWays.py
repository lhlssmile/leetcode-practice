class Solution:
    def numberOfWays(self, n: int, x: int) -> int:
        MOD = 10 ** 9 + 7
        base = 1
        powers = []

        while base ** x <= n:
            powers.append(base ** x)
            base += 1
        m = len(powers)
        # memo[idx][n]
        memo = [[-1] * (n + 1) for _ in range(m + 1)]

        def dfs(remain, idx) -> int:
            if remain == 0:
                return 1
            if remain < 0 or idx == m:
                return 0
            if memo[idx][remain] != -1:
                return memo[idx][remain]

            take = dfs(remain - powers[idx], idx + 1)
            skip = dfs(remain, idx + 1)
            memo[idx][remain] = (take + skip) % MOD
            return memo[idx][remain]

        return dfs(n, 0)
