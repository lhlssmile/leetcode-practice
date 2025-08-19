//
// Created by 24276 on 2025/8/17.
//

#include "../template/mylib.h"

class min_cost {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        //邻接表
        V<V<pair<int, int>>> graph(n), inEdges(n);

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].eb(v, w);
            inEdges[v].eb(u, w);    // w?-w...?
        }
        V<int> dist(n, INT_MAX);
        dist[0] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(0, 0);
        set<int> visited;
        while(!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();
            if (visited.count(u)) continue;
            visited.insert(u);

            if (u == n - 1) return cost;

            for (const auto& [v, w] : graph[u]) {
                if (cost + w < dist[v]) {
                    dist[v] = cost + w;
                    pq.emplace(cost + w, v);
                }
            }
            for (const auto& [v, w] : inEdges[u]) {
                if (cost + 2 * w < dist[v]) {
                    dist[v] = cost + 2 * w;
                    pq.emplace(cost + 2 * w, v);
                }
            }

        }
        return -1;
    }
};

int main() {
    min_cost ps;
    int n = 4;
    V<V<int>> edges = {
        {0, 1, 3}, {3, 1, 1}, {2, 3, 4}, {0, 2, 2}
    };
    ps.minCost(n, edges);
    return 0;
}
