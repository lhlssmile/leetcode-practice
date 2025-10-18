package main

import (
	"container/heap"
	"fmt"
)

type Pair struct {
	sum int
	i   int
	j   int
}

type MinHeapA []Pair

func (h MinHeapA) Len() int            { return len(h) }
func (h MinHeapA) Less(i, j int) bool  { return h[i].sum < h[j].sum }
func (h MinHeapA) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
func (h *MinHeapA) Push(x interface{}) { *h = append(*h, x.(Pair)) }
func (h *MinHeapA) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[:n-1]
	return x
}

func kSmallestPairs(nums1 []int, nums2 []int, k int) [][]int {
	res := [][]int{}
	if len(nums1) == 0 || len(nums2) == 0 || k == 0 {
		return res
	}

	h := &MinHeapA{}
	heap.Init(h)
	visited := make(map[[2]int]bool)

	heap.Push(h, Pair{nums1[0] + nums2[0], 0, 0})
	visited[[2]int{0, 0}] = true

	for h.Len() > 0 && len(res) < k {
		p := heap.Pop(h).(Pair)
		i, j := p.i, p.j
		res = append(res, []int{nums1[i], nums2[j]})

		if i+1 < len(nums1) {
			key := [2]int{i + 1, j}
			if !visited[key] {
				heap.Push(h, Pair{nums1[i+1] + nums2[j], i + 1, j})
				visited[key] = true
			}
		}
		if j+1 < len(nums2) {
			key := [2]int{i, j + 1}
			if !visited[key] {
				heap.Push(h, Pair{nums1[i] + nums2[j+1], i, j + 1})
				visited[key] = true
			}
		}
	}

	return res
}

func main() {
	nums1 := []int{1, 7, 11}
	nums2 := []int{2, 4, 6}
	k := 3
	fmt.Println(kSmallestPairs(nums1, nums2, k)) // [[1 2] [1 4] [1 6]]
}
