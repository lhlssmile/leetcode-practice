//
// Created by 24276 on 2025/4/2.
//
#include <vector>
#include <iostream>
using namespace std;

class maximum_triplet_value2873 {
public:
    using ll = long long;
    ll maximumTripletValue(vector<int>& nums) {
        ll ans = 0;
        auto n = nums.size();
        for(int i = 0;i < n - 2;i++) {
            for(int j = i+1;j <= n - 2;j++) {
                for(int k = j+1;k < n;k++) {
                    long long sign = nums[i] - nums[j];
                    if(sign < 0) {      //一定是负值了
                        continue;
                    }
                    ll tripletValue = sign * nums[k];
                    ans = max(ans,tripletValue);
                }
            }
        }
        return ans;
    }
    ll maximumTripletValues(vector<int>& nums) {
        auto n = nums.size();
        ll ans = 0;
        int maxVal = 0,maxDiff = 0;
        for(int k = 0;k < n;++k) {
            //计算 (nums[i] - nums[j]) * nums[k]
            ans = max(ans,(ll)maxDiff * nums[k]);

            maxDiff = max(maxDiff,maxVal - nums[k]);

            maxVal = max(maxVal,nums[k]);
        }
        return ans;
    }
};

int main() {
    maximum_triplet_value2873 solution;
    vector<int> nums = {12,6,1,2,7};
    cout << solution.maximumTripletValues(nums) << endl;
    return 0;
}
