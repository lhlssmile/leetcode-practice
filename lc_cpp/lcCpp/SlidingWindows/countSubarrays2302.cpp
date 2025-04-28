//
// Created by 24276 on 2025/4/28.
//

#include <bits/stdc++.h>
#include <vector>


using namespace std;
class count_subarrays2302 {
    using ll = long long;
    using V = vector<int>;
public:
    ll countSubarrays(V& nums,ll k) {
        // 初始化结果变量
        ll ans = 0;
        int n = nums.size();
        
        // 构建前缀和数组，prefix_sum[i]表示前i个元素的和
        // 注意prefix_sum的大小是n+1，因为要包含前0个元素的和(0)
        vector<ll> prefix_sum(n + 1, 0);
        for(int i = 0; i < n; i++) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];
        }
        
        // 遍历所有可能的右边界
        // right从1开始到n结束，因为prefix_sum[0]是前0个元素的和🌸
        // right表示子数组的右边界(不包含)，所以right <= n
        for(int right = 1; right <= n; right++) {
            // 初始化二分查找的边界
            // low和high表示可能的左边界位置
            // best记录满足条件的最小左边界
            int low = 0, high = right - 1, best = right;
            
            // 二分查找满足条件的最小左边界
            while (low <= high) {
                int mid = low + (high - low) / 2;
                // 计算子数组的和
                ll total = prefix_sum[right] - prefix_sum[mid];
                // 计算子数组的长度
                ll length = right - mid;
                
                // 如果子数组的得分小于k，说明可以尝试更小的左边界
                if (total * length < k) {
                    best = mid;
                    high = mid - 1;
                } else {
                    // 如果得分大于等于k，需要增大左边界 -> 这样[l,r]前缀和就会变小
                    low = mid + 1;
                }
            }
            // 对于当前右边界，满足条件的子数组数量是right - best
            ans += right - best;
        }
        return ans;
    }
};

int main() {
    count_subarrays2302 sol;
    long long k = 10;
    vector<int> nums = {2,1,4,3,5};
    cout << sol.countSubarrays(nums,k);
    return 0;
}
