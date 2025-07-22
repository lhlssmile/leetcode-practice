# Go语言高级特性与算法应用 🚀

专为算法竞赛和面试准备的Go语言进阶指南！

## 1. 指针与引用 - Go vs C++

### 1.1 Go语言的指针系统
```go
// Go语言指针基础
func pointerBasics() {
    // 声明和初始化
    var x int = 42
    var p *int = &x        // p是指向int的指针
    
    fmt.Printf("x的值: %d\n", x)      // 42
    fmt.Printf("x的地址: %p\n", &x)    // 0x...
    fmt.Printf("p的值: %p\n", p)      // 0x...（同&x）
    fmt.Printf("p指向的值: %d\n", *p)  // 42
    
    // 通过指针修改值
    *p = 100
    fmt.Printf("修改后x的值: %d\n", x) // 100
}

// 指针作为函数参数
func swap(a, b *int) {
    *a, *b = *b, *a
}

func testSwap() {
    x, y := 10, 20
    fmt.Printf("交换前: x=%d, y=%d\n", x, y)
    swap(&x, &y)
    fmt.Printf("交换后: x=%d, y=%d\n", x, y)
}
```

### 1.2 Go vs C++ 指针对比

| 特性 | Go | C++ |
|------|----|-----|
| **指针声明** | `var p *int` | `int* p` 或 `int *p` |
| **取地址** | `&variable` | `&variable` |
| **解引用** | `*pointer` | `*pointer` |
| **指针运算** | ❌ 不支持 | ✅ 支持 `p++, p+5` |
| **空指针** | `nil` | `nullptr` (C++11+) |
| **引用** | ❌ 无引用概念 | ✅ `int& ref = var` |
| **智能指针** | ❌ 无需要（GC） | ✅ `shared_ptr, unique_ptr` |
| **内存管理** | 🤖 自动GC | 🔧 手动管理 |

```go
// Go语言示例
func goPointerExample() {
    nums := []int{1, 2, 3}
    
    // 传递切片（引用语义）
    modifySlice(nums)
    fmt.Println(nums) // [100, 2, 3] - 被修改了！
    
    // 传递指针
    x := 42
    modifyValue(&x)
    fmt.Println(x) // 100
}

func modifySlice(s []int) {
    if len(s) > 0 {
        s[0] = 100 // 直接修改原切片
    }
}

func modifyValue(p *int) {
    *p = 100
}
```

```cpp
// C++对比示例
void cppPointerExample() {
    vector<int> nums = {1, 2, 3};
    
    // 传递引用
    modifyVector(nums);
    cout << nums[0]; // 100 - 被修改了！
    
    // 传递指针
    int x = 42;
    modifyValue(&x);
    cout << x; // 100
}

void modifyVector(vector<int>& v) {
    if (!v.empty()) {
        v[0] = 100;
    }
}

void modifyValue(int* p) {
    *p = 100;
}
```

## 2. Go语言类型系统详解

