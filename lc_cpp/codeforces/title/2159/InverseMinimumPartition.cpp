#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF64 = (ll)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n+1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        // build logs
        vector<int> lg(n+2);
        lg[1] = 0;
        for (int i = 2; i <= n+1; ++i) lg[i] = lg[i/2] + 1;

        // build sparse table for RMQ min
        int K = lg[n] + 1;
        vector<vector<ll>> st(K, vector<ll>(n+1));
        for (int i = 1; i <= n; ++i) st[0][i] = a[i];
        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            int half = 1 << (k-1);
            for (int i = 1; i + len - 1 <= n; ++i) {
                st[k][i] = min(st[k-1][i], st[k-1][i + half]);
            }
        }
        auto range_min = [&](int l, int r) -> ll {
            if (l > r) return INF64;
            int len = r - l + 1;
            int k = lg[len];
            return min(st[k][l], st[k][r - (1<<k) + 1]);
        };

        // helper for ceil division
        auto ceil_div = [&](ll x, ll y)->ll {
            return (x + y - 1) / y;
        };

        // compute dp
        vector<ll> dp(n+1, INF64);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            // try c = 1,2,3
            for (int c = 1; c <= 3; ++c) {
                // threshold for min: ceil(a[i] / c)
                ll t = ceil_div(a[i], c);
                // binary search leftmost l in [1..i] such that range_min(l,i) >= t
                int lo = 1, hi = i, ans = i;
                while (lo <= hi) {
                    int mid = (lo + hi) >> 1;
                    if (range_min(mid, i) >= t) {
                        ans = mid;
                        hi = mid - 1;
                    } else lo = mid + 1;
                }
                // now ans is L(i,c)
                dp[i] = min(dp[i], dp[ans-1] + (ll)c);
            }
        }

        cout << dp[n] << '\n';
    }
    return 0;
}
