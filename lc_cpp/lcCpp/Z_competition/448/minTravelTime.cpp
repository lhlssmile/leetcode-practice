#include <bits/stdc++.h>

#ifdef __GNUC__
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#endif

// ==== 快速宏定义 ====
#define ALL(v) v.begin(),v.end() - 1
#define V vector
#define For(i, _) for (int i = 0, i##end = (_); i < i##end; ++i) // [mylib.h: For]
#ifdef LOCAL
#define DBG(x) cerr << #x << " = " << x << endl // [mylib.h: DBG]
#else
#define DBG(x)
#endif
using namespace std;

// ==== 常用类型定义 ====
typedef vector<int> vi; // [mylib.h: vi]

// ==== 常量定义 ====
const int inf = 0x3f3f3f3f; // [mylib.h: inf]

// ==== 小工具函数 ====
template<class T> inline bool ckmin(T& x, const T& y) { return x > y ? (x = y, true) : false; } // [mylib.h: ckmin]

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<int> s(n);
        partial_sum(time.begin(), time.end() - 1, s.begin() + 1);

        vector memo(k + 1, vector(n - 1, vector<int>(n - 1)));
        auto dfs = [&](this auto&& dfs, int left_k, int i, int pre) -> int {
            if (i == n - 1) {
                return left_k ? INT_MAX / 2 : 0;
            }
            int& res = memo[left_k][i][pre]; // 注意这里是引用
            if (res) {
                return res;
            }
            res = INT_MAX;
            int t = s[i + 1] - s[pre];
            for (int nxt = i + 1; nxt < min(n, i + 2 + left_k); nxt++) {
                res = min(res, dfs(left_k - (nxt - i - 1), nxt, i + 1) + (position[nxt] - position[i]) * t);
            }
            return res;
        };
        return dfs(k, 0, 0);
    }
};

int main() {
    Solution sol;
    int l = 10, n = 4, k = 1;
    vector<int> position = {0, 3, 8, 10};
    vector<int> time = {5, 8, 3, 6};
    cout << sol.minTravelTime(l, n, k, position, time) << endl;
    return 0;
}