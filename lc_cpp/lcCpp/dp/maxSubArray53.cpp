#include <vector>
#include <iostream>
using namespace std;
class maxSubArraySolution{
public:
    int maxSubArray(vector<int>& nums){
        if(nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        int maxValue = dp[0] = nums[0];
        for(int i = 1;i < nums.size();++i){
            dp[i] = std::max(dp[i - 1] + nums[i],nums[i]);
            maxValue = std::max(maxValue,dp[i]);
        }
        return maxValue;
    }
};
int main() {
    maxSubArraySolution ps;
    vector<int> nums = {-1,1,-3,4,-1,2,1,-5,4};
    auto res = ps.maxSubArray(nums);
    cout << res << endl;
    return 0;
}
