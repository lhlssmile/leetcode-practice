package main

import (
	"fmt"
	"math"
)

// maxDifference 计算满足条件的最大差值
func maxDifference(s string, k int) int {
	inf := math.MaxInt32 / 2
	ans := -inf

	for x := 0; x < 5; x++ {
		for y := 0; y < 5; y++ {
			if y == x {
				continue
			}
			
			curS := make([]int, 5)
			preS := make([]int, 5)
			minS := [2][2]int{{inf, inf}, {inf, inf}}
			left := 0
			
			for i := 0; i < len(s); i++ {
				curS[s[i]-'0']++
				r := i + 1
				
				for r-left >= k && curS[x] > preS[x] && curS[y] > preS[y] {
					p := &minS[preS[x]&1][preS[y]&1]
					*p = min(*p, preS[x]-preS[y])
					preS[s[left]-'0']++
					left++
				}
				
				ans = max(ans, curS[x]-curS[y]-minS[(curS[x]&1)^1][curS[y]&1])
			}
		}
	}
	
	return ans
}

// maxDifferenceOptimized 优化版本：使用更具描述性的变量名和注释
func maxDifferenceOptimized(s string, k int) int {
	INF := math.MaxInt32 / 2
	maxDiff := -INF
	
	// 枚举所有可能的字符对(x,y)，其中x!=y
	for x := 0; x < 5; x++ {
		for y := 0; y < 5; y++ {
			if y == x {
				continue
			}
			
			// 当前窗口中各字符的计数
			currentCount := make([]int, 5)
			// 前缀窗口中各字符的计数
			prefixCount := make([]int, 5)
			// 存储最小差值，按奇偶性分类
			minDifference := [2][2]int{{INF, INF}, {INF, INF}}
			
			left := 0
			for i := 0; i < len(s); i++ {
				// 更新当前窗口计数
				currentCount[s[i]-'0']++
				right := i + 1
				
				// 当窗口大小>=k且满足条件时，更新最小差值
				for right-left >= k && currentCount[x] > prefixCount[x] && currentCount[y] > prefixCount[y] {
					// 根据x和y的奇偶性选择对应的最小差值
					parityX := prefixCount[x] & 1 // x的奇偶性
					parityY := prefixCount[y] & 1 // y的奇偶性
					
					// 使用指针直接修改数组元素
					p := &minDifference[parityX][parityY]
					*p = min(*p, prefixCount[x]-prefixCount[y])
					
					// 移动左指针，更新前缀计数
					prefixCount[s[left]-'0']++
					left++
				}
				
				// 计算当前最大差值
				// 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
				currentParityX := (currentCount[x] & 1) ^ 1
				currentParityY := currentCount[y] & 1
				maxDiff = max(maxDiff, currentCount[x]-currentCount[y]-minDifference[currentParityX][currentParityY])
			}
		}
	}
	
	return maxDiff
}

// maxDifferenceGo Go风格版本：利用Go的特性
func maxDifferenceGo(s string, k int) int {
	const maxDigit = 5
	INF := math.MaxInt32 / 2
	maxDiff := -INF
	
	// 将字符串转换为数字切片，避免重复转换
	digits := make([]int, len(s))
	for i, ch := range s {
		digits[i] = int(ch - '0')
	}
	
	// 枚举所有可能的字符对(x,y)，其中x!=y
	for x := 0; x < maxDigit; x++ {
		for y := 0; y < maxDigit; y++ {
			if y == x {
				continue
			}
			
			currentCount := make([]int, maxDigit)
			prefixCount := make([]int, maxDigit)
			minDifference := [2][2]int{{INF, INF}, {INF, INF}}
			
			left := 0
			for i, digit := range digits {
				currentCount[digit]++
				right := i + 1
				
				for right-left >= k && currentCount[x] > prefixCount[x] && currentCount[y] > prefixCount[y] {
					parityX, parityY := prefixCount[x]&1, prefixCount[y]&1
					minDifference[parityX][parityY] = min(minDifference[parityX][parityY], prefixCount[x]-prefixCount[y])
					prefixCount[digits[left]]++
					left++
				}
				
				currentParityX := (currentCount[x] & 1) ^ 1
				currentParityY := currentCount[y] & 1
				maxDiff = max(maxDiff, currentCount[x]-currentCount[y]-minDifference[currentParityX][currentParityY])
			}
		}
	}
	
	return maxDiff
}

// 辅助函数
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

// 测试函数
func TestMaxDifference() {
	testCases := []struct {
		s string
		k int
		expected int
	}{
		{"01234", 2, 0}, // 示例1
		{"00110", 2, 0}, // 示例2
	}
	
	for i, tc := range testCases {
		result1 := maxDifference(tc.s, tc.k)
		result2 := maxDifferenceOptimized(tc.s, tc.k)
		result3 := maxDifferenceGo(tc.s, tc.k)
		
		fmt.Printf("测试用例%d: s=%s, k=%d\n", i+1, tc.s, tc.k)
		fmt.Printf("  基本版本结果: %d\n", result1)
		fmt.Printf("  优化版本结果: %d\n", result2)
		fmt.Printf("  Go风格版本结果: %d\n", result3)
		fmt.Println()
	}
}

func main() {
	TestMaxDifference()
}