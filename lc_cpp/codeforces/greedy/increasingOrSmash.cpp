
// op1: {1, n} incresing x
// op2: {i, j} smash to 0
/**
 * 9 9 3 2 4 4 8 5 3
 * 2 3 3 4 4 5 8 9 9
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 101;
int t, n;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n + 1);
        set<int> st;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            st.insert(a[i]);
        }
        int k = st.size();
        cout << 2 * k - 1 << "\n";
    }
    return 0;
}