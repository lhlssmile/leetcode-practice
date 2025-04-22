package main

import (
	"fmt"
	"math"
)

func minWindow(s string, t string) string {
	m, n := len(s), len(t)
	if m < n {
		return ""
	}

	tCount := make([]int, 128)
	windowCount := make([]int, 128)

	for _, c := range t {
		tCount[c]++
	}

	required := n
	left, right := 0, 0
	minLen := math.MaxInt32
	start := 0

	for right < m {
		c := s[right]
		windowCount[c]++
		if tCount[c] > 0 && windowCount[c] <= tCount[c] {
			required--
		}

		for required == 0 && left <= right {
			if right-left+1 < minLen {
				minLen = right - left + 1
				start = left
			}
			leftChar := s[left]
			windowCount[leftChar]--
			if tCount[leftChar] > 0 && windowCount[leftChar] < tCount[leftChar] {
				required++
			}
			left++
		}

		right++
	}

	if minLen == math.MaxInt32 {
		return ""
	}
	return s[start : start+minLen]
}
func main() {
	s := "ADOBECODEBANC"
	t := "ABC"
	fmt.Println(minWindow(s, t))
}
