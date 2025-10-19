#include <bits/stdc++.h>
using namespace std;
int grid[15][15];
int dp[30][15][15];
int n;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    int a, b, c;
    while (cin >> a >> b >> c, a || b || c) grid[a][b] = c; 

    for (int k = 2; k <= 2 * n; k++) {
        for (int i1 = 1; i1 <= n; i1++) {
            for (int i2 = 1; i2 <= n; i2++) {
                int j1 = k - i1, j2 = k - i2;
                if (j1 < 1 || j2 < 1 || j1 > n || j2 > n) continue;
                int &res = dp[k][i1][i2];
                res = max({
                    dp[k-1][i1-1][i2-1],
                    dp[k-1][i1-1][i2],
                    dp[k-1][i1][i2-1],
                    dp[k-1][i1][i2]
                });
                res += grid[i1][j1];
                if (i1 != i2) {res += grid[i2][j2];}
            }
        }
    }
    cout << dp[2*n][n][n] << "\n";
    return 0;
}