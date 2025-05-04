//
// Created by 24276 on 2025/4/29.
//


#include "../template/mylib.h"

using namespace std;

class count_subarrays2962 {
public:
    ll countSubarrays(V<int>& nums,int k) {
        auto mx = ranges::max(nums);
        ll ans = 0;int left = 0,mx_cnt = 0;
        For(right,nums.size()) {
            mx_cnt += nums[right] == mx;
            while (mx_cnt == k) {
                mx_cnt -= nums[left] == mx;
                ++left;
            }
            ans += left;
        }
        return ans;
    }
};

int main() {
    count_subarrays2962 sol;
    V<int> nums = {1,3,2,3,3};
    int k = 2;
    cout << sol.countSubarrays(nums,k);
    return 0;
}
