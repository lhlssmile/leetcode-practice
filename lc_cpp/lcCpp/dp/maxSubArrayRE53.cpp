//
// Created by 24276 on 2025/4/12.
//

#include <vector>
#include <iostream>
using namespace std;
class max_sub_array_re53 {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // 用单一变量记录从 i+1 开始的最大和
        int next = nums[n-1]; // 相当于 dp[n-1]
        int ans = next;

        // 从后往前
        for (int i = n-2; i >= 0; i--) {
            int curr = std::max(nums[i], nums[i] + next);
            ans = std::max(ans, curr);
            next = curr;
        }

        return ans;
    }
    int maxSubArrayPrefix(vector<int>& nums) {
        int ans = INT_MIN;
        int min_pre_sum = 0;
        int pre_sum = 0;
        for (int x : nums) {
            pre_sum += x;
            ans = max(ans,pre_sum - min_pre_sum);
            min_pre_sum = min(min_pre_sum,pre_sum);
        }
        return ans;
    }
    int maxSubArrayFENZHI(vector<int>& nums) {
        return maxSubArrayHelper(nums,0,nums.size() - 1);
    }
private:
    int maxSubArrayHelper(vector<int>& nums,int left,int right) {
        if (left == right) {
            return nums[left];
        }
        int mid = left + (right - left) / 2;
        auto leftMax = maxSubArrayHelper(nums,0,mid);
        auto rightMax = maxSubArrayHelper(nums,mid + 1,right);

        int leftSum = 0,maxLeftSum = nums[mid];
        for (int i = mid; i >= left; --i) {
            leftSum += nums[i];
            maxLeftSum = max(maxLeftSum,leftSum);
        }
        // 右半部分的最大前缀和
        int rightSum = 0, maxRightSum = nums[mid + 1];
        for (int i = mid + 1; i <= right; i++) {
            rightSum += nums[i];
            maxRightSum = std::max(maxRightSum, rightSum);
        }

        // 跨越中间的和
        int crossMax = maxLeftSum + maxRightSum;

        // 合并：返回三者最大值
        return std::max({leftMax, rightMax, crossMax});
    }
};

int main() {
    max_sub_array_re53 sol;
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << sol.maxSubArrayFENZHI(nums);
    return 0;
}
