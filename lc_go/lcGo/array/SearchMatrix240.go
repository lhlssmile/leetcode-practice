package main

import "fmt"

func searchMatrix(matrix [][]int,target int) bool {
	m,n := len(matrix),len(matrix[0])
	row,column := m - 1,0

	for row >= 0 && column < n {
		if matrix[row][column] == target {
			return true
		}else if matrix[row][column] > target {
			row--
		}else {
			column++
		}
	} 
		return false
}

func main(){
	matrix := [][]int{
		{1,4,7,11,15},
                {2,5,8,12,19},
                {3,6,9,16,22},
                {10,13,14,17,24},
                {18,21,23,26,30}
	}
	target := 20
	res := searchMatrix(matrix,target)
	fmt.Println(res)
}