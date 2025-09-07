// Go语言版本 - 拼车问题 (LeetCode 1094)
package main

import (
	"fmt"
	"sort"
)

// 事件结构体
type Event struct {
	location int
	change   int
}

// 事件排序法
func carPooling(trips [][]int, capacity int) bool {
	events := make([]Event, 0, len(trips)*2)
	
	// 构建事件列表
	for _, trip := range trips {
		passengers, from, to := trip[0], trip[1], trip[2]
		events = append(events, Event{from, passengers})   // 上车事件
		events = append(events, Event{to, -passengers})    // 下车事件
	}
	
	// 排序事件：先按位置，再按变化量（下车优先）
	sort.Slice(events, func(i, j int) bool {
		if events[i].location == events[j].location {
			return events[i].change < events[j].change
		}
		return events[i].location < events[j].location
	})
	
	currentPassengers := 0
	
	// 处理所有事件
	for _, event := range events {
		currentPassengers += event.change
		if currentPassengers > capacity {
			return false
		}
	}
	
	return true
}

// 差分数组法
func carPoolingDiffArray(trips [][]int, capacity int) bool {
	diff := make(map[int]int)
	
	// 构建差分数组
	for _, trip := range trips {
		passengers, from, to := trip[0], trip[1], trip[2]
		diff[from] += passengers
		diff[to] -= passengers
	}
	
	// 获取所有位置并排序
	positions := make([]int, 0, len(diff))
	for pos := range diff {
		positions = append(positions, pos)
	}
	sort.Ints(positions)
	
	currentPassengers := 0
	
	// 按位置顺序处理
	for _, pos := range positions {
		currentPassengers += diff[pos]
		if currentPassengers > capacity {
			return false
		}
	}
	
	return true
}

func main() {
	// 测试用例
	testCases := [][][]int{
		{{2, 1, 5}, {3, 3, 7}},      // capacity = 4, expected: false
		{{2, 1, 5}, {3, 3, 7}},      // capacity = 5, expected: true
		{{2, 1, 5}, {3, 5, 7}},      // capacity = 3, expected: true
		{{3, 2, 7}, {3, 7, 9}, {8, 3, 9}}, // capacity = 11, expected: true
	}
	
	capacities := []int{4, 5, 3, 11}
	expected := []bool{false, true, true, true}
	
	fmt.Println("=== 拼车问题测试 ===")
	
	for i, trips := range testCases {
		capacity := capacities[i]
		
		result1 := carPooling(trips, capacity)
		result2 := carPoolingDiffArray(trips, capacity)
		
		fmt.Printf("测试用例 %d: ", i+1)
		fmt.Printf("trips = %v, capacity = %d\n", trips, capacity)
		fmt.Printf("事件排序法: %t\n", result1)
		fmt.Printf("差分数组法: %t\n", result2)
		fmt.Printf("预期结果: %t\n", expected[i])
		if result1 == expected[i] && result2 == expected[i] {
			fmt.Println("结果: ✓")
		} else {
			fmt.Println("结果: ✗")
		}
		fmt.Println()
	}
}

/*
算法说明：
1. 事件排序法：
   - 将每个行程转换为上车和下车事件
   - 按位置排序，同位置时下车优先
   - 模拟整个过程，检查是否超载
   
2. 差分数组法：
   - 使用差分思想，记录每个位置的乘客变化
   - 按位置顺序累加，检查是否超载
   
时间复杂度: O(n log n)
空间复杂度: O(n)
*/