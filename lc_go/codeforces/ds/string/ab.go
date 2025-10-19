package main

import (
	"fmt"
	"slices"
)

func abs(x int64) int64 {
	if x < 0 {
		return -x
	}
	return x
}

func solve(s []byte, c byte) int64 {
	pos := []int{}
	for i, b := range s {
		if b == c {
			pos = append(pos, i)
		}
	}
	if len(pos) == 0 {
		return 0
	}

	shifted := make([]int64, len(pos))
	for i := range pos {
		shifted[i] = int64(pos[i] - i)
	}
	slices.Sort(shifted)
	m := shifted[len(shifted)/2]

	var res int64
	for _, x := range shifted {
		res += abs(x - m)
	}
	return res
}

func min(a, b int64) int64 {
	if a < b {
		return a
	}
	return b
}

func main() {
	var t int
	fmt.Scan(&t)
	for i := 0; i < t; i++ {
		var n int
		var s string
		fmt.Scan(&n, &s)
		fmt.Println(min(solve([]byte(s), 'a'), solve([]byte(s), 'b')))
	}
}
