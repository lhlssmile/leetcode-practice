#include <algorithm>
#include <vector>
#include <iostream>
class subSetsWithDupSolution{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums){
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        std::sort(nums.begin(),nums.end());
        backTrack(nums,0,current,result);
         return result;
    }
private:
    void backTrack(const std::vector<int>& nums,int start,std::vector<int>& current,std::vector<
            std::vector<int>>& result){
        result.push_back(current);
        for(int i = start; i < nums.size(); ++i){
            if(i > start && nums[i] == nums[i - 1]){
                continue;
            }
            current.push_back(nums[i]);
            backTrack(nums,i + 1,current,result);
            current.pop_back();
        }
    }
};
int main() {
    subSetsWithDupSolution ps;
    std::vector<int > nums = {1,2,2};
    auto result = ps.subsetsWithDup(nums);
    std::cout << "[" << " ";
    for(const auto vec : result){
        for(const auto x : vec){
            std::cout << x << ",";
        }
        std::cout << "]," << " ";
    }
    std::cout << "]" << std::endl;
    return 0;
}
