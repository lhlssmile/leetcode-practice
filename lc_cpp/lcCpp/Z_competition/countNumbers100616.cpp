#include <vector>
#include <iostream>
#include <string>
using namespace std;

class count_numbers100616 {
    // 模拟十进制的除法和取模，把 s 转成 b 进制的数字
    vector<int> trans(string& s, int b) {
        for (char& c : s) {
            c -= '0';
        }
        vector<int> digits;
        while (!s.empty()) {
            string nxt_s; // s / b 的结果
            int rem = 0; // s % b 的结果
            for (char c : s) {
                rem = rem * 10 + c;
                int q = rem / b; // 商
                if (q || !nxt_s.empty()) {
                    nxt_s.push_back(q);
                }
                rem = rem % b;
            }
            digits.push_back(rem);
            s = std::move(nxt_s);
        }
        reverse(digits.begin(),digits.end());
        return digits;
    }

public:
    int countNumbers(string l, string r, int b) {
        vector<int> low = trans(l, b);
        vector<int> high = trans(r, b);
        int n = high.size();
        int diff_lh = n - low.size();

        vector memo(n, vector<int>(b, -1));
        auto dfs = [&](auto&& dfs, int i, int pre, bool limit_low, bool limit_high) -> int {
            if (i == n) {
                return 1;
            }
            if (!limit_low && !limit_high && memo[i][pre] >= 0) {
                return memo[i][pre];
            }

            int lo = limit_low && i >= diff_lh ? low[i - diff_lh] : 0;
            int hi = limit_high ? high[i] : b - 1;

            long long res = 0;
            for (int d = max(lo, pre); d <= hi; d++) {
                res += dfs(dfs,i + 1, d, limit_low && d == lo, limit_high && d == hi);
            }
            res %= 1'000'000'007;

            if (!limit_low && !limit_high) {
                memo[i][pre] = res;
            }
            return res;
        };
        return dfs(dfs,0, 0, true, true);
    }
};

int main() {
    count_numbers100616 sol;
    cout << sol.countNumbers("23","28",8);
    return 0;
}
