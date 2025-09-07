package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

/**
 * LeetCode 1854. 人口最多的年份
 *
 * 给你一个二维整数数组 logs，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。
 * 年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在区间 [birthi, deathi - 1] 内。
 * 注意，人在死亡当年不被计入人口内。
 * 返回 人口最多 的年份。
 *
 * 算法思路：差分数组
 * 1. 使用差分数组记录每年人口变化
 * 2. 出生年份+1，死亡年份-1
 * 3. 通过前缀和还原每年实际人口
 * 4. 找到人口最多的年份
 *
 * 时间复杂度：O(n + 101) = O(n)
 * 空间复杂度：O(101) = O(1)
 */

// 差分数组解法
func maximumPopulation(logs [][]int) int {
	diff := make([]int, 101) // 1950-2050年的差分数组

	// 构建差分数组
	for _, log := range logs {
		birth, death := log[0], log[1]
		diff[birth-1950] += 1 // 出生年份人口+1
		diff[death-1950] -= 1 // 死亡年份人口-1
	}

	maxPop, year, curr := 0, 1950, 0

	// 通过前缀和还原实际人口，同时找最大值
	for i := 0; i < 101; i++ {
		curr += diff[i]
		if curr > maxPop {
			maxPop = curr
			year = 1950 + i
		}
	}

	return year
}

// 暴力解法（用于对比）
func maximumPopulationBruteForce(logs [][]int) int {
	maxPop, resultYear := 0, 1950

	// 枚举每一年
	for year := 1950; year <= 2050; year++ {
		population := 0

		// 统计这一年的人口
		for _, log := range logs {
			birth, death := log[0], log[1]
			if year >= birth && year < death {
				population++
			}
		}

		// 更新最大人口年份
		if population > maxPop {
			maxPop = population
			resultYear = year
		}
	}

	return resultYear
}

// 事件结构体
type Event struct {
	Year   int
	Change int
}

// 优化版本：使用事件排序
func maximumPopulationEvents(logs [][]int) int {
	events := make([]Event, 0, len(logs)*2)

	// 收集所有事件
	for _, log := range logs {
		events = append(events, Event{log[0], 1})  // 出生事件
		events = append(events, Event{log[1], -1}) // 死亡事件
	}

	// 按年份排序，同年份死亡事件在前
	sort.Slice(events, func(i, j int) bool {
		if events[i].Year == events[j].Year {
			return events[i].Change < events[j].Change // 死亡事件(-1)在出生事件(1)前
		}
		return events[i].Year < events[j].Year
	})

	maxPop, resultYear, currentPop := 0, 1950, 0

	// 处理事件
	for _, event := range events {
		currentPop += event.Change
		if currentPop > maxPop {
			maxPop = currentPop
			resultYear = event.Year
		}
	}

	return resultYear
}

// 使用map的解法
func maximumPopulationMap(logs [][]int) int {
	changes := make(map[int]int)

	// 记录每年的人口变化
	for _, log := range logs {
		changes[log[0]] += 1  // 出生年份+1
		changes[log[1]] -= 1  // 死亡年份-1
	}

	// 获取所有年份并排序
	years := make([]int, 0, len(changes))
	for year := range changes {
		years = append(years, year)
	}
	sort.Ints(years)

	maxPop, resultYear, currentPop := 0, 1950, 0

	// 按年份顺序处理变化
	for _, year := range years {
		currentPop += changes[year]
		if currentPop > maxPop {
			maxPop = currentPop
			resultYear = year
		}
	}

	return resultYear
}

// 差分数组工具结构体
type DifferenceArray struct {
	diff   []int
	offset int
}

// 创建差分数组
func NewDifferenceArray(start, end int) *DifferenceArray {
	return &DifferenceArray{
		diff:   make([]int, end-start+1),
		offset: start,
	}
}

// 区间更新
func (da *DifferenceArray) Update(left, right, delta int) {
	da.diff[left-da.offset] += delta
	if right+1-da.offset < len(da.diff) {
		da.diff[right+1-da.offset] -= delta
	}
}

// 获取前缀和数组
func (da *DifferenceArray) GetPrefixSum() []int {
	result := make([]int, len(da.diff))
	result[0] = da.diff[0]
	for i := 1; i < len(da.diff); i++ {
		result[i] = result[i-1] + da.diff[i]
	}
	return result
}

