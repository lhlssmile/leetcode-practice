package main

func longestPalindrome(words []string) int {
	cnt := make([][]int, 26)

	for i := range cnt {
		cnt[i] = make([]int, 26)
	}
	for _, c := range words {
		cnt[byte(c[0]-'a')][c[1]-'a']++
	}
	ans, odd := 0, 0
	for i := range cnt {
		c := cnt[i][i]

		ans += c - c%2
		odd |= c % 2
		for j := i + 1; j < 26; j++ {
			ans += minC(cnt[i][j], cnt[j][i]) * 2
		}
	}
	return (ans + odd) * 2
}

func minC(a, b int) int {
	if a < b {
		return a
	}
	return b
}
func main() {
	words := []string{"lc", "cl", "gg"}
	longestPalindrome(words)
}
