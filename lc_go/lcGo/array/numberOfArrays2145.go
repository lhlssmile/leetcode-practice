package main

import "fmt"

func numberOfArrays(differences []int, lower, upper int) int {
	var s, minS, maxS int // s[0] = 0
	for _, d := range differences {
		s += d
		minS = min(minS, s)
		maxS = max(maxS, s)
	}
	return max(upper-lower-maxS+minS+1, 0)
}

func main() {
	differences := []int{3, -4, 5, 1, -2}
	lower, upper := -4, 5
	res := numberOfArrays(differences, lower, upper)
	fmt.Println(res)
}
