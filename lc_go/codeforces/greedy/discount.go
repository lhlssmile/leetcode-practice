package main

import (
	"fmt"
	"sort"
)

func solve(prices []int64, vouchers []int) int64 {
	sort.Slice(prices, func(i, j int) bool { return prices[i] < prices[j] })
	sort.Ints(vouchers)
	s := int64(0)
	for _, x := range prices {
		s += x
	}
	nn := len(prices)
	for _, vi := range vouchers {
		if nn < vi {
			break
		}
		s -= prices[nn-vi]
		nn -= vi
	}
	return s
}

func main() {
	var t, n, k int
	fmt.Scan(&t)
	for ; t > 0; t-- {
		fmt.Scan(&n, &k)
		prices := make([]int64, n)
		for i := 0; i < n; i++ {
			fmt.Scan(&prices[i])
		}
		vouchers := make([]int, k)
		for i := 0; i < k; i++ {
			fmt.Scan(&vouchers[i])
		}
		fmt.Println(solve(prices, vouchers))
	}
}
