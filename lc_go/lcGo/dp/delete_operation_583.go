// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

package main

import (
	"fmt"
)

// 方法一：基于最长公共子序列(LCS)的解法
// 时间复杂度：O(m*n)，空间复杂度：O(m*n)
func MinDistanceLCS(word1 string, word2 string) int {
	m, n := len(word1), len(word2)

	// 创建LCS矩阵
	lcs := make([][]int, m+1)
	for i := range lcs {
		lcs[i] = make([]int, n+1)
	}

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if word1[i-1] == word2[j-1] {
				lcs[i][j] = lcs[i-1][j-1] + 1
			} else {
				lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1])
			}
		}
	}

	// 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
	return m + n - 2*lcs[m][n]
}

// 方法二：直接使用动态规划
// 时间复杂度：O(m*n)，空间复杂度：O(m*n)
func MinDistance(word1 string, word2 string) int {
	m, n := len(word1), len(word2)

	// 创建DP矩阵
	dp := make([][]int, m+1)
	for i := range dp {
		dp[i] = make([]int, n+1)
	}

	// 初始化
	for i := 0; i <= m; i++ {
		dp[i][0] = i // 删除 word1 的前 i 个字符
	}
	for j := 0; j <= n; j++ {
		dp[0][j] = j // 删除 word2 的前 j 个字符
	}

	// 动态规划
	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if word1[i-1] == word2[j-1] {
				dp[i][j] = dp[i-1][j-1] // 字符相同，无需删除
			} else {
				dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1) // 删除一个字符
			}
		}
	}

	return dp[m][n]
}

// 辅助函数：求最大值
func maxA(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 辅助函数：求最小值
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// 测试函数
func TestDeleteOperation() {
	// 测试用例
	testCases := []struct {
		word1 string
		word2 string
	}{
		{"sea", "eat"},             // 期望输出: 2
		{"leetcode", "etco"},       // 期望输出: 4
		{"", "a"},                  // 期望输出: 1
		{"a", ""},                  // 期望输出: 1
		{"intention", "execution"}, // 期望输出: 8
	}

	for _, tc := range testCases {
		fmt.Printf("Word1: \"%s\", Word2: \"%s\"\n", tc.word1, tc.word2)
		fmt.Printf("方法一 (LCS): %d\n", MinDistanceLCS(tc.word1, tc.word2))
		fmt.Printf("方法二 (DP): %d\n", MinDistance(tc.word1, tc.word2))
		fmt.Println("-------------------")
	}
}

// 如果需要直接运行测试，可以取消注释以下main函数

func main() {
	TestDeleteOperation()
}