### 2.1 数值类型全家桶
```go
// 整数类型
var (
    // 有符号整数
    i8  int8  = -128        // 1字节，范围: -128 到 127
    i16 int16 = -32768      // 2字节，范围: -32,768 到 32,767
    i32 int32 = -2147483648 // 4字节，范围: -2^31 到 2^31-1
    i64 int64 = -9223372036854775808 // 8字节，范围: -2^63 到 2^63-1
    
    // 无符号整数
    u8  uint8  = 255        // 1字节，范围: 0 到 255
    u16 uint16 = 65535      // 2字节，范围: 0 到 65,535
    u32 uint32 = 4294967295 // 4字节，范围: 0 到 2^32-1
    u64 uint64 = 18446744073709551615 // 8字节，范围: 0 到 2^64-1
    
    // 平台相关
    i   int  = -2147483648  // 32位系统4字节，64位系统8字节
    u   uint = 4294967295   // 32位系统4字节，64位系统8字节
    ptr uintptr = 0x1000    // 存储指针的整数类型
    
    // 浮点数
    f32 float32 = 3.14159   // 4字节，IEEE-754 32位
    f64 float64 = 3.141592653589793 // 8字节，IEEE-754 64位
    
    // 复数
    c64  complex64  = 1 + 2i  // 8字节（两个float32）
    c128 complex128 = 1 + 2i  // 16字节（两个float64）
    
    // 字符和字符串
    b    byte = 'A'           // uint8的别名
    r    rune = '中'          // int32的别名，Unicode码点
    str  string = "Hello"     // UTF-8编码的字符串
    
    // 布尔类型
    flag bool = true          // 1字节，true或false
)

// 类型转换示例
func typeConversion() {
    var i int = 42
    var f float64 = float64(i)  // 显式转换
    var u uint = uint(i)        // 显式转换
    
    // 字符串转换
    str := fmt.Sprintf("%d", i)  // int转string
    num, err := strconv.Atoi(str) // string转int
    if err != nil {
        log.Fatal(err)
    }
    
    fmt.Printf("i=%d, f=%f, u=%d, str=%s, num=%d\n", i, f, u, str, num)
}
```

### 2.2 算法中的类型选择策略
```go
// 算法竞赛中的类型选择
func algorithmTypeChoice() {
    // 1. 数组索引：使用int（最常用）
    nums := make([]int, 1000000)
    for i := 0; i < len(nums); i++ {
        nums[i] = i
    }
    
    // 2. 大数计算：使用int64
    var sum int64
    for _, num := range nums {
        sum += int64(num) // 防止溢出
    }
    
    // 3. 位运算：使用uint或具体位数类型
    var mask uint32 = 0xFFFFFFFF
    result := mask & uint32(42)
    
    // 4. 字符处理：使用byte和rune
    text := "Hello, 世界!"
    for i, char := range text {
        if char > 127 { // 非ASCII字符
            fmt.Printf("位置%d: Unicode字符 %c\n", i, char)
        }
    }
    
    // 5. 精确计算：避免float，使用整数
    // 错误示例：
    // var price float64 = 0.1 + 0.2 // 可能不等于0.3
    
    // 正确示例：
    priceInCents := 10 + 20 // 以分为单位计算
    fmt.Printf("价格: %.2f元\n", float64(priceInCents)/100)
}
```

## 3. 高级数据结构与算法应用

### 3.1 自定义类型与方法
```go
// 定义链表节点
type ListNode struct {
    Val  int
    Next *ListNode
}

// 为ListNode添加方法
func (node *ListNode) String() string {
    if node == nil {
        return "nil"
    }
    return fmt.Sprintf("%d -> %s", node.Val, node.Next)
}

// 链表操作方法
func (node *ListNode) Append(val int) *ListNode {
    if node == nil {
        return &ListNode{Val: val}
    }
    
    current := node
    for current.Next != nil {
        current = current.Next
    }
    current.Next = &ListNode{Val: val}
    return node
}

func (node *ListNode) Length() int {
    count := 0
    current := node
    for current != nil {
        count++
        current = current.Next
    }
    return count
}

// 使用示例
func linkedListExample() {
    var head *ListNode
    head = head.Append(1)
    head = head.Append(2)
    head = head.Append(3)
    
    fmt.Printf("链表: %s\n", head)
    fmt.Printf("长度: %d\n", head.Length())
}
```

