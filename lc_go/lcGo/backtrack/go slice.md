# Go Slice 详解教程 🍰

## 1. 什么是 Slice？

Slice（切片）是 Go 语言中最重要的数据结构之一，它是对数组的抽象。Slice 提供了动态数组的功能，比数组更灵活、更强大。

```go
// Slice 的底层结构
type slice struct {
    ptr    *T     // 指向底层数组的指针
    len    int    // 当前长度
    cap    int    // 容量
}
```

## 2. Slice 的创建方式

### 2.1 使用 make() 函数

```go
// make([]T, length, capacity)
slice1 := make([]int, 5)      // 长度5，容量5，元素都是0
slice2 := make([]int, 3, 10)  // 长度3，容量10，元素都是0
slice3 := make([]int, 0, 5)   // 长度0，容量5，空slice

fmt.Printf("slice1: %v, len=%d, cap=%d\n", slice1, len(slice1), cap(slice1))
// 输出: slice1: [0 0 0 0 0], len=5, cap=5

fmt.Printf("slice2: %v, len=%d, cap=%d\n", slice2, len(slice2), cap(slice2))
// 输出: slice2: [0 0 0], len=3, cap=10
```

### 2.2 使用字面量 []T{}

```go
// 空slice字面量
slice1 := []int{}             // 长度0，容量0
slice2 := []int{1, 2, 3}      // 长度3，容量3，有初始值
slice3 := []string{"a", "b"}  // 长度2，容量2

fmt.Printf("slice1: %v, len=%d, cap=%d\n", slice1, len(slice1), cap(slice1))
// 输出: slice1: [], len=0, cap=0

fmt.Printf("slice2: %v, len=%d, cap=%d\n", slice2, len(slice2), cap(slice2))
// 输出: slice2: [1 2 3], len=3, cap=3
```

## 3. 🔥 make([]int, n) vs []int{} 的关键区别

### 3.1 内存分配

```go
// make([]int, n) - 预分配内存
slice1 := make([]int, 5)  // 立即分配5个int的内存空间
fmt.Println(slice1)       // [0 0 0 0 0] - 有默认零值

// []int{} - 不分配内存
slice2 := []int{}         // 不分配任何内存
fmt.Println(slice2)       // [] - 空slice
```

### 3.2 长度和容量

```go
slice1 := make([]int, 5)
fmt.Printf("make: len=%d, cap=%d\n", len(slice1), cap(slice1))
// 输出: make: len=5, cap=5

slice2 := []int{}
fmt.Printf("literal: len=%d, cap=%d\n", len(slice2), cap(slice2))
// 输出: literal: len=0, cap=0
```

### 3.3 使用场景对比

```go
// 场景1: 已知大小，需要填充数据
func scenario1() {
    // ✅ 推荐使用 make
    nums := make([]int, 10)
    for i := 0; i < 10; i++ {
        nums[i] = i * i  // 直接通过索引赋值
    }
    fmt.Println(nums) // [0 1 4 9 16 25 36 49 64 81]
}

// 场景2: 动态添加元素
func scenario2() {
    // ✅ 推荐使用 []int{}
    var nums []int  // 或者 nums := []int{}
    for i := 0; i < 10; i++ {
        nums = append(nums, i*i)  // 动态添加
    }
    fmt.Println(nums) // [0 1 4 9 16 25 36 49 64 81]
}

// 场景3: 预知容量，但长度为0
func scenario3() {
    // ✅ 推荐使用 make([]int, 0, capacity)
    nums := make([]int, 0, 10)  // 长度0，容量10
    for i := 0; i < 10; i++ {
        nums = append(nums, i*i)
    }
    fmt.Println(nums) // [0 1 4 9 16 25 36 49 64 81]
}
```

## 4. 性能对比分析

### 4.1 内存分配次数

```go
// 使用 []int{} + append - 可能多次重新分配
func inefficient() []int {
    var nums []int
    for i := 0; i < 1000; i++ {
        nums = append(nums, i)  // 可能触发多次内存重新分配
    }
    return nums
}

// 使用 make([]int, 0, n) - 一次分配
func efficient() []int {
    nums := make([]int, 0, 1000)  // 预分配容量
    for i := 0; i < 1000; i++ {
        nums = append(nums, i)  // 不会重新分配内存
    }
    return nums
}
```

### 4.2 基准测试示例

```go
func BenchmarkSliceAppend(b *testing.B) {
    for i := 0; i < b.N; i++ {
        var s []int
        for j := 0; j < 1000; j++ {
            s = append(s, j)
        }
    }
}

func BenchmarkSliceMake(b *testing.B) {
    for i := 0; i < b.N; i++ {
        s := make([]int, 0, 1000)
        for j := 0; j < 1000; j++ {
            s = append(s, j)
        }
    }
}
```

## 5. Slice 的常用操作

### 5.1 切片操作

