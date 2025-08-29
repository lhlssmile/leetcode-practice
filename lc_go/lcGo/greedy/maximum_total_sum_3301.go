// 力扣第3301题：高度互不相同的最大塔高和
package main

import (
	"math"
	"sort"
)

// MaximumTotalSum 计算高度互不相同的最大塔高和
// 思路：
// 1. 将高度数组按降序排序
// 2. 从最高的塔开始，确保每个塔的高度严格小于前一个塔
// 3. 如果无法满足条件，返回-1
// 4. 否则，返回所有调整后高度的总和
func MaximumTotalSum(maximumHeight []int) int64 {
	// 创建副本并按降序排序
	sorted := make([]int, len(maximumHeight))
	copy(sorted, maximumHeight)
	sort.Slice(sorted, func(i, j int) bool {
		return sorted[i] > sorted[j]
	})

	prev := math.MaxInt32
	var ans int64 = 0

	for _, h := range sorted {
		// 确保当前高度严格小于前一个高度
		curr := min(h, prev-1)
		if curr <= 0 {
			return -1
		}
		ans += int64(curr)
		prev = curr
	}

	return ans
}

// min 返回两个整数中的较小值
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// 以下是测试函数
func TestMaximumTotalSum() map[string]int64 {
	testCases := map[string]struct {
		heights  []int
		expected int64
	}{
		"基本测试1": {
			heights:  []int{5, 3, 4, 1, 1},
			expected: 13,
		},
		"基本测试2": {
			heights:  []int{6, 5, 3, 9, 2, 7},
			expected: 29,
		},
		"基本测试3": {
			heights:  []int{3, 2, 1},
			expected: 6,
		},
		"无法满足条件": {
			heights:  []int{1, 1, 1},
			expected: -1,
		},
	}

	results := make(map[string]int64)
	for name, tc := range testCases {
		result := MaximumTotalSum(tc.heights)
		results[name] = result
	}

	return results
}
