from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def on_ray(delx, dely, dx, dy):
    if delx == 0 and dely == 0:
        return True, 0
    if dx == 0:
        if delx != 0:
            return False, 0
        if dy == 0:
            return False, 0
        if dely % dy != 0:
            return False, 0
        k = dely // dy
        if k >= 1 and k * dy == dely:
            return True, k
        return False, 0
    if dy == 0:
        if dely != 0:
            return False, 0
        if dx == 0:
            return False, 0
        if delx % dx != 0:
            return False, 0
        k = delx // dx
        if k >= 1 and k * dx == delx:
            return True, k
        return False, 0
    # diagonal
    if delx % dx != 0 or dely % dy != 0:
        return False, 0
    k = delx // dx
    if k >= 1 and k * dx == delx and k * dy == dely:
        return True, k
    return False, 0

n, ex, ey = LII()
curr_d = SI()
enemies = [LII() for _ in range(n)]

dir_map = {
    "NORTH": (0, 1),
    "NORTHEAST": (1, 1),
    "EAST": (1, 0),
    "SOUTHEAST": (1, -1),
    "SOUTH": (0, -1),
    "SOUTHWEST": (-1, -1),
    "WEST": (-1, 0),
    "NORTHWEST": (-1, 1),
}

dx, dy = dir_map[curr_d]

min_k = float('inf')
hit_x, hit_y = -1, -1
for x, y in enemies:
    delx = x - ex
    dely = y - ey
    on, k = on_ray(delx, dely, dx, dy)
    if on and k < min_k:
        min_k = k
        hit_x, hit_y = x, y

if hit_x == -1:
    print(-1)
else:
    print(hit_x, hit_y)