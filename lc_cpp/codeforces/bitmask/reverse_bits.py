def reverse_x(x: int) -> int:
    rev = 0

    while x:
        rev = (rev << 1 ) | (x & 1)
        x >>= 1
    return rev

def solve():
    t = int(input())
    for _ in range(t):
        n = int(input())
        if n == (1 << n.bit_length()) - 1: print("NO")
        else: print("yes")

