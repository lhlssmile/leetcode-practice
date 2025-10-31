//
// Created by 24276 on 2025/10/30.
//
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pill = pair<int, ll>;
#define V vector
using vi = V<int>;
class count_stable_subarrays {
public:
    static ll CountStableSubarrays(vi& capacity) {
        map<pill, int> cnt;
     // 子数组l..r c[l] == c[r] == sum(c[l + 1..r - 1]
        ll sum = capacity[0], ans = 0;
        for (int r = 1; r < capacity.size(); r++) {
            ans += cnt[{capacity[r], sum}];
            cnt[{capacity[r - 1], capacity[r - 1] + sum}]++;
            sum += capacity[r];
        }
        return ans;
    }
};

int main() {
    return 0;
}
