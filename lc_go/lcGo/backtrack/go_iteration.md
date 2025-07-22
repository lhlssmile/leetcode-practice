# Go语言遍历方法与常用语法大全 🐹

专为算法学习准备的Go语言完整指南！

## 1. 基础遍历方法

### 1.1 `for` 循环 - Go的万能遍历
```go
// 传统C风格循环
for i := 0; i < 10; i++ {
    fmt.Println(i)
}

// 条件循环（类似while）
i := 0
for i < 10 {
    fmt.Println(i)
    i++
}

// 无限循环
for {
    // 需要break跳出
    if condition {
        break
    }
}
```

### 1.2 `range` - Go的特色遍历
```go
// 遍历切片/数组
nums := []int{1, 2, 3, 4, 5}

// 获取索引和值
for i, v := range nums {
    fmt.Printf("索引: %d, 值: %d\n", i, v)
}

// 只要索引
for i := range nums {
    fmt.Printf("索引: %d\n", i)
}

// 只要值（使用空白标识符）
for _, v := range nums {
    fmt.Printf("值: %d\n", v)
}

// 遍历字符串
str := "Hello"
for i, char := range str {
    fmt.Printf("位置: %d, 字符: %c\n", i, char)
}

// 遍历map
m := map[string]int{"a": 1, "b": 2}
for key, value := range m {
    fmt.Printf("键: %s, 值: %d\n", key, value)
}

// 遍历通道
ch := make(chan int, 3)
ch <- 1
ch <- 2
ch <- 3
close(ch)

for value := range ch {
    fmt.Printf("接收到: %d\n", value)
}
```

## 2. 数据结构与遍历

### 2.1 切片 (Slice) - 动态数组
```go
// 创建切片
var nums []int                    // 零值切片
nums = make([]int, 5)            // 长度为5的切片
nums = make([]int, 5, 10)        // 长度5，容量10
nums = []int{1, 2, 3, 4, 5}      // 字面量创建

// 切片操作
fmt.Println(len(nums))           // 长度
fmt.Println(cap(nums))           // 容量
nums = append(nums, 6)           // 追加元素
subSlice := nums[1:4]            // 切片操作 [1,4)

// 二维切片
matrix := make([][]int, 3)
for i := range matrix {
    matrix[i] = make([]int, 4)
}

// 遍历二维切片
for i, row := range matrix {
    for j, val := range row {
        fmt.Printf("[%d][%d] = %d\n", i, j, val)
    }
}
```

### 2.2 数组 (Array) - 固定长度
```go
// 创建数组
var arr [5]int                   // 零值数组
arr = [5]int{1, 2, 3, 4, 5}      // 初始化
auto := [...]int{1, 2, 3}        // 自动推断长度

// 遍历数组
for i := 0; i < len(arr); i++ {
    fmt.Printf("arr[%d] = %d\n", i, arr[i])
}

for i, v := range arr {
    fmt.Printf("索引: %d, 值: %d\n", i, v)
}
```

### 2.3 映射 (Map) - 哈希表
```go
// 创建map
var m map[string]int             // 零值map（nil）
m = make(map[string]int)         // 初始化
m = map[string]int{              // 字面量创建
    "apple":  5,
    "banana": 3,
}

// map操作
m["orange"] = 8                  // 添加/更新
value, exists := m["apple"]      // 检查存在性
if exists {
    fmt.Printf("apple: %d\n", value)
}
delete(m, "banana")              // 删除

// 遍历map（顺序不保证）
for key, value := range m {
    fmt.Printf("%s: %d\n", key, value)
}

// 只遍历键
for key := range m {
    fmt.Printf("键: %s\n", key)
}
```

### 2.4 字符串处理
```go
// 字符串遍历
str := "Hello, 世界"

// 按字节遍历
for i := 0; i < len(str); i++ {
    fmt.Printf("字节 %d: %c\n", i, str[i])
}

// 按Unicode字符遍历（推荐）
for i, char := range str {
    fmt.Printf("位置 %d: %c\n", i, char)
}

// 转换为rune切片处理中文
runes := []rune(str)
for i, r := range runes {
    fmt.Printf("字符 %d: %c\n", i, r)
}

// 字符串构建
var builder strings.Builder
for i := 0; i < 5; i++ {
    builder.WriteString(fmt.Sprintf("第%d个 ", i))
}
result := builder.String()
```

## 3. 算法常用模式

