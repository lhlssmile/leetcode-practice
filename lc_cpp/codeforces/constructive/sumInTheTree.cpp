//
// Created by 24276 on 2025/10/19.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> parent;
vector<ll> s;
vector<vector<int>> g;

ll ans = 0;
bool bad = false;

void dfs(int u, int p) {
    if (s[u] == -1) {
        if (g[u].empty()) {
            // 没有孩子，就继承父节点的s
            s[u] = s[p];
        } else {
            ll mn = LLONG_MAX;
            for (int v : g[u]) {
                mn = min(mn, s[v]);
            }
            if (mn < s[p]) {
                bad = true;
                return;
            }
            s[u] = mn;
        }
    }
    ans += s[u] - s[p];
    for (int v : g[u]) dfs(v, u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    parent.resize(n + 1);
    s.resize(n + 1);
    g.assign(n + 1, {});

    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        g[parent[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> s[i];

    s[0] = 0; // 虚拟根节点
    dfs(1, 0);

    if (bad) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}
