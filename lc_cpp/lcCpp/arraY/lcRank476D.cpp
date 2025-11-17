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

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
/**
 *
 * 给你一个整数数组 nums。

如果 nums 的一个 子数组 中 没有逆序对 ，即不存在满足 i < j 且 nums[i] > nums[j] 的下标对，则该子数组被称为 稳定 子数组。

同时给你一个长度为 q 的 二维整数数组 queries，其中每个 queries[i] = [li, ri] 表示一个查询。对于每个查询 [li, ri]，请你计算完全包含在 nums[li..ri] 内的 稳定子数组 的数量。

返回一个长度为 q 的整数数组 ans，其中 ans[i] 是第 i 个查询的答案。

注意：

子数组 是数组中一个连续且 非空 的元素序列。
单个元素的子数组被认为是稳定的。
 */
/**
 * 1 <= nums.length <= 1e5
1 <= nums[i] <= 1e5
1 <= queries.length <= 1e5
queries[i] = [li, ri]
0 <= li <= ri <= nums.length - 1©
 */
int main() {
    int n, q;
    cin >> n >> q;
    vi a(n); For(i, n) cin >> a[i];
    struct Query { int l, r, id; };
    V<Query> qs(q);
    For(i, q) { int l, r; cin >> l >> r; qs[i] = {l + 1, r + 1, i}; }
    V<int> E(n + 2);
    E[n] = n;
    ROF(i, 1, n) {
        if (a[i - 1] <= a[i]) E[i] = E[i + 1];
        else E[i] = i;
    }
    V<vi> bucket(n + 2);
    FOR(i, 1, n + 1) bucket[E[i]].pb(i);
    struct BIT {
        int N; V<long long> t;
        BIT(int n=0){init(n);} void init(int n){N=n; t.assign(n+1,0);}
        void add(int i, long long v){ for(; i<=N; i+=i&-i) t[i]+=v; }
        long long sum(int i){ long long r=0; for(; i>0; i-=i&-i) r+=t[i]; return r; }
        long long range(int l,int r){ return sum(r)-sum(l-1); }
    } bitSum(n), bitCnt(n);
    V<long long> prefIdx(n + 1);
    FOR(i, 1, n + 1) prefIdx[i] = prefIdx[i - 1] + i;
    V<Query> ord = qs;
    ranges::sort(ALL(ord), [](const Query& A, const Query& B){ return A.r < B.r; });
    V<long long> ans(q);
    int p = 0;
    FOR(r, 1, n + 1) {
        EACH(i, bucket[r]) { bitSum.add(i, E[i]); bitCnt.add(i, 1); }
        while (p < q && ord[p].r == r) {
            int l = ord[p].l;
            int id = ord[p].id;
            int len = r - l + 1;
            long long sE = bitSum.range(l, r);
            long long cE = bitCnt.range(l, r);
            long long sMin = sE + 1LL * r * (len - cE);
            long long sI = prefIdx[r] - prefIdx[l - 1];
            ans[id] = sMin - sI + len;
            ++p;
        }
    }
    For(i, q) cout << ans[i] << '\n';
    return 0;
}
