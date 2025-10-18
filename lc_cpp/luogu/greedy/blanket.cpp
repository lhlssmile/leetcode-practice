
#include <bits/stdc++.h>
using namespace std;
int n;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<array<int, 4>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        // a b g k
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
    }
    int x, y;
    cin >> x >> y;
    int ans = -1;
    for (int i = n; i > 0; i--) {
        int l = a[i][0], b = a[i][1], g = a[i][2], k = a[i][3];
        if (x >= l && x <= l + g && y >= b && y <= b + k) {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";

    return 0;
}