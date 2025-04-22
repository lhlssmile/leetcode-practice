//
// Created by 24276 on 2025/3/28.
//

#include <vector>
#include <iostream>
using namespace std;

class can_jump55 {
public:
    /**
     * 1.dp ? 2.greedy
     * @param nums given nums
     * @return
     */
    bool canJump(vector<int>& nums) {
        auto n = nums.size();
        //怎么定义状态?dp表示什么.? scope contains [0,nums[i]]跳至最大下标?
        vector<bool> dp(n,false);
        dp[0] = true;
        for(int i = 1; i < n;++i) {
            //怎么转移状态
            for (int j = 0;j < i;j++) {
                if(dp[j] && j + nums[j] >= i) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n - 1];
    }
    bool canJumpGreedy(vector<int>& nums) {
        //倒着往回遍历,看上一个距离最远的nums[i]是否能跳至nums[n - 1]
        auto n = nums.size();
        int target = n - 1;
        for(int i = n - 2;i >= 0;--i) {
            if(i + nums[i] >= target) {
                target = i;
            }
        }
        return target == 0;
    }
    bool canJump2(vector<int>& nums) {
        int n = nums.size();
        int max_reach = 0;
        for(int i = 0;i < n && i <= max_reach;i++) {
            max_reach = max(max_reach,i + nums[i]);
            if(max_reach >= n - 1) return true;
        }
        return max_reach >= n - 1;
    }
};

int main() {
    can_jump55 solution;
    vector<int> nums = {2,3,1,1,4};
    cout << solution.canJump(nums) << endl;
    return 0;
}
