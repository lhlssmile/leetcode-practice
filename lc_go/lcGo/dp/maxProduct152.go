package main

import "fmt"

// maxProduct 计算数组中连续子数组的最大乘积
// 使用动态规划，维护两个数组：
// dpMax[i] 表示以 nums[i] 结尾的子数组的最大乘积
// dpMin[i] 表示以 nums[i] 结尾的子数组的最小乘积
func maxProduct(nums []int)(maxProducts int) {
	n := len(nums)
	// 初始化 dp 数组
	dpMax := make([]int,n)
	dpMin := make([]int,n)
	
	// 初始化第一个元素
	dpMax[0] = nums[0]
	dpMin[0] = nums[0]
	maxProducts = nums[0]

	// 遍历数组，计算每个位置的最大和最小乘积
	for i := 1; i < n; i++ {
		// 当前元素可能是新的子数组起点，或者与前面的子数组相乘
		// 需要考虑正负号的影响，所以同时维护最大和最小值
		dpMax[i] = max(nums[i], max(dpMax[i-1]*nums[i], dpMin[i-1]*nums[i]))
		dpMin[i] = min(nums[i], min(dpMax[i-1]*nums[i], dpMin[i-1]*nums[i]))
		// 更新全局最大值
		maxProducts = max(maxProducts, dpMax[i])
	}
	return 
}

func main(){
	nums := []int{-2,3,-4}
	res := maxProduct(nums)
	fmt.Println(res)
}