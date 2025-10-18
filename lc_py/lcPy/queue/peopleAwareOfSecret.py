class Solution:
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        MOD = 10 ** 9 + 7
        dp = [0] * (n + 1)
        dp[1] = 1
        for i in range(2, n + 1):
            # 第 i 天的新人数
            for j in range(max(1, i - forget + 1), i - delay + 1):
                dp[i] = (dp[i] + dp[j]) % MOD

        # 第 n 天还记得秘密的人
        ans = 0
        for i in range(n - forget + 1, n + 1):
            if i >= 1:
                ans = (ans + dp[i]) % MOD
        return ans


if __name__ == '__main__':
    s = Solution()
    print(s.peopleAwareOfSecret(6, 2, 4))
