typedef long long LL;
#define V vector
#include <bits/stdc++.h>
using namespace std;

class lengthAfterTransformations3335 {
    const int MOD = 1e9 + 7;
public:
    int lengthAfterTransformations(string s, int t) {
        int n = s.size();
        V<LL> dp(t + 1); // dp[i]表示第i次转换后的长度
        dp[0] = n; // 初始长度为n
        
        // 对于每个字符，计算它对每次转换的贡献
        for(char c : s) {
            V<LL> char_dp(t + 1);
            char_dp[0] = 1; // 初始每个字符长度为1
            
            for(int i = 1; i <= t; i++) {
                if(c == 'z') {
                    // 'z'变成'ab'，长度变为2
                    char_dp[i] = 2;
                } else {
                    // 其他字符变成下一个字母，长度不变
                    char_dp[i] = char_dp[i-1];
                }
            }
            
            // 累加每个字符的贡献
            for(int i = 0; i <= t; i++) {
                dp[i] = (dp[i] + char_dp[i] - 1) % MOD;
            }
        }
        
        return dp[t];
    }
};

int main(){
    lengthAfterTransformations3335 sol;
    string s = "abcyy";
    int t = 2;
    cout << sol.lengthAfterTransformations(s,t); 
}
