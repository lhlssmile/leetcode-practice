from collections import defaultdict
from typing import List
import sys
from collections import Counter

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''
a: ai = {1, 2 * 1e5}
最小代价使得gcd(ai, aj) > 1 (1 <= i < j <= n)
能让/有必要ai超过上界吗? 
b: cost
'''

'''
b_i = 1。每次操作将某个 a_i 增加 1，代价为 1。求最小总代价，使得存在一对 (i, j) 使 gcd(a_i, a_j) > 1。

关键结论：答案只可能是 0、1 或 2。
- 若当前就存在两个数共享某个质因数（含 2），则答案为 0。
- 若增量 1 次即可让某个质因数同时整除两数（一个已经整除、另一个加 1 后整除），答案为 1。
- 否则答案为 2（例如把两个奇数各 +1 变成偶数）。

实现要点：用最小质因数（SPF）线性筛，统计：
- cntDiv[p] = 当前有多少 a_i 被质数 p 整除；
- cntPlus[p] = 有多少 a_i + 1 被质数 p 整除。
若存在 p 使 cntDiv[p] >= 2，则输出 0；否则若存在 p 使 cntDiv[p] >= 1 且 cntPlus[p] >= 1，则输出 1；否则输出 2。
该判断覆盖所有质因数（含 2），无需 O(n^2) 枚举对。
'''

MAXV = 200001  # 覆盖 a_i <= 2e5 以及 a_i+1 <= 200001


def build_spf(limit: int):
    spf = [0] * (limit + 1)
    primes = []
    for i in range(2, limit + 1):
        if spf[i] == 0:
            spf[i] = i
            primes.append(i)
        for p in primes:
            v = p * i # ex v = 6 primes = 2,3
            if v > limit or p > spf[i]:
                break
            spf[v] = p
    return spf


spf = build_spf(MAXV)


def factorize_unique(x: int) -> List[int]:
    res = []
    while x > 1:
        p = spf[x]
        res.append(p)
        while x % p == 0:
            x //= p
    return res


t = II()
def main():

    for _ in range(t):
        n = II()
        a = LII()
        _ = LII()  # b 行，易版 b_i=1，读取但不使用

        cntDiv = defaultdict(int)
        cntPlus = defaultdict(int)
        used_primes = set()

        # 统计 a_i 的质因数
        for x in a:
            for p in factorize_unique(x):
                cntDiv[p] += 1
                used_primes.add(p)

        # 统计 (a_i + 1) 的质因数
        for x in a:
            y = x + 1
            for p in factorize_unique(y):
                cntPlus[p] += 1
                used_primes.add(p)

        # 判定 0 或 1
        ans = 2
        for p in used_primes:
            if cntDiv[p] >= 2:
                ans = 0
                break
        if ans != 0:
            for p in used_primes:
                if cntDiv[p] >= 1 and cntPlus[p] >= 1:
                    ans = 1
                    break

        print(ans)



if __name__ == '__main__':
    main()
