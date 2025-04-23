package main

import (
	"fmt"
	"strconv"
)

/**
 * @brief LeetCode 1399. 统计最大组的数目
 *
 * 给你一个整数 n。
 * 请你先求出从 1 到 n 的每个整数 10 进制表示下的数位和（每一位上的数字相加）。
 * 然后把数位和相等的数字放到同一个组中。
 * 请你统计每个组中的数字数目，并返回数字数目并列最多的组有多少个。
 *
 * 示例 1：
 * 输入：n = 13
 * 输出：4
 * 解释：数位和为 1 的有 1、10，数位和为 2 的有 2、11，数位和为 3 的有 3、12，数位和为 4 的有 4、13，以此类推。
 * 共有 9 个组，将数位和相同的数字分为同一组：
 * [1, 10], [2, 11], [3, 12], [4, 13], [5], [6], [7], [8], [9]
 * 最多的组是数位和为 1, 2, 3, 4 的组，每个组中有 2 个数。
 * 所以最终答案是 4。
 *
 * 解题思路：
 * 使用数位 DP (Digit DP) 来解决。
 * 目标是计算对于每个可能的数位和 `target` (1 到 36，因为 n <= 10000，最大数位和是 9+9+9+9=36)，
 * 有多少个小于等于 n 的数字，其数位和等于 `target`。
 * 然后找到出现次数最多的数位和，并统计有多少个这样的数位和。
 */

var (
	dp [5][37]int // dp[pos][sum]
	s  string
)

/**
 * @brief 计算数字数目并列最多的组有多少个
 * @param n 上限整数
 * @return 数字数目并列最多的组的数量
 */
func countLargestGroup(n int) int {
	s = strconv.Itoa(n)
	maxCount := 0
	ans := 0

	// 遍历所有可能的数位和 target (1 到 36)
	for target := 1; target <= 36; target++ {
		// 重置 dp 数组，-1 表示未计算
		for i := range dp {
			for j := range dp[i] {
				dp[i][j] = -1
			}
		}
		cnt := dfs(0, 0, true, target)

		if cnt > maxCount {
			ans = 1
			maxCount = cnt
		} else if cnt > 0 && cnt == maxCount {
			ans++
		}
	}
	return ans
}

/**
 * @brief 数位 DP 的核心函数 (深度优先搜索)
 * @param pos 当前处理到的数字位数 (从左到右, 0-indexed)
 * @param sum 当前累加的数位和
 * @param tight 是否受到 n 的约束 (true 表示当前位最大只能取 s[pos])
 * @param target 目标数位和
 * @return 从当前状态出发，能够构成数位和为 target 的数字个数
 */
func dfs(pos int, sum int, tight bool, target int) int {
	if pos == len(s) {
		if sum == target {
			return 1
		}
		return 0
	}

	// 记忆化搜索：仅在非 tight 状态下使用
	if !tight && dp[pos][sum] != -1 {
		return dp[pos][sum]
	}

	res := 0
	up := 9
	if tight {
		up = int(s[pos] - '0')
	}

	for d := 0; d <= up; d++ {
		if sum+d > target { // 剪枝
			continue
		}
		res += dfs(pos+1, sum+d, tight && (d == up), target)
	}

	// 仅在非 tight 状态下记录结果
	if !tight {
		dp[pos][sum] = res
	}
	return res
}

// 主函数用于测试
func main() {
	fmt.Println(countLargestGroup(13)) // 输出 4
	fmt.Println(countLargestGroup(2))  // 输出 2
	fmt.Println(countLargestGroup(1))  // 输出 1
	fmt.Println(countLargestGroup(46)) // 输出 6
}
