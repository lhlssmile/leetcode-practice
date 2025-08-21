//
// Created by 24276 on 2025/8/21.
//
#include <vector>
using namespace std;
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int last = -1;
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] == 1) {
                if (i - last <= k && last != -1){
                    return false;
                }
                last = i;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 1, 1, 0}; int k = 3;
    s.kLengthApart(nums, k);
    return 0;
}
