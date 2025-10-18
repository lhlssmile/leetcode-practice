#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string &s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++, r--;
    }
    return true;
}

bool isNonDecreasing(const string &s) {
    for (int i = 1; i < (int)s.size(); i++)
        if (s[i] < s[i - 1]) return false;
    return true;
}

tuple<int, vector<int>> solve(string s) {
    int n = s.size();

    // 从大到小枚举 mask，更容易匹配样例输出风格
    for (int mask = 0; mask < (1 << n); mask++) {
        string p, x;
        vector<int> idx;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                p += s[i];
                idx.push_back(i + 1);
            } else {
                x += s[i];
            }
        }
        if (isNonDecreasing(p) && isPalindrome(x)) {
            return {(int)idx.size(), idx};
        }
    }
    return {-1, {}};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        auto [k, idx] = solve(s);
        if (k == -1) cout << -1 << "\n";
        else {
            cout << k << "\n";
            if (k > 0) {
                for (int i = 0; i < k; i++) {
                    cout << idx[i] << (i + 1 == k ? '\n' : ' ');
                }
            }
        }
    }
    return 0;
}
