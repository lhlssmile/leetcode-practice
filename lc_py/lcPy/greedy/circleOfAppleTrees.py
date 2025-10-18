import sys
input = lambda: sys.stdin.readline().strip()

t = int(input())
outs = []
 
for _ in range(t):
    n = int(input())
    nums = list(map(int, input().split()))
    # There can be hash collisions, but n is small enough.
    outs.append(len(set(nums)))
 
print('\n'.join(map(str, outs)))