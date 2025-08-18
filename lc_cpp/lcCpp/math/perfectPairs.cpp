//
// Created by 24276 on 2025/8/17.
//
typedef long long ll;
#include <vector>
using namespace std;
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        ll ans = 0;
        int left = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            nums[i] = abs(nums[i]);
        }
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++) {
            while (nums[left] * 2 < nums[i]) {
                left++;
            }
            ans += i - left;
        }
        return ans;
    }
};