#include <vector>
#include <iostream>
#include <unordered_set>
class searchRotateSortArraySolution{
public:
    std::unordered_set<int> nums_set;
    bool search(std::vector<int>& nums,int target){
        nums_set.insert(nums.begin(),nums.end());
        if(nums_set.find(target) != nums_set.end()){
            return true;
        }
        return false;
    }
    bool searchUseSTL(std::vector<int>& nums,int target){
        return std::find(nums.begin(),nums.end(),target) != nums.end();
    }
    //二分 查找

    bool searchBinary(std::vector<int>& nums,int target){
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;
            // 处理重复元素导致无法判断有序的情况
            if (nums[left] == nums[mid]) {
                left++;
                continue;
            }
            // 判断左右半部分的有序性
            if (nums[left] < nums[mid]) { // 左半有序
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // 右半有序
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return false;
    }
};
int main() {
    searchRotateSortArraySolution ps;
    std::vector<int> nums = {1,0,1,1,1};
    std::cout << ps.searchBinary(nums,0) << std::endl;
    return 0;
}
