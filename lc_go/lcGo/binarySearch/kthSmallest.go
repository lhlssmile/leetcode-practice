package binarySearch

import (
	"container/heap"
	"fmt"
)

// 二分查找解法
func kthSmallest(matrix [][]int, k int) int {
	n := len(matrix)
	lo := matrix[0][0]
	hi := matrix[n-1][n-1]

	for lo < hi {
		mid := lo + (hi-lo)/2
		count := countLessEqual(matrix, mid)
		if count < k {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}

func countLessEqual(matrix [][]int, target int) int {
	n := len(matrix)
	i := n - 1
	j := 0
	count := 0

	for i >= 0 && j < n {
		if matrix[i][j] <= target {
			count += i + 1 // 当前列中有i+1个元素小于等于target
			j++
		} else {
			i--
		}
	}
	return count
}

// 最小堆解法

// 定义堆元素结构
type Item struct {
	Value int
	Row   int
	Col   int
}

// 定义最小堆
type MinHeap []Item

func (h MinHeap) Len() int           { return len(h) }
func (h MinHeap) Less(i, j int) bool { return h[i].Value < h[j].Value }
func (h MinHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *MinHeap) Push(x interface{}) {
	*h = append(*h, x.(Item))
}

func (h *MinHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func kthSmallestHeap(matrix [][]int, k int) int {
	n := len(matrix)
	h := &MinHeap{}
	heap.Init(h)

	// 将第一列的元素加入堆
	for i := 0; i < n && i < k; i++ {
		heap.Push(h, Item{Value: matrix[i][0], Row: i, Col: 0})
	}

	// 弹出k-1个元素
	item := Item{}
	for i := 1; i < k; i++ {
		item = heap.Pop(h).(Item)
		row := item.Row
		col := item.Col

		if col+1 < n {
			heap.Push(h, Item{Value: matrix[row][col+1], Row: row, Col: col + 1})
		}
	}

	return heap.Pop(h).(Item).Value
}

// 测试函数
func TestKthSmallest() {
	// 测试用例1
	matrix1 := [][]int{
		{1, 5, 9},
		{10, 11, 13},
		{12, 13, 15},
	}
	k1 := 8
	fmt.Println("Binary Search:", kthSmallest(matrix1, k1))
	fmt.Println("Heap:", kthSmallestHeap(matrix1, k1))

	// 测试用例2
	matrix2 := [][]int{
		{1, 2},
		{1, 3},
	}
	k2 := 2
	fmt.Println("Binary Search:", kthSmallest(matrix2, k2))
	fmt.Println("Heap:", kthSmallestHeap(matrix2, k2))
}

/*
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
*/