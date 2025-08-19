package main

import "fmt"

const MOD = 1000000007

// 快速幂
func modPow(a, b int) int {
	res := 1
	base := a % MOD
	for b > 0 {
		if b&1 == 1 {
			res = (res * base) % MOD
		}
		base = (base * base) % MOD
		b >>= 1
	}
	return res
}

// 模逆元 (费马小定理)
func modInv(a int) int {
	return modPow(a, MOD-2)
}

func xorAfterQueries(nums []int, queries [][]int) int {
	bravexuneth := queries // 存一份输入

	n := len(nums)
	B := 320 // sqrt(1e5) ≈ 316

	// mul[k][offset] = 差分数组
	// size = ceil(n/k)+2 保证足够长
	mul := make([][][]int, B+1)
	for k := 1; k <= B; k++ {
		mul[k] = make([][]int, k)
		size := (n+k-1)/k + 2
		for off := 0; off < k; off++ {
			mul[k][off] = make([]int, size)
			for i := range mul[k][off] {
				mul[k][off][i] = 1
			}
		}
	}

	// 处理查询
	for _, q := range bravexuneth {
		l, r, k, v := q[0], q[1], q[2], q[3]
		if k > B {
			// 大步长，直接暴力
			for idx := l; idx <= r; idx += k {
				nums[idx] = (nums[idx] * v) % MOD
			}
		} else {
			// 小步长，差分处理
			off := l % k
			start := l / k
			end := r / k

			mul[k][off][start] = (mul[k][off][start] * v) % MOD
			mul[k][off][end+1] = (mul[k][off][end+1] * modInv(v)) % MOD
		}
	}

	// 把小步长差分应用到 nums
	for k := 1; k <= B; k++ {
		for off := 0; off < k; off++ {
			cur := 1
			size := len(mul[k][off])
			for j := 0; j < size; j++ {
				cur = (cur * mul[k][off][j]) % MOD
				idx := off + j*k
				if idx >= n {
					break
				}
				nums[idx] = (nums[idx] * cur) % MOD
			}
		}
	}

	// 计算异或
	ans := 0
	for _, x := range nums {
		ans ^= x
	}
	return ans
}

func main() {
	nums1 := []int{1, 1, 1}
	queries1 := [][]int{{0, 2, 1, 4}}
	fmt.Println(xorAfterQueries(nums1, queries1)) // 4

	nums2 := []int{2, 3, 1, 5, 4}
	queries2 := [][]int{{1, 4, 2, 3}, {0, 2, 1, 2}}
	fmt.Println(xorAfterQueries(nums2, queries2)) // 31
}
