#include <iostream>
#include <vector>
using namespace std;
class searchRange34Solutions {
public:
    searchRange34Solutions() = default;
    ~searchRange34Solutions() = default;
    vector<int> searchRange(vector<int>& nums,int target){
        int start = findSubscript(nums,target);
        if(start == nums.size() || nums[start] != target){
            return {-1,-1};
        }
        int end = findSubscript(nums,target + 1) - 1;
        return {start,end};
    }
private:
    int findSubscript(vector<int>& nums,int target){
        //开区间的写法.?
        int left = - 1,right = static_cast<int>(nums.size());
        while (left + 1 < right){
            int mid = left + (right - left) / 2;
            if(nums[mid] >= target){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};

int main() {
    searchRange34Solutions ps;
    int target = 8;std::vector<int> nums = {5,7,7,8,8,10};
    auto res = ps.searchRange(nums,target);
    for(const auto& x : res){
        std::cout << x << " ";
    }
    return 0;
}
