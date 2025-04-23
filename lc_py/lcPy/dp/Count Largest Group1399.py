from functools import cache


class CountLargestGroup:
    def countLargestGroup(self,n: int) -> int:
        s = list(map(int,str(n)))
        m = len(s)

        @cache
        def dfs(i: int,left: int,limit_high: bool) -> int:
            if i == m:
                return 1 if left == 0 else 0
            hi = s[i] if limit_high else 9
            res = 0

            for d in range(min(hi,left) + 1):
                res += dfs(i + 1,left - d,limit_high and d ==hi)
            return res
        max_cnt = ans = 0
        for target in range(1,m * 9 + 1):
            cnt = dfs(0,target,True)
            if cnt > max_cnt:
                max_cnt = cnt
                ans = 1
            elif cnt == max_cnt:
                ans += 1
        return ans


if __name__ == '__main__':
    sol = CountLargestGroup()
    print(sol.countLargestGroup(13))