### 3.2 接口与多态
```go
// 定义数据结构接口
type DataStructure interface {
    Size() int
    IsEmpty() bool
    Clear()
}

// 栈实现
type Stack struct {
    items []int
}

func (s *Stack) Push(item int) {
    s.items = append(s.items, item)
}

func (s *Stack) Pop() (int, bool) {
    if len(s.items) == 0 {
        return 0, false
    }
    index := len(s.items) - 1
    item := s.items[index]
    s.items = s.items[:index]
    return item, true
}

func (s *Stack) Size() int {
    return len(s.items)
}

func (s *Stack) IsEmpty() bool {
    return len(s.items) == 0
}

func (s *Stack) Clear() {
    s.items = s.items[:0]
}

// 队列实现
type Queue struct {
    items []int
}

func (q *Queue) Enqueue(item int) {
    q.items = append(q.items, item)
}

func (q *Queue) Dequeue() (int, bool) {
    if len(q.items) == 0 {
        return 0, false
    }
    item := q.items[0]
    q.items = q.items[1:]
    return item, true
}

func (q *Queue) Size() int {
    return len(q.items)
}

func (q *Queue) IsEmpty() bool {
    return len(q.items) == 0
}

func (q *Queue) Clear() {
    q.items = q.items[:0]
}

// 多态使用
func useDataStructure(ds DataStructure) {
    fmt.Printf("大小: %d, 是否为空: %t\n", ds.Size(), ds.IsEmpty())
    if !ds.IsEmpty() {
        ds.Clear()
        fmt.Printf("清空后大小: %d\n", ds.Size())
    }
}

func polymorphismExample() {
    stack := &Stack{}
    stack.Push(1)
    stack.Push(2)
    
    queue := &Queue{}
    queue.Enqueue(1)
    queue.Enqueue(2)
    
    fmt.Println("栈:")
    useDataStructure(stack)
    
    fmt.Println("队列:")
    useDataStructure(queue)
}
```

### 3.3 泛型编程（Go 1.18+）
```go
// 泛型栈
type GenericStack[T any] struct {
    items []T
}

func (s *GenericStack[T]) Push(item T) {
    s.items = append(s.items, item)
}

func (s *GenericStack[T]) Pop() (T, bool) {
    var zero T
    if len(s.items) == 0 {
        return zero, false
    }
    index := len(s.items) - 1
    item := s.items[index]
    s.items = s.items[:index]
    return item, true
}

// 泛型比较函数
type Ordered interface {
    ~int | ~int8 | ~int16 | ~int32 | ~int64 |
    ~uint | ~uint8 | ~uint16 | ~uint32 | ~uint64 |
    ~float32 | ~float64 | ~string
}

func Max[T Ordered](a, b T) T {
    if a > b {
        return a
    }
    return b
}

func Min[T Ordered](a, b T) T {
    if a < b {
        return a
    }
    return b
}

// 泛型二分查找
func BinarySearch[T Ordered](arr []T, target T) int {
    left, right := 0, len(arr)-1
    
    for left <= right {
        mid := left + (right-left)/2
        if arr[mid] == target {
            return mid
        } else if arr[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    return -1
}

// 使用示例
func genericsExample() {
    // 整数栈
    intStack := &GenericStack[int]{}
    intStack.Push(1)
    intStack.Push(2)
    val, ok := intStack.Pop()
    fmt.Printf("弹出: %d, 成功: %t\n", val, ok)
    
    // 字符串栈
    strStack := &GenericStack[string]{}
    strStack.Push("hello")
    strStack.Push("world")
    str, ok := strStack.Pop()
    fmt.Printf("弹出: %s, 成功: %t\n", str, ok)
    
    // 泛型函数
    fmt.Printf("Max(10, 20) = %d\n", Max(10, 20))
    fmt.Printf("Min(3.14, 2.71) = %f\n", Min(3.14, 2.71))
    
    // 泛型二分查找
    nums := []int{1, 3, 5, 7, 9, 11}
    index := BinarySearch(nums, 7)
    fmt.Printf("7在数组中的位置: %d\n", index)
}
```

## 4. 内存管理与性能优化

