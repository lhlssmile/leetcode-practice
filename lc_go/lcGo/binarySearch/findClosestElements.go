package main

import (
    "container/heap"
    "fmt"
    "math"
    "sort"
)

// 方法1: 二分扩展法
func findClosestElements(arr []int, k int, x int) []int {
    n := len(arr)
    idx := sort.SearchInts(arr, x)
    
    left, right := idx-1, idx
    
    for right-left-1 < k {
        if left < 0 {
            right++
        } else if right >= n {
            left--
        } else {
            if x-arr[left] <= arr[right]-x {
                left--
            } else {
                right++
            }
        }
    }
    
    return arr[left+1 : right]
}

// 方法2: 滑动窗口法
func findClosestElementsSlidingWindow(arr []int, k int, x int) []int {
    left, right := 0, len(arr)-k
    
    for left < right {
        mid := left + (right-left)/2
        if x-arr[mid] > arr[mid+k]-x {
            left = mid + 1
        } else {
            right = mid
        }
    }
    
    return arr[left : left+k]
}

// 大根堆实现
type MaxHeap [][]int // [distance, value, index]

func (h MaxHeap) Len() int { return len(h) }
func (h MaxHeap) Less(i, j int) bool {
    if h[i][0] != h[j][0] {
        return h[i][0] > h[j][0] // 距离大的在前
    }
    return h[i][1] > h[j][1] // 距离相同时值大的在前
}
func (h MaxHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }
func (h *MaxHeap) Push(x interface{}) {
    *h = append(*h, x.([]int))
}
func (h *MaxHeap) Pop() interface{} {
    old := *h
    n := len(old)
    x := old[n-1]
    *h = old[0 : n-1]
    return x
}

// 方法3: 大根堆法
func findClosestElementsMaxHeap(arr []int, k int, x int) []int {
    h := &MaxHeap{}
    heap.Init(h)
    
    for i, num := range arr {
        distance := int(math.Abs(float64(num - x)))
        if h.Len() < k {
            heap.Push(h, []int{distance, num, i})
        } else {
            top := (*h)[0]
            if distance < top[0] || (distance == top[0] && num < top[1]) {
                heap.Pop(h)
                heap.Push(h, []int{distance, num, i})
            }
        }
    }
    
    // 提取结果并排序
    type pair struct {
        index int
        value int
    }
    
    var temp []pair
    for h.Len() > 0 {
        item := heap.Pop(h).([]int)
        temp = append(temp, pair{item[2], item[1]})
    }
    
    sort.Slice(temp, func(i, j int) bool {
        return temp[i].index < temp[j].index
    })
    
    result := make([]int, len(temp))
    for i, p := range temp {
        result[i] = p.value
    }
    return result
}

// 方法3优化: 大根堆法 - 提前终止
func findClosestElementsOptimizedHeap(arr []int, k int, x int) []int {
    h := &MaxHeap{}
    heap.Init(h)
    
    for i, num := range arr {
        distance := int(math.Abs(float64(num - x)))
        if h.Len() < k {
            heap.Push(h, []int{distance, num, i})
        } else {
            top := (*h)[0]
            if distance < top[0] || (distance == top[0] && num < top[1]) {
                heap.Pop(h)
                heap.Push(h, []int{distance, num, i})
            } else if distance > top[0] {
                break // 提前终止
            }
        }
    }
    
    type pair struct {
        index int
        value int
    }
    
    var temp []pair
    for h.Len() > 0 {
        item := heap.Pop(h).([]int)
        temp = append(temp, pair{item[2], item[1]})
    }
    
    sort.Slice(temp, func(i, j int) bool {
        return temp[i].index < temp[j].index
    })
    
    result := make([]int, len(temp))
    for i, p := range temp {
        result[i] = p.value
    }
    return result
}

func main() {
    arr := []int{1, 2, 3, 4, 5}
    k, x := 4, 3
    
    fmt.Println("二分扩展法:", findClosestElements(arr, k, x))
    fmt.Println("滑动窗口法:", findClosestElementsSlidingWindow(arr, k, x))
    fmt.Println("大根堆法:", findClosestElementsMaxHeap(arr, k, x))
    fmt.Println("优化堆法:", findClosestElementsOptimizedHeap(arr, k, x))
}