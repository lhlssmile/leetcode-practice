//
// Created by 24276 on 2025/10/16.
//

#include <bits/stdc++.h>
typedef long long ll;

ll solve(std::vector<int>& nums) {
    int m = nums.back();
    ll ans = 0L;

    for (int i = (int)nums.size() - 2; i >= 0; i--) {
        int k = (nums[i] - 1) / m;
        ans += k;
        m = nums[i] / (k + 1);
    }
    return ans;
}
class minimum_replacement {
public:
    ll minimumReplacement(std::vector<int>& nums) {
        return solve(nums);
    }
};
signed main() {
    minimum_replacement ps;
    std::vector<int> nums = {9, 6, 5};
    ps.minimumReplacement(nums);
    // std::cout << solve(nums);

}