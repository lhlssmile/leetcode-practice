//
// Created by 24276 on 2025/4/10.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
class number_of_powerful_int2999 {
public:
    ll numberOfPowerfulInt(ll start,ll finish,int limit,string s) {
        string low = to_string(start);
        string high = to_string(finish);
        int n = high.size();
        low = string(n - low.size(), '0') + low; // 补前导零，和 high 对齐
        int diff = n - s.size();

        vector<long long> memo(n, -1);
        auto dfs = [&](auto&& dfs, int i, bool limit_low, bool limit_high) -> long long {
            if (i == low.size()) {
                return 1;
            }

            if (!limit_low && !limit_high && memo[i] != -1) {
                return memo[i]; // 之前计算过
            }

            // 第 i 个数位可以从 lo 枚举到 hi
            // 如果对数位还有其它约束，应当只在下面的 for 循环做限制，不应修改 lo 或 hi
            int lo = limit_low ? low[i] - '0' : 0;
            int hi = limit_high ? high[i] - '0' : 9;

            long long res = 0;
            if (i < diff) { // 枚举这个数位填什么
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += dfs(dfs,i + 1, limit_low && d == lo, limit_high && d == hi);
                }
            } else { // 这个数位只能填 s[i-diff]
                int x = s[i - diff] - '0';
                if (lo <= x && x <= min(hi, limit)) {
                    res = dfs(dfs,i + 1, limit_low && x == lo, limit_high && x == hi);
                }
            }

            if (!limit_low && !limit_high) {
                memo[i] = res; // 记忆化 (i,false,false)
            }
            return res;
        };
        return dfs(dfs,0, true, true);
    }
};

int main() {
    number_of_powerful_int2999 solution;
    long long start = 1,finish = 6000;
    int limit = 4;
    string s = "124";
    cout << solution.numberOfPowerfulInt(start,finish,limit,s);
    return 0;
}
