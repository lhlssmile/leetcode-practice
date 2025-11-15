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
    t = II()
    for _ in range(t):
        s = SI()
        n = len(s)
        infinite = False
        for i, c in enumerate(s[:n - 1]):
            if c != '<' and s[i + 1] != '>':
                infinite = True
                break
        if infinite: print(-1); continue
        l, r = 0, 0
        if '*' in s:
            j = s.index('*')
            print(max(j + 1, n - j));
            continue
        while l < n and s[l] == '<':
            l += 1
        while r < n and s[n - 1 - r] == '>':
            r += 1
        print(max(l, r))


if __name__ == '__main__':
    main()
