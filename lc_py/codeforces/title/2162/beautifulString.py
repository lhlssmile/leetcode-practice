

def isPalindrome(s: str) -> bool:
    return s == s[::-1]

def isNonDecaresing(s: str) -> bool:
    return all(s[i] >= s[i - 1] for i in range(1, len(s)))

def solve(s: str):
    n = len(s)
    for mask in range(1 << n):
        p = []
        x = []
        idx = []
        for i in range(n):
            if (mask >> i) & 1:
                p.append(s[i])
                idx.append(i + 1)
            else:
                x.append(s[i])
        if isNonDecaresing(p) and isPalindrome(x):
            return len(idx), idx
    return -1, []

t = int(input())
for _ in range(t):
    n = int(input())
    s = input().strip()
    k, idx = solve(s)
    if k == -1: print(-1)
    else: 
        print(k)
        if k > 0:
            print(*idx)