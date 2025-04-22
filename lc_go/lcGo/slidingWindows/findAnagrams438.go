package main

import "fmt"

func findAnagrams(s string, p string) []int {
	result := []int{}
	if len(s) < len(p) {
		return result
	}

	pCount := make([]int, 26)
	for _, c := range p {
		pCount[c-'a']++
	}

	windowCount := make([]int, 26)
	left, right := 0, 0

	for right < len(s) {
		if pCount[s[right]-'a'] == 0 {
			windowCount = make([]int, 26)
			left = right + 1
			right = left
			continue
		}

		windowCount[s[right]-'a']++

		for windowCount[s[right]-'a'] > pCount[s[right]-'a'] {
			windowCount[s[left]-'a']--
			left++
		}

		if right-left+1 == len(p) {
			result = append(result, left)
			windowCount[s[left]-'a']--
			left++
		}

		right++
	}

	return result
}

func main() {
	s, p := "cbaebabacd", "abc"
	res := findAnagrams(s, p)
	fmt.Println(res)

}
