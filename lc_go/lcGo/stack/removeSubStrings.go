package main

type pair struct {
	c byte
	k int
}

func removeSubstrings(s string, k int) string {
	st := []pair{}

	for i := 0; i < len(s); i++ {
		b := s[i]
		if len(st) > 0 && st[len(st)-1].c == s[i] {
			st[len(st)-1].k++
		} else {
			st = append(st, pair{c: b, k: 1})
		}
		if len(st) >= 2 && st[len(st)-1].c == ')' && st[len(st)-1].k >= k && st[len(st)-2].c == '(' && st[len(st)-2].k >= k {
			st[len(st)-1].k -= k
			if st[len(st)-1].k == 0 {
				st = st[:len(st)-1]
			}
			st[len(st)-2].k -= k
			if st[len(st)-2].k == 0 {
				st = st[:len(st)-2]
			}
		}

	}
	ans := make([]byte, 0, len(s))
	for _, e := range st {
		for j := 0; j < e.k; j++ {
			ans = append(ans, e.c)
		}
	}
	return string(ans)
}

func main() {

}
