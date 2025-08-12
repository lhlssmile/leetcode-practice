//
// Created by 24276 on 2025/8/12.
//
#include <valarray>
#include <vector>
using namespace std;
typedef long long ll;
#define pb push_back
class number_of_ways {
    static constexpr int MOD = 1e9 + 7;
public:
    int numberOfWays(int n, int x) {
        vector<int> powers;
        int base = 1;
        while (std::pow(base, x) <= n) {
            powers.pb(pow(base, x));
            base++;
        }
        int m = powers.size();
        // memo[n][id]
        vector memo(n + 1, vector<ll>(m + 1, -1));
        auto dfs = [&](this auto&& dfs, int remain, int idx) -> ll {
            if (remain == 0) return 1;
            if (remain < 0 || idx == m) return 0;
            if (memo[remain][idx] != -1) return memo[remain][idx];
            int take = dfs(remain - powers[idx], idx + 1);
            int skip = dfs(remain, idx + 1);
            memo[remain][idx] = (skip + take) % MOD;
            return memo[remain][idx];
        };
        return dfs(n, 0);
    }
};

int main() {
    number_of_ways ps;
    ps.numberOfWays(10, 2);
    return 0;
}
