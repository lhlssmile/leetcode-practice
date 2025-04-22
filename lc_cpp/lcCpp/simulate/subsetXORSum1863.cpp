//
// Created by 24276 on 2025/4/5.
//

#include <vector>
#include <iostream>
using namespace std;

class subset_xor_sum1863 {
public:
    int subsetXORSum(vector<int>& nums) {
        //找子集
        auto subsets = this->subsets(nums);
        int ans = 0;
        //计算和
        for(auto const& subset : subsets) {
            int xoAr = 0;
            for(int ele : subset) {
                //先异或 再相加
                xoAr ^= ele;
            }
            ans += xoAr;
        }
        return ans;
    }
    int subSetXORSum(vector<int>& nums) {
        //用一个整数 mask 表示子集，mask 的二进制位表示哪些元素被选中。
        auto n = nums.size();
        int total = 0;
        //左移一位1 满足 子集个数
        for(int mask = 0; mask < (1 << n);mask++) {
            int xorSum = 0;
            for(int i = 0;i < n;i++) {
                //将 1 左移 i 位，得到一个只有第 i 位是 1 的数。
                if (mask & (1 << i)) {
                    xorSum ^= nums[i];
                }
            }
            total += xorSum;
        }
        return total;
    }
private:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        auto n = nums.size();
        vector<int> path;
        auto dfs = [&](auto&& dfs,int start,vector<int>& path) -> void {
            ans.push_back(path);
            for(int i = start;i < n;i++) {
                path.push_back(nums[i]);
                dfs(dfs,i + 1,path);
                path.pop_back();
            }
        };
        dfs(dfs,0,path);
        return ans;
    }
};

int main() {
    vector<int> nums = {5,1,6};
    subset_xor_sum1863 solution;
    cout << solution.subSetXORSum(nums);
    return 0;
}
