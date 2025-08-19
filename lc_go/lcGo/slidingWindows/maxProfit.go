package main

func maxProfit(prices []int, strategy []int, k int) int64 {
	n, maxChange, currentChange, originalProfit := len(prices), 0, 0, 0

	for i := 0; i < n; i++ {
		originalProfit += (strategy[i] * prices[i])
	}

	for i := 0; i < k/2; i++ {
		currentChange += -strategy[i] * prices[i]
	}
	for i := k / 2; i < k; i++ {
		currentChange += (1 - strategy[i]) * prices[i]
	}
	maxChange = currentChange
	for i := 1; i < n-k+1; i++ {
		j := i - 1
		currentChange -= -strategy[j] * prices[j]

		jMid := i + k/2 - 1

		currentChange -= (1 - strategy[jMid]) * prices[jMid]
		currentChange += -strategy[jMid] * prices[jMid]

		jNew := i + k - 1

		currentChange += (1 - strategy[jNew]) * prices[jNew]
		maxChange = max(currentChange, maxChange)
	}
	return int64(originalProfit + max(0, maxChange))
}
func main() {

}
