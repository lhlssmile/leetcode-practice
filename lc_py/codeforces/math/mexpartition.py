import sys
def solve(a):
    cnt = [0] * 102
    for x in a:
        cnt[x] += 1
    mex = 0
    for i in range(102):
        if cnt[i] == 0:
            mex = i 
            break
    return mex

if __name__ == "__main__":
    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        a = [int(x) for x in data[idx:idx + n]]
        idx += n
        print(solve(a))
        