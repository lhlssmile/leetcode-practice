//
// Created by 24276 on 2025/4/2.
//

#include <vector>
#include <iostream>
using namespace std;

class subsets78 {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        // 每次从当前位置开始考虑选或不选
        dfs(nums, 0, path);
        return res;
    }

    void dfs(vector<int>& nums, int start, vector<int>& path) {
        // 每次进入函数时，当前path就是一个有效子集，加入结果
        res.push_back(path);

        // 从start开始，避免重复
        for(int i = start; i < nums.size(); i++) {
            // 选择当前元素
            path.push_back(nums[i]);
            // 递归处理下一个位置
            dfs(nums, i + 1, path);
            // 回溯，不选当前元素
            path.pop_back();
        }
    }
};

int main() {
    subsets78 solution;
    vector<int> nums = {1,2,3};
    auto res = solution.subsets(nums);
    cout << "[";
    for(int i = 0; i < res.size(); i++) {
        cout << "[";
        for(int j = 0; j < res[i].size(); j++) {
            cout << res[i][j];
            if(j < res[i].size() - 1) cout << ",";
        }
        cout << "]";
        if(i < res.size() - 1) cout << ",";
    }
    cout << "]";
    return 0;
}
