package main

import (
	"fmt"
	"math"
)

func numberOfWays(n int, x int) int {
	const MOD = 1_000_000_007

	powers := []int{}

	for base := 1; int(math.Pow(float64(base), float64(x))) <= n; base++ {
		p := int(math.Pow(float64(base), float64(x)))
		powers = append(powers, p)
	}
	dp := make([]int, n+1)
	dp[0] = 1

	for _, p := range powers {
		for s := n; s >= p; s-- {
			dp[s] = (dp[s] + dp[s-p]) % MOD
		}
	}
	return dp[n]
}

func main() {
	n, x := 10, 2
	fmt.Println(numberOfWays(n, x))

}
