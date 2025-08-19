class Solution:
    def new21Game(self, n: int, k: int, maxPts: int) -> float:
        dp = [None] * (k + maxPts)
        s = 0

        for i in range(k, k + maxPts):
            dp[i] = 1 if i <= n else 0
            s += dp[i]
        for i in range(k - 1, -1, -1):
            dp[i] = s/maxPts
            s = s - dp[i + maxPts] + dp[i]
        return dp[0]



if __name__ == '__main__':
    s = Solution()
    s.new21Game(21, 17, 10)