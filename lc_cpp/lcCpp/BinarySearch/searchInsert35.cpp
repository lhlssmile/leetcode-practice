//
// Created by 24276 on 2025/3/26.
//

#include <vector>
#include <iostream>
using namespace std;

class search_insert35 {
public:
    /**
     * use binary Search,if do not exist target,then insert target continuous
     * @param nums sorted array
     * @param target target value,used to find index
     * @return
     */
    int searchInsert(vector<int>& nums,int target) {
        int left = 0,right = nums.size();
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            if(nums[mid] >= target) {
                right = mid;
            }else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    search_insert35 solution;
    vector<int> nums = {1,3,5,6};int target = 2;
    cout << solution.searchInsert(nums,target);
    return 0;
}
