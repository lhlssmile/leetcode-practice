//
// Created by 24276 on 2025/4/22.
//

#include <iostream>
#include <vector>
using namespace std;

class ideal_arrays2388{
public:
    using ll = long long;
    int idealArrays(int n,int maxValues) {
        ll ideal_array_counts = 0;
        const int  MOD = 1e9 + 7;
        //dp?
        //长度为i的理想数组
        vector dp(n + 1,vector<ll>(maxValues + 1,0));
        for (int j = 1;j <= maxValues;j++) {
            dp[1][j] = 1;   // 长度为1 只要j不大于maxValue就满足(n = 1的ideal array
        }
        //怎么转移状态
        for (int i = 2;i <= n;i++) {
            for (int k = 1;k <= maxValues;++k) {
                for (int m = 1;k * m <= maxValues;++m) {
                    int j = k * m;
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                }
            }
        }
        for (int j = 1;j <= maxValues;++j) {
            ideal_array_counts = (ideal_array_counts + dp[n][j]) % MOD;
        }
        return ideal_array_counts;
    }
};

int main() {
    ideal_arrays2388 sol;
    int n = 2,maxValue =5 ;
    cout << sol.idealArrays(n,maxValue);
    return 0;
}
