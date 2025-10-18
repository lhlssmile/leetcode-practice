from math import inf

class Solution:
    def assignBikes(self, workers: list[list[int]], bikes: list[list[int]]) -> int:
        n, m = len(workers), len(bikes)
        size = 1 << m
        dp = [inf] * size
        dp[0] = 0

        def dist(p1, p2):
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

        for mask in range(size):
            k = bin(mask).count("1")  # 已分配的工人数
            if k >= n:
                continue
            for j in range(m):
                if not (mask & (1 << j)):  # 车 j 还没被分配
                    nxt = mask | (1 << j)
                    dp[nxt] = min(dp[nxt], dp[mask] + dist(workers[k], bikes[j]))

        ans = inf
        for mask in range(size):
            if bin(mask).count("1") == n:  # 正好分配了 n 个工人
                ans = min(ans, dp[mask])
        return ans


if __name__ == '__main__':
    s = Solution()
    workers = [[0, 0], [2, 1]]
    bikes = [[1, 2], [3, 3]]
    print(Solution().assignBikes(workers, bikes))  # 输出 6
