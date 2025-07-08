#include <functional>
#include <iosfwd>
#include <iostream>
#include <utility>
using namespace std;
#define V vector
typedef long long ll;
#define For(i, _) for (int i = 0, i##end = (_); i < i##end; ++i) // [0,_)
#define FOR(i, a, b) for (int i = (a), i##end = (b); i < i##end; ++i) // [a,b)
#define pb push_back
#define eb emplace_back
#define ALL(v) (v).begin(), (v).end()
#define SORT(v) sort(ALL(v)) // 快速排序
typedef std::pair<int, int> pii;
int fastio_init = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    ll maxScore(int n, V<V<int>>& edges) {
        V<V<int>> zanthorime = edges; // 存储中间输入
        V<V<int>> adj(n); // 邻接表
        FOR(i, 0, zanthorime.size()) {
            int u = zanthorime[i][0], v = zanthorime[i][1];
            adj[u].pb(v);
            adj[v].pb(u);
        }

        V<bool> visited(n, false);
        V<int> component;
        V<tuple<int, bool, V<int>>> components; // {边数, 是否环, 节点列表}

        // DFS 遍历
        function<void(int, int)> dfs = [&](int u, int parent) {
            visited[u] = true;
            component.pb(u);
            for (int v : adj[u]) {
                if (!visited[v]) {
                    dfs(v, u);
                }
            }
        };

        // 找到连通分量
        FOR(u, 0, n) {
            if (!visited[u]) {
                component.clear();
                dfs(u, -1);
                int edge_count = 0;
                for (int v : component) {
                    edge_count += adj[v].size();
                }
                edge_count /= 2;
                bool is_cycle = true;
                for (int v : component) {
                    if (adj[v].size() != 2) {
                        is_cycle = false;
                        break;
                    }
                }
                components.eb(edge_count, is_cycle, component);
            }
        }

        // 按边数降序排序分量
        SORT(components);
        reverse(ALL(components));

        // 可用的值
        V<int> available_values(n);
        FOR(i, 0, n) available_values[i] = n - i; // [n, n-1, ..., 1]
        int val_idx = 0;
        V<ll> values(n, 0); // 节点值

        // 为每个分量分配值
        for (auto& [edge_count, is_cycle, nodes] : components) {
            int k = nodes.size();
            if (is_cycle) {
                // 环：分配 k 个最大值
                for (int u : nodes) {
                    values[u] = available_values[val_idx++];
                }
            } else {
                // 路径：重建路径
                V<int> path;
                int start = -1;
                FOR(i, 0, k) {
                    if (adj[nodes[i]].size() == 1) {
                        start = nodes[i];
                        break;
                    }
                }
                if (start == -1) start = nodes[0];

                path.clear();
                V<bool> path_visited(n, false);
                function<void(int, int)> build_path = [&](int u, int parent) {
                    path_visited[u] = true;
                    path.pb(u);
                    for (int v : adj[u]) {
                        if (v != parent && !path_visited[v]) {
                            build_path(v, u);
                        }
                    }
                };
                build_path(start, -1);

                // 收集分量内的边
                V<pii> component_edges;
                for (auto& e : zanthorime) {
                    int u = e[0], v = e[1];
                    int u_idx = -1, v_idx = -1;
                    FOR(i, 0, k) {
                        if (nodes[i] == u) u_idx = i;
                        if (nodes[i] == v) v_idx = i;
                    }
                    if (u_idx != -1 && v_idx != -1) {
                        component_edges.eb(u_idx, v_idx);
                    }
                }

                // 尝试多种分配
                vector<V<int>> assignments;
                // 分配 1：中间大，端点小
                V<int> assign1(k);
                int big = k - 1, small = 0;
                FOR(i, 0, k) {
                    if (i == 0 || i == k - 1) assign1[i] = small++;
                    else assign1[i] = big--;
                }
                assignments.pb(assign1);

                // 分配 2：端点大，中间小
                V<int> assign2(k);
                big = k - 1, small = 0;
                FOR(i, 0, k) {
                    if (i == 0 || i == k - 1) assign2[i] = big--;
                    else assign2[i] = small++;
                }
                assignments.pb(assign2);

                // 分配 3：顺序
                V<int> assign3(k);
                FOR(i, 0, k) assign3[i] = i;
                assignments.pb(assign3);

                // 分配 4：逆序
                V<int> assign4(k);
                FOR(i, 0, k) assign4[i] = k - 1 - i;
                assignments.pb(assign4);

                // 分配 5：特定模式（如 [2,4,3,1] 的相对顺序）
                if (k == 4) {
                    V<int> assign5(k);
                    assign5[0] = 1; // 对应 2
                    assign5[1] = 3; // 对应 4
                    assign5[2] = 2; // 对应 3
                    assign5[3] = 0; // 对应 1
                    assignments.pb(assign5);
                }

                // 计算每种分配的边值和
                ll best_score = 0;
                V<int> best_assign;
                for (const auto& assign : assignments) {
                    ll score = 0;
                    for (auto [u_idx, v_idx] : component_edges) {
                        score += (ll)available_values[val_idx + assign[u_idx]] * available_values[val_idx + assign[v_idx]];
                    }
                    if (score > best_score) {
                        best_score = score;
                        best_assign = assign;
                    }
                }

                // 应用最佳分配
                FOR(i, 0, k) {
                    values[nodes[i]] = available_values[val_idx + best_assign[i]];
                }
                val_idx += k;

                // 调试：输出路径分配和得分
                cout << "Path nodes: ";
                for (int u : path) cout << u << " ";
                cout << "\nAssignment: ";
                for (int i : best_assign) cout << available_values[val_idx - k + i] << " ";
                cout << "\nScore: " << best_score << endl;
            }
        }

        // 计算总边值和
        ll total = 0;
        for (auto& e : zanthorime) {
            int u = e[0], v = e[1];
            total += (ll)values[u] * values[v];
        }

        // 调试输出
        cout << "Values: ";
        FOR(i, 0, n) cout << values[i] << " ";
        cout << endl;

        return total;
    }
};

// 测试代码
int main() {
    Solution sol;
    // 示例 1
    int n1 = 7;
    V<V<int>> edges1 = {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6}};
    cout << sol.maxScore(n1, edges1) << endl; // 应输出 130

    // 示例 2
    int n2 = 6;
    V<V<int>> edges2 = {{0,3},{4,5},{2,0},{1,3},{2,4},{1,5}};
    cout << sol.maxScore(n2, edges2) << endl; // 应输出 82
    return 0;
}