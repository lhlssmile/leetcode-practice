package main

import "fmt"

func findMatrix(nums []int) [][]int {
	// 统计频率
	freq := make(map[int]int)
	for _, num := range nums {
		freq[num]++
	}

	// 构造二维数组
	var result [][]int
	for len(freq) > 0 {
		currentRow := []int{}
		// 临时记录当前行使用的元素
		used := make(map[int]bool)

		// 遍历频率表
		for num := range freq {
			if !used[num] {
				currentRow = append(currentRow, num)
				used[num] = true
				freq[num]--
				if freq[num] == 0 {
					delete(freq, num)
				}
			}
		}
		result = append(result, currentRow)
	}

	return result
}

func findMatrix1(nums []int) [][]int {
	freq := make(map[int]int)
	maxFreq := 0
	//用 range 遍历 nums，_ 表示忽略索引。
	for _, num := range nums {
		freq[num]++
		if freq[num] > maxFreq {
			maxFreq = freq[num]
		}
	}

	result := make([][]int, maxFreq)
	for i := range result {
		result[i] = []int{} // 初始化每一行为空切片
	}

	// 将每个元素按频率分配到行中
	for num, count := range freq {
		for i := 0; i < count; i++ {
			result[i] = append(result[i], num)
		}
	}
	return result
}

func main() {
	nums := []int{1, 3, 4, 1, 2, 3, 1}
	result := findMatrix1(nums)
	fmt.Println(result) // 输出: [[1 3 4 2] [1 3] [1]]
}
