// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

package main

import (
	"fmt"
	"strings"
)

// KMP算法实现
func repeatedSubstringPatternKMP(s string) bool {
	n := len(s)
	if n <= 1 {
		return false
	}
	
	// 构建KMP的next数组
	next := make([]int, n+1)
	next[0] = -1
	j := -1
	
	for i := 0; i < n; i++ {
		for j >= 0 && s[i] != s[j] {
			j = next[j]
		}
		j++
		next[i+1] = j
	}
	
	periodLen := n - next[n]
	return n%periodLen == 0 && periodLen != n
}

// 字符串拼接方法
func repeatedSubstringPatternConcat(s string) bool {
	// 将字符串与自身拼接，然后去掉首尾字符
	// 如果原字符串是重复模式，那么在新字符串中一定能找到原字符串
	doubleS := s + s
	return strings.Contains(doubleS[1:len(doubleS)-1], s)
}

// 暴力枚举方法
func repeatedSubstringPatternBrute(s string) bool {
	n := len(s)
	if n <= 1 {
		return false
	}
	
	for i := 1; i <= n/2; i++ {
		if n%i == 0 {
			pattern := s[:i]
			valid := true
			for j := i; j < n; j += i {
				if s[j:j+i] != pattern {
					valid = false
					break
				}
			}
			if valid {
				return true
			}
		}
	}
	return false
}

func main() {
	testCases := []string{
		"abab",
		"aba",
		"abcabcabcabc",
		"a",
		"aa",
	}
	
	fmt.Println("=== 重复的子字符串模式检测 ===")
	
	for i, s := range testCases {
		fmt.Printf("\n测试用例 %d: \"%s\"\n", i+1, s)
		
		result1 := repeatedSubstringPatternKMP(s)
		result2 := repeatedSubstringPatternConcat(s)
		result3 := repeatedSubstringPatternBrute(s)
		
		fmt.Printf("KMP算法: %t\n", result1)
		fmt.Printf("字符串拼接: %t\n", result2)
		fmt.Printf("暴力枚举: %t\n", result3)
		
		// 验证结果一致性
		if result1 != result2 || result2 != result3 {
			fmt.Printf("警告: 结果不一致!\n")
		}
	}
}