```go
slice := []int{0, 1, 2, 3, 4, 5}

// 基本切片
fmt.Println(slice[1:4])   // [1 2 3]
fmt.Println(slice[:3])    // [0 1 2]
fmt.Println(slice[2:])    // [2 3 4 5]
fmt.Println(slice[:])     // [0 1 2 3 4 5]

// 三参数切片 [start:end:cap]
subSlice := slice[1:3:4]  // [1 2], cap=3
fmt.Printf("subSlice: %v, len=%d, cap=%d\n", subSlice, len(subSlice), cap(subSlice))
```

### 5.2 添加和删除元素

```go
// 添加元素
slice := []int{1, 2, 3}
slice = append(slice, 4)           // [1 2 3 4]
slice = append(slice, 5, 6, 7)     // [1 2 3 4 5 6 7]

// 合并slice
other := []int{8, 9}
slice = append(slice, other...)    // [1 2 3 4 5 6 7 8 9]

// 删除元素（删除索引i的元素）
i := 2
slice = append(slice[:i], slice[i+1:]...)  // 删除索引2的元素
```

### 5.3 复制 Slice

```go
// 浅拷贝 - 共享底层数组
original := []int{1, 2, 3}
shallow := original[:]  // 浅拷贝
shallow[0] = 999
fmt.Println(original)   // [999 2 3] - 原slice也被修改

// 深拷贝 - 独立的底层数组
original = []int{1, 2, 3}
deep := make([]int, len(original))
copy(deep, original)    // 深拷贝
deep[0] = 999
fmt.Println(original)   // [1 2 3] - 原slice不受影响
fmt.Println(deep)       // [999 2 3]
```

## 6. 实战应用场景

### 6.1 动态规划中的应用

```go
// 斐波那契数列
func fibonacci(n int) []int {
    if n <= 0 {
        return []int{}
    }
    if n == 1 {
        return []int{0}
    }
    
    // 预分配容量，避免多次重新分配
    dp := make([]int, n)
    dp[0], dp[1] = 0, 1
    
    for i := 2; i < n; i++ {
        dp[i] = dp[i-1] + dp[i-2]
    }
    return dp
}
```

### 6.2 回溯算法中的应用

```go
// N皇后问题中的路径记录
func solveNQueens(n int) [][]string {
    var result [][]string
    board := make([]string, n)
    
    // 初始化棋盘
    for i := range board {
        board[i] = strings.Repeat(".", n)
    }
    
    var backtrack func(row int)
    backtrack = func(row int) {
        if row == n {
            // 深拷贝当前解
            solution := make([]string, n)
            copy(solution, board)
            result = append(result, solution)
            return
        }
        
        for col := 0; col < n; col++ {
            if isValid(board, row, col) {
                // 放置皇后
                board[row] = board[row][:col] + "Q" + board[row][col+1:]
                backtrack(row + 1)
                // 撤销
                board[row] = board[row][:col] + "." + board[row][col+1:]
            }
        }
    }
    
    backtrack(0)
    return result
}
```

## 7. 常见陷阱和最佳实践

### 7.1 Slice 扩容机制

```go
func demonstrateGrowth() {
    slice := make([]int, 0, 1)
    
    for i := 0; i < 10; i++ {
        fmt.Printf("Before append: len=%d, cap=%d\n", len(slice), cap(slice))
        slice = append(slice, i)
        fmt.Printf("After append: len=%d, cap=%d\n", len(slice), cap(slice))
        fmt.Println("---")
    }
}

// 输出显示容量增长规律：1 -> 2 -> 4 -> 8 -> 16...
```

### 7.2 避免内存泄漏

```go
// ❌ 错误：可能导致内存泄漏
func badSubSlice(data []byte) []byte {
    return data[10:20]  // 仍然引用整个底层数组
}

// ✅ 正确：创建独立的slice
func goodSubSlice(data []byte) []byte {
    result := make([]byte, 10)
    copy(result, data[10:20])
    return result
}
```

### 7.3 最佳实践总结

```go
// 1. 已知大小时使用 make
knownSize := make([]int, 100)

// 2. 动态增长时预分配容量
dynamic := make([]int, 0, 100)

// 3. 有初始值时使用字面量
withValues := []int{1, 2, 3, 4, 5}

// 4. 空slice使用字面量
emptySlice := []int{}

// 5. 大量append操作时预分配容量
func efficientAppend(n int) []int {
    result := make([]int, 0, n)  // 预分配容量
    for i := 0; i < n; i++ {
        result = append(result, i)
    }
    return result
}
```

## 8. 总结 🎯

| 创建方式 | 使用场景 | 优点 | 缺点 |
|---------|---------|------|------|
| `make([]T, n)` | 已知大小，需要通过索引赋值 | 一次分配，性能好 | 有默认零值 |
| `make([]T, 0, n)` | 预知容量，动态添加 | 避免重新分配 | 需要估算容量 |
| `[]T{}` | 空slice或有初始值 | 简洁，灵活 | 可能多次重新分配 |
| `[]T{v1, v2}` | 有明确初始值 | 直观，高效 | 固定初始大小 |

**记住这个口诀：**
- 📏 **已知大小用 make**
- 🔄 **动态增长预分配**
- 📝 **有值直接用字面量**
- 🚀 **性能优先选 make**

希望这个教程能帮你彻底理解 Go 的 slice！🎉