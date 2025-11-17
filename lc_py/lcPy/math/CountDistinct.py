
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
    x = II()
    s = str(x)
    L = len(s)
    ans = 0

    for k in range(1, L):
        ans += 9 ** k

    for i, c in enumerate(s):
        d = int(c)
        if d == 0:
            break
        ans += (d - 1) * (9 - (L - i - 1))

    else:ans+=1

    print(ans)


if __name__ == '__main__':

    main()