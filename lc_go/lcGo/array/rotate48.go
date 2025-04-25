package main

import "fmt"

func rotate(matrix [][]int) {
    n := len(matrix)

    // Step 1: 转置
    for i := 0; i < n; i++ {
        for j := i + 1; j < n; j++ {
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
        }
    }

    // Step 2: 每一行反转
    for i := 0; i < n; i++ {
        reverse(matrix[i])
    }
}

func reverse(row []int) {
    left, right := 0, len(row)-1
    for left < right {
        row[left], row[right] = row[right], row[left]
        left++
        right--
    }
}

func main(){
	matrix := [][]int{
		{1,2,3},
		{4,5,6},
		{7,8,9},
	}
	rotate(matrix)
	fmt.Println(matrix)
}