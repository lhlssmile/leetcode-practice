

// n 偶数 配对 最大差值最小

#include <bits/stdc++.h>
using namespace std;
const int N = 2 * 100005;
int t, n;
typedef long long ll;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        
        cin >> n;
        vector<ll> A(n);
        for (int i = 0; i < n; i++) cin >> A[i];
        ll res = INT_MIN;
        sort(A.begin(), A.end());
        for (int i = 1; i < n; i+= 2) {
            ll diff = A[i] - A[i - 1];
            if (diff > res) res = diff;
        }
        cout << res << "\n";
    }
    return 0;
}