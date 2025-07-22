/*
LeetCode 17. 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

示例 1：
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

示例 2：
输入：digits = ""
输出：[]

示例 3：
输入：digits = "2"
输出：["a","b","c"]
*/

package main

import (
	"fmt"
	"strings"
)

// Solution 解决方案结构体
type Solution struct{}

// letterCombinations 回溯算法实现
func (s *Solution) letterCombinations(digits string) []string {
	// 数字到字母的映射
	mapping := map[byte]string{
		'2': "abc",
		'3': "def",
		'4': "ghi",
		'5': "jkl",
		'6': "mno",
		'7': "pqrs",
		'8': "tuv",
		'9': "wxyz",
	}

	// 边界条件
	if len(digits) == 0 {
		return []string{}
	}

	var result []string
	var path []byte // 使用字节切片构建路径

	// 回溯函数
	var backtrack func(index int)
	backtrack = func(index int) {
		// 递归终止条件
		if index == len(digits) {
			result = append(result, string(path))
			return
		}

		// 获取当前数字对应的字母
		digit := digits[index]
		letters := mapping[digit]

		// 遍历所有可能的字母
		for i := 0; i < len(letters); i++ {
			// 选择
			path = append(path, letters[i])
			// 递归
			backtrack(index + 1)
			// 回滚
			path = path[:len(path)-1]
		}
	}

	backtrack(0)
	return result
}

// letterCombinationsIterative 迭代实现（队列BFS）
func (s *Solution) letterCombinationsIterative(digits string) []string {
	mapping := map[byte]string{
		'2': "abc", '3': "def", '4': "ghi", '5': "jkl",
		'6': "mno", '7': "pqrs", '8': "tuv", '9': "wxyz",
	}

	if len(digits) == 0 {
		return []string{}
	}

	// 初始化队列
	queue := []string{""}

	// 逐个处理数字
	for _, digit := range digits {
		letters := mapping[byte(digit)]
		var nextQueue []string

		// 处理队列中的每个组合
		for _, combination := range queue {
			// 为每个字母创建新组合
			for _, letter := range letters {
				nextQueue = append(nextQueue, combination+string(letter))
			}
		}
		queue = nextQueue
	}

	return queue
}

// letterCombinationsDebug 带调试信息的回溯版本
func (s *Solution) letterCombinationsDebug(digits string) []string {
	mapping := map[byte]string{
		'2': "abc", '3': "def", '4': "ghi", '5': "jkl",
		'6': "mno", '7': "pqrs", '8': "tuv", '9': "wxyz",
	}

	fmt.Printf("\n=== 开始回溯调试: digits = '%s' ===\n", digits)

	if len(digits) == 0 {
		fmt.Println("输入为空，返回空切片")
		return []string{}
	}

	var result []string
	var path []byte
	combinationCount := 0

	var backtrack func(index int, depth string)
	backtrack = func(index int, depth string) {
		fmt.Printf("%s进入 backtrack(index=%d), 当前路径: %s\n", depth, index, string(path))

		// 递归终止条件
		if index == len(digits) {
			combinationCount++
			combination := string(path)
			result = append(result, combination)
			fmt.Printf("%s✅ 找到组合 #%d: '%s'\n", depth, combinationCount, combination)
			return
		}

		// 获取当前数字对应的字母
		digit := digits[index]
		letters := mapping[digit]
		fmt.Printf("%s处理数字 '%c', 对应字母: '%s'\n", depth, digit, letters)

		// 遍历所有可能的字母
		for i, letter := range letters {
			fmt.Printf("%s选择字母 '%c' (%d/%d)\n", depth, letter, i+1, len(letters))

			// 选择
			path = append(path, byte(letter))
			fmt.Printf("%s路径更新: %s\n", depth, string(path))

			// 递归
			backtrack(index+1, depth+"  ")

			// 回滚
			path = path[:len(path)-1]
			fmt.Printf("%s回滚: 移除 '%c', 路径恢复: %s\n", depth, letter, string(path))
		}
	}

	backtrack(0, "")
	fmt.Printf("=== 调试结束，共找到 %d 个组合 ===\n", len(result))
	return result
}

// 测试函数
func testLetterCombinations() {
	solution := &Solution{}

	fmt.Println("🧪 Go语言回溯算法测试 - 电话号码字母组合")
	fmt.Println(strings.Repeat("=", 60))

	// 测试用例
	testCases := []struct {
		digits   string
		expected int // 期望的组合数量
	}{
		{"23", 9},
		{"", 0},
		{"2", 3},
		{"234", 27},
	}

	for i, tc := range testCases {
		fmt.Printf("\n📝 测试用例 %d: digits = '%s'\n", i+1, tc.digits)

		// 回溯算法
		backtrackResult := solution.letterCombinations(tc.digits)
		fmt.Printf("回溯算法结果: %v\n", backtrackResult)
		fmt.Printf("结果数量: %d\n", len(backtrackResult))

		// 迭代算法
		iterativeResult := solution.letterCombinationsIterative(tc.digits)
		fmt.Printf("迭代算法结果: %v\n", iterativeResult)

		// 验证结果一致性
		if len(backtrackResult) == len(iterativeResult) {
			fmt.Println("✅ 两种方法结果数量一致")
		} else {
			fmt.Println("❌ 两种方法结果数量不一致！")
		}

		fmt.Println(strings.Repeat("-", 50))
	}

	// 调试版本演示
	fmt.Printf("\n🔍 调试版本演示: digits = '23'\n")
	debugResult := solution.letterCombinationsDebug("23")
	fmt.Printf("调试结果: %v\n", debugResult)
}

// 算法分析
func algorithmAnalysis() {
	fmt.Println("\n📊 算法分析")
	fmt.Println(strings.Repeat("=", 40))

	fmt.Println("\n🎯 回溯算法核心思想:")
	principles := []string{
		"1. 选择：从当前数字对应的字母中选择一个",
		"2. 递归：处理下一个数字",
		"3. 回滚：撤销当前选择，尝试其他可能",
		"4. 剪枝：当处理完所有数字时，记录结果",
	}
	for _, principle := range principles {
		fmt.Printf("  %s\n", principle)
	}

	fmt.Println("\n⚡ 复杂度分析:")
	fmt.Println("  时间复杂度: O(3^m × 4^n)")
	fmt.Println("    其中 m 是对应3个字母的数字个数，n 是对应4个字母的数字个数")
	fmt.Println("  空间复杂度: O(3^m × 4^n)")
	fmt.Println("    用于存储所有组合结果")

	fmt.Println("\n🔧 Go语言特性应用:")
	features := []string{
		"• 使用 []byte 构建路径，避免字符串频繁拼接",
		"• 利用切片的 append 和切片操作实现回滚",
		"• 使用 map[byte]string 进行数字到字母的映射",
		"• 闭包函数实现递归回溯",
		"• 结构体方法组织代码",
	}
	for _, feature := range features {
		fmt.Printf("  %s\n", feature)
	}
}

func main() {
	// 运行测试
	testLetterCombinations()

	// 算法分析
	algorithmAnalysis()

	fmt.Println("\n🎉 Go语言回溯算法学习完成！")
}