import sys
from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


def solve():
    input = sys.stdin.readline
    t = int(input())
    out_lines = []
    for _ in range(t):
        n = II()
        a = LII()

        P = [0] * (n + 1)
        for i in range(1, n + 1):
            P[i] = P[i - 1] + a[i - 1]

        base_sum = P[n]
        max_delta = 0
        maxA = -10**30  # 充当负无穷

        for r in range(1, n + 1):
            A_r = -r * r + r + P[r - 1]
            if A_r > maxA:
                maxA = A_r
            B_r = r * r + r - P[r]
            cand = maxA + B_r
            if cand > max_delta:
                max_delta = cand

        out_lines.append(str(base_sum + max(0, max_delta)))
    print("\n".join(out_lines))


if __name__ == "__main__":
    solve()