#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class rob198 {
public:
    // 方法1：标准DP解法（修复边界情况）
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]); // 修复：选择较大的那个
        
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]); // 修复：前两个房子的最优选择
        
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        
        return dp[n - 1];
    }
    
    // 方法2：空间优化版本（O(1)空间）
    int robOptimized(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        
        int prev2 = nums[0];                    // dp[i-2]
        int prev1 = max(nums[0], nums[1]);      // dp[i-1]
        
        for (int i = 2; i < n; i++) {
            int curr = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    // 方法3：递归+记忆化（展示思路）
    int robMemo(vector<int>& nums) {
        vector<int> memo(nums.size(), -1);
        return robHelper(nums, 0, memo);
    }
    
private:
    int robHelper(vector<int>& nums, int i, vector<int>& memo) {
        if (i >= nums.size()) return 0;
        if (memo[i] != -1) return memo[i];
        
        // 选择：抢劫当前房子 vs 不抢劫当前房子
        int rob = nums[i] + robHelper(nums, i + 2, memo);  // 抢劫当前，跳过下一个
        int notRob = robHelper(nums, i + 1, memo);         // 不抢劫当前，考虑下一个
        
        memo[i] = max(rob, notRob);
        return memo[i];
    }
};

// 测试函数
void testRobber() {
    rob198 solution;
    
    // 测试用例1：原始测试
    vector<int> nums1 = {2, 7, 9, 3, 1};
    cout << "测试用例1: [2,7,9,3,1]" << endl;
    cout << "标准DP: " << solution.rob(nums1) << endl;
    cout << "空间优化: " << solution.robOptimized(nums1) << endl;
    cout << "递归记忆化: " << solution.robMemo(nums1) << endl;
    cout << endl;
    
    // 测试用例2：边界情况 - 长度为2
    vector<int> nums2 = {2, 7};
    cout << "测试用例2: [2,7] (长度为2)" << endl;
    cout << "标准DP: " << solution.rob(nums2) << endl;
    cout << "空间优化: " << solution.robOptimized(nums2) << endl;
    cout << "递归记忆化: " << solution.robMemo(nums2) << endl;
    cout << endl;
    
    // 测试用例3：边界情况 - 长度为1
    vector<int> nums3 = {5};
    cout << "测试用例3: [5] (长度为1)" << endl;
    cout << "标准DP: " << solution.rob(nums3) << endl;
    cout << "空间优化: " << solution.robOptimized(nums3) << endl;
    cout << "递归记忆化: " << solution.robMemo(nums3) << endl;
    cout << endl;
    
    // 测试用例4：特殊情况
    vector<int> nums4 = {1, 2, 3, 1};
    cout << "测试用例4: [1,2,3,1]" << endl;
    cout << "标准DP: " << solution.rob(nums4) << endl;
    cout << "空间优化: " << solution.robOptimized(nums4) << endl;
    cout << "递归记忆化: " << solution.robMemo(nums4) << endl;
}

int main() {
    testRobber();
    
    cout << "\n=== 算法分析 ===" << endl;
    cout << "问题：打家劫舍 - 不能抢劫相邻的房子" << endl;
    cout << "\n状态定义：dp[i] = 前i+1个房子能抢到的最大金额" << endl;
    cout << "状态转移：dp[i] = max(dp[i-1], dp[i-2] + nums[i])" << endl;
    cout << "\n边界情况处理：" << endl;
    cout << "- n == 0: return 0" << endl;
    cout << "- n == 1: return nums[0]" << endl;
    cout << "- n == 2: return max(nums[0], nums[1])  // 关键修复" << endl;
    cout << "\n复杂度分析：" << endl;
    cout << "- 时间复杂度：O(n)" << endl;
    cout << "- 空间复杂度：O(n) -> O(1)优化" << endl;
    
    return 0;
}

/*
题目分析：打家劫舍（House Robber）

问题描述：
- 一排房子，每个房子有一定金额
- 不能抢劫相邻的房子（会触发警报）
- 求能抢到的最大金额

原代码问题分析：
1. 当nums.size() == 2时，dp[1] = nums[1]是错误的
2. 应该是dp[1] = max(nums[0], nums[1])，选择前两个房子中较大的
3. 缺少边界情况的完整处理

DP思路：
1. 状态定义：dp[i] = 抢劫前i+1个房子能获得的最大金额
2. 状态转移：
   - 抢劫第i个房子：dp[i-2] + nums[i]
   - 不抢劫第i个房子：dp[i-1]
   - dp[i] = max(dp[i-1], dp[i-2] + nums[i])
3. 边界情况：
   - dp[0] = nums[0]
   - dp[1] = max(nums[0], nums[1])

优化策略：
1. 空间优化：只需要前两个状态，O(n) -> O(1)
2. 递归+记忆化：展示问题的递归本质

关键洞察：
- 每个位置都面临"抢"或"不抢"的选择
- 抢了当前位置就不能抢前一个位置
- 动态规划记录每个位置的最优解
*/
