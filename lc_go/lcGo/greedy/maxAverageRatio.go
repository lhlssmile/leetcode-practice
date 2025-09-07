package main

import (
    "container/heap"
    "fmt"
)

type ClassInfo struct {
    gain  float64
    pass  int
    total int
}

type MaxHeap []ClassInfo

func (h MaxHeap) Len() int           { return len(h) }
func (h MaxHeap) Less(i, j int) bool { return h[i].gain > h[j].gain }
func (h MaxHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *MaxHeap) Push(x interface{}) {
    *h = append(*h, x.(ClassInfo))
}

func (h *MaxHeap) Pop() interface{} {
    old := *h
    n := len(old)
    x := old[n-1]
    *h = old[0 : n-1]
    return x
}

func calculateGain(pass, total int) float64 {
    return float64(pass+1)/float64(total+1) - float64(pass)/float64(total)
}

func maxAverageRatio(classes [][]int, extraStudents int) float64 {
    h := &MaxHeap{}
    heap.Init(h)
    
    // 初始化堆
    for _, class := range classes {
        pass, total := class[0], class[1]
        gain := calculateGain(pass, total)
        heap.Push(h, ClassInfo{gain, pass, total})
    }
    
    // 分配额外学生
    for i := 0; i < extraStudents; i++ {
        top := heap.Pop(h).(ClassInfo)
        pass := top.pass + 1
        total := top.total + 1
        gain := calculateGain(pass, total)
        heap.Push(h, ClassInfo{gain, pass, total})
    }
    
    // 计算平均通过率
    totalRatio := 0.0
    for h.Len() > 0 {
        top := heap.Pop(h).(ClassInfo)
        totalRatio += float64(top.pass) / float64(top.total)
    }
    
    return totalRatio / float64(len(classes))
}

func main() {
    // 测试用例1
    classes1 := [][]int{{1, 2}, {3, 5}, {2, 2}}
    extraStudents1 := 2
    result1 := maxAverageRatio(classes1, extraStudents1)
    fmt.Printf("测试用例1: %.5f\n", result1)
    
    // 测试用例2
    classes2 := [][]int{{2, 4}, {3, 9}, {4, 5}, {2, 10}}
    extraStudents2 := 4
    result2 := maxAverageRatio(classes2, extraStudents2)
    fmt.Printf("测试用例2: %.5f\n", result2)
}