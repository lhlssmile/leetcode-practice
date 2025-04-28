//
// Created by 24276 on 2025/3/26.
//

#include <vector>
#include <iostream>

using namespace std;

class length_of_lis300 {
public:
    /**
     * analysis:
     *      1.一维dp 定义状态 dp[i] represented as nums[i] ending subArray(increment)
     *      2.状态转移 define j > i,check i ∈ [0,j - 1]
     * @param nums given nums(Integer)
     * @return find a longest subArray(Increment)
     */
    static int lengthOfLIS(vector<int>& nums) {
        auto n = nums.size();
        if (n == 0) return 0;
        vector<int> dp(n,1);
        int max_len = 1;
        for(int i = 1;i < n;++i) {
            for(int j = 0;j < i;++j) {
                if(nums[j] < nums[i]) {
                    dp[i] = max(dp[i],dp[j] + 1);
                }
            }
            max_len = max(max_len,dp[i]);
        }
        return max_len;
    }

    /**
     * analysis:
     *      1.protect a subarry(tails),tails[i] record as length(i+1) subArray(increment)
     *      希望尽量让子序列增长，但如果当前数字比所有末尾都大，就加到后面；如果比某些末尾小，就替换掉最接近的大值，
     * @param nums given nums
     * @return
     */
    static int LengthOfLISBINARYSEARCH(vector<int>& nums) {
        auto n = nums.size();
        if (n == 0) return 0;
        vector<int> tails;
        for(auto num : nums) {
            if(tails.empty() || num > tails.back()) {
                tails.push_back(num);
            }else {
                //找到第一个 >= num的subscript下标。替换为当前
                int pos = lower_bound(tails.begin(), tails.end(), num) - tails.begin();
                tails[pos] = num;
            }
        }
        return tails.size();
    }
};

int main() {
    length_of_lis300 solution;
    vector<int> nums= {10,9,2,5,3,7,101,18};
    cout << solution.LengthOfLISBINARYSEARCH(nums) << endl;
    return 0;
}

