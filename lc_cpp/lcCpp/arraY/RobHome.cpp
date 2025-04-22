#include <vector>
#include <iostream>
class RobSolution{
public:
    int rob(std::vector<int>& nums){
        if(nums.empty()) return 0;
        if(nums.size() == 1) return nums[0];
        std::vector<int> dp(nums.size(),0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0],nums[1]);
        for(int i = 2;i < nums.size();++i){
            dp[i] = std::max(dp[i - 2] + nums[i],dp[i - 1]);
        }
        return dp[nums.size() - 1];
    }
};
int main() {
    RobSolution ps;
    std::vector<int> nums = {1,2,3,1};
    std::cout << ps.rob(nums) << std::endl;
    return 0;
}
