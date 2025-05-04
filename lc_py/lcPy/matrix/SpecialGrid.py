from typing import List
class SpecialGrid:
    def specialGrid(self, n: int) -> List[List[int]]:
        a = [[0] * (1 << n) for _ in range(1 << n)]
        val = 0

        def dfs(u: int, d: int, l: int, r: int) -> None:
            if d - u == 1:
                nonlocal val
                a[u][l] = val
                val += 1
                return
            m = (d - u) // 2
            dfs(u, u + m, l + m, r)
            dfs(u + m, d, l + m, r)
            dfs(u + m, d, l, l + m)
            dfs(u, u + m, l, l + m)

        dfs(0, 1 << n, 0, 1 << n)
        return a


if __name__ == '__main__':
    sol = SpecialGrid()
    print(sol.specialGrid(1))