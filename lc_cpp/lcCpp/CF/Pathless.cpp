#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        // 先排序
        sort(a.begin(), a.end());

        // 尝试一种构造：把最大的数放在前面，让和尽快超过 s
        vector<int> res = a;
        reverse(res.begin(), res.end()); // 降序

        // 检查是否能阻止 Alice
        // 因为 n 很小，我们可以直接模拟所有可能路径和
        auto canAliceWin = [&](vector<int> arr) {
            // BFS 所有路径
            set<pair<int,int>> visited; // (位置, 当前和)
            queue<pair<int,int>> q;
            q.push({0, arr[0]});
            visited.insert({0, arr[0]});

            while (!q.empty()) {
                auto [pos, sum] = q.front();
                q.pop();
                if (pos == n-1 && sum == s) return true;
                for (int d : {-1, 1}) {
                    int np = pos + d;
                    if (np >= 0 && np < n) {
                        int nsum = sum + arr[np];
                        if (!visited.count({np, nsum})) {
                            visited.insert({np, nsum});
                            q.push({np, nsum});
                        }
                    }
                }
            }
            return false;
        };

        if (!canAliceWin(res)) {
            for (int i = 0; i < n; i++) {
                cout << res[i] << (i + 1 == n ? '\n' : ' ');
            }
        } else {
            cout << -1 << "\n";
        }
    }
    return 0;
}
