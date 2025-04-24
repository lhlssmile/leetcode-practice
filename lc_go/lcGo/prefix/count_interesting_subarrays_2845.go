package prefix

import (
	"fmt"
)

// countInterestingSubarrays 统计趣味子数组
// LeetCode 2845: https://leetcode.cn/problems/count-interesting-subarrays/
// 思路：前缀和 + 哈希表 + 模运算
func countInterestingSubarrays(nums []int, modulo int, k int) int64 {
	count := make(map[int]int64) // 哈希表，存储 <前缀和 % modulo, 出现次数>
	count[0] = 1                 // 初始化，处理 l=0 的情况，空前缀和模 modulo 为 0
	var ans int64 = 0            // 结果
	prefixSum := 0               // 当前的前缀和（满足 num % modulo == k 的元素个数）

	for _, num := range nums { // 遍历数组
		if num%modulo == k { // 如果当前元素满足条件
			prefixSum++ // 前缀和加 1
		}

		// 计算我们需要的前一个前缀和模 modulo 的值
		// P[l] % modulo == (P[r+1] % modulo - k % modulo + modulo) % modulo
		need := (prefixSum - k%modulo + modulo) % modulo

		// 查找哈希表中是否存在需要的 need 值
		if val, ok := count[need]; ok {
			ans += val // 如果存在，将对应的次数加到结果中
		}

		// 将当前的前缀和模 modulo 加入哈希表
		count[prefixSum%modulo]++
	}
	return ans
}

func main() {
	nums1 := []int{3, 1, 9, 6}
	modulo1 := 3
	k1 := 0
	fmt.Println(countInterestingSubarrays(nums1, modulo1, k1)) // 预期输出 2

	nums2 := []int{3, 2, 4}
	modulo2 := 2
	k2 := 1
	fmt.Println(countInterestingSubarrays(nums2, modulo2, k2)) // 预期输出 3
}