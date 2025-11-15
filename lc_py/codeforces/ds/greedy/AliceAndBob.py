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
    for _ in range(t):
        n, a = LII()
        v = LII()
        less, greater = 0, 0

        for x in v:
            if x <= a:
                less += 1
            else: greater += 1
        if less < greater:
            print(a + 1)
        else:
            print(max(0, a - 1))


if __name__ == '__main__':
    t = II()
    main()