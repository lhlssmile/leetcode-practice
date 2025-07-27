//
// Created by 24276 on 2025/7/26.
//


#include <limits.h>
#include <vector>
class find_max_average {
public:
    double findMaxAverage(std::vector<int>& nums, int k) {
        int ans = INT_MIN;
        int sum = 0;

        for (int i = 0;i < k; i++) {
            sum += nums[i];
        }

        ans = sum;

        for (int i = k; i < nums.size(); i++) {
            sum += nums[i] - nums[i - k];
            ans = std::max(ans, sum);
        }

        return static_cast<double>(ans) / k;
        }
};