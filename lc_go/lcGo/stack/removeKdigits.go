package main

import "fmt"

func removeKdigits(num string, k int) string {
	var stack []byte
	
	for i := 0; i < len(num); i++ {
		d := num[i]
		// 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
		for len(stack) > 0 && k > 0 && stack[len(stack)-1] > d {
			stack = stack[:len(stack)-1]
			k--
		}
		stack = append(stack, d)
	}
	
	// 如果还没删完，从后面删
	for k > 0 && len(stack) > 0 {
		stack = stack[:len(stack)-1]
		k--
	}
	
	// 去掉前导零
	start := 0
	for start < len(stack) && stack[start] == '0' {
		start++
	}
	
	result := string(stack[start:])
	if result == "" {
		return "0"
	}
	return result
}

func main() {
	// 测试用例
	fmt.Println(removeKdigits("1432219", 3)) // "1219"
	fmt.Println(removeKdigits("10200", 1))   // "200"
	fmt.Println(removeKdigits("10", 2))      // "0"
}