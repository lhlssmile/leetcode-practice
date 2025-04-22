//
// Created by 24276 on 2025/4/3.
//

#include <vector>
#include <iostream>
using namespace std;

class first_missing_postive41 {
public:
    int firstMissingPostive(vector<int>& nums) {
        int n = nums.size();
        /**
         *  将数组中每个数都放到正确的位置
         *  例如 value 1 应该在索引 0 ...以此类推
         */
        for(int i = 0;i < n;i++) {
            //当前值在有效范围{1,n} 且当前值不在正确位置上  那么就交换
            //nums[i] 应该放在nums[i] - 1的位置
            while(nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i],nums[nums[i] - 1]);
            }
        }
        //找到第一个不在正确位置的数
        for(int i = 0;i < n;i++) {
            if(nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};

int main() {
    first_missing_postive41 solution;
    vector<int> nums = {3,4,-1,1};
    cout << solution.firstMissingPostive(nums);
    return 0;
}
