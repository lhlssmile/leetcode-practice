package main

import (
	"math"
	"sort"
)

func minCost(basket1, basket2 []int) int64 {
	// 统计频次
	totalCnt := make(map[int64]int)
	for _, x := range basket1 {
		totalCnt[int64(x)]++
	}
	for _, x := range basket2 {
		totalCnt[int64(x)]++
	}

	// 检查是否可均分
	for _, cnt := range totalCnt {
		if cnt%2 != 0 {
			return -1
		}
	}

	// 计算需要交换的元素
	cnt1, cnt2 := make(map[int64]int), make(map[int64]int)
	for _, x := range basket1 {
		cnt1[int64(x)]++
	}
	for _, x := range basket2 {
		cnt2[int64(x)]++
	}
	var swaps []int64
	for val, _ := range totalCnt {
		diff := cnt1[val] - cnt2[val]
		if diff > 0 {
			for i := 0; i < diff/2; i++ {
				swaps = append(swaps, val)
			}
		} else if diff < 0 {
			for i := 0; i < -diff/2; i++ {
				swaps = append(swaps, val)
			}
		}
	}

	// 排序并计算成本
	sort.Slice(swaps, func(i, j int) bool { return swaps[i] < swaps[j] })
	n := len(swaps) / 2
	minVal := int64(math.MaxInt64)
	for _, x := range basket1 {
		if int64(x) < minVal {
			minVal = int64(x)
		}
	}
	for _, x := range basket2 {
		if int64(x) < minVal {
			minVal = int64(x)
		}
	}

	var totalCost int64
	for i := 0; i < n; i++ {
		x, y := swaps[n-1-i], swaps[n+i]
		totalCost += min(x, y, 2*minVal) // 直接交换或用min_val中介
	}

	return totalCost
}

// 辅助函数：取三者最小值
func min(a, b, c int64) int64 {
	if a <= b && a <= c {
		return a
	}
	if b <= a && b <= c {
		return b
	}
	return c
}
