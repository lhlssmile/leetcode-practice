//
// Created by 24276 on 2025/7/18.
//

#include <iostream>
#include <vector>
using namespace std;
class search_range_a34 {
public:
    vector<int> searchRange(vector<int>& nums,int target) {
        int start = lower_bound(nums,target);
        if (start == nums.size() || nums[start] != target) {
            return {-1,-1};
        }
        int end = lower_bound(nums,target + 1) - 1;
        return {start,end};
    }
private:
    int lower_bound(vector<int>& nums,int target) {
        int left = 0,right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
            }else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    vector<int> nums = {5,7,7,8,8,10};
    search_range_a34 ps;
    ps.searchRange(nums,8);
    return 0;
}
