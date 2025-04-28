//
// Created by 24276 on 2025/4/16.
//
#include <vector>
#include <bits/ranges_algo.h>
using namespace std;
class rotate189 {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> copy_array(nums.size());
        int n = nums.size();
        int idx = 0;
        for(int x:nums){
            copy_array[idx++] = x;
        }
        k = k % n;
        for (int i = 0;i < n;i++){
            nums[i] = copy_array[(n - k + i) % n];
        }
    }
    void rotatea(vector<int>& nums, int k) {
        k %= nums.size();
        ranges::reverse(nums);
        ranges::reverse(nums.begin(),nums.begin() + k);
        ranges::reverse(nums.begin() + k,nums.end());
    }
};

int main() {
    rotate189 sol;
    vector<int> nums = {1,2,3,4,5,6,7}; int k = 3;
    sol.rotate(nums,k);
    return 0;
}
