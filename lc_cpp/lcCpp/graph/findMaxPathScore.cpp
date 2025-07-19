//
// Created by 24276 on 2025/7/19.
//
/**
* 给你一个包含 n 个节点（编号从 0 到 n - 1）的有向无环图。图由长度为 m 的二维数组 edges 表示，其中 edges[i] = [ui, vi, costi] 表示从节点 ui 到节点 vi 的单向通信，恢复成本为 costi。

一些节点可能处于离线状态。给定一个布尔数组 online，其中 online[i] = true 表示节点 i 在线。节点 0 和 n - 1 始终在线。

从 0 到 n - 1 的路径如果满足以下条件，那么它是 有效 的：

路径上的所有中间节点都在线。
路径上所有边的总恢复成本不超过 k。
对于每条有效路径，其 分数 定义为该路径上的最小边成本。

返回所有有效路径中的 最大 路径分数（即最大 最小 边成本）。如果没有有效路径，则返回 -1。

  

示例 1:

输入: edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [true,true,true,true], k = 10

输出: 3

解释:



图中有两条从节点 0 到节点 3 的可能路线：

路径 0 → 1 → 3

总成本 = 5 + 10 = 15，超过了 k (15 > 10)，因此此路径无效。

路径 0 → 2 → 3

总成本 = 3 + 4 = 7 <= k，因此此路径有效。

此路径上的最小边成本为 min(3, 4) = 3。

没有其他有效路径。因此，所有有效路径分数中的最大值为 3。

示例 2:

输入: edges = [[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]], online = [true,true,true,false,true], k = 12

输出: 6

解释:



节点 3 离线，因此任何通过 3 的路径都是无效的。

考虑从 0 到 4 的其余路线：

路径 0 → 1 → 4

总成本 = 7 + 5 = 12 <= k，因此此路径有效。

此路径上的最小边成本为 min(7, 5) = 5。

路径 0 → 2 → 3 → 4

节点 3 离线，因此无论成本多少，此路径无效。

路径 0 → 2 → 4

总成本 = 6 + 6 = 12 <= k，因此此路径有效。

此路径上的最小边成本为 min(6, 6) = 6。

在两条有效路径中，它们的分数分别为 5 和 6。因此，答案是 6。

  

提示:

n == online.length
2 <= n <= 5 * 104
0 <= m == edges.length <= min(105, n * (n - 1) / 2)
edges[i] = [ui, vi, costi]
0 <= ui, vi < n
ui != vi
0 <= costi <= 109
0 <= k <= 5 * 1013
online[i] 是 true 或 false，且 online[0] 和 online[n - 1] 均为 true。
给定的图是一个有向无环图。©leetcode
*/
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <set>
#include <climits>
#include <algorithm>
using namespace std;
class find_max_path_score {
public:
    // 方法1：基础DFS解法（递归回溯）
    int findMaxPathScore_basic(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // 构建邻接表
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }
        
        int maxScore = -1;
        
        // DFS递归函数
        function<void(int, long long, int)> dfs = [&](int node, long long cost, int minEdge) {
            if (node == n - 1) {
                if (cost <= k) {
                    maxScore = max(maxScore, minEdge);
                }
                return;
            }
            
            for (auto& [nextNode, edgeCost] : graph[node]) {
                if (online[nextNode] && cost + edgeCost <= k) {
                    dfs(nextNode, cost + edgeCost, min(minEdge, edgeCost));
                }
            }
        };
        
        dfs(0, 0, INT_MAX);
        return maxScore;
    }
    
    // 方法2：优化DFS + 记忆化
    int findMaxPathScore_memo(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // 构建邻接表
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }
        
        // memo[node][cost] = 从node开始，剩余成本为cost时的最大路径分数
        map<pair<int, long long>, int> memo;
        
        function<int(int, long long)> dfs = [&](int node, long long remainCost) -> int {
            if (node == n - 1) return INT_MAX; // 到达终点
            
            auto key = make_pair(node, remainCost);
            if (memo.count(key)) return memo[key];
            
            int result = -1;
            for (auto& [nextNode, edgeCost] : graph[node]) {
                if (online[nextNode] && remainCost >= edgeCost) {
                    int subResult = dfs(nextNode, remainCost - edgeCost);
                    if (subResult != -1) {
                        result = max(result, min(edgeCost, subResult));
                    }
                }
            }
            
            return memo[key] = result;
        };
        
        return dfs(0, k);
    }
    
    // 方法3：二分搜索 + DFS验证（最优解法）
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // 构建邻接表
        vector<vector<pair<int, int>>> graph(n);
        set<int> allCosts;
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            allCosts.insert(edge[2]);
        }
        
        vector<int> costs(allCosts.begin(), allCosts.end());
        
        // 检查是否存在最小边权重至少为minCost的有效路径
        auto canReach = [&](int minCost) -> bool {
            function<bool(int, long long)> dfs = [&](int node, long long cost) -> bool {
                if (node == n - 1) return cost <= k;
                
                for (auto& [nextNode, edgeCost] : graph[node]) {
                    if (online[nextNode] && edgeCost >= minCost && cost + edgeCost <= k) {
                        if (dfs(nextNode, cost + edgeCost)) {
                            return true;
                        }
                    }
                }
                return false;
            };
            
            return dfs(0, 0);
        };
        
        // 二分搜索最大的最小边权重
        int left = 0, right = costs.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canReach(costs[mid])) {
                result = costs[mid];
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};

