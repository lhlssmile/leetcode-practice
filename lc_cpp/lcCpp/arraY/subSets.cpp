#include <vector>
using namespace std;
class subSetsSolution{
public:
    vector<vector<int>> subsets(vector<int>& nums){
        vector<vector<int>> res;
        vector<int> path;
        backTrack(nums,0,path,res);
        return res;
    }
    void backTrack(vector<int>& nums,int start,vector<int>& path,vector<vector<int>>& res){
        res.push_back(path);
        for(int i = start;i < nums.size();++i){
            //similar with dfs
            path.push_back(nums[i]);
            backTrack(nums,i + 1,path,res);
            path.pop_back();
        }
    }
};
int main() {
    subSetsSolution ps;
    vector<int> nums = {1,2,3};
    auto result = ps.subsets(nums);
    return 0;
}
