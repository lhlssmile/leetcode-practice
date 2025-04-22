package main

import "fmt"

func isValid(s string) bool {
	if len(s)%2 != 0 {
		return false
	}
	mp := map[rune]rune{
		')': '(',
		']': '[',
		'}': '{',
	}
	st := []rune{}
	for _, c := range s {
		if mp[c] == 0 {
			st = append(st, c)
		} else {
			if len(st) == 0 || st[len(st)-1] != mp[c] {
				return false
			}
			st = st[:len(st)-1]
		}
	}
	return len(st) == 0
}

func main() {
	s := "(())"
	result := isValid(s)
	fmt.Println(result)
}
