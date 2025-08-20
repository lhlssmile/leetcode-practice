package main

func findCoins(numWays []int) []int {
	n := len(numWays)
	f := make([]int, n+1)
	f[0] = 1
	ans := []int{}

	for i := 1; i <= n; i++ {
		ways := numWays[i-1]
		if ways == f[i] {
			continue
		}
		if ways-1 != f[i] {
			return nil
		}
		ans = append(ans, i)
		for c := i; c <= n; c++ {
			f[c] += f[c-i]
		}
	}
	return ans
}
func main() {
	numWays := []int{1, 2, 2, 3, 4}
	findCoins(numWays)
}
