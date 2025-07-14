'''

给你一个无向连通图，包含 n 个节点，节点编号从 0 到 n - 1，以及一个二维整数数组 edges，其中 edges[i] = [ui, vi, wi] 表示一条连接节点 ui 和节点 vi 的无向边，边权为 wi，另有一个整数 k。

你可以从图中移除任意数量的边，使得最终的图中 最多 只包含 k 个连通分量。

连通分量的 成本 定义为该分量中边权的 最大值 。如果一个连通分量没有边，则其代价为 0。

请返回在移除这些边之后，在所有连通分量之中的 最大成本 的 最小可能值 。

 

示例 1：

输入： n = 5, edges = [[0,1,4],[1,2,3],[1,3,2],[3,4,6]], k = 2

输出： 4

解释：



移除节点 3 和节点 4 之间的边（权值为 6）。
最终的连通分量成本分别为 0 和 4，因此最大代价为 4。
示例 2：

输入： n = 4, edges = [[0,1,5],[1,2,5],[2,3,5]], k = 1

输出： 5

解释：



无法移除任何边，因为只允许一个连通分量（k = 1），图必须保持完全连通。
该连通分量的成本等于其最大边权，即 5。
 

提示：

1 <= n <= 5 * 10^4
0 <= edges.length <= 10^5
edges[i].length == 3
0 <= ui, vi < n
1 <= wi <= 10^6
1 <= k <= n
输入图是连通图。
'''

from typing import List


class UnionFind:
    """并查集数据结构"""

    def __init__(self, n):
        self.parent = list(range(n))  # 初始化每个节点的父节点为自己
        self.rank = [0] * n  # 用于优化的秩
        self.components = n  # 连通分量数量

    def find(self, x):
        """查找根节点，带路径压缩优化"""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # 路径压缩
        return self.parent[x]

    def union(self, x, y):
        """合并两个集合，返回是否成功合并"""
        root_x, root_y = self.find(x), self.find(y)
        if root_x == root_y:
            return False  # 已经在同一个集合中

        # 按秩合并优化
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

        self.components -= 1  # 连通分量减1
        return True


class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        """
        思路：
        1. 要让最大成本最小，我们需要移除权重最大的边
        2. 使用Kruskal算法的逆向思维：从小到大添加边，直到连通分量数量 <= k
        3. 二分查找答案：二分最大边权，检查能否在不超过该权重的情况下达到k个连通分量
        """
        if k >= n:
            return 0  # 如果k >= n，每个节点都是独立的连通分量，成本为0
        
        if not edges:  # 如果没有边，已经有n个连通分量
            return 0

        # 获取所有边权并排序，用于二分查找
        weights = sorted(set(edge[2] for edge in edges))

        def canAchieve(max_weight):
            """检查在最大边权不超过max_weight的情况下，能否达到k个连通分量"""
            uf = UnionFind(n)

            # 只添加权重 <= max_weight 的边
            for u, v, w in edges:
                if w <= max_weight:
                    uf.union(u, v)

            return uf.components <= k

        # 二分查找最小的最大边权
        left, right = 0, len(weights) - 1
        result = weights[-1]  # 最坏情况是最大边权

        while left <= right:
            mid = (left + right) // 2
            if canAchieve(weights[mid]):
                result = weights[mid]
                right = mid - 1  # 尝试更小的权重
            else:
                left = mid + 1

        return result


if __name__ == '__main__':
    ps = Solution()
    print("测试用例1:", ps.minCost(5, [
        [0, 1, 4], [1, 2, 3], [1, 3, 2], [3, 4, 6]
    ], 2))  # 预期: 4
    
    print("测试用例2:", ps.minCost(4, [
        [0, 1, 5], [1, 2, 5], [2, 3, 5]
    ], 1))  # 预期: 5
    
    print("测试用例3 (Bug修复):", ps.minCost(4, [
        [0, 1, 5], [1, 2, 5], [2, 3, 5]
    ], 4))  # 预期: 0 (k >= n)
