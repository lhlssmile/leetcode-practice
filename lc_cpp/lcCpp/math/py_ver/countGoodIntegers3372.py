from math import factorial


class CountGoodIntegers:
    def countGoodIntegers(self,n:int,k:int) -> int:
        fac = [factorial(i) for i in range(n + 1)]
        ans = 0
        base = 10 ** ((n - 1) // 2)
