package main

import (
	"fmt"
	"math"
)

const EPS = 1e-6

func judgePoint24(cards []int) bool {
	nums := make([]float64, len(cards))
	for i, v := range cards {
		nums[i] = float64(v)
	}
	return solve(nums)
}

func solve(nums []float64) bool {
	n := len(nums)
	if n == 1 {
		return math.Abs(nums[0]-24.0) < EPS
	}

	// 枚举任意两张卡片
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			// 剩余的数字
			next := []float64{}
			for k := 0; k < n; k++ {
				if k != i && k != j {
					next = append(next, nums[k])
				}
			}

			// 尝试所有运算
			for _, x := range compute(nums[i], nums[j]) {
				next = append(next, x)
				if solve(next) {
					return true
				}
				next = next[:len(next)-1]
			}
		}
	}
	return false
}

func compute(a, b float64) []float64 {
	res := []float64{a + b, a - b, b - a, a * b}
	if math.Abs(b) > EPS {
		res = append(res, a/b)
	}
	if math.Abs(a) > EPS {
		res = append(res, b/a)
	}
	return res
}

func main() {
	fmt.Println(judgePoint24([]int{4, 1, 8, 7})) // true
	fmt.Println(judgePoint24([]int{1, 2, 1, 2})) // false
}
