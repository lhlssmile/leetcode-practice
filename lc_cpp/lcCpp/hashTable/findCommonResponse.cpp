//
// Created by 24276 on 2025/4/28.
//

#include "../template/mylib.h"
using namespace std;
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
#define s string
#define ump unordered_map
#define ust unordered_set
using namespace std;
#define V vector
// ==== 常用类型定义 ====
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<string> vs;
using namespace std;
class Solution {
public:
    std::s findCommonResponse(vector<vector<string>>& r) {
        ump<s,int>cnt;
        int mx=0;
        s ret;
        for(const auto &i:r)
            for(string j:ust(ALL(i))){
            if(ckmax(mx,++cnt[j]))ret=j;
            else if(mx==cnt[j])ckmin(ret,j);
        }
        return ret;
    }

    s mostCommonResponse(V<V<s>>& responses) {
        ump<s,int> cnt;

        For(i,responses.size()) {
             ust<s> unique(ALL(responses[i]));
             for(const auto& s : unique) {
                 cnt[s]++;
             }
        }
        int max_cnt = 0;
        s ans = "";
        for (const auto& [s,f] : cnt) {
            if (f > max_cnt) {
                max_cnt = f;
                ans = s;
            }else if (f == max_cnt && s < ans) {
                ans = s;
            }
        }
        return ans;
    }
};

int main() {
    Timer t; // 使用模板中的 Timer 计时

    Solution sol;
    vector<vector<string>> test1 = {
        {"good", "ok", "good", "ok"},
        {"ok", "bad", "good", "ok", "ok"},
        {"good"},
        {"bad"}
    };
    cout << "Test 1: " << sol.mostCommonResponse(test1) << " (Expected: good)" << endl;

    vector<vector<string>> test2 = {
        {"good", "ok", "good"},
        {"ok", "bad"},
        {"bad", "notsure"},
        {"great", "good"}
    };
    cout << "Test 2: " << sol.mostCommonResponse(test2) << " (Expected: bad)" << endl;

    t.print(); // 打印时间和内存
    return 0;
}
