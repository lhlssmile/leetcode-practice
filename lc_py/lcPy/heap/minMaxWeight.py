import heapq
from cmath import inf
from typing import List


class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        if len(edges) < n - 1: return -1
        g = [[] for _ in range(n)]

        for x, y, w in edges:
            g[y].append((x, w))

        dis = [inf] * n

        dis[0] = 0

        pq = [(0, 0)]  # dist, node

        while pq:
            d, x = heapq.heappop(pq)
            if d > dis[x]: continue

            for y, w in g[x]:
                new_d = max(w, d)
                if new_d < dis[y]:
                    dis[y] = new_d
                    heapq.heappush(pq, (new_d, y))

        ans = max(dis)
        return -1 if ans == inf else ans


if __name__ == '__main__':
    edges = [[1, 0, 1], [2, 0, 2], [3, 0, 1], [4, 3, 1], [2, 1, 1]]
    threshold = 2
    s = Solution()
    print(s.minMaxWeight(5,edges, 2))