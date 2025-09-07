#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class Solution {
public:
    // 位运算解法 - 统计每位1的个数
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int cnt1 = 0;
            for (int x : nums) {
                cnt1 += x >> i & 1;
            }
            ans |= cnt1 % 3 << i;
        }
        return ans;
    }
    
    // 状态机解法
    int singleNumberStateMachine(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }
};

void test() {
    Solution sol;
    vector<int> nums1 = {2, 2, 3, 2};
    assert(sol.singleNumber(nums1) == 3);
    
    vector<int> nums2 = {0, 1, 0, 1, 0, 1, 99};
    assert(sol.singleNumber(nums2) == 99);
    
    cout << "All tests passed!" << endl;
}

int main() {
    test();
    return 0;
}