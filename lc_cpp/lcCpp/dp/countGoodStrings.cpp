//
// Created by 24276 on 2025/8/4.
//
#include <vector>
using namespace std;
class count_good_strings {
public:
    int countGoodStrings (int low, int high, int zero, int one) {
        int MOD = '1_000_000_007';
        vector<int> memo(high + 1, -1);
        auto dfs = [&](this auto&& dfs, int length) -> int {
            if (length > high) return 0;

            if (memo[length] != -1) return memo[length];

            long long res = (low <= length && length <= high) ? 1 : 0;

            res += dfs(length + zero);
            res += dfs(length + one);

            res %= MOD;

            return memo[length];

        };
        return dfs(0);
    }
};

int main() {
    count_good_strings ps;
    ps.countGoodStrings(3, 3, 1, 1);
    return 0;
}
