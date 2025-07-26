package main

import "fmt"

func lengthOfLongestSubstring(s string) int {

	ans := 0
	var left int = 0

	cnt := map[byte]int{}
	runes := []rune(s)
	for right, x := range runes {
		cnt[byte(x)] += 1
		for cnt[byte(x)] > 1 {
			cnt[s[left]]--
			left++
		}
		ans = max(ans, right-left+1)
	}

	return ans

}

func main() {
	testCases := []struct {
		input    string
		expected int
	}{
		{"abcabcbb", 3},     // "abc"
		{"bbbbb", 1},        // "b"
		{"pwwkew", 3},       // "wke"
		{"", 0},             // 空字符串
		{"au", 2},           // "au"
		{"dvdf", 3},         // "vdf"
		{"你好世界你好", 4}, // Unicode测试
	}

	for _, tc := range testCases {
		result := lengthOfLongestSubstring(tc.input)
		fmt.Printf("Input: %q, Expected: %d, Got: %d\n",
			tc.input, tc.expected, result)
	}
}
