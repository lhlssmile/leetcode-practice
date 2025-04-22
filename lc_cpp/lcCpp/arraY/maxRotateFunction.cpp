#include <vector>
#include <iostream>
class maxRotateFuncSolution{
public:
    int maxRotateFunction(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        // 计算初始F(0)和总和S
        long long F = 0, S = 0;
        for (int i = 0; i < n; ++i) {
            F += i * nums[i];
            S += nums[i];
        }

        long long max_val = F;

        // 递推计算后续F值
        for (int i = 0; i < n-1; ++i) {
            F = F + S - n * nums[n-1 - i]; // 核心递推公式
            max_val = std::max(max_val, F);
        }

        return max_val;
    }
};
int main() {
    maxRotateFuncSolution ps;
    std::vector<int> nums = {4,3,2,6};
    std::cout << ps.maxRotateFunction(nums) << std::endl;
    return 0;
}
