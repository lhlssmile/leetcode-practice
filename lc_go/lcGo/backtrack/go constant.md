# Go 常量使用指南 🐹

## 1. 基本常量声明

### 单个常量
```go
const pi = 3.14159
const name = "Go语言"
const isActive = true
```

### 多个常量
```go
const (
    width  = 100
    height = 200
    depth  = 50
)
```

## 2. 类型化常量 vs 无类型常量

### 类型化常量
```go
const typedInt int = 42
const typedFloat float64 = 3.14
```

### 无类型常量（推荐）
```go
const untypedInt = 42      // 可以用于任何整数类型
const untypedFloat = 3.14  // 可以用于任何浮点类型
```

## 3. 预定义常量（类似 C++ 的 INT_MAX）

### 数值极限常量
```go
import "math"

// 整数极限
const (
    MaxInt8   = 1<<7 - 1     // 127
    MinInt8   = -1 << 7      // -128
    MaxInt16  = 1<<15 - 1    // 32767
    MinInt16  = -1 << 15     // -32768
    MaxInt32  = 1<<31 - 1    // 2147483647
    MinInt32  = -1 << 31     // -2147483648
    MaxInt64  = 1<<63 - 1    // 9223372036854775807
    MinInt64  = -1 << 63     // -9223372036854775808
)

// 无符号整数极限
const (
    MaxUint8  = 1<<8 - 1     // 255
    MaxUint16 = 1<<16 - 1    // 65535
    MaxUint32 = 1<<32 - 1    // 4294967295
    MaxUint64 = 1<<64 - 1    // 18446744073709551615
)

// 浮点数极限和特殊值（类似 Python 的 inf）
const (
    MaxFloat32 = math.MaxFloat32  // 3.4028235e+38
    MaxFloat64 = math.MaxFloat64  // 1.7976931348623157e+308
    
    // 特殊浮点值
    PositiveInf = math.Inf(1)     // 正无穷
    NegativeInf = math.Inf(-1)    // 负无穷
    NaN         = math.NaN()      // 非数字
)
```

### 使用 math 包的常量
```go
import "math"

func example() {
    // 数学常量
    fmt.Println(math.Pi)    // 3.141592653589793
    fmt.Println(math.E)     // 2.718281828459045
    
    // 浮点数极限
    fmt.Println(math.MaxFloat64)  // 最大 float64 值
    fmt.Println(math.SmallestNonzeroFloat64)  // 最小非零 float64 值
    
    // 特殊值检查
    if math.IsInf(someValue, 1) {
        fmt.Println("正无穷")
    }
    if math.IsNaN(someValue) {
        fmt.Println("非数字")
    }
}
```

## 4. iota 枚举器

### 基本用法
```go
const (
    Sunday = iota    // 0
    Monday           // 1
    Tuesday          // 2
    Wednesday        // 3
    Thursday         // 4
    Friday           // 5
    Saturday         // 6
)
```

### 高级 iota 用法
```go
// 跳过值
const (
    _ = iota         // 跳过 0
    KB = 1 << (10 * iota)  // 1024
    MB                     // 1048576
    GB                     // 1073741824
    TB                     // 1099511627776
)

// 位掩码
const (
    FlagNone = 1 << iota  // 1
    FlagRed               // 2
    FlagGreen             // 4
    FlagBlue              // 8
)
```

## 5. 实际应用示例

### 算法题中的常用常量
```go
package main

import (
    "fmt"
    "math"
)

const (
    // 常用的大数值（类似 C++ 的 INT_MAX）
    INF = math.MaxInt32  // 或者 1e9
    
    // 模运算常量
    MOD = 1000000007
    
    // 方向数组常量
    DIRECTIONS = 4
)

// 方向向量
var (
    dx = [4]int{-1, 1, 0, 0}   // 上下左右
    dy = [4]int{0, 0, -1, 1}
)

func dijkstra() {
    // 初始化距离为无穷大
    dist := make([]int, 100)
    for i := range dist {
        dist[i] = INF
    }
    
    // 使用常量
    if dist[0] == INF {
        fmt.Println("未访问")
    }
}

func modOperation(a, b int) int {
    return (a + b) % MOD
}
```

### 字符串常量
```go
const (
    // HTTP 状态码
    StatusOK       = 200
    StatusNotFound = 404
    StatusError    = 500
    
    // 错误消息
    ErrNotFound = "item not found"
    ErrInvalid  = "invalid input"
    
    // 配置常量
    DefaultTimeout = 30  // 秒
    MaxRetries     = 3
)
```

## 6. 常量的特点

1. **编译时确定**：常量值必须在编译时就能确定
2. **不可修改**：常量一旦声明就不能修改
3. **类型推断**：无类型常量可以根据上下文自动推断类型
4. **高精度**：无类型数值常量可以有任意精度

## 7. 常见错误

```go
// ❌ 错误：不能用变量初始化常量
var x = 10
const y = x  // 编译错误

// ❌ 错误：不能修改常量
const z = 5
z = 10  // 编译错误

// ✅ 正确：使用字面量或其他常量
const a = 10
const b = a * 2
```

## 8. 最佳实践

1. **使用有意义的名称**：`const MaxUsers = 1000` 而不是 `const M = 1000`
2. **分组相关常量**：使用 `const ()` 块
3. **使用 iota 创建枚举**：避免魔法数字
4. **优先使用无类型常量**：提供更好的灵活性

希望这个指南能帮助你更好地理解和使用 Go 语言中的常量！🚀