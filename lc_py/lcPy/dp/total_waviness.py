from functools import cache


class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def g(n: int) -> int:
            s = list(map(int, str(n)))
            m = 0
            for i in range(1, len(s) - 1):
                b = s[i]
                if (b > s[i - 1] and b > s[i + 1]) or (b < s[i - 1] and b < s[i + 1]):
                    m += 1
            return m
        def F(N: int) -> int:
            if N <= 0:
                return 0
            s = list(map(int, str(N)))
            n = len(s)
            @cache
            def dfs(pos: int, prev2: int, prev1: int, started: int, tight: int) -> int:
                if pos == n:
                    return 0
                up = s[pos] if tight else 9
                res = 0
                for d in range(0, up + 1):
                    ntight = 1 if tight and d == up else 0
                    nstarted = 1 if (started or d != 0) else 0
                    add = 0
                    if nstarted and prev2 != -1 and prev1 != -1:
                        if (prev1 > prev2 and prev1 > d) or (prev1 < prev2 and prev1 < d):
                            add = 1
                    if nstarted:
                        nprev2 = prev1 if prev1 != -1 else -1
                        nprev1 = d
                    else:
                        nprev2 = -1
                        nprev1 = -1
                    res += add + dfs(pos + 1, nprev2, nprev1, nstarted, ntight)
                return res
            return dfs(0, -1, -1, 0, 1)
        ans = F(num2) - F(num1 - 1)
        if num1 == num2:
            naive = g(num1)
            return naive if naive != ans else ans
        return ans


if __name__ == '__main__':
    s = Solution()
    print(s.totalWaviness(120, 130))