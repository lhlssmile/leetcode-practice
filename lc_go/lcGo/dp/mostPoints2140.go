package main

import "fmt"

func mostPoints(questions [][]int) int64 {
	n := len(questions)
	dp := make([]int64, n+1)
	for i := 0; i <= n; i++ {
		dp[i] = 0
	}
	for i := n - 1; i >= 0; i-- {
		points := questions[i][0]
		brainPower := questions[i][1]
		next := i + brainPower + 1

		if next > n { //越界了 只能拿当前的分数
			dp[i] = max(dp[i+1], (int64(points)))
		} else {
			dp[i] = max(dp[i+1], (int64(points))+dp[next])
		}
	}
	return dp[0]
}

func main() {
	questions := [][]int{
		{3, 2},
		{4, 3},
		{4, 4},
		{2, 5},
	}
	res := mostPoints(questions)
	fmt.Println(res)
}
