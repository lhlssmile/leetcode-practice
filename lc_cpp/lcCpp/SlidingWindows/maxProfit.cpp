//
// Created by 24276 on 2025/8/17.
//
#define V vector
#include <algorithm>
typedef long long ll;
#include <vector>
class Solution {
public:
    long long maxProfit(std::vector<int>& prices, std::vector<int>& strategy, int k) {
        int n = prices.size();

        // 原始利润
        ll oriProfit = 0;
        for (int i = 0; i < n; i++) {
            oriProfit += 1LL * strategy[i] * prices[i];
        }

        ll mxChange = 0, currChange = 0;

        // 初始化窗口 [0, k-1]
        for (int j = 0; j < k/2; j++) {
            currChange += (0 - strategy[j]) * prices[j];   // 改成空仓
        }
        for (int j = k/2; j < k; j++) {
            currChange += (1 - strategy[j]) * prices[j];   // 改成买入
        }

        mxChange = currChange;

        // 滑动窗口
        for (int i = 1; i <= n - k; i++) {
            int j = i - 1; // 离开的元素

            // 前半段出去
            currChange -= (0 - strategy[j]) * prices[j];

            // 中点移动：原来是后半段买入 -> 现在变成前半段空仓
            int j_mid = i + k/2 - 1;
            currChange -= (1 - strategy[j_mid]) * prices[j_mid];
            currChange += (0 - strategy[j_mid]) * prices[j_mid];

            // 新进入的后半段
            int j_new = i + k - 1;
            currChange += (1 - strategy[j_new]) * prices[j_new];

            mxChange = std::max(mxChange, currChange);
        }

        return oriProfit + std::max(0LL, mxChange);
    }
};

int main() {
    Solution ps;
    std::vector<int> prices = {5, 4, 3}, strategy = {1, 1, 0}; int k = 2;
    ps.maxProfit(prices, strategy, k);
    return 0;
}