### 4.1 切片的内存模型
```go
func sliceMemoryModel() {
    // 切片的三要素：指针、长度、容量
    nums := make([]int, 3, 5) // 长度3，容量5
    fmt.Printf("长度: %d, 容量: %d\n", len(nums), cap(nums))
    
    // 切片扩容机制
    for i := 0; i < 10; i++ {
        nums = append(nums, i)
        fmt.Printf("添加%d后 - 长度: %d, 容量: %d\n", i, len(nums), cap(nums))
    }
    
    // 预分配优化
    // 错误方式：频繁扩容
    var badSlice []int
    for i := 0; i < 1000000; i++ {
        badSlice = append(badSlice, i) // 可能触发多次扩容
    }
    
    // 正确方式：预分配
    goodSlice := make([]int, 0, 1000000) // 预分配容量
    for i := 0; i < 1000000; i++ {
        goodSlice = append(goodSlice, i) // 不会扩容
    }
}

// 切片复制与共享
func sliceCopyAndShare() {
    original := []int{1, 2, 3, 4, 5}
    
    // 切片操作（共享底层数组）
    slice1 := original[1:4]  // [2, 3, 4]
    slice2 := original[2:]   // [3, 4, 5]
    
    fmt.Printf("原始: %v\n", original)
    fmt.Printf("slice1: %v\n", slice1)
    fmt.Printf("slice2: %v\n", slice2)
    
    // 修改slice1会影响原数组
    slice1[0] = 100
    fmt.Printf("修改slice1后:\n")
    fmt.Printf("原始: %v\n", original) // [1, 100, 3, 4, 5]
    fmt.Printf("slice2: %v\n", slice2) // [3, 4, 5] - 未受影响
    
    // 深拷贝避免共享
    copied := make([]int, len(original))
    copy(copied, original)
    copied[0] = 999
    fmt.Printf("深拷贝后:\n")
    fmt.Printf("原始: %v\n", original) // 不变
    fmt.Printf("拷贝: %v\n", copied)   // [999, ...]
}
```

### 4.2 字符串优化技巧
```go
func stringOptimization() {
    // 字符串拼接优化
    
    // 低效方式：频繁创建新字符串
    var result string
    for i := 0; i < 1000; i++ {
        result += fmt.Sprintf("item%d ", i) // 每次都创建新字符串
    }
    
    // 高效方式1：使用strings.Builder
    var builder strings.Builder
    builder.Grow(1000 * 10) // 预分配容量
    for i := 0; i < 1000; i++ {
        builder.WriteString(fmt.Sprintf("item%d ", i))
    }
    result1 := builder.String()
    
    // 高效方式2：使用字节切片
    var buffer []byte
    for i := 0; i < 1000; i++ {
        buffer = append(buffer, fmt.Sprintf("item%d ", i)...)
    }
    result2 := string(buffer)
    
    // 字符串与字节切片转换
    str := "Hello, World!"
    bytes := []byte(str)        // 字符串转字节切片（拷贝）
    str2 := string(bytes)       // 字节切片转字符串（拷贝）
    
    // 零拷贝转换（不安全，仅在确保不修改时使用）
    import "unsafe"
    
    // 字符串转字节切片（零拷贝，只读）
    unsafeBytes := *(*[]byte)(unsafe.Pointer(&str))
    
    // 字节切片转字符串（零拷贝）
    unsafeStr := *(*string)(unsafe.Pointer(&bytes))
    
    fmt.Printf("结果长度: %d, %d\n", len(result1), len(result2))
}
```

## 5. 并发编程基础（算法相关）

