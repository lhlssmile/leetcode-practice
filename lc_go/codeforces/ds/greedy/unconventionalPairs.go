package main

import (
	"fmt"
	"math"
	"slices"
)

var (
	t, n int
)

func main() {
	fmt.Scan(&t)
	for ; t > 0; t-- {
		fmt.Scan(&n)
		a := make([]int64, n)
		for i := 0; i < n; i++ {
			fmt.Scan(&a[i])
		}
		slices.Sort(a)
		var res int64 = math.MinInt64
		for i := 1; i < n; i += 2 {
			d := a[i] - a[i-1]
			if d > res {
				res = d
			}
		}
		fmt.Println(res)
	}
}
