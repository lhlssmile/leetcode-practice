package main

func partitionString(s string) []string {
	ans := []string{}
	seen := [26]bool{}

	cur := ""

	for _, c := range s {
		idx := c - 'a'
		if seen[idx] {
			ans = append(ans, cur)
			cur = string(c)
			seen = [26]bool{}
			seen[idx] = true
		} else {
			cur += string(c)
			seen[idx] = true
		}
	}
	if cur != "" {
		ans = append(ans, cur)
	}
	return ans
}
func main() {

}
