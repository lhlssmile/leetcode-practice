package main

import (
	"math"
	"slices"
)

func minimumDeletions(word string, k int) int {
	freq := make([]int, 26)

	for _, b := range word {
		freq[b-'a']++
	}
	slices.Sort(freq)
	mxSave := 0
	for i, base := range freq {
		s := 0
		for _, c := range freq[i:] {
			s += int(math.Min(float64(c), float64(base+k)))
		}
		mxSave = max(mxSave, s)
	}
	return len(word) - mxSave
}

func main() {
	word := "dabdcbdcdcd"
	minimumDeletions(word, 2)
}
