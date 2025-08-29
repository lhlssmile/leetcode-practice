// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

package lcJava.dp;

import java.util.Arrays;

public class DeleteOperation583 {
    
    // 方法一：基于最长公共子序列(LCS)的解法
    // 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    public int minDistanceLCS(String word1, String word2) {
        int m = word1.length(), n = word2.length();
        
        int[][] lcs = new int[m + 1][n + 1];
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                } else {
                    lcs[i][j] = Math.max(lcs[i - 1][j], lcs[i][j - 1]);
                }
            }
        }
        
        // 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
        return m + n - 2 * lcs[m][n];
    }
    
    // 方法二：直接使用动态规划
    // 时间复杂度：O(m*n)，空间复杂度：O(m*n)
    public int minDistance(String word1, String word2) {
        int m = word1.length(), n = word2.length();
        int[][] dp = new int[m + 1][n + 1];
        
        // 初始化
        for (int i = 0; i <= m; i++) dp[i][0] = i; // 删除 word1 的前 i 个字符
        for (int j = 0; j <= n; j++) dp[0][j] = j; // 删除 word2 的前 j 个字符
        
        // 动态规划
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1]; // 字符相同，无需删除
                } else {
                    dp[i][j] = Math.min(dp[i - 1][j] + 1, dp[i][j - 1] + 1); // 删除一个字符
                }
            }
        }
        
        return dp[m][n];
    }
    
    // 测试函数
    public static void main(String[] args) {
        DeleteOperation583 solution = new DeleteOperation583();
        
        // 测试用例
        String[][] testCases = {
            {"sea", "eat"},           // 期望输出: 2
            {"leetcode", "etco"},     // 期望输出: 4
            {"", "a"},                 // 期望输出: 1
            {"a", ""},                 // 期望输出: 1
            {"intention", "execution"} // 期望输出: 8
        };
        
        for (String[] tc : testCases) {
            System.out.println("Word1: \"" + tc[0] + "\", Word2: \"" + tc[1] + "\"");
            System.out.println("方法一 (LCS): " + solution.minDistanceLCS(tc[0], tc[1]));
            System.out.println("方法二 (DP): " + solution.minDistance(tc[0], tc[1]));
            System.out.println("-------------------");
        }
    }
}