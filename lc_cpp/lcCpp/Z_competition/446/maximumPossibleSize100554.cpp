//
// Created by 24276 on 2025/4/20.
//

#include <vector>
#include <iostream>
using namespace std;
class maximum_possible_size100554 {
    using ll = long long;
public:
    vector<ll> resultArray(vector<int>& nums,int k) {
        int n = nums.size();
        if (k <= 0) {
            return {};
        }
        vector<ll> total_result (k,0);
        vector<ll> current_dp(k,0);

        for(int i = 0;i < n;i++) {
            // 计算当前元素模 k 的值。题目保证 nums[i] 是正整数。
            int num_mod_k = nums[i] % k;

            // next_dp[x] 用于计算以当前元素 nums[i] 结尾的子数组的余数分布
            // 每次循环开始时重新初始化为 0
            std::vector<long long> next_dp(k, 0);

            // 1. 处理由单个元素 nums[i] 构成的子数组
            // 这个子数组以 nums[i] 结尾，其乘积模 k 的余数是 num_mod_k
            // 计数增加 1
            next_dp[num_mod_k]++;

            // 2. 将 nums[i] 追加到以 nums[i-1] 结尾的子数组末尾
            // 遍历上一轮的状态 current_dp (代表以 nums[i-1] 结尾的子数组)
            for (int prev_rem = 0; prev_rem < k; ++prev_rem) {
                // 如果存在以 nums[i-1] 结尾且余数为 prev_rem 的子数组
                if (current_dp[prev_rem] > 0) {
                    long long count = current_dp[prev_rem]; // 获取这种子数组的数量

                    // 计算新的子数组（以 nums[i] 结尾）的乘积模 k 的余数
                    // 使用 1LL 确保乘法在 long long 范围内进行，防止溢出
                    int new_rem = (1LL * prev_rem * num_mod_k) % k;

                    // 将这些子数组的数量加到 next_dp 对应新余数的位置
                    next_dp[new_rem] += count;
                }
            }

            // 3. 将本轮计算出的、以 nums[i] 结尾的所有子数组的计数，累加到总结果 total_result 中
            for (int rem = 0; rem < k; ++rem) {
                total_result[rem] += next_dp[rem];
            }

            // 4. 更新 current_dp 为 next_dp，为下一轮迭代（处理 nums[i+1]）做准备
            // vector 的赋值操作会复制内容
            current_dp = next_dp;
        }
        return total_result;
    }

};

int main() {
    maximum_possible_size100554 sol;
    vector<int> nums = {1,2,3,4,5};
    int k = 3;
    sol.resultArray(nums,k);
    return 0;
}