// 找到最大值的索引
func (da *DifferenceArray) FindMaxIndex() int {
	prefixSum := da.GetPrefixSum()
	maxVal, maxIdx := prefixSum[0], 0
	for i := 1; i < len(prefixSum); i++ {
		if prefixSum[i] > maxVal {
			maxVal = prefixSum[i]
			maxIdx = i
		}
	}
	return maxIdx + da.offset
}

// 使用工具结构体的解法
func maximumPopulationWithUtil(logs [][]int) int {
	diffArray := NewDifferenceArray(1950, 2050)

	for _, log := range logs {
		diffArray.Update(log[0], log[1]-1, 1)
	}

	return diffArray.FindMaxIndex()
}

// 函数式编程风格解法
func maximumPopulationFunctional(logs [][]int) int {
	// 使用闭包创建差分数组处理器
	processDiff := func() int {
		diff := make([]int, 101)

		// 应用所有变化
		for _, log := range logs {
			diff[log[0]-1950] += 1
			diff[log[1]-1950] -= 1
		}

		// 找到最大人口年份
		maxPop, year, curr := 0, 1950, 0
		for i := 0; i < 101; i++ {
			curr += diff[i]
			if curr > maxPop {
				maxPop, year = curr, 1950+i
			}
		}
		return year
	}

	return processDiff()
}

// 并发版本（适用于大数据）
func maximumPopulationConcurrent(logs [][]int) int {
	const numWorkers = 4
	const chunkSize = len(logs) / numWorkers

	// 创建通道收集结果
	resultChan := make(chan []int, numWorkers)

	// 启动工作协程
	for i := 0; i < numWorkers; i++ {
		go func(start int) {
			diff := make([]int, 101)
			end := start + chunkSize
			if start+chunkSize > len(logs) {
				end = len(logs)
			}

			// 处理分配的日志
			for j := start; j < end; j++ {
				log := logs[j]
				diff[log[0]-1950] += 1
				diff[log[1]-1950] -= 1
			}

			resultChan <- diff
		}(i * chunkSize)
	}

	// 合并结果
	finalDiff := make([]int, 101)
	for i := 0; i < numWorkers; i++ {
		diff := <-resultChan
		for j := 0; j < 101; j++ {
			finalDiff[j] += diff[j]
		}
	}

	// 找到最大人口年份
	maxPop, year, curr := 0, 1950, 0
	for i := 0; i < 101; i++ {
		curr += finalDiff[i]
		if curr > maxPop {
			maxPop = curr
			year = 1950 + i
		}
	}

	return year
}

// 泛型版本的差分数组（Go 1.18+）
type GenericDifferenceArray[T comparable] struct {
	diff   []int
	offset T
	toInt  func(T) int
	fromInt func(int) T
}

// 创建泛型差分数组
func NewGenericDifferenceArray[T comparable](start, end T, toInt func(T) int, fromInt func(int) T) *GenericDifferenceArray[T] {
	startInt, endInt := toInt(start), toInt(end)
	return &GenericDifferenceArray[T]{
		diff:    make([]int, endInt-startInt+1),
		offset:  start,
		toInt:   toInt,
		fromInt: fromInt,
	}
}

// 泛型区间更新
func (gda *GenericDifferenceArray[T]) Update(left, right T, delta int) {
	leftInt, rightInt := gda.toInt(left), gda.toInt(right)
	offsetInt := gda.toInt(gda.offset)
	gda.diff[leftInt-offsetInt] += delta
	if rightInt+1-offsetInt < len(gda.diff) {
		gda.diff[rightInt+1-offsetInt] -= delta
	}
}

// 泛型找最大值索引
func (gda *GenericDifferenceArray[T]) FindMaxIndex() T {
	prefixSum := make([]int, len(gda.diff))
	prefixSum[0] = gda.diff[0]
	for i := 1; i < len(gda.diff); i++ {
		prefixSum[i] = prefixSum[i-1] + gda.diff[i]
	}

	maxVal, maxIdx := prefixSum[0], 0
	for i := 1; i < len(prefixSum); i++ {
		if prefixSum[i] > maxVal {
			maxVal = prefixSum[i]
			maxIdx = i
		}
	}

	offsetInt := gda.toInt(gda.offset)
	return gda.fromInt(maxIdx + offsetInt)
}

