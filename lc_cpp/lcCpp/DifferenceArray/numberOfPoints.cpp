//
// Created by 24276 on 2025/8/19.
//
#define V vector
#include <vector>
#include <bits/ranges_algo.h>

class Solution {
public:
    int numberOfPoints(std::vector<std::vector<int>>& nums) {
        int mx_end = std::ranges::max(nums, {}, [](const auto& a) {return a[1];})[1];
        std::vector<int> diff(mx_end + 2);
        for (auto& interval : nums) {
            diff[interval[0]]++;
            diff[interval[1] + 1]--;
        }
        int ans = 0, s = 0;

        for (int d : diff) {
            s += d;
            ans += s > 0;
        }
        return ans;
    }
};

int main() {
    Solution s;
    std::vector<std::vector<int>> nums = {{3,6}, {1, 5}, {4, 7}};
    s.numberOfPoints(nums);
    return 0;
}