### 3.1 双指针遍历
```go
func twoPointers(nums []int) {
    left, right := 0, len(nums)-1
    
    for left < right {
        // 处理逻辑
        if nums[left] + nums[right] == target {
            // 找到答案
            break
        } else if nums[left] + nums[right] < target {
            left++
        } else {
            right--
        }
    }
}
```

### 3.2 滑动窗口
```go
func slidingWindow(s string) {
    left := 0
    window := make(map[byte]int)
    
    for right := 0; right < len(s); right++ {
        // 扩大窗口
        window[s[right]]++
        
        // 收缩窗口
        for /* 窗口需要收缩的条件 */ {
            window[s[left]]--
            if window[s[left]] == 0 {
                delete(window, s[left])
            }
            left++
        }
        
        // 更新答案
    }
}
```

### 3.3 回溯遍历
```go
func backtrack(path []int, used []bool) {
    // 终止条件
    if len(path) == targetLength {
        result = append(result, append([]int{}, path...))
        return
    }
    
    // 选择列表
    for i := 0; i < len(nums); i++ {
        if used[i] {
            continue
        }
        
        // 做选择
        path = append(path, nums[i])
        used[i] = true
        
        // 递归
        backtrack(path, used)
        
        // 撤销选择
        path = path[:len(path)-1]
        used[i] = false
    }
}
```

### 3.4 DFS/BFS 遍历
```go
// DFS - 深度优先搜索
func dfs(graph [][]int, visited []bool, node int) {
    visited[node] = true
    fmt.Printf("访问节点: %d\n", node)
    
    for _, neighbor := range graph[node] {
        if !visited[neighbor] {
            dfs(graph, visited, neighbor)
        }
    }
}

// BFS - 广度优先搜索
func bfs(graph [][]int, start int) {
    visited := make([]bool, len(graph))
    queue := []int{start}
    visited[start] = true
    
    for len(queue) > 0 {
        node := queue[0]
        queue = queue[1:]
        fmt.Printf("访问节点: %d\n", node)
        
        for _, neighbor := range graph[node] {
            if !visited[neighbor] {
                visited[neighbor] = true
                queue = append(queue, neighbor)
            }
        }
    }
}
```

## 4. Go语言特色语法

### 4.1 多重赋值
```go
// 交换变量
a, b := 1, 2
a, b = b, a

// 函数多返回值
value, ok := m["key"]
result, err := someFunction()

// 忽略某些返回值
_, err := someFunction()
```

### 4.2 类型断言与类型选择
```go
// 类型断言
var i interface{} = "hello"
str, ok := i.(string)
if ok {
    fmt.Printf("字符串: %s\n", str)
}

// 类型选择
switch v := i.(type) {
case string:
    fmt.Printf("字符串: %s\n", v)
case int:
    fmt.Printf("整数: %d\n", v)
default:
    fmt.Printf("未知类型: %T\n", v)
}
```

### 4.3 defer 语句
```go
func example() {
    defer fmt.Println("最后执行")
    defer fmt.Println("倒数第二执行")
    
    fmt.Println("正常执行")
    // 输出顺序：
    // 正常执行
    // 倒数第二执行
    // 最后执行
}
```

### 4.4 goroutine 与 channel
```go
// goroutine - 轻量级线程
go func() {
    fmt.Println("并发执行")
}()

// channel - 通信管道
ch := make(chan int, 2)  // 缓冲通道
go func() {
    ch <- 42
    ch <- 24
    close(ch)
}()

// 接收数据
for value := range ch {
    fmt.Printf("接收: %d\n", value)
}
```

### 4.5 结构体与方法
```go
// 定义结构体
type Person struct {
    Name string
    Age  int
}

// 方法
func (p Person) String() string {
    return fmt.Sprintf("%s (%d岁)", p.Name, p.Age)
}

// 指针方法（可修改结构体）
func (p *Person) SetAge(age int) {
    p.Age = age
}

// 使用
p := Person{Name: "张三", Age: 25}
p.SetAge(26)
fmt.Println(p.String())
```

## 5. 常用内置函数

### 5.1 切片操作函数
```go
// append - 追加元素
nums := []int{1, 2, 3}
nums = append(nums, 4, 5, 6)
nums = append(nums, []int{7, 8, 9}...)

// copy - 复制切片
src := []int{1, 2, 3}
dst := make([]int, len(src))
copy(dst, src)

// len - 长度
fmt.Println(len(nums))

// cap - 容量
fmt.Println(cap(nums))
```

