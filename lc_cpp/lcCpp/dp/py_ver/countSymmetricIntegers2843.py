from functools import cache


class CountSymmetricIntegers:
    def countSymmetricIntegers(self,low:int,high:int) -> int:
        high = list(map(ord,str(high)))
        n = len(high)
        low = list(map(ord,str(low).zfill(n)))  # 补充前导0

        @cache
        def dfs(i:int,start:int,diff:int,limit_low:bool,limit_high:bool) ->int:

            if i == n:
                return 1 if diff == 0 else 0

            lo = low[i] if limit_low else 0
            hi = high[i] if limit_high else 9

            if start < 0 and (n - i) % 2:
                return 0 if lo else dfs(i + 1,start,diff,True,False)
            is_left = start < 0 or i < (start + n) // 2
            res = 0
            for d in range(lo,hi + 1):
                res += dfs(i + 1,
                        i if start < 0 and d else start,
                        diff + (d if is_left else -d),
                        limit_low and d == lo,
                        limit_high and d == hi
                           )
        return dfs(0,-1,0,True,True)