#include <bits/stdc++.h>
using namespace std;
const int N = 102;
int t, n, cnt[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));  // 清零 cnt
        cin >> n;
        vector<int> A(n);  // 用 vector 替换 A[n]
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < n; i++) {
            int x = A[i];
            if (x < N) cnt[x]++;  // 防越界，虽题目 <=100
        }
        int mex = 0;
        for (int i = 0; i < N; i++) {
            if (cnt[i] == 0) {
                mex = i;
                break;
            }
        }
        cout << mex << '\n';  // 加换行
    }
    return 0;
}