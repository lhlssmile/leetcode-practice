#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        if (k == n * n - 1) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        vector<string> grid(n, string(n, ' '));

        int filled = 0;
        for (int i = 0; i < n && filled < k; i++) {
            for (int j = 0; j < n && filled < k; j++) {
                grid[i][j] = 'U';
                filled++;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == ' ') {
                    if (i == n - 1 && j == n - 1)
                        grid[i][j] = 'L';
                    else if (i == n - 1)
                        grid[i][j] = 'R';
                    else
                        grid[i][j] = 'D';
                }
            }
        }

        for (auto &row : grid) cout << row << '\n';
    }
}
