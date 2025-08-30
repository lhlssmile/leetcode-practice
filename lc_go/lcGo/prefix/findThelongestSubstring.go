package main

func findTheLongestSubstring(s string) int {
	n := len(s)
	first := make(map[int]int) // 记录状态第一次出现的位置
	first[0] = -1              // 空字符串状态为0，位置-1
	state := 0                 // 当前前缀的元音奇偶状态
	maxLen := 0                // 最长子字符串长度

	// 元音映射：a=0, e=1, i=2, o=3, u=4
	vowelPos := make([]int, 128)
	for i := range vowelPos {
		vowelPos[i] = -1
	}
	vowelPos['a'] = 0
	vowelPos['e'] = 1
	vowelPos['i'] = 2
	vowelPos['o'] = 3
	vowelPos['u'] = 4

	// 遍历字符串
	for i := 0; i < n; i++ {
		// 如果是元音，更新状态（翻转对应位的奇偶性）
		if pos := vowelPos[s[i]]; pos != -1 {
			state ^= 1 << pos // 翻转第pos位
		}

		// 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
		if j, exists := first[state]; exists {
			maxLen = max(maxLen, i-j)
		} else {
			// 记录状态第一次出现的位置
			first[state] = i
		}
	}

	return maxLen
}

func main() {
	s := "eleetminicoworoep"
	println(findTheLongestSubstring(s))

}
