package main

import "fmt"

const N int = 101

var (
	t, n int
)

func solve(a []int) int {
	st := make(map[int]struct{})
	for _, x := range a {
		st[x] = struct{}{}
	}
	k := len(st)
	return 2*k - 1

}
func main() {
	fmt.Scan(&t)

	for ; t > 0; t-- {
		fmt.Scan(&n)
		a := make([]int, n)

		for i := 0; i < n; i++ {
			fmt.Scan(&a[i])
		}
		fmt.Println(solve(a))
	}
}
