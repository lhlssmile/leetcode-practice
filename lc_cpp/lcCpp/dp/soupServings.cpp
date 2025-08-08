//
// Created by 24276 on 2025/8/8.
//
#define ll long long
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>



class soup_servings {
public:
    double soupServings(int n) {
        std::unordered_map<int, std::unordered_map<int, double>> memo;
        const std::vector<std::pair<int, int>> operations = {{100, 0}, {75, 25}, {50, 50}, {25, 75}};

        auto dfs = [&](auto&& dfs,int a, int b) -> double {
            if (a <= 0 && b <= 0) return 0.5; // 同时耗尽
            if (a <= 0) return 1.0; // A先耗尽
            if (b <= 0) return 0.0; // B先耗尽
            if (memo[a].count(b)) return memo[a][b]; // 查备忘录

            double prob = 0.0;
            for (const auto& op : operations) {
                int new_a = a - op.first;
                int new_b = b - op.second;
                prob += 0.25 * dfs(dfs,new_a, new_b);
            }
            memo[a][b] = prob; // 存备忘录
            return prob;
        };

        return dfs(dfs,n, n);
    }
    double soupServingsDP(int n ) {
        if (n >= 5000) return 1.0;

        n = (n + 24) / 25;
        std::vector<std::vector<double>> dp (n + 1, std::vector<double>(n + 1, 0.0));
        dp[0][0] = 0.5;
        for (int b = 1; b <= n; ++b) dp[0][b] = 1.0;
        for (int a = 1; a <= n; ++a) dp[a][0] = 0.0;

        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n;b++) {
                dp[a][b] = 0.25 * (
                dp[std::max(0, a - 4)][b] +
                dp[std::max(0, a - 3)][std::max(0, b - 1)] +
                dp[std::max(0, a - 2)][std::max(0, b - 2)] +
                dp[std::max(0, a - 1)][std::max(0, b - 3)]
                );
            }
        }
        return dp[n][n];
    }
};

int main() {
    soup_servings ps;
    ps.soupServingsDP(100);
    return 0;
}
