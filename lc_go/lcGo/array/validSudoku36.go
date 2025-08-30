package main

import "fmt"

/*
LeetCode 36. 有效的数独

请你判断一个 9 x 9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
1. 数字 1-9 在每一行只能出现一次。
2. 数字 1-9 在每一列只能出现一次。
3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

注意：
- 一个有效的数独（部分已填充）不一定是可解的。
- 只需要根据以上规则，验证已经填入的数字是否有效即可。
- 空白格用 '.' 表示。
*/

// isValidSudoku 使用位运算检查数独是否有效
// 时间复杂度: O(n²)，其中 n = 9 是数独的大小
// 空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
func isValidSudoku(board [][]byte) bool {
	// 检查行
	for i := 0; i < 9; i++ {
		mask := 0
		for j := 0; j < 9; j++ {
			if board[i][j] == '.' {
				continue
			}
			num := int(board[i][j] - '0')
			if mask&(1<<num) != 0 {
				return false
			}
			mask |= (1 << num)
		}
	}

	// 检查列
	for j := 0; j < 9; j++ {
		mask := 0
		for i := 0; i < 9; i++ {
			if board[i][j] == '.' {
				continue
			}
			num := int(board[i][j] - '0')
			if mask&(1<<num) != 0 {
				return false
			}
			mask |= (1 << num)
		}
	}

	// 检查 3×3 宫
	for block := 0; block < 9; block++ {
		mask := 0
		for i := 0; i < 3; i++ {
			for j := 0; j < 3; j++ {
				r := (block/3)*3 + i
				c := (block%3)*3 + j
				if board[r][c] == '.' {
					continue
				}
				num := int(board[r][c] - '0')
				if mask&(1<<num) != 0 {
					return false
				}
				mask |= (1 << num)
			}
		}
	}

	return true
}

// isValidSudokuMap 使用哈希表检查数独是否有效（替代方案）
// 时间复杂度: O(n²)，其中 n = 9 是数独的大小
// 空间复杂度: O(n²)，使用了哈希表来存储每行、每列和每个3x3宫格中的数字
func isValidSudokuMap(board [][]byte) bool {
	// 初始化行、列和块的哈希表
	rows := make([]map[byte]bool, 9)
	cols := make([]map[byte]bool, 9)
	boxes := make([]map[byte]bool, 9)

	for i := 0; i < 9; i++ {
		rows[i] = make(map[byte]bool)
		cols[i] = make(map[byte]bool)
		boxes[i] = make(map[byte]bool)
	}

	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			if board[i][j] == '.' {
				continue
			}

			num := board[i][j]
			boxIdx := (i/3)*3 + j/3

			// 检查是否已在行、列或块中出现
			if rows[i][num] || cols[j][num] || boxes[boxIdx][num] {
				return false
			}

			// 添加到哈希表中
			rows[i][num] = true
			cols[j][num] = true
			boxes[boxIdx][num] = true
		}
	}

	return true
}

func main() {
	validBoard := [][]byte{
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'},
	}

	invalidBoard := [][]byte{
		{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'},
	}

	fmt.Println("Valid board (bit method):", isValidSudoku(validBoard))
	fmt.Println("Invalid board (bit method):", isValidSudoku(invalidBoard))

	fmt.Println("Valid board (map method):", isValidSudokuMap(validBoard))
	fmt.Println("Invalid board (map method):", isValidSudokuMap(invalidBoard))
}