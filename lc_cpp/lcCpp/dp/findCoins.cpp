//
// Created by 24276 on 2025/8/21.
//
#include "../template/mylib.h"
class find_coins {
public:
    V<int> findCoins(V<int>& numWays) {
        V<int> ans;
        int n = numWays.size();
        V<int> f(n + 1, 0);
        f[0] = 1;
        for (int c = 1; c <= n;c++) {
            int dpc = numWays[c - 1];
            if (dpc == f[c]) {
                continue;
            }
            if (dpc - 1 != f[c]) {
                return {};
            }
            ans.push_back(c);
            for (int j = c; j <= n;j++) {
                f[j] += f[j - c];
            }
        }
        return ans;
    }
};

int main() {
    return 0;
}
