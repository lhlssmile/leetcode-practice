//
// Created by 24276 on 2025/11/18.
//
#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int main() {
    /**
     * 题意（普通话版）：
     * - 给出 n 个非负整数 a[i]。对每个 a[i]，找一个 a[j]（可是任意位置），使得 a[i] & a[j] == 0；若不存在输出 -1。
     *
     * 思路：位掩码 + 子集和（SOS）预处理
     * - 把每个值视为一个 22 位以内的掩码（因为最大值 <= 2^22-1 约 4e6）。
     * - 我们希望找 y 使得 x & y == 0；这等价于 y ⊆ ~x（在考虑的位域内）。
     * - 构造数组 dp[mask]：保存“是否存在一个数等于某个子集”的信息，并通过 SOS 把子集存在性传播到所有超集。
     *   实现方法（对子集求和的存在性版本）：
     *   dp 初始在位置 value 上填入该值；再做逐位累加：
     *   for bit: for mask: 若 mask 的该位为 1，则用 dp[mask ^ (1<<bit)] 填补 dp[mask]；
     *   完成后，dp[mask] 表示“存在某个数组元素，它的掩码是 mask 的某个子集”。
     * - 查询：对 x，令 comp = 全 1 掩码按位异或 x（即 ~x 在位域内），答案就是 dp[comp]；因为 comp 的所有子集都包含在 ~x 内。
     *
     * 复杂度：
     * - 令 U = 1<<B（B 为位数，约 22）；预处理 O(B * U)；查询 O(n)。内存 O(U)。
     *
     * 输入输出约定：
     * - 输入：n，随后 n 个整数 a[i]。
     * - 输出：n 个整数 ans[i]（空格分隔），若不存在兼容数则为 -1。
     */

    int n; if (!(cin >> n)) return 0;
    vi a(n); For(i, n) cin >> a[i];

    int maxv = 0; For(i, n) maxv = max(maxv, a[i]);
    int B = 0; while ((1 << B) <= maxv && B < 22) ++B; // 至少覆盖到最大值，最多 22 位
    if (B == 0) B = 1; // 处理全 0 情况
    int U = 1 << B;

    vector<int> dp(U, -1);
    For(i, n) dp[a[i]] = a[i]; // 记录存在这些精确掩码的值

    for (int bit = 0; bit < B; ++bit) {
        for (int mask = 0; mask < U; ++mask) {
            if (mask & (1 << bit)) {
                if (dp[mask] == -1) dp[mask] = dp[mask ^ (1 << bit)];
            }
        }
    }

    vi ans(n, -1);
    int FULL = U - 1;
    For(i, n) {
        int comp = FULL ^ a[i];
        ans[i] = dp[comp];
    }

    For(i, n) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}