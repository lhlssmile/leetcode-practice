#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200010;
int t, n, k;

ll solve(vector<ll>& p, vector<int>& v) {
    sort(p.begin(), p.end());
    sort(v.begin(), v.end());
    ll s = 0;
    for (auto x : p) s += x;  // 改用循环，避免 accumulate 潜在问题（虽 bits 有，但稳）
    int nn = n;
    for (int i = 0; i < k; i++) {
        if (nn < v[i]) break;
        s -= p[nn - v[i]];
        nn -= v[i];
    }
    return s;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<ll> prices(n);
        vector<int> voucher(k);
        for (int i = 0; i < n; i++) cin >> prices[i];
        for (int i = 0; i < k; i++) cin >> voucher[i];
        cout << solve(prices, voucher) << "\n";
    }
    return 0;
}