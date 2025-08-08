package main

func vowelStrings(words []string, queries [][]int) []int {
	n := len(words)

	prefix := make([]int, n+1)
	for i := range prefix {
		prefix[i] = 0
	}

	isVowel := func(c byte) bool {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
	}
	isVowelWord := func(w string) bool {
		return isVowel(w[0]) && isVowel(w[len(w)-1])
	}
	for i, w := range words {
		if isVowelWord(w) {
			prefix[i+1] = prefix[i] + 1
		} else {
			prefix[i+1] = prefix[i]
		}
	}
	ans := make([]int, len(queries))
	for i, q := range queries {
		l, r := q[0], q[1]
		ans[i] = prefix[r+1] - prefix[l]
	}
	return ans
}

func main() {

}
