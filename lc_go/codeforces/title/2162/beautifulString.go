package main

import (
	"fmt"
)

func isPalindrome(s []byte) bool {
	l, r := 0, len(s)-1
	for l < r {
		if s[l] != s[r] {
			return false
		}
		l++
		r--
	}
	return true
}

func isNotDecreasing(s []byte) bool {
	for i := 1; i < len(s); i++ {
		if s[i] < s[i-1] {
			return false
		}
	}
	return true
}

func solve(s []byte) (int, []int) {
	n := len(s)
	for mask := 0; mask < (1 << n); mask++ {
		var p, x []byte
		var idx []int
		for i := 0; i < n; i++ {
			if (mask>>i)&1 == 1 {
				p = append(p, s[i])
				idx = append(idx, i+1)
			} else {
				x = append(x, s[i])
			}
		}
		if isNotDecreasing(p) && isPalindrome(x) {
			return len(idx), idx
		}
	}
	return -1, nil
}

func main() {
	var t, n int
	fmt.Scan(&t)
	for ; t > 0; t-- {
		fmt.Scan(&n)
		var s string
		fmt.Scan(&s)
		k, idx := solve([]byte(s))
		if k == -1 {
			fmt.Println(-1)
		} else {
			fmt.Println(k)
			if k > 0 {
				for i, v := range idx {
					if i > 0 {
						fmt.Print(" ")
					}
					fmt.Print(v)
				}
				fmt.Println()
			}
		}
	}
}
