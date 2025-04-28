package main

import (
	"fmt"
	"math"
	"math/bits"
	"slices"
	"strconv"
)

func concatenatedDivisibility(nums []int, k int) []int {
	slices.Sort(nums)
	n := len(nums)

	pow10 := make([]int, n)

	for i, x := range nums {
		pow10[i] = int(math.Pow10(len(strconv.Itoa(x))))
	}
	ans := make([]int, n)
	vis := make([][]bool, 1<<n)

	for i := range vis {
		vis[i] = make([]bool, k)
	}
	var dfs func(int, int) bool

	dfs = func(s, x int) bool {
		if s == 0 {
			return x == 0
		}
		if vis[s][x] {
			return false
		}
		vis[s][x] = true
		// 这段代码使用位运算来遍历所有可能的数字组合
		// t := uint(s) 将状态s转换为无符号整数，用于位运算
		// t > 0 表示还有未使用的数字
		// t &= t - 1 是Brian Kernighan算法，用于快速计算二进制中1的个数
		// 每次循环都会清除最低位的1，直到所有1都被清除
		// i := bits.TrailingZeros(t) 获取最低位1的位置，即当前要处理的数字索引
		// 如果dfs返回true，说明找到了一个解，将当前数字加入答案数组
		// 由于数字是倒序加入的，最后需要反转答案数组

		for t := uint(s); t > 0; t &= t - 1 {
			i := bits.TrailingZeros(t)
			if dfs(s^1<<i, (x*pow10[i]+nums[i])%k) {
				ans = append(ans, nums[i])
				return true
			}
		}
		return false
	}
	if !dfs(1<<n-1, 0) {
		return nil
	}
	slices.Reverse(ans)
	return ans
}

func main() {
	nums := []int{3, 12, 45}
	k := 10
	res := concatenatedDivisibility(nums, k)
	fmt.Println(res)
}
