#include <string>
#include <iostream>
#include <vector>
using namespace std;
class check_partitioning1745 {
public:
    bool checkPartitioning(string s) {
        return palindromePartitiona(s,3) == 0;
    }
private:
    bool palindromePartition(string s,int k) {
        auto n = s.size();
        //path上是否为回文?
        vector<vector<bool>> path(n, vector<bool>(n, false));
        for(int i = 0; i < n;++i) {
            path[i][i] = true;
        }
        for(int len = 2;len <= n; ++len) {
            for(int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if(len == 2) {
                    path[i][j] = s[i] == s[j];
                }else {
                    path[i][j] = path[i + 1][j - 1] && s[i] == s[j];
                }
            }
        }
        for(int i = 0;i < n -2;++i) {
            if(path[0][i]) {
                for(int j = i + 1;j < n - 1;++j) {
                    if(path[i+1][j] && path[j+1][n-1]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int pal1ndromePartition(string s,int k) {
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
    // 1278. 分割回文串 III
    int palindromePartitiona(string& s, int k) {
        int n = s.size();
        vector min_change(n, vector<int>(n));
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                min_change[i][j] = min_change[i + 1][j - 1] + (s[i] != s[j] ? 1 : 0);
            }
        }

        auto f = move(min_change[0]);
        //i = 2时候分成3个字符串
        for (int i = 1; i < k; i++) {
            //最后一个分区的结束位置
            for (int r = n - k + i; r >= i; r--) {
                f[r] = INT_MAX;
                //最后一个分区的开始位置
                for (int l = i; l <= r; l++) {
                    f[r] = min(f[r], f[l - 1] + min_change[l][r]);
                }
            }
        }
        //  ·🌸三层for结束后 代表意义为将s(n = s.length()) 分成k(3)个回文串的最小修改次数
        return f[n - 1];
    }

};

int main() {
    check_partitioning1745 ps;
    cout << ps.checkPartitioning("bcbddxy") << endl;
    return 0;
}
