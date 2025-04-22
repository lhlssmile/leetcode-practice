package main

import "fmt"

func rowAndMaximumOnes(mat [][]int) []int {
	m := len(mat)
	n := len(mat[0])
	max_ones := 0
	min_row_subscript := 0

	for i := 0; i < m; i++ {
		curr_ones := 0
		for j := 0; j < n; j++ {
			if mat[i][j] == 1 {
				curr_ones += 1
			}
		}
		if curr_ones > max_ones {
			max_ones = curr_ones
			min_row_subscript = i
		}
	}
	return []int{min_row_subscript, max_ones}
}
func way2(mat [][]int) []int {
	rowIdx, maxSum := -1, -1

	for i, row := range mat {
		s := 0
		for _, x := range row {
			s += x
		}
		if s > maxSum {
			rowIdx, maxSum = i, s
		}
	}
	return []int{rowIdx, maxSum}
}

func main() {
	mat := [][]int{{0, 1}, {0, 1}}
	res := rowAndMaximumOnes(mat)
	fmt.Println(res)

}
