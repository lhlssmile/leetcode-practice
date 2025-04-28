using namespace std;
#include <vector>
#include <iostream>
class searchRangeSolution {
public:
    searchRangeSolution() = default;
    ~searchRangeSolution() = default;
    std::vector<int> searchRange(std::vector<int>& nums,int target){
        std::vector<int> notFound(2,-1);
        if(nums.size() == 1 || nums.size() == 0) return notFound;
        int left = 0,right = nums.size() - 1;
        std::vector<int> ans;
        while(left < right){
            int mid = (left + right) / 2;
            if(nums[mid] == target){
                ans.push_back(mid);
                if(nums[mid - 1] == target){
                    ans.push_back(mid - 1);
                }else{
                    ans.push_back(mid + 1);
                }
                break;
            }
            else if(nums[mid] < target){
                left = mid;
            }else{
                right = mid;
            }
        }
        if(ans.size() > 1){
            return ans;
        }
        return notFound;
    }
    std::vector<int> searchRange2(std::vector<int>& nums,int target){
        int start = lower_bound(nums, target);
        if (start == nums.size() || nums[start] != target) {
            return {-1, -1}; // nums 中没有 target
        }
        // 如果 start 存在，那么 end 必定存在
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};

    }
private:
    // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right]
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            } else {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            }
        }
        // 循环结束后 left = right+1
        // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
        // 所以 left 就是第一个 >= target 的元素下标
        return left;
    }

};
int main() {
    searchRangeSolution ps;
    int target = 8;std::vector<int> nums = {5,7,7,8,8,10};
    auto res = ps.searchRange2(nums,target);
    for(const auto& x : res){
        std::cout << x << " ";
    }
    return 0;
}