int main() {
    find_max_path_score solution;
    
    // 测试用例1
    vector<vector<int>> edges1 = {{0,1,5},{1,3,10},{0,2,3},{2,3,4}};
    vector<bool> online1 = {true, true, true, true};
    long long k1 = 10;
    
    cout << "测试用例1:" << endl;
    cout << "基础DFS: " << solution.findMaxPathScore_basic(edges1, online1, k1) << endl;
    cout << "记忆化DFS: " << solution.findMaxPathScore_memo(edges1, online1, k1) << endl;
    cout << "二分搜索: " << solution.findMaxPathScore(edges1, online1, k1) << endl;
    
    // 测试用例2
    vector<vector<int>> edges2 = {{0,1,7},{1,4,5},{0,2,6},{2,3,6},{3,4,2},{2,4,6}};
    vector<bool> online2 = {true, true, true, false, true};
    long long k2 = 12;
    
    cout << "\n测试用例2:" << endl;
    cout << "基础DFS: " << solution.findMaxPathScore_basic(edges2, online2, k2) << endl;
    cout << "记忆化DFS: " << solution.findMaxPathScore_memo(edges2, online2, k2) << endl;
    cout << "二分搜索: " << solution.findMaxPathScore(edges2, online2, k2) << endl;
    
    return 0;
}

/*
=== 算法分析与解题思路 ===

【题目核心】
- 在有向无环图中找从节点0到节点n-1的有效路径
- 有效路径条件：1) 中间节点都在线 2) 总成本不超过k
- 路径分数 = 路径上最小边权重
- 目标：找所有有效路径中的最大分数

【解法对比】

1. 基础DFS解法（递归回溯）
   - 思路：从节点0开始，递归探索所有可能路径
   - 参数：当前节点、累计成本、当前路径最小边权重
   - 优点：思路直观，易于理解
   - 缺点：可能存在重复计算，时间复杂度较高
   - 时间复杂度：O(2^n) 最坏情况
   - 空间复杂度：O(n) 递归栈深度

2. 记忆化DFS解法
   - 思路：在DFS基础上添加记忆化，避免重复计算
   - 状态：memo[node][remainCost] = 最大路径分数
   - 优点：减少重复计算，提高效率
   - 缺点：空间消耗较大（k值很大时）
   - 时间复杂度：O(n * k)
   - 空间复杂度：O(n * k)

3. 二分搜索 + DFS验证（最优解法）
   - 思路：二分搜索答案，对每个候选答案用DFS验证
   - 关键：将"最大化最小值"转化为"判定性问题"
   - 优点：时间复杂度最优，适合大规模数据
   - 缺点：实现稍复杂
   - 时间复杂度：O(m * log(m) * (n + m))
   - 空间复杂度：O(n + m)

【关键技巧】

1. 图的表示
   - 使用邻接表存储：vector<vector<pair<int, int>>> graph
   - pair<nextNode, edgeCost> 存储邻接节点和边权重

2. DFS剪枝优化
   - 提前检查成本是否超限：cost + edgeCost <= k
   - 检查节点是否在线：online[nextNode]
   - 只考虑满足最小权重要求的边：edgeCost >= minCost

3. 二分搜索技巧
   - 搜索空间：所有边权重的去重排序数组
   - 判定函数：检查是否存在最小边权重≥target的有效路径
   - 单调性：如果权重x可达，则所有≤x的权重都可达

【复杂度分析】
- n: 节点数量 (≤ 5*10^4)
- m: 边数量 (≤ 10^5)
- k: 成本限制 (≤ 5*10^13)

对于此题规模，推荐使用二分搜索解法，既保证正确性又有最优时间复杂度。

【扩展思考】
1. 如果图有环怎么办？需要添加访问标记避免死循环
2. 如果要求路径数量？修改DFS返回值为路径计数
3. 如果要求具体路径？在DFS中记录路径信息
4. 多源多汇问题？可以添加虚拟源点和汇点
*/
