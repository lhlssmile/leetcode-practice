//
// Created by 24276 on 2025/11/17.
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
    int wl, pl; cin >> wl >> pl;
    vs words(wl), puzzles(pl);
    For(i, wl) cin>>words[i];
    For(i, pl) cin>>puzzles[i];
    /**
     * 题意（普通话版）：
     * - 每个 puzzle 是 7 个小写字母，问：有多少个单词 word 满足：
     *   1) word 中出现的所有字母都在 puzzle 里（word 的字母集合 ⊆ puzzle 的字母集合）
     *   2) word 必须包含 puzzle 的第一个字母
     *
     * 思路：用“位掩码”+“子集枚举”（SOS 思想）
     * - 把一个字符串转换成 26 位的整数 mask（第 k 位表示是否包含第 k 个字母），
     *   这样“字母集合 ⊆”就变成了“mask 是另一个 mask 的子集”。
     * - 先把所有 words 的掩码统计频次 freq[mask]。
     * - 对于每个 puzzle：
     *   设 pmask 是 puzzle 的掩码，firstBit 是 puzzle[0] 对应的位。
     *   我们只枚举 pmask 去掉 firstBit 后的 6 位的所有子集 sub（共有 2^6 个），
     *   然后把 firstBit 强制加入：sub | firstBit，这样就保证包含 puzzle 的第一个字母。
     *   统计 freq[sub | firstBit] 之和，就是答案。
     * - 复杂度：预处理 O(wl * 词长)；每个 puzzle 遍历 2^6 个子集，总体 O(pl * 64)。
     *
     * 输入输出约定：
     * - 输入：wl pl，后跟 wl 行 words，pl 行 puzzles。
     * - 输出：pl 个整数，分别是每个 puzzle 的答案（空格分隔）。
     */

    auto toMask = [](const string& s) {
        int m = 0;
        for (char c : s) m |= 1 << (c - 'a');
        return m;
    };

    umpii freq;
    freq.reserve(wl * 2);
    For(i, wl) {
        int m = toMask(words[i]);
        if (__builtin_popcount((unsigned)m) <= 7) freq[m]++;
        // 优化：字母种类超过 7 的单词不可能被任何 puzzle 覆盖，直接忽略。
    }

    vi ans(pl, 0);
    For(i, pl) {
        const string& p = puzzles[i];
        int pmask = toMask(p);
        int firstBit = 1 << (p[0] - 'a');
        int rest = pmask ^ firstBit; // 剩余 6 位

        int cnt = 0;
        for (int sub = rest; ; sub = (sub - 1) & rest) {
            cnt += freq[sub | firstBit];
            if (sub == 0) break;
        }
        ans[i] = cnt;
    }

    For(i, pl) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}