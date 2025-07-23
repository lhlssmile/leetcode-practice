package main

func longestPalindrome(s string) string {
	n := len(s)
	if n == 0 {
		return ""
	}

	// 创建 n×n 的 DP 数组
	dp := make([][]bool, n)
	for i := range dp {
		dp[i] = make([]bool, n) // 必须为每一行分配内存
	}

	start, maxLen := 0, 1

	// 单个字符都是回文
	for i := 0; i < n; i++ {
		dp[i][i] = true
	}

	// 检查长度为 2 的子串
	for i := 0; i < n-1; i++ {
		if s[i] == s[i+1] {
			dp[i][i+1] = true
			start, maxLen = i, 2
		}
	}

	// 检查长度大于 2 的子串
	for length := 3; length <= n; length++ {
		for i := 0; i <= n-length; i++ {
			j := i + length - 1
			if s[i] == s[j] && dp[i+1][j-1] {
				dp[i][j] = true
				start, maxLen = i, length
			}
		}
	}

	return s[start : start+maxLen]
}

func main() {

}
