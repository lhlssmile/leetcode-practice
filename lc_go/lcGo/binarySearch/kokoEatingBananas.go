// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

package main

import (
	"fmt"
	"math"
	"sort"
)

// 标准二分查找实现
func minEatingSpeedBinarySearch(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	left, right := 1, maxInSlice(piles)
	
	for left < right {
		mid := left + (right-left)/2
		totalHours := 0
		
		for _, pile := range piles {
			totalHours += (pile + mid - 1) / mid // ceil(pile / mid)
		}
		
		if totalHours <= h {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}

// 使用math.Ceil的版本
func minEatingSpeedWithCeil(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	left, right := 1, maxInSlice(piles)
	
	for left < right {
		mid := left + (right-left)/2
		totalHours := 0
		
		for _, pile := range piles {
			totalHours += int(math.Ceil(float64(pile) / float64(mid)))
		}
		
		if totalHours <= h {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}

// 暴力枚举版本
func minEatingSpeedBruteForce(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	maxPile := maxInSlice(piles)
	
	for k := 1; k <= maxPile; k++ {
		totalHours := 0
		for _, pile := range piles {
			totalHours += (pile + k - 1) / k
		}
		
		if totalHours <= h {
			return k
		}
	}
	
	return maxPile
}

// 优化版本 - 提前计算边界
func minEatingSpeedOptimized(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	// 计算总香蕉数
	totalBananas := 0
	for _, pile := range piles {
		totalBananas += pile
	}
	
	// 最小速度：总数除以时间（向上取整）
	minSpeed := (totalBananas + h - 1) / h
	maxSpeed := maxInSlice(piles)
	
	// 如果最小速度就能完成，直接返回
	if canFinish(piles, h, minSpeed) {
		return minSpeed
	}
	
	left, right := minSpeed, maxSpeed
	
	for left < right {
		mid := left + (right-left)/2
		
		if canFinish(piles, h, mid) {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}

// 使用sort.Search的版本
func minEatingSpeedWithSortSearch(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	maxPile := maxInSlice(piles)
	
	// sort.Search找到第一个使canFinish返回true的k
	return sort.Search(maxPile, func(k int) bool {
		if k == 0 {
			return false
		}
		return canFinish(piles, h, k)
	}) + 1 // sort.Search从0开始，我们需要从1开始
}

// 辅助函数：检查是否能在h小时内完成
func canFinish(piles []int, h, k int) bool {
	totalHours := 0
	for _, pile := range piles {
		totalHours += (pile + k - 1) / k
		if totalHours > h {
			return false // 提前退出优化
		}
	}
	return totalHours <= h
}

// 辅助函数：找到切片中的最大值
func maxInSlice(slice []int) int {
	if len(slice) == 0 {
		return 0
	}
	
	max := slice[0]
	for _, v := range slice[1:] {
		if v > max {
			max = v
		}
	}
	return max
}

// 使用泛型的版本（Go 1.18+）
func Max[T ~int | ~int32 | ~int64](slice []T) T {
	if len(slice) == 0 {
		var zero T
		return zero
	}
	
	max := slice[0]
	for _, v := range slice[1:] {
		if v > max {
			max = v
		}
	}
	return max
}

func minEatingSpeedGeneric(piles []int, h int) int {
	if len(piles) == 0 {
		return 0
	}
	
	left, right := 1, Max(piles)
	
	for left < right {
		mid := left + (right-left)/2
		totalHours := 0
		
		for _, pile := range piles {
			totalHours += (pile + mid - 1) / mid
		}
		
		if totalHours <= h {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}

func main() {
	testCases := []struct {
		piles []int
		h     int
	}{
		{[]int{3, 6, 7, 11}, 8},
		{[]int{30, 11, 23, 4, 20}, 5},
		{[]int{30, 11, 23, 4, 20}, 6},
		{[]int{1, 1, 1, 1}, 4},
		{[]int{312884470}, 312884469},
	}
	
	fmt.Println("=== 爱吃香蕉的珂珂 ===")
	
	for i, tc := range testCases {
		fmt.Printf("\n测试用例 %d: piles=%v, h=%d\n", i+1, tc.piles, tc.h)
		
		result1 := minEatingSpeedBinarySearch(tc.piles, tc.h)
		result2 := minEatingSpeedWithCeil(tc.piles, tc.h)
		result3 := minEatingSpeedBruteForce(tc.piles, tc.h)
		result4 := minEatingSpeedOptimized(tc.piles, tc.h)
		result5 := minEatingSpeedWithSortSearch(tc.piles, tc.h)
		result6 := minEatingSpeedGeneric(tc.piles, tc.h)
		
		fmt.Printf("标准二分查找: %d\n", result1)
		fmt.Printf("使用math.Ceil: %d\n", result2)
		fmt.Printf("暴力枚举: %d\n", result3)
		fmt.Printf("优化版本: %d\n", result4)
		fmt.Printf("sort.Search版本: %d\n", result5)
		fmt.Printf("泛型版本: %d\n", result6)
		
		// 验证结果一致性
		results := []int{result1, result2, result3, result4, result5, result6}
		for j := 1; j < len(results); j++ {
			if results[j] != results[0] {
				panic(fmt.Sprintf("结果不一致! 期望: %d, 实际: %d", results[0], results[j]))
			}
		}
		fmt.Println("✓ 所有实现结果一致")
	}
	
	fmt.Println("\n=== Go语言特性说明 ===")
	fmt.Println("1. 切片操作: 动态数组，支持append和切片")
	fmt.Println("2. range循环: 简洁的迭代语法")
	fmt.Println("3. 多返回值: 函数可以返回多个值")
	fmt.Println("4. defer语句: 延迟执行，常用于资源清理")
	fmt.Println("5. 接口: 隐式实现，支持多态")
	fmt.Println("6. goroutine: 轻量级线程，支持并发")
	fmt.Println("7. channel: 用于goroutine间通信")
	fmt.Println("8. 泛型: Go 1.18+支持类型参数")
	fmt.Println("9. sort包: 提供高效的搜索和排序算法")
	fmt.Println("10. 错误处理: 显式错误返回，避免异常")
}

/*
Go语言特性详解:

1. **切片(Slice)**:
   - 动态数组，底层是数组的引用
   - 支持append操作动态扩容
   - 切片操作[start:end]创建子切片

2. **range循环**:
   - 简洁的迭代语法，支持索引和值
   - for i, v := range slice
   - 只需要值时可以省略索引: for _, v := range slice

3. **函数特性**:
   - 支持多返回值
   - 函数是一等公民，可以作为参数传递
   - 支持闭包和匿名函数

4. **接口系统**:
   - 隐式实现，无需显式声明
   - 支持多态和依赖注入
   - 空接口interface{}可以接受任何类型

5. **并发模型**:
   - goroutine: 轻量级线程，由Go运行时管理
   - channel: 用于goroutine间安全通信
   - select语句: 多路复用channel操作

6. **内存管理**:
   - 垃圾回收器自动管理内存
   - 指针支持但限制了指针运算
   - 值类型和引用类型明确区分

7. **错误处理**:
   - 显式错误返回，通常作为最后一个返回值
   - 避免异常机制，错误处理更明确
   - panic/recover用于处理严重错误

8. **包系统**:
   - 基于目录的包组织
   - 大写字母开头的标识符为公开
   - import语句支持别名和点导入

9. **标准库**:
   - 丰富的标准库，涵盖网络、文件、加密等
   - sort包提供高效的排序和搜索算法
   - fmt包提供格式化输入输出

10. **泛型(Go 1.18+)**:
    - 类型参数支持
    - 类型约束和类型推断
    - 提高代码复用性和类型安全
*/