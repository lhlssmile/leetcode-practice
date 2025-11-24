//
// Created by 24276 on 2025/11/18.
//
#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int main() {
    // 示例：构造一棵树，演示点权/边权前缀和、路径和、子树和
    // 树：
    // 1
    // ├─ 2
    // │  ├─ 4
    // │  └─ 5
    // └─ 3
    //    ├─ 6
    //    └─ 7
    // 边权：1-2(3), 1-3(2), 2-4(4), 2-5(1), 3-6(5), 3-7(7)
    // 点权：w = [_, 5, 2, 4, 3, 1, 6, 2]

    int n = 7, root = 1;
    V<V<pair<int,int>>> g(n + 1);
    auto add = [&](int u, int v, int w){ g[u].pb({v,w}); g[v].pb({u,w}); };
    add(1,2,3); add(1,3,2); add(2,4,4); add(2,5,1); add(3,6,5); add(3,7,7);

    vi w = {0,5,2,4,3,1,6,2};

    const int LOG = 20;
    V<vi> up(LOG, vi(n + 1, 0));
    vi parent(n + 1, 0), depth(n + 1, 0);
    V<ll> sumPoint(n + 1, 0), sumEdge(n + 1, 0);
    vi tin(n + 1, 0), tout(n + 1, 0), order; order.reserve(n);
    V<ll> sub(n + 1, 0);
    vi arr(n + 1, 0);
    int timer = 0;

    function<void(int,int)> dfs = [&](int u, int p){
        parent[u] = p; up[0][u] = p; tin[u] = ++timer; depth[u] = (p ? depth[p] + 1 : 0);
        sumPoint[u] = (p ? sumPoint[p] : 0) + w[u];
        sub[u] = w[u];
        arr[tin[u]] = w[u];
        order.pb(u);
        for (auto &e : g[u]){
            int v = e.fi, wuv = e.se; if (v == p) continue;
            sumEdge[v] = sumEdge[u] + wuv;
            dfs(v, u);
            sub[u] += sub[v];
        }
        tout[u] = timer;
    };

    dfs(root, 0);
    for (int j = 1; j < LOG; ++j) For(u, n + 1) up[j][u] = up[j-1][ up[j-1][u] ];

    auto lca = [&](int a, int b){
        if (depth[a] < depth[b]) swap(a,b);
        int diff = depth[a] - depth[b];
        for (int j = 0; j < LOG; ++j) if (diff & (1<<j)) a = up[j][a];
        if (a == b) return a;
        for (int j = LOG-1; j >= 0; --j) if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
        return up[0][a];
    };

    auto pathSumPoint = [&](int u, int v){ int c = lca(u,v); return sumPoint[u] + sumPoint[v] - 2*sumPoint[c] + w[c]; };
    auto pathSumEdge  = [&](int u, int v){ int c = lca(u,v); return sumEdge[u]  + sumEdge[v]  - 2*sumEdge[c]; };

    V<ll> pref(n + 1, 0); for (int i = 1; i <= n; ++i) pref[i] = pref[i-1] + arr[i];
    auto subtreeSumEuler = [&](int u){ return pref[tout[u]] - pref[tin[u]-1]; };

    cout << "sumPoint[4] (root->4, 点权) = " << sumPoint[4] << '\n';
    cout << "sumEdge[6]  (root->6, 边权) = " << sumEdge[6]  << '\n';
    cout << "pathSumPoint(4,6) = " << pathSumPoint(4,6) << '\n';
    cout << "pathSumEdge(5,7)  = " << pathSumEdge(5,7)  << '\n';
    cout << "subtreeSum[2] via dfs = " << sub[2] << '\n';
    cout << "subtreeSum[2] via euler = " << subtreeSumEuler(2) << '\n';

    return 0;
}