#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
class word_break139 {
public:
    /**
     *ex:s = "leetcode"
     * mind:倒推往回,ex 枚举最后一段的长度 = 1 'e' 那么剩下为 "leetcod"
     *      继续长度为2 "de" + "leetco"
     *              3 "ode" + "leetc"
     *              4 "code" + "leet"
     * 长为 1，即子串 s[i−1:i]，如果它在 wordDict 中，那么问题变成：能否把前缀 s[:i−1] 划分成若干段，使得每段都在 wordDict 中，即 dfs(i−1)。
       长为 2，即子串 s[i−2:i]，如果它在 wordDict 中，那么问题变成：能否把前缀 s[:i−2] 划分成若干段，使得每段都在 wordDict 中，即 dfs(i−2)。
       长为 3，即子串 s[i−3:i]，如果它在 wordDict 中，那么问题变成：能否把前缀 s[:i−3] 划分成若干段，使得每段都在 wordDict 中，即 dfs(i−3)。

     * @param s
     * @param wordDict
     * @return
     */
    bool wordBreak(string s,vector<string>& wordDict) {
        int max_len = ranges::max(wordDict,{},&string::length).length();
        unordered_set<string> words(wordDict.begin(),wordDict.end());
        int n = s.length();
        vector<int> f(n + 1);
        f[0] = true;
        for(int i = 1;i <= n;i++) {
            //没必要检查大于max_length 的字串长度 因为这些都不在wordDict里
            for(int j = i - 1;j >= max(i - max_len,0);j--) {
                auto sub_string = s.substr(j, i - j);
                if(f[j] && words.count(sub_string)) {
                    f[i] = true;
                    break;
                }
            }
        }
        return f[n];
    }
    bool wordBreaka(string s,vector<string>& wordDict) {
        auto n = s.size();
        unordered_set<string> wordSet(wordDict.begin(),wordDict.end());
        vector<int> dp(n + 1,false);
        dp[0] = true;
        for(int i = 1; i <= n;++i) {
            for(int j = 0;j < i;++j) {
                //找子字符拼起来是否能在dict中找到，若是有直接当成前缀
                auto sub_str = s.substr(j,i - j);
                if (dp[j] && wordSet.count(sub_str)) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }





    /**
    auto n = static_cast<int>(s.size());
        vector<int> dp(n + 1,false);
        //这里把0下标当作空了?
        dp[0] = true;
        unordered_set<string> wordSet(wordDict.begin(),wordDict.end());
        for(int i = 1;i <= n; ++i) {
            for(int j = 0;j < i;++j) {
                auto sub_str = s.substr(j,i - j);
                if(wordSet.count(sub_str) && dp[i]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
     */
};

int main() {
    word_break139 ps;
    vector<string> wordDict = {"cats","dog","sand","and","cat"};
    cout << ps.wordBreak("catsanddog",wordDict) << endl;
    return 0;
}
