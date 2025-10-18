def ok(x, y, z):
    for i in range(30):
        xi = (x >> i)&1
        yi = (y >> i)&1
        zi = (z >> i)&1
        if xi + yi + zi == 2: return False
    return True

t = int(input())
for _ in range(t):
    x, y, z = map(int, input().split())
    print("YES" if ok(x, y, z) else "NO")