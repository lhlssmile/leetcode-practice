#include <iostream>
#include <string>
#include <vector>
using namespace std;
class partition131 {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        if(n == 1) return {{s}};
        //dp 存储下标i-j是否为回文
        vector<vector<bool>> dp(n,vector<bool>(n,false));
        //单个字符串一定是回文
        for(int i = 0;i < n;++i) {
            dp[i][i] = true;
        }
        for(int len = 2;len <= n;++len) {
            for(int i = 0;i <= n - len;++i) {
                int j = i + len - 1;
                if(len == 2) {
                    //字串长度为2直接判断前后是否相等
                    dp[i][j] = (s[i] == s[j]);
                }else {
                    //否则需要判断首位是否相等。除首尾的字串也是同样
                    dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                }
            }
        }
        vector<vector<string>> result;
        vector<string> current;
        backTrack(0,current,result,s,dp);
        return result;
    }
private:
    void backTrack(int start,vector<string>& current,vector<vector<string>>& result,const string& s,
        const vector<vector<bool>>& dp) {
        if(start == s.length()) {
            result.push_back(current);
            return;
        }
        for(int end = start; end < s.length();++end) {
            if(dp[start][end]) {
                current.push_back(s.substr(start,end - start + 1));
                backTrack(end + 1,current,result,s,dp);
                current.pop_back();
            }
        }
    }
};

int main() {
    partition131 ps;
    auto res = ps.partition("aab");
    cout << "[" << endl;
    for(auto const& vec : res) {
        cout << "[" << " ";
        for(auto const& ele : vec) {
            cout << ele << " ";
        }
        cout << "]" << " ";
    }
    cout << "]" << endl;
    return 0;
}