### 5.1 Goroutine与Channel
```go
// 并行计算示例
func parallelSum(nums []int) int {
    if len(nums) <= 1000 {
        // 小数组直接计算
        sum := 0
        for _, num := range nums {
            sum += num
        }
        return sum
    }
    
    // 大数组分块并行计算
    numWorkers := 4
    chunkSize := len(nums) / numWorkers
    resultChan := make(chan int, numWorkers)
    
    for i := 0; i < numWorkers; i++ {
        start := i * chunkSize
        end := start + chunkSize
        if i == numWorkers-1 {
            end = len(nums) // 最后一块包含剩余元素
        }
        
        go func(chunk []int) {
            sum := 0
            for _, num := range chunk {
                sum += num
            }
            resultChan <- sum
        }(nums[start:end])
    }
    
    // 收集结果
    totalSum := 0
    for i := 0; i < numWorkers; i++ {
        totalSum += <-resultChan
    }
    
    return totalSum
}

// 生产者-消费者模式
func producerConsumer() {
    tasks := make(chan int, 10)
    results := make(chan int, 10)
    
    // 生产者
    go func() {
        defer close(tasks)
        for i := 1; i <= 100; i++ {
            tasks <- i
        }
    }()
    
    // 消费者（多个worker）
    numWorkers := 3
    var wg sync.WaitGroup
    
    for w := 0; w < numWorkers; w++ {
        wg.Add(1)
        go func(workerID int) {
            defer wg.Done()
            for task := range tasks {
                // 模拟计算（平方）
                result := task * task
                results <- result
                fmt.Printf("Worker %d: %d^2 = %d\n", workerID, task, result)
            }
        }(w)
    }
    
    // 等待所有worker完成
    go func() {
        wg.Wait()
        close(results)
    }()
    
    // 收集结果
    var allResults []int
    for result := range results {
        allResults = append(allResults, result)
    }
    
    fmt.Printf("共处理了 %d 个结果\n", len(allResults))
}
```

### 5.2 同步原语
```go
import (
    "sync"
    "sync/atomic"
)

// 互斥锁示例
type SafeCounter struct {
    mu    sync.Mutex
    count int
}

func (c *SafeCounter) Increment() {
    c.mu.Lock()
    defer c.mu.Unlock()
    c.count++
}

func (c *SafeCounter) Value() int {
    c.mu.Lock()
    defer c.mu.Unlock()
    return c.count
}

// 原子操作示例
type AtomicCounter struct {
    count int64
}

func (c *AtomicCounter) Increment() {
    atomic.AddInt64(&c.count, 1)
}

func (c *AtomicCounter) Value() int64 {
    return atomic.LoadInt64(&c.count)
}

// 性能对比
func concurrencyBenchmark() {
    const numGoroutines = 1000
    const numIncrements = 1000
    
    // 测试互斥锁
    safeCounter := &SafeCounter{}
    var wg1 sync.WaitGroup
    
    start := time.Now()
    for i := 0; i < numGoroutines; i++ {
        wg1.Add(1)
        go func() {
            defer wg1.Done()
            for j := 0; j < numIncrements; j++ {
                safeCounter.Increment()
            }
        }()
    }
    wg1.Wait()
    mutexTime := time.Since(start)
    
    // 测试原子操作
    atomicCounter := &AtomicCounter{}
    var wg2 sync.WaitGroup
    
    start = time.Now()
    for i := 0; i < numGoroutines; i++ {
        wg2.Add(1)
        go func() {
            defer wg2.Done()
            for j := 0; j < numIncrements; j++ {
                atomicCounter.Increment()
            }
        }()
    }
    wg2.Wait()
    atomicTime := time.Since(start)
    
    fmt.Printf("互斥锁结果: %d, 耗时: %v\n", safeCounter.Value(), mutexTime)
    fmt.Printf("原子操作结果: %d, 耗时: %v\n", atomicCounter.Value(), atomicTime)
}
```

## 6. 算法实现技巧

