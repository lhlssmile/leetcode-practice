using namespace std;
#include <vector>
#include <iostream>
class rob_home_lcr89 {
public:
    static int rob(vector<int>& nums) {
        vector<int> dp(nums.size());
        int n = nums.size();
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        dp[0] = nums[0];dp[1] = std::max(nums[0],nums[1]);
        for(int i = 2; i< nums.size();++i) {
            dp[i] = std::max(dp[i - 1],dp[i - 2] + nums[i]);
            //不必要 因为一直在偷钱。越多越好 直接返回dp[n - 1]
            // sum = std::max(sum,dp[i]);
        }
        return dp[n - 1];
    }
    static int robHome(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        vector<int> dp(n);
        int prev2 = nums[0],prev1 = std::max(nums[0],nums[1]);
        for(int i = 2;i < n;++i) {
            int current = std::max(prev1,prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        //返回第最后一家总共偷的钱
        return prev1;
    }
};

int main() {
    rob_home_lcr89 ps;
    std::vector<int> nums = {2,7,9,3,1};
    std::cout << ps.rob(nums) << std::endl;
    return 0;
}
