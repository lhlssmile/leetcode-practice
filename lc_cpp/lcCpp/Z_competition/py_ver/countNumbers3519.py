from functools import cache
from typing import List

class CountNumbers:
    def countNumbers(self,l:str,r:str,b:int) -> int:
        def trans(s:str) -> List[int]:      # 字符串转进制
            x = int(s)
            digits = []
            while x:
                x,r = divmod(x,b)
                digits.append(r)
            digits.reverse()
            return digits
        high = trans(r)
        n = len(high)
        low = trans(l)
        low = [0] * (n - len(l)) + low      # 补上前导0
        @cache
        def dfs(i:int,pre:int,limit_low:bool,limit_high:bool) ->int:
            if i == n:
                return 1
            lo = low[i] if limit_low else 0
            hi = high[i] if limit_high else b - 1

            res = 0

            for d in range(max(lo,pre),hi + 1):
                res += dfs(i + 1,d,limit_low and d == lo,limit_high and d == hi)
            return res % 1_000_000_007
        return dfs(0,0,True,True)



if __name__ == '__main__':
    sol = CountNumbers()
    res = sol.countNumbers("23","28",8)
    print(res)