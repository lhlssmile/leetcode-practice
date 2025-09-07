package main

import "fmt"

func prefix(n int64) int64 {
	ans := int64(0)
	base := int64(1)
	k := int64(1)

	for {
		nextBase := base * 4
		L := base
		R := nextBase - 1
		if n >= R {
			ans += (R - L + 1) * k
		} else {
			ans += (n - L + 1) * k
			break
		}
		base = nextBase
		k++
	}
	return ans
}

func minOperations(queries [][]int) int64 {
	total := int64(0)
	for _, q := range queries {
		l := int64(q[0])
		r := int64(q[1])
		S := prefix(r) - prefix(l-1)
		total += (S + 1) / 2
	}
	return total
}

// 测试函数
func testMinOperations() {
	fmt.Println("=== LeetCode 最小操作数问题 ===")

	// 测试用例1
	queries1 := [][]int{{1, 4}, {2, 6}, {3, 8}}
	result1 := minOperations(queries1)
	fmt.Printf("测试用例1: %v -> 结果: %d\n", queries1, result1)

	// 测试用例2
	queries2 := [][]int{{1, 10}, {5, 15}}
	result2 := minOperations(queries2)
	fmt.Printf("测试用例2: %v -> 结果: %d\n", queries2, result2)

	// 测试用例3
	queries3 := [][]int{{1, 1}, {2, 2}, {3, 3}}
	result3 := minOperations(queries3)
	fmt.Printf("测试用例3: %v -> 结果: %d\n", queries3, result3)

	// 测试prefix函数
	fmt.Println("\nprefix函数测试:")
	for i := int64(1); i <= 10; i++ {
		fmt.Printf("prefix(%d) = %d\n", i, prefix(i))
	}
}

func main() {
	testMinOperations()
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是(S+1)/2

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

Go语言特性:
1. 静态类型
2. 垃圾回收
3. 并发支持
4. 简洁语法
5. 快速编译
*/