//
// Created by 24276 on 2025/8/24.
//
#define V vector
#include <climits>
#include <utility>
#include <vector>

class Solution {
    using pii = std::pair<int, int>;
public:
    std::vector<int> maxValue(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> res(n);
        std::vector<pii> stk;
        for (int i = 0; i < n; i++) {
            while (stk.size() > 1 && nums[i] < stk[stk.size() - 2].second) {
                stk[stk.size() - 2].second = stk.back().second;
                stk.pop_back();
            }
            if (stk.empty() || nums[i] >= stk.back().second) {
                stk.emplace_back(i, nums[i]);
            }
        }
        stk.emplace_back(n, INT_MAX);
        for (int i = 0; i < stk.size() - 1; i++) {
            for (int j = stk[i].first; j < stk[i + 1].first; j++) {
                res[j] = stk[i].second;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    std::V<int> nums = {2,1, 3};
    s.maxValue(nums);
    return 0;
}
