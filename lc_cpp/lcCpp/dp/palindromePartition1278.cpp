#include <vector>
#include <iostream>
#include <string>
using namespace std;
class palindrome_partition1278 {
public:
    /**
     * dp[i][j]: 预计s[i...j]转为回文所需要的最少需改次数
     * cuts[i][k]:s[o...i-1]分割为k个回文串最小修改次数
     * @param s str
     * @param k sub str nums
     * @return minimum modified times
     */
    int palindromePartition(string s,int k) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int i = 0; i < n; ++i) {
            dp[i][i] = 0;
        }
        for(int len = 2;len <= n; ++len) {
            for(int i = 0;i <= n - len;++i) {
                //i~j
                int j = i + len - 1;
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                }else {
                    //此时需要修改字符
                    dp[i][j] = dp[i + 1][j - 1] + 1;
                }
            }
        }
        vector<vector<int>> cuts(n + 1,vector<int>(k + 1,INT_MAX));
        /**
         * cuts[i][j]：表示 s[0..i-1] 分割成 j 个回文子串所需的最少修改次数。
         * p：最后一个子串的起点。
         * j：当前分割成 j 个回文子串。
         * i：当前考虑的字符串末尾索引（0-based，扩展到 n）。
         */
        cuts[0][0] = 0;
        for(int i = 1;i <= n; ++i) {
            //0~ subscript(i - 1)切为1个回文串 直接调用dp
            cuts[i][1] = dp[0][i - 1];
            //切割成两个以上的回文串? 但是最多为k?
            for(int j = 2;j <= min(i,k);++j) {
                //将str分成了j个字串。然后移动p(即从哪一个子字符开始?)    确保p前的字串是回文
                for (int p = j-1; p < i; ++p) {
                    // dp[p][j-1]: 将前p个字符分成j-1个回文子串的最少修改次数
                    // cost[p][i-1]: 将s[p...i-1]变成回文串的修改次数
                    dp[i][j] = min(dp[i][j], dp[p][j-1] + dp[p][i-1]);
                }
            }
        }
        return cuts[n][k];
    }
    int palindRomePartitions(string s,int k) {
        int n = s.size();
        if (n == 0 || k > n) return -1;

        // 预计算 min_change[i][j]：s[i..j] 转为回文的最少修改次数
        vector<vector<int>> min_change(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) min_change[i][i] = 0;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j] && len == 2) {
                    min_change[i][j] = 0;
                } else if (s[i] == s[j]) {
                    min_change[i][j] = min_change[i + 1][j - 1];
                } else {
                    min_change[i][j] = min(min_change[i + 1][j], min_change[i][j - 1]) + 1;
                }
            }
        }

        // 调试输出 DP 表
        cout << "min_change Table:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << min_change[i][j] << " ";
            }
            cout << endl;
        }

        // f[i][r]：s[0..r] 分割成 i+1 个回文子串的最少修改次数
        vector<vector<int>> f(k, vector<int>(n, INT_MAX));
        for (int r = 0; r < n; r++) {
            f[0][r] = min_change[0][r];
        }
        for (int i = 1; i < k; i++) {
            for (int r = i; r < n; r++) {
                for (int l = i - 1; l < r; l++) {
                    if (f[i - 1][l] != INT_MAX) {
                        f[i][r] = min(f[i][r], f[i - 1][l] + min_change[l + 1][r]);
                    }
                }
            }
        }

        // 调试输出 f 表
        cout << "f Table:" << endl;
        for (int i = 0; i < k; i++) {
            for (int r = 0; r < n; r++) {
                cout << f[i][r] << " ";
            }
            cout << endl;
        }

        return f[k - 1][n - 1];
    }
    int palindRomEPartitions(string s,int k) {
        int n = s.size();
        vector min_change(n,vector<int>(n));
        for(int i = n - 2;i >= 0;i--) {
            for(int j = i + 1;j < n;++j) {
                min_change[i][j] = min_change[i + 1][j - 1] + (s[i] != s[j] ? 1 : 0);
            }
        }
        vector f(k,vector<int>(n,INT_MAX));
        f[0] = std::move(min_change[0]);
        for(int i = 1;i < k;++i) {
            for(int r = i;r <= n - k + i;r++) {
                for(int l = i;l <= r;l++) {
                    f[i][r] = min(f[i][r],f[i - 1][l - 1] + min_change[l][r]);
                }
            }
        }
        return f[k - 1][n - 1];
    }
    int palindromePartition1(string s, int k) {
        int n = s.size();

        // cost[i][j]: 将子串s[i...j]变成回文串的最少修改次数
        vector<vector<int>> cost(n, vector<int>(n, 0));

        // 计算任意子串变成回文串的成本
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    cost[i][j] = cost[i+1][j-1];
                } else {
                    cost[i][j] = cost[i+1][j-1] + 1; // 需要修改一个字符
                }
            }
        }

        // dp[i][j]: 将前i个字符分割成j个回文子串的最少修改次数
        vector<vector<int>> dp(n+1, vector<int>(k+1, INT_MAX/2)); // 避免溢出

        // 初始化：将前i个字符分成1个子串
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = cost[0][i-1];
        }

        // 动态规划填表
        for (int i = 1; i <= n; ++i) {
            for (int j = 2; j <= min(i, k); ++j) {
                for (int p = j-1; p < i; ++p) {
                    // dp[p][j-1]: 将前p个字符分成j-1个回文子串的最少修改次数
                    // cost[p][i-1]: 将s[p...i-1]变成回文串的修改次数
                    dp[i][j] = min(dp[i][j], dp[p][j-1] + cost[p][i-1]);
                }
            }
        }

        return dp[n][k];
    }

    /**
     * ps:仿写 灵茶山
     * @param s
     * @param k
     * @return
     */
    int palindromeRewrite(string s,int k) {
        //ex: s.length() == 7 (subscript:0~6)
        auto n = s.size();
        //返回i-j的最小修改次数(成为回文
        vector min_change(n,vector<int>(n,0));
        for(int i = n - 2;i >= 0; --i) {
            for(int j = i + 1;j < n;++j) {
                min_change[i][j] = min_change[i + 1][j - 1] + (s[i] != s[j] ? 1 : 0);
            }
        }
        //f: 存储下标0~r 切割为i + 1个字符串的最小次数
        vector f(k,vector<int>(n,INT_MAX / 2));
        //即切割为1个字符串(没动相当于
        f[0] = std::move(min_change[0]);
        //i:当前切割成几个部分?
        for(int i = 1; i < k;++i) {
            //对于 f[i][r] 中的 r，因为右边还有 k−1−i 个子串，所以 r 至多枚举到 n−1−(k−1−i)=n−k+i。
            //（继续枚举没有意义，这些状态不会参与状态转移。）
            for (int r = 1;r <= n - k + i;++r) {
                for(int l = i;l <= r;++l) {
                    //此时为切割成i + 1个串     min为处理一个字串 f[i][l - 1]为切割成i个字符串最小次数
                    //l~r是最后一个分区
                    f[i][r] = min(f[i][r],f[i - 1][l - 1] + min_change[l][r]);
                }
            }
        }
        return f[n - 1][k - 1];
    }
};

int main() {
    palindrome_partition1278 ps;
    string s = "tcymekt";
    cout << ps.palindRomEPartitions(s,4) << endl;
    return 0;
}
