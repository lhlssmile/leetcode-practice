//
// Created by 24276 on 2025/3/27.
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class minimum_cost2712 {
public:
//     可以维护一个前缀全部变成 0 或 1 的最小成本，同时维护后缀全部变成 0 和 1 的最小成本来求解答案。
//
// 定义 suf[i][0] 表示从第 i 个字符开始的后缀全部变成 0 所需要的最小成本，定义 suf[i][1] 表示从第 i 个字符的后缀全部变成 1 所需的最小成本，转移方程为：
//
// 若 s[i] 为 1，则：
// suf[i][1]=suf[i+1][1]
// suf[i][0]=suf[i+1][0]+(n−i)
// 若 s[i] 为 0，则：
// suf[i][1]=suf[i+1][0]+(n−i)
// suf[i][0]=suf[i+1][0]
// 前缀的状态 pre[i][0] 和 pre[i][1] 的定义和转移过程类似，遍历所有的 i，求解 min(pre[i][0]+suf[i+1][0],pre[i][1]+suf[i+1][1]) 的最小值即可。
//
    using ll = long long;
    /**
     *
     * @param s given binary str
     * @return 
     */
    ll minimumCost(string s) {
        int n = s.size();
        vector<vector<ll>> suf(n + 1, vector<ll>(2, 0));
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '1') {
                suf[i][1] = suf[i + 1][1];
                suf[i][0] = suf[i + 1][1] + (n - i);
            } else {
                suf[i][1] = suf[i + 1][0] + (n - i);
                suf[i][0] = suf[i + 1][0];
            }
        }

        vector<ll> pre(2);
        ll res = 1e18;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                // pre[0]：将 s[0:i] 变为全 '0' 的最小成本。
                pre[0] = pre[1] + i + 1;
            } else {
                //pre[1]：将 s[0:i] 变为全 '1' 的最小成本。
                pre[1] = pre[0] + i + 1;
            }
            res = min(res, min(pre[0] + suf[i + 1][0], pre[1] + suf[i + 1][1]));
        }
        return res;
    }

};

int main() {
    minimum_cost2712 solution;
    cout << solution.minimumCost("010101") << endl;
    return 0;
}