### 6.1 常用算法模板
```go
// 快速排序
func quickSort(arr []int, low, high int) {
    if low < high {
        pi := partition(arr, low, high)
        quickSort(arr, low, pi-1)
        quickSort(arr, pi+1, high)
    }
}

func partition(arr []int, low, high int) int {
    pivot := arr[high]
    i := low - 1
    
    for j := low; j < high; j++ {
        if arr[j] < pivot {
            i++
            arr[i], arr[j] = arr[j], arr[i]
        }
    }
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i + 1
}

// 归并排序
func mergeSort(arr []int) []int {
    if len(arr) <= 1 {
        return arr
    }
    
    mid := len(arr) / 2
    left := mergeSort(arr[:mid])
    right := mergeSort(arr[mid:])
    
    return merge(left, right)
}

func merge(left, right []int) []int {
    result := make([]int, 0, len(left)+len(right))
    i, j := 0, 0
    
    for i < len(left) && j < len(right) {
        if left[i] <= right[j] {
            result = append(result, left[i])
            i++
        } else {
            result = append(result, right[j])
            j++
        }
    }
    
    result = append(result, left[i:]...)
    result = append(result, right[j:]...)
    
    return result
}

// 动态规划：最长公共子序列
func longestCommonSubsequence(text1, text2 string) int {
    m, n := len(text1), len(text2)
    dp := make([][]int, m+1)
    for i := range dp {
        dp[i] = make([]int, n+1)
    }
    
    for i := 1; i <= m; i++ {
        for j := 1; j <= n; j++ {
            if text1[i-1] == text2[j-1] {
                dp[i][j] = dp[i-1][j-1] + 1
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
            }
        }
    }
    
    return dp[m][n]
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```

### 6.2 位运算技巧
```go
// 位运算常用操作
func bitOperations() {
    x := 42 // 二进制: 101010
    
    // 基本操作
    fmt.Printf("x = %d (二进制: %b)\n", x, x)
    fmt.Printf("x & 1 = %d (检查最低位)\n", x&1)
    fmt.Printf("x | 1 = %d (设置最低位)\n", x|1)
    fmt.Printf("x ^ 1 = %d (翻转最低位)\n", x^1)
    fmt.Printf("x << 1 = %d (左移一位，相当于*2)\n", x<<1)
    fmt.Printf("x >> 1 = %d (右移一位，相当于/2)\n", x>>1)
    
    // 高级技巧
    fmt.Printf("x & (x-1) = %d (清除最低位的1)\n", x&(x-1))
    fmt.Printf("x & (-x) = %d (保留最低位的1)\n", x&(-x))
    fmt.Printf("^x = %d (按位取反)\n", ^x)
    
    // 判断是否为2的幂
    isPowerOfTwo := func(n int) bool {
        return n > 0 && (n&(n-1)) == 0
    }
    fmt.Printf("42是2的幂: %t\n", isPowerOfTwo(42))
    fmt.Printf("32是2的幂: %t\n", isPowerOfTwo(32))
    
    // 计算二进制中1的个数
    countBits := func(n int) int {
        count := 0
        for n != 0 {
            count++
            n &= n - 1 // 清除最低位的1
        }
        return count
    }
    fmt.Printf("42的二进制中1的个数: %d\n", countBits(42))
}

// 位运算解决算法问题
func bitAlgorithms() {
    // 找出数组中唯一出现一次的数字（其他都出现两次）
    findSingle := func(nums []int) int {
        result := 0
        for _, num := range nums {
            result ^= num // 异或运算，相同数字会抵消
        }
        return result
    }
    
    nums := []int{2, 3, 2, 4, 4}
    fmt.Printf("唯一数字: %d\n", findSingle(nums))
    
    // 交换两个数字（不使用临时变量）
    swapWithoutTemp := func(a, b int) (int, int) {
        a ^= b
        b ^= a
        a ^= b
        return a, b
    }
    
    x, y := 10, 20
    fmt.Printf("交换前: x=%d, y=%d\n", x, y)
    x, y = swapWithoutTemp(x, y)
    fmt.Printf("交换后: x=%d, y=%d\n", x, y)
}
```

## 7. 调试与性能分析

