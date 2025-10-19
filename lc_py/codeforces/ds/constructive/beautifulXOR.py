import sys
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


def clz(x: int):
    return 32 - x.bit_length()

t = II()
for _ in range(t):
    ab = LII()
    a, b = ab[0], ab[1]
    if clz(a) > clz(b):
        print("-1")
    elif a == b: print("0")
    else:
        val = []
        for i in range(31):
            x = (1 << i)
            if (x & a) == 0 and x <= a: 
                a += x
                val.append(x)
        for i in range(31):
            x = (1 << i)
            if (b & x) == 0 and x <= a: val.append(x)
        print(len(val))
        print(*val)