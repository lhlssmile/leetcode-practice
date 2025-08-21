package main

import (
	"container/heap"
	"fmt"
	"sort"
)

type MinHeap []int

func (h MinHeap) Len() int            { return len(h) }
func (h MinHeap) Less(i, j int) bool  { return h[i] < h[j] }
func (h MinHeap) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
func (h *MinHeap) Push(x interface{}) { *h = append(*h, x.(int)) }
func (h *MinHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[:n-1]
	return x
}

func maxScore(nums1, nums2 []int, k int) []int64 {
	n := len(nums1)
	a := make([][3]int, n)
	for i := 0; i < n; i++ {
		a[i] = [3]int{nums1[i], nums2[i], i}
	}
	sort.Slice(a, func(i, j int) bool {
		if a[i][0] == a[j][0] {
			return a[i][2] < a[j][2]
		}
		return a[i][0] < a[j][0]
	})

	ans := make([]int64, n)
	h := &MinHeap{}
	heap.Init(h)
	var sum int64 = 0

	for i := 0; i < n; {
		j := i
		for j < n && a[j][0] == a[i][0] {
			j++
		}
		// 给这一组答案
		for t := i; t < j; t++ {
			ans[a[t][2]] = sum
		}
		// 再加入堆
		for t := i; t < j; t++ {
			val := a[t][1]
			if h.Len() < k {
				heap.Push(h, val)
				sum += int64(val)
			} else if h.Len() > 0 && (*h)[0] < val {
				sum -= int64((*h)[0])
				heap.Pop(h)
				heap.Push(h, val)
				sum += int64(val)
			}
		}
		i = j
	}

	return ans
}

func main() {
	nums1 := []int{4, 2, 1, 5, 3}
	nums2 := []int{10, 20, 30, 40, 50}
	k := 2
	fmt.Println(maxScore(nums1, nums2, k)) // [0 0 0 0]
}
