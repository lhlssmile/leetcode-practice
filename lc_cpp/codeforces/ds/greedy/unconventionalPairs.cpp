//
// Created by 24276 on 2025/10/17.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> A(n);  // 用 long long 防溢出，虽 diff 安全但稳
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        sort(A.begin(), A.end());
        long long res = 0;  // 初始化为 0
        for (int i = 1; i < n; i += 2) {
            long long diff = A[i] - A[i - 1];
            if (diff > res) {
                res = diff;
            }
        }
        cout << res << '\n';
    }
    return 0;
}