// 使用泛型的解法
func maximumPopulationGeneric(logs [][]int) int {
	toInt := func(year int) int { return year }
	fromInt := func(idx int) int { return idx }

	diffArray := NewGenericDifferenceArray(1950, 2050, toInt, fromInt)

	for _, log := range logs {
		diffArray.Update(log[0], log[1]-1, 1)
	}

	return diffArray.FindMaxIndex()
}

// 测试函数
func testMaximumPopulation() {
	// 测试用例1
	logs1 := [][]int{{1950, 1961}, {1960, 1971}, {1970, 1981}}
	fmt.Printf("测试用例1 - 差分数组: %d\n", maximumPopulation(logs1))        // 期望: 1960
	fmt.Printf("测试用例1 - 暴力解法: %d\n", maximumPopulationBruteForce(logs1))
	fmt.Printf("测试用例1 - 事件解法: %d\n", maximumPopulationEvents(logs1))
	fmt.Printf("测试用例1 - Map解法: %d\n", maximumPopulationMap(logs1))
	fmt.Printf("测试用例1 - 工具类: %d\n", maximumPopulationWithUtil(logs1))
	fmt.Printf("测试用例1 - 函数式: %d\n", maximumPopulationFunctional(logs1))
	fmt.Printf("测试用例1 - 泛型: %d\n", maximumPopulationGeneric(logs1))

	// 测试用例2
	logs2 := [][]int{{1993, 1999}, {2000, 2010}}
	fmt.Printf("测试用例2: %d\n", maximumPopulation(logs2)) // 期望: 1993

	// 测试用例3：边界情况
	logs3 := [][]int{{1950, 1951}, {1951, 1952}, {1952, 1953}}
	fmt.Printf("测试用例3: %d\n", maximumPopulation(logs3)) // 期望: 1950

	// 测试用例4：重叠区间
	logs4 := [][]int{{1950, 1960}, {1955, 1965}, {1958, 1968}}
	fmt.Printf("测试用例4: %d\n", maximumPopulation(logs4)) // 期望: 1958
}

// 性能测试
func performanceTest() {
	rand.Seed(42)

	// 生成大量测试数据
	largeLogs := make([][]int, 100000)
	for i := 0; i < len(largeLogs); i++ {
		birth := 1950 + rand.Intn(80)
		death := birth + 1 + rand.Intn(20)
		if death > 2050 {
			death = 2050
		}
		largeLogs[i] = []int{birth, death}
	}

	// 测试不同算法的性能
	algorithms := map[string]func([][]int) int{
		"差分数组":  maximumPopulation,
		"事件排序":  maximumPopulationEvents,
		"Map解法": maximumPopulationMap,
		"并发版本":  maximumPopulationConcurrent,
	}

	for name, algorithm := range algorithms {
		start := time.Now()
		result := algorithm(largeLogs)
		duration := time.Since(start)
		fmt.Printf("%s耗时: %.2f ms, 结果: %d\n", name, float64(duration.Nanoseconds())/1e6, result)
	}
}

func main() {
	fmt.Println("=== LeetCode 1854: 人口最多的年份 ===")
	testMaximumPopulation()
	fmt.Println("\n=== 性能测试 ===")
	performanceTest()
}

/*
算法特点分析：

1. 差分数组解法 (推荐)
   - 时间复杂度：O(n + 101)
   - 空间复杂度：O(101)
   - 适用于区间更新问题
   - 代码简洁，效率最高

2. 暴力解法
   - 时间复杂度：O(101 * n)
   - 空间复杂度：O(1)
   - 思路直观，但效率较低

3. 事件排序解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 适用于年份范围很大的情况

4. Map解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 自动去重，代码简洁

5. 并发版本
   - 适用于大数据处理
   - 利用多核优势
   - 需要注意数据竞争

6. 泛型版本
   - 类型安全
   - 代码复用性高
   - Go 1.18+ 特性

Go语言特性应用：
- 切片：动态数组
- 结构体：数据封装
- 方法：面向对象编程
- 接口：多态性
- 协程：并发编程
- 通道：协程通信
- 泛型：类型安全和代码复用
- 闭包：函数式编程
- defer：资源管理
- 包管理：模块化
*/