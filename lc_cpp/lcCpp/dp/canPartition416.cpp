//
// Created by 24276 on 2025/4/7.
//

#include <bitset>
#include <vector>
#include <iostream>
#include <numeric>
using namespace std;

class can_partition416 {
public:
    /**
     *  🌸0-1背包问题 计算数组和 如果为奇数直接返回false 因为无法平分
     *    否则找到一个数组使得和为 sum / 2
     * 怎么定义状态? dp   -> dp[i][j] 记前i个数 能否分割为和j的子集
     * 怎么转移状态?      -> 选择 nums[i - 1] then dp[i-1][j] = dp[i-1][j-nums[i-1]] (j > nums[i - 1]
     * @param nums
     * @return
     */
    bool canPartition(vector<int>& nums) {
        int n = nums.size(),sum = 0;
        if (n == 1) return false;
        for (auto num : nums) {
            sum += num;
        }
        if (sum  % 2 != 0) return false;
        int target = sum / 2;
        vector dp(n + 1,vector<bool>(target + 1,false));
        for(int i = 0;i < n;i++) {
            dp[i][0] = true;
        }
        for (int i = 1;i <= n;i++) {
            for(int j = 1;j <= target;j++) {
                //不选当前数
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][target];
    }
    bool canPartitiona(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        // 如果总和为奇数，无法平分
        if (sum % 2 != 0) {
            return false;
        }

        int target = sum / 2;

        // dp[j]表示是否可以选出一些数使得它们的和为j
        vector<bool> dp(target + 1, false);
        dp[0] = true;  // 和为0是可能的（不选任何数）

        for (int num : nums) {
            // 从后往前遍历，避免在同一轮迭代中重复使用当前数字
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
    bool canpartition(vector<int>& nums) {
        bitset<10001> bit;
        bit[0] = 1;
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum & 1) return false;
        for(int x : nums) {
            bit |= bit << x;
            if (bit[sum / 2]) return true;
        }
        return false;
    }
};

int main() {
    can_partition416 solution;
    vector<int> nums = {1,5,11,5};
    cout << solution.canpartition(nums);
    return 0;
}
