#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class permuteUniqueSolution{
public:
    vector<vector<int>> permuteUnique(vector<int>& nums){
        vector<vector<int>> res;
        std::sort(nums.begin(),nums.end());
        vector<int> path;
        vector<bool> used(nums.size(),false);
        this->backTrack(nums,used,path,res);
        return res;
    }
    void backTrack(vector<int>& nums,vector<bool>& used,vector<int>& path,vector<vector<int>>& res){
        if(path.size() == nums.size()){
            res.push_back(path);
        }
        for(int i = 0; i < nums.size();++i){
            if(used[i]) continue;
            if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backTrack(nums,used,path,res);
            path.pop_back();
            used[i] = false;
        }
    }
};
int main() {
    permuteUniqueSolution ps;
    vector<int> nums = {1,1,2};
    auto res = ps.permuteUnique(nums);
    for (const auto& vec : res) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
