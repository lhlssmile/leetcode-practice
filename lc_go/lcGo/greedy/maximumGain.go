// 删除子字符串 - 贪心算法 + 栈
// 关键思路：优先删除分数更高的子串，用栈模拟删除过程

package main

import (
	"fmt"
)

// Solution 解决方案结构体
type Solution struct{}

// maximumGain 标准贪心+栈解法
func (s *Solution) maximumGain(str string, x int, y int) int {
	// 贪心策略：优先删除分数更高的子串
	if x >= y {
		// ab分数更高，先删ab再删ba
		score1 := s.removeSubstring(&str, 'a', 'b', x)
		score2 := s.removeSubstring(&str, 'b', 'a', y)
		return score1 + score2
	} else {
		// ba分数更高，先删ba再删ab
		score1 := s.removeSubstring(&str, 'b', 'a', y)
		score2 := s.removeSubstring(&str, 'a', 'b', x)
		return score1 + score2
	}
}

// maximumGainOptimized 优化版本 - 一次性处理
func (s *Solution) maximumGainOptimized(str string, x int, y int) int {
	// 确保x >= y，简化逻辑
	first, second := byte('a'), byte('b')
	if x < y {
		x, y = y, x
		first, second = second, first
	}
	stack := make([]byte, 0)
	score := 0

	// 第一次遍历：删除高分子串
	for i := 0; i < len(str); i++ {
		c := str[i]
		if len(stack) > 0 && stack[len(stack)-1] == first && c == second {
			stack = stack[:len(stack)-1] // pop
			score += x                   // 高分
		} else {
			stack = append(stack, c) // push
		}
	}

	// 第二次遍历：删除低分子串
	remaining := stack
	stack = make([]byte, 0)
	for _, c := range remaining {
		if len(stack) > 0 && stack[len(stack)-1] == second && c == first {
			stack = stack[:len(stack)-1] // pop
			score += y                   // 低分
		} else {
			stack = append(stack, c) // push
		}
	}

	return score
}

// maximumGainDetailed 详细版本 - 带调试信息
func (s *Solution) maximumGainDetailed(str string, x int, y int) int {
	fmt.Printf("输入字符串: %s\n", str)
	fmt.Printf("ab得分: %d, ba得分: %d\n", x, y)

	if x >= y {
		fmt.Println("策略: ab分数更高，先删ab再删ba")
		score1 := s.removeSubstringDebug(&str, 'a', 'b', x, "ab")
		score2 := s.removeSubstringDebug(&str, 'b', 'a', y, "ba")
		fmt.Printf("最终结果: %d + %d = %d\n", score1, score2, score1+score2)
		return score1 + score2
	} else {
		fmt.Println("策略: ba分数更高，先删ba再删ab")
		score1 := s.removeSubstringDebug(&str, 'b', 'a', y, "ba")
		score2 := s.removeSubstringDebug(&str, 'a', 'b', x, "ab")
		fmt.Printf("最终结果: %d + %d = %d\n", score1, score2, score1+score2)
		return score1 + score2
	}
}

// removeSubstring 删除指定子串的辅助函数
func (s *Solution) removeSubstring(str *string, first byte, second byte, points int) int {
	stack := make([]byte, 0)
	score := 0

	for i := 0; i < len(*str); i++ {
		c := (*str)[i]
		if len(stack) > 0 && stack[len(stack)-1] == first && c == second {
			stack = stack[:len(stack)-1] // pop
			score += points
		} else {
			stack = append(stack, c) // push
		}
	}

	// 更新字符串为剩余字符
	*str = string(stack)
	return score
}

// removeSubstringDebug 带调试信息的删除函数
func (s *Solution) removeSubstringDebug(str *string, first byte, second byte, points int, name string) int {
	stack := make([]byte, 0)
	score := 0
	removedCount := 0

	fmt.Printf("\n开始删除 %s (分数: %d)\n", name, points)
	fmt.Printf("处理字符串: %s\n", *str)

	for i := 0; i < len(*str); i++ {
		c := (*str)[i]
		if len(stack) > 0 && stack[len(stack)-1] == first && c == second {
			stack = stack[:len(stack)-1] // pop
			score += points
			removedCount++
			fmt.Printf("  位置%d: 删除%c%c, 得分+%d, 总分:%d\n", i, first, second, points, score)
		} else {
			stack = append(stack, c) // push
		}
	}

	// 更新字符串
	*str = string(stack)
	fmt.Printf("删除%d个%s, 得分:%d\n", removedCount, name, score)
	fmt.Printf("剩余字符串: %s\n", *str)

	return score
}

// testMaximumGain 测试函数
func testMaximumGain() {
	solution := &Solution{}

	testCases := []struct {
		s string
		x int
		y int
	}{
		{"cdbcbbaaabab", 4, 5},   // 示例1
		{"aabbaaxybbaabb", 5, 4}, // 示例2
		{"aabb", 1, 2},
		{"abab", 3, 4},
		{"baba", 2, 5},
	}

	fmt.Println("=== 最大得分测试 ===")
	for _, testCase := range testCases {
		result := solution.maximumGain(testCase.s, testCase.x, testCase.y)
		fmt.Printf("输入: s='%s', x=%d, y=%d -> 输出: %d\n", testCase.s, testCase.x, testCase.y, result)
	}

	fmt.Println("\n=== 详细过程演示 ===")
	solution.maximumGainDetailed("aabbaaxybbaabb", 5, 4)
}

// analyzeComplexity 算法复杂度分析
func analyzeComplexity() {
	fmt.Println("\n=== 算法复杂度分析 ===")
	fmt.Println("时间复杂度: O(n)")
	fmt.Println("  - 两次遍历字符串: 2 * O(n)")
	fmt.Println("  - 栈操作: O(1)")
	fmt.Println("\n空间复杂度: O(n)")
	fmt.Println("  - 栈空间: 最坏情况O(n)")
	fmt.Println("\n关键优化:")
	fmt.Println("  - 贪心策略避免了动态规划的O(n²)复杂度")
	fmt.Println("  - 栈操作比字符串删除更高效")
}

// greedyLearningTips 贪心算法学习要点
func greedyLearningTips() {
	fmt.Println("\n=== 贪心算法学习要点 ===")

	fmt.Println("\n1. 贪心策略:")
	fmt.Println("   - 优先选择分数更高的操作")
	fmt.Println("   - 局部最优 → 全局最优")

	fmt.Println("\n2. 为什么这题可以用贪心?")
	fmt.Println("   - 删除ab和删除ba是独立的操作")
	fmt.Println("   - 先删高分的不会影响低分的最优性")
	fmt.Println("   - 满足贪心选择性质")

	fmt.Println("\n3. 栈的作用:")
	fmt.Println("   - 模拟字符串删除过程")
	fmt.Println("   - 遇到匹配就删除(弹栈)")
	fmt.Println("   - 不匹配就保留(入栈)")

	fmt.Println("\n4. Go语言特点:")
	fmt.Println("   - 使用slice模拟栈")
	fmt.Println("   - append()入栈，[:len-1]出栈")
	fmt.Println("   - 指针传递避免字符串拷贝")

	fmt.Println("\n5. 与其他语言对比:")
	fmt.Println("   - Go: slice操作简洁")
	fmt.Println("   - C++: STL stack更直观")
	fmt.Println("   - Python: list操作最灵活")
}

func main() {
	testMaximumGain()
	analyzeComplexity()
	greedyLearningTips()
}
