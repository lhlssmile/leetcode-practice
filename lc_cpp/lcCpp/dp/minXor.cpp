#include <climits>
#include <vector>
//
// Created by 24276 on 2025/8/18.
//
using namespace std;
#define V vector
typedef long long ll;
#define V vector
class Solution {
    const int MOD = 1e9 + 7;
public:
    int minXor(std::vector<int>& nums, int k) {
        int n = nums.size();
        V<ll> prefix(n + 1, 0);
        for (int i = 0; i < n;i++) {
            // 0 xor 1 = 1
            prefix[i + 1] = prefix[i] ^ nums[i];
        }
        V dp(k + 1, V<ll>(n, INT_MAX));
        for (int i = 0; i < n;i++) {
            dp[1][i] = prefix[i + 1];
        }
        for (int i = 2; i <= k; i++) {
            for (int j = i - 1; j < n; j++) {
                for (int p = i - 2; p < j;p++) {
                    ll cur_xor = prefix[j + 1] ^ prefix[p + 1];
                    dp[i][j] = std::min(dp[i][j], std::max(dp[i - 1][p], cur_xor));
                }
            }
        }
        return dp[k][n - 1];
    }
};

int main() {
    Solution ps;
    std::vector<int> nums = {1, 2, 3}; int k = 2;
    ps.minXor(nums, k);
    return 0;
}
