package main

import (
	"fmt"
)

const N = 100005

var (
	t, n int
	b    [N]int64
	a    [N]int
	val  int
)

func main() {
	fmt.Scan(&t)
	for ; t > 0; t-- {
		fmt.Scan(&n)
		for i := 1; i <= n; i++ {
			fmt.Scan(&b[i])
		}
		val = 1
		a[1] = val
		val++
		for i := 2; i <= n; i++ {
			d := b[i] - b[i-1]
			p := int64(i) - d
			if p == 0 {
				a[i] = val
				val++
			} else {
				a[i] = a[p]
			}
		}
		for i := 1; i <= n; i++ {
			if i > 1 {
				fmt.Print(" ")
			}
			fmt.Print(a[i])
		}
		fmt.Println()
	}
}
