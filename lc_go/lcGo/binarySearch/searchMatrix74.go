package main

import "fmt"

func searchMatrix(matrix [][]int, target int) bool {
	m, n := len(matrix), len(matrix[0])
	left, right := 0, m*n

	for left < right {
		mid := left + (right-left)/2
		row := mid / n
		col := mid % n
		if matrix[row][col] == target {
			return true
		} else if matrix[row][col] > target {
			right = mid
		} else {
			left = mid + 1
		}
	}
	return false
}

func main() {
	matrix := [][]int{
		{1, 3, 5, 7},
		{10, 11, 16, 20},
		{23, 30, 34, 60},
	}
	target := 3
	res := searchMatrix(matrix, target)
	fmt.Println(res)
}
