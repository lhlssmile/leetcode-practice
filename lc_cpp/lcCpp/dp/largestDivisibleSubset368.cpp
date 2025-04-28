//
// Created by 24276 on 2025/4/6.
//

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class largest_divisible_subset368 {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 排序
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            bool canInsert = true;
            for (int j = 0; j < ans.size(); j++) {
                // 双向检查
                if (nums[i] % ans[j] != 0 && ans[j] % nums[i] != 0) {
                    canInsert = false;
                    break;
                }
            }
            if (canInsert) ans.push_back(nums[i]);
        }
        return ans;
    }

    vector<int> largestDivisibleSubsetRe(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        //dp[i]表示 以nums[i]结尾的最大整除子集大小
        vector<int> dp(n,1);
        //记录前一个元素的下标
        vector<int> prev(n,-1);
        int maxSize = 1,maxIndex = 0;
        for(int i = 0;i < n;i++) {
            for(int j = 0;j < i;j++) {
                if(nums[i] % nums[j] == 0) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }
            if(dp[i] > maxSize) {
                maxSize = dp[i];
                maxIndex = i;
            }
        }
        vector<int> result;
        while(maxIndex != -1) {
            result.push_back(nums[maxIndex]);
            maxIndex = prev[maxIndex];
        }
        reverse(result.begin(),result.end());
        return result;
    }


};

int main() {
    largest_divisible_subset368 solution;
    vector<int> nums = {3,4,16,8};
    auto res = solution.largestDivisibleSubsetRe(nums);
    for (int ele : res) {
        cout << ele << " ";
    }
    return 0;
}
