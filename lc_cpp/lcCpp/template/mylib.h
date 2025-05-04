// mylib.h
#ifndef MYLIB_H
#define MYLIB_H

#include <bits/stdc++.h>

#ifdef __GNUC__
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#endif

// ==== 快速宏定义 ====
#define ALL(v) (v).begin(), (v).end()
#define For(i, _) for (int i = 0, i##end = (_); i < i##end; ++i) // [0,_)
#define FOR(i, a, b) for (int i = (a), i##end = (b); i < i##end; ++i) // [a,b)
#define Rep(i, _) for (int i = (_)-1; i >= 0; --i) // [0,_)
#define REP(i, a, b) for (int i = (b)-1, i##end = (a); i >= i##end; --i) // [a,b)
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
#define fi first
#define se second
#define V vector
// #define s string
#define ump unordered_map
#define ust unordered_set
#define SORT(v) sort(ALL(v)) // 快速排序
#define BINARY_SEARCH(v, x) binary_search(ALL(v), x) // 二分查找
#define FILL(arr, val) fill(arr, arr + sizeof(arr)/sizeof(arr[0]), val) // 快速初始化数组
#ifdef LOCAL
#define DBG(x) cerr << #x << " = " << x << endl // 调试输出
#else
#define DBG(x)
#endif
#include <queue>
using namespace std;

// ==== 常用类型定义 ====
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;
typedef std::vector<std::string> vs;
typedef priority_queue<int, vi, less<int>> pq_max; // 大顶堆
typedef std::priority_queue<int, vi, greater<int>> pq_min; // 小顶堆

// ==== 常量定义 ====
const int dir[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // 上右下左
const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

// ==== 小工具函数 ====
template<class T> inline bool ckmin(T& x, const T& y) { return x > y ? (x = y, true) : false; }
template<class T> inline bool ckmax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

// ==== 输入输出加速 ====
int fastio_init = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

// ==== 时间和内存统计器 ====
#include <chrono>


struct Timer {
    chrono::high_resolution_clock::time_point start_time;

    Timer() { start_time = chrono::high_resolution_clock::now(); }

    void print() {
        auto end_time = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double, milli>(end_time - start_time).count();
        cout << fixed << setprecision(2) << "⏱️ Time: " << elapsed << " ms" << '\n';

#ifdef ENABLE_MEMORY_STAT
        // Windows 内存统计（需手动定义 ENABLE_MEMORY_STAT）
#include <windows.h>
#include <psapi.h>
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            cout << "📦 Memory: " << pmc.WorkingSetSize / 1024 / 1024 << " MB" << endl;
        }
#endif
    }
};

#endif // MYLIB_H