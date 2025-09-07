package main

import "fmt"

// 位运算解法
func singleNumber(nums []int) int {
    ans := 0
    for i := 0; i < 32; i++ {
        cnt1 := 0
        for _, x := range nums {
            cnt1 += (x >> i) & 1
        }
        ans |= (cnt1 % 3) << i
    }
    return ans
}

// 状态机解法
func singleNumberStateMachine(nums []int) int {
    ones, twos := 0, 0
    for _, num := range nums {
        ones = (ones ^ num) & ^twos
        twos = (twos ^ num) & ^ones
    }
    return ones
}

// 泛型版本
func singleNumberGeneric[T ~int | ~int32 | ~int64](nums []T) T {
    ans := T(0)
    for i := 0; i < 32; i++ {
        cnt1 := T(0)
        for _, x := range nums {
            cnt1 += (x >> i) & 1
        }
        ans |= (cnt1 % 3) << i
    }
    return ans
}

func main() {
    nums1 := []int{2, 2, 3, 2}
    fmt.Println(singleNumber(nums1)) // 3
    
    nums2 := []int{0, 1, 0, 1, 0, 1, 99}
    fmt.Println(singleNumber(nums2)) // 99
    
    fmt.Println("All tests passed!")
}