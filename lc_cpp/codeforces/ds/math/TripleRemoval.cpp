//
// Created by 24276 on 2025/11/5.
//
#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
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
    int t;
    cin >> t;
    For(_, t) {
        int n, q;
        cin >> n >> q;
        vi a(n + 1);
        a[0] = -1;  // Sentinel to handle diff[1]
        For(i, n) {
            int idx = i + 1;
            cin >> a[idx];
        }
        vi sum0(n + 1, 0);
        vi sum1(n + 1, 0);
        vi diffsum(n + 1, 0);
        For(i, n) {
            int idx = i + 1;
            sum0[idx] = sum0[idx - 1] + (a[idx] == 0);
            sum1[idx] = sum1[idx - 1] + (a[idx] == 1);
            int d = (a[idx] != a[idx - 1]);
            diffsum[idx] = diffsum[idx - 1] + d;
        }
        For(iq, q) {
            int l, r;
            cin >> l >> r;
            int z = sum0[r] - sum0[l - 1];
            int o = sum1[r] - sum1[l - 1];
            if (z % 3 != 0 || o % 3 != 0) {
                cout << -1 << '\n';
                continue;
            }
            int num_ops = z / 3 + o / 3;
            int switches = diffsum[r] - diffsum[l];
            int num_pairs = r - l;  // == len - 1
            int ans = num_ops;
            if (switches == num_pairs) {
                ans += 1;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}