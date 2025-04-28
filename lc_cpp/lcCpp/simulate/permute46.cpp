//
// Created by 24276 on 2025/4/2.
//

#include <iostream>
#include <vector>
using namespace std;

class permute46 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        //回溯
        auto n = nums.size();
        if(n == 1) return {nums};
        vector<vector<int>> ans;
        vector<int> path;
        vector<bool> used(nums.size(),false);
        return backTrack(nums,used,path,ans);
    }
    vector<vector<int>> backTrack(vector<int>& nums,vector<bool>& used,vector<int>& path,vector<vector<int>>& ans) {
        //一条路径的长度为nums的长度时 该插入进ans中
        if(path.size() == nums.size()) {
            ans.push_back(path);
        }
        for(int i = 0;i < nums.size();i++) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backTrack(nums,used,path,ans);
            path.pop_back();
            used[i] = false;
        }
        return ans;
    }

    vector<vector<int>> permuteDFS(vector<int> nums) {
        auto n = nums.size();
        vector<vector<int>> ans;
        vector<int> path(n),on_path(n);

        auto dfs = [&](auto&& dfs,int i) -> void {
            if(i == n) {
                ans.push_back(path);
                return;
            }
            for(int j = 0;j < n;j++) {
                if(!on_path[j]) {
                    path[i] = nums[j];
                    on_path[j] = true;
                    dfs(dfs,i + 1);
                    on_path[j] = false;
                }
            }
        };

        dfs(dfs,0);
        return ans;
    }
};

int main() {
    permute46 solution;
    vector<int> nums = {1,2,3};
    auto res = solution.permuteDFS(nums);
    cout << "[";
    for(auto vec : res) {
        cout << "[";
        for(auto ele : vec) {
            cout << ele << " ";
        }
        cout << "]";
    }
    cout << "]";
    return 0;
}
