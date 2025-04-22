#include <iostream>
#include <vector>
#include <algorithm>
class sortArrayByParitySolution{
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums){
        std::sort(nums.begin(),nums.end());
        int i = 0,oddIndex = 0;

        std::vector<int> res(nums.size(),0);
        for(;i < nums.size();++i){
            if(nums[i] % 2 == 0){
                int odd_ptr = 2 * oddIndex + 0;
                res[odd_ptr] =nums[i];
                ++oddIndex;
            }
        }
        int j = 0,evenIndex = 0;
        for(;j < nums.size() ;++j){
            if(nums[j] % 2 == 1){
                int even_ptr = 2 * evenIndex + 1;
                res[even_ptr] = nums[j];
                ++evenIndex;
            }
        }
        return res;
    }
    std::vector<int> sortArrayUseDoublePtr(std::vector<int>& nums){
        int n = nums.size();
        int j = 1;
        for(int i = 0;i < n;i += 2){
            if(nums[i] % 2 == 1){
                j += 2;
            }
            std::swap(nums[i],nums[j]);
        }
        return nums;
    }
};
int main() {
    sortArrayByParitySolution ps;
    std::vector<int > nums = {4,2,5,7,3,3,4,4};
    auto res = ps.sortArrayUseDoublePtr(nums);
    for(const auto & ele : res){
        std::cout << ele << ",";
    }
    return 0;
}
