package main

func deleteAndEarn(nums []int) int {
	maxVal := 0

	counts := make(map[int]int)

	for _, x := range nums {
		maxVal = max(maxVal, x)
		counts[x] += x
