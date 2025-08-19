//
// Created by 24276 on 2025/8/19.
//
#include <vector>
using namespace std;
#define V vector
#define V vector
class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        V<int> ans(n - k + 1, -1);
        // 先算出第一个窗口
        bool isConsecutive = true;

        for (int i = 1; i < k; i++) {
            if (nums[i] != nums[i - 1] + 1) {
                isConsecutive =false;
                break;
            }
        }
        if (isConsecutive) ans[0] = nums[k - 1];

        for (int i = 1; i <= n - k; i++) {
            if (ans[i - 1] != -1 && nums[i + k - 1] == nums[i + k - 2] + 1) {
                ans[i] = nums[i + k - 1];
            }else {
                bool isConsecutive = true;

                for (int j = i + 1; j < i + k; j++) {
                    if (nums[j] != nums[j - 1] + 1) {
                        isConsecutive = false;
                        break;
                    }
                }
                if (isConsecutive) ans[i] = nums[i + k - 1];
            }
        }
        return ans;
    }
};

int main() {
    V<int> nums = {1, 2, 3, 4, 3, 2, 5};
    Solution s; int k = 3;
    s.resultsArray(nums, k);
    return 0;
}
