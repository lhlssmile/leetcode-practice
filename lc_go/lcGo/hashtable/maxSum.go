package main

import (
	"fmt"
	"math"
)

// maxSum 删除任意数量元素后，找到元素互不相同的连续非空子数组的最大和
// 约束：1 <= nums.length <= 100, -100 <= nums[i] <= 100
func maxSum(nums []int) int {
	n := len(nums)
	maxResult := math.MinInt32
	
	// 枚举所有可能的删除方案（位运算）
	for mask := 1; mask < (1 << n); mask++ {
		// 构建保留元素的子数组
		var subArray []int
		for i := 0; i < n; i++ {
			if (mask & (1 << i)) != 0 {
				subArray = append(subArray, nums[i])
			}
		}
		
		// 在子数组中找最大无重复连续子数组和
		currentMax := findMaxUniqueSubarray(subArray)
		if currentMax > maxResult {
			maxResult = currentMax
		}
	}
	
	return maxResult
}

// findMaxUniqueSubarray 在给定数组中找到元素互不相同的连续子数组的最大和
func findMaxUniqueSubarray(arr []int) int {
	if len(arr) == 0 {
		return math.MinInt32
	}
	
	maxSum := math.MinInt32
	
	// 枚举所有可能的起始位置
	for i := 0; i < len(arr); i++ {
		seen := make(map[int]bool)
		currentSum := 0
		
		// 从位置i开始向右扩展
		for j := i; j < len(arr); j++ {
			// 如果遇到重复元素，停止扩展
			if seen[arr[j]] {
				break
			}
			
			seen[arr[j]] = true
			currentSum += arr[j]
			
			// 更新最大值
			if currentSum > maxSum {
				maxSum = currentSum
			}
		}
	}
	
	return maxSum
}

// 测试函数
func testSolution() {
	testCases := []struct {
		nums     []int
		expected int
	}{
		{[]int{1, 2, 3, 4, 5}, 15},           // 不删除任何元素
		{[]int{1, 1, 0, 1, 1}, 1},            // 删除重复元素
		{[]int{2, -10, 6}, 8},                // 删除负数，保留[2,6]
		{[]int{-1, -2, -3}, -1},              // 全负数，选择最大的单个元素
		{[]int{5, 4, 2, 4, 9, 6}, 23},        // 删除重复的4，保留[5,2,9,6]
	}
	
	for i, tc := range testCases {
		result := maxSum(tc.nums)
		fmt.Printf("测试用例 %d: nums=%v, 期望=%d, 实际=%d", i+1, tc.nums, tc.expected, result)
		if result == tc.expected {
			fmt.Println(" ✓")
		} else {
			fmt.Println(" ✗")
		}
	}
}

func main() {
	// 运行测试
	testSolution()
	
	// 单独测试用户提到的用例
	fmt.Println("\n=== 单独测试 ===")
	nums := []int{2, -10, 6}
	result := maxSum(nums)
	fmt.Printf("maxSum(%v) = %d\n", nums, result)
}
