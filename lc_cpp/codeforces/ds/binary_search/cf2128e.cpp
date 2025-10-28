#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 10);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    auto check = [&] (int vl) -> pair<int, int> {
        vector<int> sum(n + 10);
        for (int i = 1; i <= n; i++) {
            if (a[i] >= vl) sum[i] = 1;
            else sum[i] = -1;
            sum[i] += sum[i - 1];
        }
        int pos = 0;
        for (int i = k; i <= n; i++) {
            if (sum[i - k] < sum[pos]) pos = i - k;
            if (sum[i] - sum[pos] >= 0)
                return {pos + 1, i};
        }
        return {0, 0};
    };
    int l = 1, r = n, mid, ans = -1;
    pair<int, int> res;
    while (l <= r) {
        mid = (l + r) / 2;
        pair<int, int> pr = check(mid);
        if (pr.first != 0) l = mid + 1, ans = mid, res = pr;
        else r = mid - 1;
    }
    cout << ans << " " << res.first << " " << res.second << endl;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}