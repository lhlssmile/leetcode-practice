#include <vector>
#include <bits/stdc++.h>

using namespace std;

class maxProduct152{
public:
    int maxProduct(vector<int>& nums){
        // 获取数组长度，初始化最大乘积为第一个元素
        int n = nums.size(), max_product = nums[0];
        // 创建两个动态规划数组，分别记录以当前位置结尾的最大和最小乘积
        vector<int> dp_max(n), dp_min(n);
        // 初始化第一个位置的值
        dp_max[0] = dp_min[0] = nums[0];
        
        // 从第二个位置开始遍历
        for (int i = 1; i < n; i++) {
            // 计算当前位置的最大乘积，考虑三种情况：
            // 1. 前一个位置的最大乘积乘以当前数
            // 2. 前一个位置的最小乘积乘以当前数（负负得正）
            // 3. 只取当前数（重新开始子数组）
            dp_max[i] = max({dp_max[i-1] * nums[i], dp_min[i-1] * nums[i], nums[i]});
            // 计算当前位置的最小乘积，同样考虑三种情况
            dp_min[i] = min({dp_max[i-1] * nums[i], dp_min[i-1] * nums[i], nums[i]});
            // 更新全局最大乘积
            max_product = max(max_product, dp_max[i]);
        }
        return max_product;
    }
};
int main(){
    maxProduct152 sol;
    vector<int> nums = {2,3,-2,4,-1};
    cout << sol.maxProduct(nums) << endl;
    return 0;

}