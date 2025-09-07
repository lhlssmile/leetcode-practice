package main

import "fmt"

func canThreePartsEqualSum(arr []int) bool {
	sum := 0
	for _, v := range arr {
		sum += v
	}
	if sum%3 != 0 {
		return false
	}

	part, currentSum := 0, 0

	for _, x := range arr {
		currentSum += x
		if currentSum == sum/3 {
			currentSum = 0
			part++
		}
	}
	return part >= 3
}

// 测试函数
func testCanThreePartsEqualSum() {
	fmt.Println("=== LeetCode 1013: 将数组分成和相等的三个部分 ===")

	// 测试用例1
	arr1 := []int{0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1}
	result1 := canThreePartsEqualSum(arr1)
	fmt.Printf("测试用例1: %v -> 结果: %t\n", arr1, result1)

	// 测试用例2
	arr2 := []int{0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1}
	result2 := canThreePartsEqualSum(arr2)
	fmt.Printf("测试用例2: %v -> 结果: %t\n", arr2, result2)

	// 测试用例3
	arr3 := []int{3, 3, 3}
	result3 := canThreePartsEqualSum(arr3)
	fmt.Printf("测试用例3: %v -> 结果: %t\n", arr3, result3)

	// 测试用例4
	arr4 := []int{1, 1, 1, 1}
	result4 := canThreePartsEqualSum(arr4)
	fmt.Printf("测试用例4: %v -> 结果: %t\n", arr4, result4)

	// 测试用例5
	arr5 := []int{0, 0, 0, 0}
	result5 := canThreePartsEqualSum(arr5)
	fmt.Printf("测试用例5: %v -> 结果: %t\n", arr5, result5)
}

func main() {
	testCanThreePartsEqualSum()
}

/*
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回false
2. 遍历数组，累加当前和
3. 当累加和等于目标值(sum/3)时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)

Go语言特性:
1. 静态类型
2. 垃圾回收
3. 并发支持
4. 简洁语法
5. 快速编译
*/