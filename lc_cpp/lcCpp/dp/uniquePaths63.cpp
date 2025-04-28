#include <vector>
#include <iostream>
using namespace std;
class unique_paths63 {
public:
    int uniquePaths(int m,int n) {
        //数组的写法?
        vector dp(m,vector<int>(n,0));
        dp[0][0] = 1;
        for(int i = 0;i < m;++i)    dp[i][0] = 1;
        for(int i = 0;i < n;++i)    dp[0][i] = 1;
        for(int i = 1;i < m;++i) {
            for(int j = 1;j < n;++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
    int uniquePathsDFS(int m,int n) {
        vector memo(m,vector<int>(n));
        auto dfs = [&](auto&& dfs,int i,int j) {
            if(i < 0 || j < 0) {
                return 0;
            }
            if(i == 0 && j == 0) {
                return 1;
            }
            int& res = memo[i][j];
            if(res) {
                return res;
            }
            return res = dfs(dfs,i - 1,j) + dfs(dfs,i,j - 1);
        };
        return dfs(dfs,m - 1,n - 1);
    }
};

int main() {
    int m = 3,n = 7;
    unique_paths63 ps;
    cout << ps.uniquePathsDFS(m,n) << endl;
    return 0;
}
