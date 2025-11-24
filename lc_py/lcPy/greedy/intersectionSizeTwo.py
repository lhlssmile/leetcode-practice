from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def main():
    n = II()

    intervals = []

    for _ in range(n):
        intervals.append(LII())

    se_ls, ls, res = -1, -1, 0
    intervals.sort(key= lambda a: (a[1], -a[0]))
    for s, e in intervals:
        if s <= se_ls:
            continue
        elif s > ls:
            res += 2
            se_ls = e - 1
            ls = e
        else:
            res += 1
            se_ls = ls
            ls = e
    return res


if __name__ == '__main__':
    main()

