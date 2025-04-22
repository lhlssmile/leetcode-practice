package main

import "fmt"

func countPrefixes(words []string, s string) int {
	ans := 0

	for _, word := range words {
		if len(word) > len(s) {
			continue
		}
		isPrefix := true
		for i := 0; i < len(word); i++ {
			if word[i] != s[i] {
				isPrefix = false
				break
			}
		}
		if isPrefix {
			ans += 1
		}
	}
	return ans
}

func main() {
	words := []string{"a", "b", "c", "ab", "bc", "abc"}
	s := "abc"
	res := countPrefixes(words, s)
	fmt.Println(res)

}
