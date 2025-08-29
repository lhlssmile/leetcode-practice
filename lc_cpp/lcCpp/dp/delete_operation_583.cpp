// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

#include <bits/stdc++.h>
using namespace std;

#define V vector

class Solution {
public:
    // 方法一：基于最长公共子序列(LCS)的解法
    // 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    int minDistanceLCS(string word1, string word2) {
        int m = word1.size(), n = word2.size();

        V<V<int>> lcs(m + 1, V<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                } else {
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                }
            }
        }
        // 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
        return m + n - 2 * lcs[m][n];
    }
    
    // 方法二：直接使用动态规划
    // 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // 初始化
        for (int i = 0; i <= m; ++i) dp[i][0] = i; // 删除 word1 的前 i 个字符
        for (int j = 0; j <= n; ++j) dp[0][j] = j; // 删除 word2 的前 j 个字符
        
        // 动态规划
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1]; // 字符相同，无需删除
                } else {
                    dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1); // 删除一个字符
                }
            }
        }
        
        return dp[m][n];
    }
};

// 测试函数
int main() {
    Solution sol;
    
    // 测试用例
    vector<pair<string, string>> testCases = {
        {"sea", "eat"},       // 期望输出: 2
        {"leetcode", "etco"}, // 期望输出: 4
        {"", "a"},           // 期望输出: 1
        {"a", ""},           // 期望输出: 1
        {"intention", "execution"} // 期望输出: 8
    };
    
    for (const auto& tc : testCases) {
        cout << "Word1: \"" << tc.first << "\", Word2: \"" << tc.second << "\"" << endl;
        cout << "方法一 (LCS): " << sol.minDistanceLCS(tc.first, tc.second) << endl;
        cout << "方法二 (DP): " << sol.minDistance(tc.first, tc.second) << endl;
        cout << "-------------------" << endl;
    }
    
    return 0;
}