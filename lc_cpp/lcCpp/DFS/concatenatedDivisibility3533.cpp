//
// Created by 24276 on 2025/4/28.
//
#include "../template/mylib.h"

using namespace std;

class concatenated_divisibility3533 {
public:
    V<int> concatenatedDivisibility(V<int>& nums,int k) {
        // 首先对数组进行排序，这样可以保证找到字典序最小的解
        ranges::sort(nums);
        int n = nums.size();
        
        // 预处理每个数字的10的幂次，用于后续计算模值
        // 例如：数字12的pow10值为100，因为12是两位数
        vector<int> pow10(n);
        for (int i = 0; i < n; i++) {
            pow10[i] = pow(10, to_string(nums[i]).size());
        }

        vector<int> ans;
        // vis数组用于记忆化搜索，避免重复计算
        // vis[s][x]表示状态s（二进制位表示已使用的数字）和模值x是否已经被访问过
        // 1 << n 表示所有数字的使用状态，k表示模值范围
        vector vis(1 << n, vector<uint8_t>(k));
        
        //s: 用二进制代表 nums中被选择的数例如 nums.size() = 3,那么 1 << 3 - 1 = 7 -> 111表示三个数都未使用
        //x: 当前数字模k的结果。

        // 使用lambda表达式定义dfs函数
        auto dfs = [&](this auto&& dfs, int s, int x) -> bool {
            // 如果所有数字都已使用完（s == 0）
            if (s == 0) {
                // 检查当前模值是否为0，即是否能被k整除
                return x == 0;
            }
            // 如果这个状态已经被访问过，直接返回false避免重复计算
            if (vis[s][x]) {
                return false;
            }
            // 标记当前状态为已访问
            vis[s][x] = true;
            
            // 遍历所有未使用的数字
            for (int i = 0; i < n; i++) {
                // 检查数字i是否未被使用（s & (1 << i)）
                if (s & (1 << i)) {
                    // 计算新的模值：(当前模值 * 10^位数 + 新数字) % k
                    int new_x = (x * pow10[i] + nums[i]) % k;
                    // 递归搜索
                    if (dfs(s ^ (1 << i), new_x)) {
                        // 如果找到解，将当前数字加入答案
                        ans.push_back(nums[i]);
                        return true;
                    }
                }
            }
            return false;
        };
        
        // 从所有数字都未使用的状态开始搜索
        if (!dfs((1 << n) - 1, 0)) {
            return {};
        }
        // 由于数字是倒序加入答案的，需要反转
        ranges::reverse(ans);
        return ans;
    }
};

int main() {
    concatenated_divisibility3533 sol;
    vector<int> nums = {3,12,45};int k = 5;
    auto res = sol.concatenatedDivisibility(nums,k);
    for(int re : res) {
        cout << re << " ";
    }
    return 0;
}
