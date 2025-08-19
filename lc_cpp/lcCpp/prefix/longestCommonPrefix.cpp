//
// Created by 24276 on 2025/8/18.
//
#include <vector>
#include <string>
#include "../template/mylib.h"
using namespace std;
int get_lcp(string s1, string s2) {
    int min_len = min(s1.size(), s2.size());
    for (int i = 0; i < min_len; i++) {
        if (s1[i] != s2[i]) return i;
    }
    return min_len;
}
class longest_common_prefix {
public:
    vector<int> longestCommonPrefix(vs& words) {
        int n = words.size();
        V<int> ans(n, 0);
        int i;
        V<int> lcp(n - 1, 0);
        if (n <= 1) return {0};
        FOR(i,0, n - 1) lcp[i] = get_lcp(words[i], words[i + 1]);

        V<int> preMax(n - 1, 0), sufMax(n - 1, 0);
        preMax[0] = lcp[0];
        FOR(i, 1, n - 1) preMax[i] = max(preMax[i - 1], lcp[i]);
        sufMax[n - 2] = lcp[n - 2];
        for(int j = n - 3; j > -1;j--) {
            sufMax[j] = max(sufMax[j + 1], lcp[j]);
        }
        // REP(i,0, n - 2) sufMax[i] = max(sufMax[i + 1], lcp[i]);
        For(i, n) {
            int mx = 0;
            if (i - 2 >= 0) {
                mx = max(mx, preMax[i - 2]);
            }
            if (i + 1 <= n - 2) {
                mx = max(mx, sufMax[i + 1]);
            }
            if (0 < i && i < n - 1) {
                mx = max(mx, get_lcp(words[i - 1], words[i + 1]));
            }
            ans[i] = mx;
        }
        return ans;
    }
};

int main() {
    return 0;
}
