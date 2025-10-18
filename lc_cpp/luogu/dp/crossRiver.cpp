
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int n, m, hx, hy;

ll dp[25][25];
bool block[25][25];  // 被马控制的格子
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
long long dfs(int x, int y) {
    if (x < 0 || y < 0 || block[y][x]) return 0;
    if (x == 0 && y == 0) return 1;
    if (dp[y][x] != -1) return dp[y][x];
    dp[y][x] = dfs(x - 1, y) + dfs(x, y - 1);
    return dp[y][x];
}
signed main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> hx >> hy;
    memset(dp, -1, sizeof(dp));
    memset(block, false, sizeof(block));
    block[hx][hy] = true;
    for (int i = 0; i < 8; i++) {
        int nx = hx + dx[i], ny = hy + dy[i];
        if (nx >= 0 && nx <= n && ny <= m && ny >= 0) {
            block[nx][ny] = true;
        }
    }
    cout << dfs(n, m) << "\n";
    return 0;
}