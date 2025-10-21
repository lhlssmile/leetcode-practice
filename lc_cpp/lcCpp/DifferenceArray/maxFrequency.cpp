//
// Created by 24276 on 2025/10/21.
//


#include <bits/stdc++.h>
using namespace std;
#define V vector
using vi = vector<int>;
using umpii = unordered_map<int, int>;
int solve(vi& a, int k, int op) {
    unordered_map<int, int> cnt;
    map<int, int> diff;
    for (int x : a) {
        cnt[x]++;
        diff[x]; // 把 x 插入 diff，以保证下面能遍历到 x
        diff[x - k]++; // 把 [x-k, x+k] 中的每个整数的出现次数都加一
        diff[x + k + 1]--;
    }

    int ans = 0, sum_d = 0;
    for (auto& [x, d] : diff) {
        sum_d += d;
        ans = max(ans, min(sum_d, cnt[x] + op));
    }
    return ans;
}

signed main() {
    vi nums = {1, 4, 5};
    int k = 1, op = 2;
    cout << solve(nums, k, op) << "\n";
    return 0;
}