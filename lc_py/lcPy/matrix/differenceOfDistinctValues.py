from typing import List


class Solution:
    def differenceOfDistinctValues(self, grid: List[List[int]]) -> List[List[int]]:
        st = set()
        m, n = len(grid), len(grid[0])
        ans = [[0] * n for _ in range(m)]
        for k in range(1, m + n):
            j_min = max(0, n - k)
            j_max = min(n - 1, m - 1 + n - k)
            st.clear()
            for j in range(j_min, j_max + 1):
                i = k + j - n
                ans[i][j] = len(st)
                st.add(grid[i][j])
            st.clear()
            for j in range(j_max, j_min - 1, -1):
                i = k + j - n
                ans[i][j] = abs(ans[i][j] - len(st))
                st.add(grid[i][j])
        return ans


if __name__ == '__main__':
    grid = [[1,2,3],[3,1,5],[3,2,1]]

    s = Solution()
    s.differenceOfDistinctValues(grid)