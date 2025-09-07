// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

package main

import (
	"fmt"
	"strconv"
)

func evalRPN(tokens []string) int {
	stack := make([]int, 0)
	
	for _, token := range tokens {
		switch token {
		case "+":
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			stack = append(stack, a+b)
		case "-":
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			stack = append(stack, a-b)
		case "*":
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			stack = append(stack, a*b)
		case "/":
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			stack = append(stack, a/b)
		default:
			num, _ := strconv.Atoi(token)
			stack = append(stack, num)
		}
	}
	
	return stack[0]
}

// 使用map的实现
func evalRPNWithMap(tokens []string) int {
	stack := make([]int, 0)
	operators := map[string]func(int, int) int{
		"+": func(a, b int) int { return a + b },
		"-": func(a, b int) int { return a - b },
		"*": func(a, b int) int { return a * b },
		"/": func(a, b int) int { return a / b },
	}
	
	for _, token := range tokens {
		if op, exists := operators[token]; exists {
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			stack = append(stack, op(a, b))
		} else {
			num, _ := strconv.Atoi(token)
			stack = append(stack, num)
		}
	}
	
	return stack[0]
}

// 使用指针优化的实现
func evalRPNOptimized(tokens []string) int {
	stack := make([]int, 0, len(tokens))
	
	for _, token := range tokens {
		switch token {
		case "+", "-", "*", "/":
			n := len(stack)
			a, b := stack[n-2], stack[n-1]
			stack = stack[:n-2]
			
			var result int
			switch token {
			case "+":
				result = a + b
			case "-":
				result = a - b
			case "*":
				result = a * b
			case "/":
				result = a / b
			}
			stack = append(stack, result)
		default:
			num, _ := strconv.Atoi(token)
			stack = append(stack, num)
		}
	}
	
	return stack[0]
}

func testEvalRPN() {
	fmt.Println("=== 逆波兰表达式求值测试 ===")
	
	// 测试用例
	testCases := []struct {
		tokens   []string
		expected int
	}{
		{[]string{"2", "1", "+", "3", "*"}, 9},                                                           // ((2 + 1) * 3) = 9
		{[]string{"4", "13", "5", "/", "+"}, 6},                                                          // (4 + (13 / 5)) = 6
		{[]string{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}, 22}, // 22
	}
	
	for i, tc := range testCases {
		result1 := evalRPN(tc.tokens)
		result2 := evalRPNWithMap(tc.tokens)
		result3 := evalRPNOptimized(tc.tokens)
		
		fmt.Printf("测试用例%d: %v\n", i+1, tc.tokens)
		fmt.Printf("标准实现结果: %d\n", result1)
		fmt.Printf("Map实现结果: %d\n", result2)
		fmt.Printf("优化实现结果: %d\n", result3)
		fmt.Printf("期望结果: %d\n", tc.expected)
		fmt.Printf("所有实现正确: %t\n", 
			result1 == tc.expected && result2 == tc.expected && result3 == tc.expected)
		fmt.Println()
	}
	
	fmt.Println("=== Go语言特性说明 ===")
	fmt.Println("1. 切片: 动态数组实现栈")
	fmt.Println("2. 映射: 内置哈希表")
	fmt.Println("3. 函数类型: 一等公民")
	fmt.Println("4. 结构体: 数据组织")
	fmt.Println("5. 错误处理: 显式错误返回")
}

func main() {
	testEvalRPN()
}

/*
Go语言实现特点:

1. **简洁语法**:
   - 简洁的语法结构
   - 类型推断
   - 无需分号

2. **内置数据结构**:
   - 切片作为动态数组
   - 映射作为哈希表
   - 字符串处理

3. **函数特性**:
   - 函数作为一等公民
   - 闭包支持
   - 多返回值

4. **性能优化**:
   - 编译型语言
   - 垃圾回收
   - 并发支持

5. **错误处理**:
   - 显式错误返回
   - 无异常机制
   - 简洁的错误处理

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/