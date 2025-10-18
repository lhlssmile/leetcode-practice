
#include <bits/stdc++.h>

using namespace std;
const int N = 11;
int t, n;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        // 1 6 7 9 9 -> prefix 0 1 7 14 23 32
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        int s = accumulate(a.begin(), a.end(), 0);
        sort(a.begin(), a.end());
        int res = s / n;
        vector<int> prefix (n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
        int l = 1, r = a.size() - 1;
        for (; l <= r; l++) {
            int curr = (prefix[r + 1] - prefix[l]) / (r - l + 1);
            res = max(res, curr);
        }
        cout << res << "\n";
    }
    return 0;
}