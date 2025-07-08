//
// Created by 24276 on 2025/5/10.
//

#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;
class max_freq_sum {
public:
    int maxFreqSum(string s) {
        int cnt[26]{0};
        int n = s.size();
        for(int i = 0;i < n;i++) {
            cnt[s[i] - '0']++;
        }
        int yuanyin_max_cnt = 0,fuyin_max_cnt = 0;

        
    }
    int minDeletion(string s,int k ) {
        unordered_set<char> st(s.begin(),s.end());
        return s.size() - k;
    }
};

int main() {
    max_freq_sum sol;
    cout << sol.minDeletion("yyyzz",1);
    return 0;
}
