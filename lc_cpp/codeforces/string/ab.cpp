#include <bits/stdc++.h>
using namespace std;

long long solve_one(const string &s, char c) {
    vector<long long> pos;
    for (int i = 0; i < (int)s.size(); ++i)
        if (s[i] == c) pos.push_back(i);
    if (pos.empty()) return 0;
    vector<long long> shifted;
    for (int i = 0; i < (int)pos.size(); ++i)
        shifted.push_back(pos[i] - i);
    sort(shifted.begin(), shifted.end());
    long long m = shifted[shifted.size() / 2];
    long long res = 0;
    for (auto x : shifted) res += llabs(x - m);
    return res;
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
        cout << min(solve_one(s, 'a'), solve_one(s, 'b')) << "\n";
    }
    return 0;
}