### 7.1 调试技巧
```go
// 调试宏定义
const DEBUG = true

func debugPrint(format string, args ...interface{}) {
    if DEBUG {
        fmt.Printf("[DEBUG] "+format+"\n", args...)
    }
}

// 算法调试示例
func debugBinarySearch(arr []int, target int) int {
    left, right := 0, len(arr)-1
    step := 0
    
    debugPrint("开始二分查找: target=%d, arr=%v", target, arr)
    
    for left <= right {
        step++
        mid := left + (right-left)/2
        debugPrint("步骤%d: left=%d, right=%d, mid=%d, arr[mid]=%d", 
                   step, left, right, mid, arr[mid])
        
        if arr[mid] == target {
            debugPrint("找到目标，位置: %d", mid)
            return mid
        } else if arr[mid] < target {
            debugPrint("arr[mid] < target，搜索右半部分")
            left = mid + 1
        } else {
            debugPrint("arr[mid] > target，搜索左半部分")
            right = mid - 1
        }
    }
    
    debugPrint("未找到目标")
    return -1
}

// 性能测试
func benchmarkAlgorithm() {
    sizes := []int{1000, 10000, 100000, 1000000}
    
    for _, size := range sizes {
        // 生成测试数据
        data := make([]int, size)
        for i := range data {
            data[i] = rand.Intn(size)
        }
        
        // 测试排序性能
        dataCopy := make([]int, len(data))
        copy(dataCopy, data)
        
        start := time.Now()
        sort.Ints(dataCopy)
        duration := time.Since(start)
        
        fmt.Printf("排序 %d 个元素耗时: %v\n", size, duration)
    }
}
```

### 7.2 内存分析
```go
import (
    "runtime"
    "time"
)

// 内存使用监控
func memoryUsage() {
    var m runtime.MemStats
    
    // 强制垃圾回收
    runtime.GC()
    runtime.ReadMemStats(&m)
    
    fmt.Printf("分配的内存: %d KB\n", m.Alloc/1024)
    fmt.Printf("总分配的内存: %d KB\n", m.TotalAlloc/1024)
    fmt.Printf("系统内存: %d KB\n", m.Sys/1024)
    fmt.Printf("GC次数: %d\n", m.NumGC)
}

// 内存泄漏检测示例
func memoryLeakExample() {
    fmt.Println("开始内存测试...")
    memoryUsage()
    
    // 创建大量数据
    var data [][]int
    for i := 0; i < 1000; i++ {
        slice := make([]int, 1000)
        for j := range slice {
            slice[j] = j
        }
        data = append(data, slice)
    }
    
    fmt.Println("创建数据后:")
    memoryUsage()
    
    // 清理数据
    data = nil
    runtime.GC()
    time.Sleep(100 * time.Millisecond) // 等待GC完成
    
    fmt.Println("清理数据后:")
    memoryUsage()
}
```

## 8. Go语言算法学习总结

### 8.1 Go vs C++ 算法实现对比

| 特性 | Go | C++ |
|------|----|----- |
| **内存管理** | 🤖 自动GC | 🔧 手动管理 |
| **指针安全** | ✅ 类型安全 | ⚠️ 需要小心 |
| **编译速度** | 🚀 极快 | 🐌 较慢 |
| **运行性能** | 🏃 良好 | 🏃‍♂️ 优秀 |
| **代码简洁** | ✅ 简洁明了 | ⚠️ 相对复杂 |
| **并发支持** | 🌟 原生支持 | 🔧 需要库支持 |
| **学习曲线** | 📈 平缓 | 📈 陡峭 |

### 8.2 算法竞赛中的Go语言优势

1. **快速开发**：语法简洁，编译快速
2. **内存安全**：避免指针错误和内存泄漏
3. **并发处理**：天然支持并行算法
4. **丰富标准库**：sort、container等包
5. **跨平台**：一次编译，到处运行

### 8.3 学习建议

```go
// 算法学习路径
func learningPath() {
    steps := []string{
        "1. 掌握Go基础语法和数据结构",
        "2. 理解指针和内存模型",
        "3. 学习常用算法模板",
        "4. 练习LeetCode题目",
        "5. 掌握并发编程",
        "6. 性能优化技巧",
        "7. 参与算法竞赛",
    }
    
    for i, step := range steps {
        fmt.Printf("%s\n", step)
        if i < len(steps)-1 {
            fmt.Println("   ↓")
        }
    }
}
```

**记住**：Go语言的哲学是"简洁、高效、可读"，在算法实现中也要遵循这个原则！🐹✨

---

*Happy Coding with Go! 🚀*