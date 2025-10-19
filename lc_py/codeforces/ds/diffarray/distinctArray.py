from typing import List

def solve(b: List[int]) -> List[int]:
    nxtval = 1
    n = len(b)
    a = []
    prevdiff = 0
    for i in range(n):
        if i == 0:
            diff = b[0]
        else:
            diff = b[i] - b[i - 1]
        
        if diff > prevdiff:
            a[i] = nxtval
            nxtval += 1
        else:
            if i > 0: a[i] = a[i - 1]
            else: a[i] = 1
        prevdiff = diff

    return a

if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        n = int(input())
        b = []
        for _ in range(n):
            b[i] = int(input())
        
        a = solve(b)
        for x in a:
            print(x)
        print(" ")