### 5.2 字符串处理
```go
import "strings"

// 常用字符串函数
str := "Hello, World!"
fmt.Println(strings.Contains(str, "World"))  // true
fmt.Println(strings.Index(str, "World"))     // 7
fmt.Println(strings.ToLower(str))            // "hello, world!"
fmt.Println(strings.Split(str, ", "))        // ["Hello" "World!"]
fmt.Println(strings.Join([]string{"a", "b"}, "-")) // "a-b"
```

### 5.3 数学运算
```go
import "math"

// 常用数学函数
fmt.Println(math.Max(3.14, 2.71))    // 3.14
fmt.Println(math.Min(3.14, 2.71))    // 2.71
fmt.Println(math.Abs(-5))            // 5
fmt.Println(math.Pow(2, 3))          // 8
fmt.Println(math.Sqrt(16))           // 4
```

## 6. 错误处理

```go
// Go的错误处理模式
func divide(a, b float64) (float64, error) {
    if b == 0 {
        return 0, fmt.Errorf("除数不能为零")
    }
    return a / b, nil
}

// 使用
result, err := divide(10, 2)
if err != nil {
    fmt.Printf("错误: %v\n", err)
    return
}
fmt.Printf("结果: %.2f\n", result)
```

## 7. 算法实现技巧

### 7.1 快速排序
```go
func quickSort(nums []int, left, right int) {
    if left < right {
        pivot := partition(nums, left, right)
        quickSort(nums, left, pivot-1)
        quickSort(nums, pivot+1, right)
    }
}

func partition(nums []int, left, right int) int {
    pivot := nums[right]
    i := left - 1
    
    for j := left; j < right; j++ {
        if nums[j] <= pivot {
            i++
            nums[i], nums[j] = nums[j], nums[i]
        }
    }
    
    nums[i+1], nums[right] = nums[right], nums[i+1]
    return i + 1
}
```

### 7.2 二分查找
```go
func binarySearch(nums []int, target int) int {
    left, right := 0, len(nums)-1
    
    for left <= right {
        mid := left + (right-left)/2
        
        if nums[mid] == target {
            return mid
        } else if nums[mid] < target {
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    
    return -1
}
```

### 7.3 动态规划
```go
func fibonacci(n int) int {
    if n <= 1 {
        return n
    }
    
    dp := make([]int, n+1)
    dp[0], dp[1] = 0, 1
    
    for i := 2; i <= n; i++ {
        dp[i] = dp[i-1] + dp[i-2]
    }
    
    return dp[n]
}
```

## 8. 性能优化技巧

### 8.1 预分配切片容量
```go
// 好的做法 - 预分配容量
result := make([]int, 0, expectedSize)

// 避免频繁扩容
for i := 0; i < expectedSize; i++ {
    result = append(result, i)
}
```

### 8.2 使用字符串构建器
```go
// 高效的字符串拼接
var builder strings.Builder
builder.Grow(expectedLength) // 预分配容量

for _, str := range strings {
    builder.WriteString(str)
}

result := builder.String()
```

### 8.3 避免不必要的内存分配
```go
// 重用切片
func processData(data []int) {
    // 重用同一个临时切片
    temp := make([]int, 0, len(data))
    
    for _, batch := range batches {
        temp = temp[:0] // 重置长度但保留容量
        // 处理批次...
    }
}
```

## 9. 调试技巧

```go
import (
    "fmt"
    "log"
    "runtime"
)

// 打印调试信息
func debugPrint(msg string, vars ...interface{}) {
    _, file, line, _ := runtime.Caller(1)
    fmt.Printf("[DEBUG] %s:%d - %s\n", file, line, fmt.Sprintf(msg, vars...))
}

// 使用
debugPrint("变量值: %v", someVariable)
```

## 10. 总结

Go语言的遍历特点：
- **简洁性**: `range` 关键字统一处理各种数据结构
- **安全性**: 自动处理边界，避免越界访问
- **高效性**: 编译器优化，性能接近C语言
- **并发性**: 内置goroutine支持并发遍历

**算法实现建议**：
1. 优先使用 `range` 进行遍历
2. 注意切片的容量预分配
3. 合理使用指针避免不必要的复制
4. 利用Go的多返回值特性处理错误
5. 使用defer确保资源清理

🎉 **现在你已经掌握了Go语言的核心遍历方法和常用语法，可以开始愉快地刷算法题了！**