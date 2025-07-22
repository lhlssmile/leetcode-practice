#include <string>
#include <vector>
using namespace std;
class longest_common_subsequence{
public:
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector memo(m + 1,vector<int>(n + 1, -1));

    auto dfs = [&](this auto&& dfs, int i, int j) -> int {
        if (i < 0 || j < 0) {
            return 0;
        }
        int& res = memo[i][j];
        if(res != -1) {
            return res;
        }
        if (text1[i] == text2[j]) {
            res = 1 + dfs(i - 1, j - 1);
        }else {
            res = max(dfs(i - 1, j), dfs(i, j - 1));
        }
        memo[i][j] = res;
        return res;
    };

    return dfs(m - 1, n - 1);
}
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector dp(m + 1,vector<int>(n + 1,0));

    for (int i = 1;i <= m;i++ ){
        for (int j = 1;j <= n;j++){
            if (text1[i - 1] == text2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
};
int main(){

}