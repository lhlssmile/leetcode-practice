
from collections import defaultdict
from typing import List
import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()



n = II()
a = LII()

MAX = 10 ** 6 + 1
exist = [False] * MAX
for x in a: exist[x] = True

f = [0] * MAX

ans = 1

for x in range(1, MAX):
    if not exist[x]: continue

    f[x] = max(f[x], 1)

    for y in range(x * 2, MAX, x):
        if exist[y]:
            f[y] = max(f[y], f[x] + 1)
    ans = max(f[x], ans)

print(ans)

