from typing import List


class Solution:
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
        n = len(matrix)

        def countLessEqual(x: int) -> int:
            i, j = n - 1, 0
            cnt = 0
            while i >= 0 and j < n:
                if matrix[i][j] <= x:
                    cnt += i + 1
                    j += 1
                else:
                    i -= 1
            return cnt

        lo, hi = matrix[0][0], matrix[-1][-1]

        while lo < hi:
            m = lo + (hi - lo) // 2
            if countLessEqual(m) < k:
                lo = m + 1
            else:
                hi = m
        return lo


if __name__ == '__main__':
    s = Solution()
    s.kthSmallest([[1, 5, 9], [10, 11, 13], [12, 13, 15]], 8)
