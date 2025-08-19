package main

import "math"

func minSwaps(nums []int) int {
	var evenPos, oddPos []int
	for i, x := range nums {
		if x%2 == 0 {
			evenPos = append(evenPos, i)
		} else {
			oddPos = append(oddPos, i)
		}
	}

	evenCnt, oddCnt := len(evenPos), len(oddPos)
	if abs(evenCnt-oddCnt) > 1 {
		return -1
	}

	res := math.MaxInt32

	// 偶数开头
	if evenCnt >= oddCnt {
		cost := 0
		for i := 0; i < evenCnt; i++ {
			target := i * 2
			cost += abs(evenPos[i] - target)
		}
		res = int(math.Min(float64(res), float64(cost)))
	}

	// 奇数开头
	if oddCnt >= evenCnt {
		cost := 0
		for i := 0; i < oddCnt; i++ {
			target := i * 2
			cost += abs(oddPos[i] - target)
		}
		res = int(math.Min(float64(res), float64(cost)))
	}

	return res
}

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}

func main() {
	nums := []int{1, 2, 3, 4, 5}
	println(minSwaps(nums))
}
