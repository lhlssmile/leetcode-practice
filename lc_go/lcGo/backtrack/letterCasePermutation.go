package main

import (
	"fmt"
	"strings"
	"unicode"
)

func letterCasePermutation(s string) []string {
	ans := []string{}
	path := []rune{}

	var dfs func(s string, i int)
	dfs = func(s string, i int) {
		if i == len(s) {
			ans = append(ans, string(path))
			return
		}

		ch := rune(s[i])
		if unicode.IsDigit(ch) {
			path = append(path, ch)
			dfs(s, i+1)
			path = path[:len(path)-1]
		} else {
			// 小写
			path = append(path, unicode.ToLower(ch))
			dfs(s, i+1)
			path = path[:len(path)-1]

			// 大写
			path = append(path, unicode.ToUpper(ch))
			dfs(s, i+1)
			path = path[:len(path)-1]
		}
	}

	dfs(s, 0)
	return ans
}

// 测试函数
func main() {
	// 测试用例1
	s1 := "a1b2"
	result1 := letterCasePermutation(s1)
	fmt.Printf("Input: %s\n", s1)
	fmt.Printf("Output: %s\n", strings.Join(result1, ", "))

	// 测试用例2
	s2 := "3z4"
	result2 := letterCasePermutation(s2)
	fmt.Printf("Input: %s\n", s2)
	fmt.Printf("Output: %s\n", strings.Join(result2, ", "))
}

/*
算法思路：递归回溯生成所有可能的字母大小写排列
时间复杂度：O(2^n)，其中n是字符串中字母的数量
空间复杂度：O(n)，递归栈的深度和临时字符串的空间
*/