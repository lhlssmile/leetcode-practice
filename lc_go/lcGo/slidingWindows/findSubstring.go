package main

func findSubstring(s string, words []string) []int {
	n := len(words)
	m := len(s)
	k := len(words[0])
	totalLen := n * k
	var ans []int

	if m < totalLen {
		return ans
	}

	// 需求表
	need := make(map[string]int)
	for _, w := range words {
		need[w]++
	}

	// 遍历起点：对齐方式
	for offset := 0; offset < k; offset++ {	
		left := offset
		window := make(map[string]int)
		count := 0 // 窗口内匹配的单词数

		// 枚举每个单词起点
		for right := offset; right+k <= m; right += k {
			w := s[right : right+k]

			// 窗口右扩
			if _, exists := need[w]; exists {
				window[w]++
				count++						

				// 如果某个单词超频，收缩窗口
				for window[w] > need[w] {
					lw := s[left : left+k]
					window[lw]--
					left += k
					count--
				}

				// 如果窗口刚好包含n个单词
				if count == n {
					ans = append(ans, left)
					// 再往前收缩一步，准备找下一个
					lw := s[left : left+k]
					window[lw]--
					left += k
					count--
				}
			} else {
				// 不在need中，清空窗口
				window = make(map[string]int)
				count = 0
				left = right + k
			}
		}
	}

	return ans
}

func main() {
	s := "barfoothefoobarman"
	words := []string{"foo", "bar"}

	findSubstring(s, words)
}
