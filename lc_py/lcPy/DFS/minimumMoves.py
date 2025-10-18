from itertools import permutations


class Solution:
    def minimumMoves(self, grid):
        stones, empty = [], []
        # 统计多余石头和空格子
        for i in range(3):
            for j in range(3):
                if grid[i][j] == 0:
                    empty.append((i, j))
                elif grid[i][j] > 1:
                    for _ in range(grid[i][j] - 1):
                        stones.append((i, j))

        m = len(empty)
        ans = float('inf')

        # 枚举所有空格子分配顺序
        for perm in permutations(range(m)):
            cost = 0
            for k, idx in enumerate(perm):
                sx, sy = stones[k]
                ex, ey = empty[idx]
                cost += abs(sx - ex) + abs(sy - ey)
            ans = min(ans, cost)

        return ans


if __name__ == '__main__':
    s = Solution()
    grid = [[1, 3, 0], [1, 0, 0], [1, 0, 3]]
    print(s.minimumMoves(grid))
