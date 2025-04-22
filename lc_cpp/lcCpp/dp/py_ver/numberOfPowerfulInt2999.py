from linecache import cache

#数位DP

class NumberOfPowerfulInt2999:
    def numberOfPowerfulInt(self,start:int,finish:int,limit:int,s:str) -> int:
        low = str(start)
        high = str(finish)
        n = len(high)
        low = '0' * (n - len(low)) + low    #  补充前导0    此时low high对齐了
        diff = n - len(s)       # 除去后缀的部分 & 不可以随便填 要求数位 < limit
        @cache
    # 基础版  不考虑前导0
        # 现在只是支持上界 即{0,finish}  ->limit_low 支持下界
        # def dfs(i :int,limit_low:int,limit_high:bool) -> int:
        #     if i == n:
        #         return 1        # 找到了合法数字
        #     # 看看当前位的最小值 前边的位为low[i]那么当前位也是
        #     lo = int(low[i]) if limit_low else 0
        #     # 第i个数位可以从哪里枚举到哪里? {0,9}最大可填范围(high)如果前边都为high[i]那么当前位也是
        #     hi = int(high[i]) if limit_high else 9
        #     res = 0
        #     if i < diff:
        #         for d in range(lo,min(hi,limit) + 1):
        #             # 前边都为上界 并且当前也为上界 那么后边的数位也只能为{0,high[i]} 否则可以为{0,9}
        #             res += dfs(i + 1,limit_low and d == lo,limit_high and d == hi)
        #     else:
        #       # 此时必须填后缀
        #         x = int(s[i - diff])
        #         if lo <= x <= min(hi,limit):
        #              res = dfs(i + 1,limit_low and x == lo,limit_high and x == hi)
        #     return res

    #扩展版 支持前导0
        # is_num 前边是否填了非0数
        def dfs(i :int,limit_low:int,limit_high:bool,is_num:bool) -> int:
            if i == n:
                return 1        # 找到了合法数字
            res = 0
            if not is_num and low[i] == '0':  #前边全为0  limit_low一定为True
                # 这一位也可以为0                        high没有前导0
                res += dfs(i + 1,True,False,False)


            # 看看当前位的最小值 前边的位为low[i]那么当前位也是
            lo = int(low[i]) if limit_low else 0
            # 第i个数位可以从哪里枚举到哪里? {0,9}最大可填范围(high)如果前边都为high[i]那么当前位也是
            hi = int(high[i]) if limit_high else 9
            d0 = 0 if is_num else 1     #如果前边填了非0数那么可以从0开始 否则为1(因为前边是前导0
            if i < diff:
                for d in range(max(d0,lo),min(hi,limit) + 1):
                    # 前边都为上界 并且当前也为上界 那么后边的数位也只能为{0,high[i]} 否则可以为{0,9}
                    res += dfs(i + 1,limit_low and d == lo,limit_high and d == hi,True)
            else:
                # 此时必须填后缀
                x = int(s[i - diff])
                if max(d0,lo) <= x <= min(hi,limit):
                    res = dfs(i + 1,limit_low and x == lo,limit_high and x == hi,True)
            return res
        return dfs(0,True,True,False)

if __name__ == '__main__':
    solution = NumberOfPowerfulInt2999()
    res = solution.numberOfPowerfulInt(1,6000,4,"124")
    print(res)