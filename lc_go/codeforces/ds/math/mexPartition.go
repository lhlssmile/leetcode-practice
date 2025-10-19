package main

import (
	"fmt"
)

var (
	t, n int
	a    []int
)

func solve(a []int) int {
	var mex int = 0
	// n := len(a)
	cnt := make([]int, 102)
	for _, x := range a {
		cnt[x]++
	}
	for i := 0; i <= 101; i++ {
		if cnt[i] == 0 {
			mex = i
			break
		}
	}
	return mex
}
func main() {
	fmt.Scan(&t)
	for ; t > 0; t-- {
		fmt.Scan(&n)
		a = make([]int, n)
		for i := 0; i < n; i++ {
			fmt.Scan(&a[i])
		}
		fmt.Println(solve(a))
	}

}
