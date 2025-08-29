// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 辅助函数：求最大值
int max(int a, int b) {
    return a > b ? a : b;
}

// 辅助函数：求最小值
int min(int a, int b) {
    return a < b ? a : b;
}

// 方法一：基于最长公共子序列(LCS)的解法
// 时间复杂度：O(m*n)，空间复杂度：O(m*n)
int minDistanceLCS(char* word1, char* word2) {
    int m = strlen(word1);
    int n = strlen(word2);
    
    // 创建LCS矩阵
    int** lcs = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        lcs[i] = (int*)calloc(n + 1, sizeof(int));
    }
    
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
    int result = m + n - 2 * lcs[m][n];
    
    // 释放内存
    for (int i = 0; i <= m; i++) {
        free(lcs[i]);
    }
    free(lcs);
    
    return result;
}

// 方法二：直接使用动态规划
// 时间复杂度：O(m*n)，空间复杂度：O(m*n)
int minDistance(char* word1, char* word2) {
    int m = strlen(word1);
    int n = strlen(word2);
    
    // 创建DP矩阵
    int** dp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    
    // 初始化
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i; // 删除 word1 的前 i 个字符
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j; // 删除 word2 的前 j 个字符
    }
    
    // 动态规划
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // 字符相同，无需删除
            } else {
                dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1); // 删除一个字符
            }
        }
    }
    
    int result = dp[m][n];
    
    // 释放内存
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// 测试函数
int main() {
    // 测试用例
    char* testCases[][2] = {
        {"sea", "eat"},           // 期望输出: 2
        {"leetcode", "etco"},     // 期望输出: 4
        {"", "a"},                 // 期望输出: 1
        {"a", ""},                 // 期望输出: 1
        {"intention", "execution"} // 期望输出: 8
    };
    
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTestCases; i++) {
        printf("Word1: \"%s\", Word2: \"%s\"\n", testCases[i][0], testCases[i][1]);
        printf("方法一 (LCS): %d\n", minDistanceLCS(testCases[i][0], testCases[i][1]));
        printf("方法二 (DP): %d\n", minDistance(testCases[i][0], testCases[i][1]));
        printf("-------------------\n");
    }
    
    return 0;
}