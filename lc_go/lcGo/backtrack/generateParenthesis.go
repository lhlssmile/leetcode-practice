package main

import (
	"fmt"
	"strings"
)

// 生成括号问题 - Go语言实现
// 给定 n 对括号，生成所有有效的括号组合

// 方法1：回溯算法 + 栈验证
func generateParenthesis(n int) []string {
	/*
		🎯 核心思想：回溯 + 栈验证括号有效性
		- 生成所有可能的2n长度序列
		- 用栈验证括号序列是否有效
	*/
	var ans []string
	var path []byte

	var dfs func(i int)
	dfs = func(i int) {
		// 终止条件：生成了2n个字符
		if i == 2*n {
			if isValid(path) {
				ans = append(ans, string(path))
			}
			return
		}

		// 选择 '('
		path = append(path, '(')
		dfs(i + 1)
		path = path[:len(path)-1] // 回溯

		// 选择 ')'
		path = append(path, ')')
		dfs(i + 1)
		path = path[:len(path)-1] // 回溯
	}

	dfs(0)
	return ans
}

// 验证括号序列是否有效
func isValid(brackets []byte) bool {
	var stack []byte
	for _, bracket := range brackets {
		if bracket == '(' {
			stack = append(stack, bracket)
		} else { // bracket == ')'
			if len(stack) == 0 {
				return false
			}
			stack = stack[:len(stack)-1] // 出栈
		}
	}
	return len(stack) == 0
}

// 方法2：优化回溯 - 边构建边验证 (推荐)
func generateParenthesisOptimized(n int) []string {
	/*
		🚀 优化思路：在构建过程中就进行剪枝
		关键观察：
		1. 左括号数量不能超过 n
		2. 右括号数量不能超过左括号数量
		3. 右括号数量不能超过 n
	*/
	var ans []string
	var path []byte

	var dfs func(leftCount, rightCount int)
	dfs = func(leftCount, rightCount int) {
		// 终止条件：生成了 n 对括号
		if leftCount == n && rightCount == n {
			ans = append(ans, string(path))
			return
		}

		// 剪枝 + 选择
		// 选择 '('：左括号数量不能超过 n
		if leftCount < n {
			path = append(path, '(')
			dfs(leftCount+1, rightCount)
			path = path[:len(path)-1] // 回溯
		}

		// 选择 ')'：右括号数量不能超过左括号数量
		if rightCount < leftCount {
			path = append(path, ')')
			dfs(leftCount, rightCount+1)
			path = path[:len(path)-1] // 回溯
		}
	}

	dfs(0, 0)
	return ans
}

// 方法3：字符串拼接版本
func generateParenthesisString(n int) []string {
	/*
		🎨 字符串版本：不用切片，直接拼接字符串
	*/
	var ans []string

	var dfs func(current string, left, right int)
	dfs = func(current string, left, right int) {
		// 终止条件
		if left == n && right == n {
			ans = append(ans, current)
			return
		}

		// 添加左括号
		if left < n {
			dfs(current+"(", left+1, right)
		}

		// 添加右括号
		if right < left {
			dfs(current+")", left, right+1)
		}
	}

	dfs("", 0, 0)
	return ans
}

// 🧪 测试函数
func testGenerateParenthesis() {
	testCases := []struct {
		n        int
		expected []string
	}{
		{1, []string{"()"}},
		{2, []string{"(())", "()()"}},
		{3, []string{"((()))", "(()())", "(())()", "()(())", "()()()"}},
	}

	fmt.Println("=== 生成括号测试 ===")

	for _, tc := range testCases {
		fmt.Printf("\nn = %d (期望 %d 种组合):\n", tc.n, len(tc.expected))

		// 测试方法1：回溯 + 栈验证
		result1 := generateParenthesis(tc.n)
		fmt.Printf("  方法1 (回溯+栈): %v\n", result1)

		// 测试方法2：优化回溯
		result2 := generateParenthesisOptimized(tc.n)
		fmt.Printf("  方法2 (优化回溯): %v\n", result2)

		// 测试方法3：字符串版本
		result3 := generateParenthesisString(tc.n)
		fmt.Printf("  方法3 (字符串版): %v\n", result3)

		// 验证结果数量
		if len(result1) == len(tc.expected) && len(result2) == len(tc.expected) && len(result3) == len(tc.expected) {
			fmt.Printf("  ✅ 所有方法结果数量正确\n")
		} else {
			fmt.Printf("  ❌ 结果数量不正确\n")
		}
	}
}

// 🎨 可视化回溯过程
func visualizeBacktrackProcess(n int) {
	fmt.Printf("\n=== 回溯过程可视化 (n=%d) ===\n", n)

	var ans []string
	var path []byte
	step := 0

	var dfs func(left, right, depth int)
	dfs = func(left, right, depth int) {
		step++
		indent := strings.Repeat("  ", depth)
		fmt.Printf("%s步骤%d: path=%s, left=%d, right=%d\n", indent, step, string(path), left, right)

		// 终止条件
		if left == n && right == n {
			ans = append(ans, string(path))
			fmt.Printf("%s✅ 找到解: %s\n", indent, string(path))
			return
		}

		// 选择 '('
		if left < n {
			fmt.Printf("%s尝试添加 '('\n", indent)
			path = append(path, '(')
			dfs(left+1, right, depth+1)
			path = path[:len(path)-1]
			fmt.Printf("%s回溯，移除 '('\n", indent)
		}

		// 选择 ')'
		if right < left {
			fmt.Printf("%s尝试添加 ')'\n", indent)
			path = append(path, ')')
			dfs(left, right+1, depth+1)
			path = path[:len(path)-1]
			fmt.Printf("%s回溯，移除 ')'\n", indent)
		}
	}

	dfs(0, 0, 0)
	fmt.Printf("\n最终结果: %v\n", ans)
}

func main() {
	// 基本测试
	fmt.Println("🎯 Go语言版本的生成括号算法")
	fmt.Printf("generateParenthesis(3) = %v\n", generateParenthesis(3))
	fmt.Printf("generateParenthesisOptimized(3) = %v\n", generateParenthesisOptimized(3))

	// 运行完整测试
	testGenerateParenthesis()

	// 可视化小例子
	fmt.Println("\n" + strings.Repeat("=", 50))
	visualizeBacktrackProcess(2)

	/*
		📚 Go语言回溯算法学习笔记：

		1. Go的切片特性：
		   - 使用 append() 添加元素
		   - 使用 slice[:len(slice)-1] 移除最后一个元素（回溯）
		   - 切片是引用类型，修改会影响原切片

		2. Go的函数特性：
		   - 使用闭包捕获外部变量
		   - var dfs func(...) 声明递归函数
		   - 函数内部定义函数

		3. Go的字符串处理：
		   - []byte 和 string 的转换
		   - strings.Repeat() 生成重复字符串
		   - 字符串拼接性能考虑

		4. 时间复杂度：
		   - 第 n 个卡特兰数：C_n = (2n)! / ((n+1)! * n!)
		   - 约为 O(4^n / n^(3/2))
	*/
}
