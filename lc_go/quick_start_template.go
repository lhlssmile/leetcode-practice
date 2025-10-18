package main

import (
	"fmt"
	"strings"
)

/*
LeetCode Go 快速开始模板
使用方法:
1. 复制这个模板到新文件
2. 修改函数名和实现逻辑
3. 在main函数中添加测试用例
4. 按 Ctrl+F5 运行或点击右上角运行按钮
*/

// sampleProblem 示例问题：找到数组中的最大值
func sampleProblem(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	
	maxVal := nums[0]
	for i := 1; i < len(nums); i++ {
		if nums[i] > maxVal {
			maxVal = nums[i]
		}
	}
	
	return maxVal
}

// testCase 测试用例结构
type testCase struct {
	input    []int
	expected int
	desc     string
}

// runTests 运行所有测试用例
func runTests() {
	tests := []testCase{
		{[]int{1, 3, 2, 5, 4}, 5, "正常数组"},
		{[]int{-1, -3, -2}, -1, "负数数组"},
		{[]int{}, 0, "空数组"},
		{[]int{42}, 42, "单元素数组"},
	}
	
	passed := 0
	total := len(tests)
	
	for i, test := range tests {
		result := sampleProblem(test.input)
		fmt.Printf("测试 %d (%s):\n", i+1, test.desc)
		fmt.Printf("  输入: %v\n", test.input)
		fmt.Printf("  期望: %d\n", test.expected)
		fmt.Printf("  实际: %d\n", result)
		
		if result == test.expected {
			fmt.Printf("  ✅ 通过\n\n")
			passed++
		} else {
			fmt.Printf("  ❌ 失败\n\n")
		}
	}
	
	fmt.Printf("测试结果: %d/%d 通过\n", passed, total)
	if passed == total {
		fmt.Println("🎉 所有测试通过!")
	} else {
		fmt.Println("❌ 部分测试失败")
	}
}

// 常用工具函数

// max 返回两个整数中的较大值
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// min 返回两个整数中的较小值
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// abs 返回整数的绝对值
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

// reverse 反转整数切片
func reverse(nums []int) {
	for i, j := 0, len(nums)-1; i < j; i, j = i+1, j-1 {
		nums[i], nums[j] = nums[j], nums[i]
	}
}

func main() {
	fmt.Println("🐹 Go LeetCode 快速开始模板")
	fmt.Println(strings.Repeat("=", 40))
	
	runTests()
}