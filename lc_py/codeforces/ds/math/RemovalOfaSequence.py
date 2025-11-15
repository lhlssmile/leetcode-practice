import sys

def solve():
    input = sys.stdin.readline
    t = int(input())
    N = 10 ** 12
    for _ in range(t):
        x, y, k = map(int, input().split())
        if y == 1:
            print(-1)
            continue
        idx = k
        for _ in range(x):
            if idx > N:
                break
            idx += (idx - 1) // (y - 1)
        print(idx if idx <= N else -1)


if __name__ == "__main__":
    solve()