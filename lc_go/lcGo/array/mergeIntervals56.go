package main

import (
	"fmt"
	"sort"
)

func merge(intervals [][]int) [][]int {
	if len(intervals) == 0 {
		return [][]int{}
	}

	// 按 start 升序排序
	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0]
	})

	result := [][]int{}
	start, end := intervals[0][0], intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		if intervals[i][0] <= end { // 重叠
			if intervals[i][1] > end {
				end = intervals[i][1]
			}
		} else { // 不重叠
			result = append(result, []int{start, end})
			start, end = intervals[i][0], intervals[i][1]
		}
	}

	// 加入最后一个区间
	result = append(result, []int{start, end})

	return result
}

func main() {
	intervals := [][]int{{1, 3}, {2, 6}, {8, 10}, {15, 18}}
	res := merge(intervals)
	fmt.Println(res)
}
