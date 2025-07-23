# Go 变量声明与赋值详解教程 🐱

## 1. 变量声明的所有方式

### 1.1 var 关键字声明

```go
// 基本语法：var 变量名 类型
var name string
var age int
var isStudent bool

// 声明时初始化
var name string = "小猫"
var age int = 18
var isStudent bool = true

// 类型推断（省略类型）
var name = "小猫"     // 自动推断为 string
var age = 18         // 自动推断为 int
var isStudent = true // 自动推断为 bool

// 批量声明
var (
    name      string = "小猫"
    age       int    = 18
    isStudent bool   = true
)

// 零值声明（不初始化）
var name string    // "" (空字符串)
var age int        // 0
var isStudent bool // false
var ptr *int       // nil
var slice []int    // nil
var m map[string]int // nil
```

### 1.2 短变量声明 `:=`

```go
// 基本语法：变量名 := 值
name := "小猫"     // 等价于 var name = "小猫"
age := 18         // 等价于 var age = 18
isStudent := true // 等价于 var isStudent = true

// 多变量同时声明
name, age := "小猫", 18
x, y, z := 1, 2, 3

// 函数返回值接收
result, err := someFunction()
value, ok := m["key"]  // map 查找
data, err := ioutil.ReadFile("file.txt")

// 注意：:= 只能在函数内部使用！
func main() {
    name := "小猫"  // ✅ 正确
}

// name := "小猫"  // ❌ 错误：不能在包级别使用
```

### 1.3 赋值操作符 `=`

```go
// 基本赋值
var name string
name = "小猫"  // 给已声明的变量赋值

// 重新赋值
name = "大猫"
age = 20

// 多重赋值
a, b = b, a  // 交换变量值
x, y = 10, 20

// 复合赋值操作符
age += 1   // age = age + 1
age -= 1   // age = age - 1
age *= 2   // age = age * 2
age /= 2   // age = age / 2
age %= 3   // age = age % 3

// 位运算赋值
num &= 0xFF   // num = num & 0xFF
num |= 0x01   // num = num | 0x01
num ^= 0x01   // num = num ^ 0x01
num <<= 1     // num = num << 1
num >>= 1     // num = num >> 1
```

## 2. 🔥 三种方式的详细对比

| 方式 | 语法 | 使用场景 | 作用域 | 类型推断 |
|------|------|----------|--------|----------|
| `var` | `var name type` | 包级别变量、零值初始化 | 包级别/函数内 | 支持 |
| `:=` | `name := value` | 函数内快速声明 | 仅函数内 | 自动 |
| `=` | `name = value` | 给已存在变量赋值 | - | 不涉及 |

### 2.1 使用场景详解

```go
package main

import "fmt"

// 包级别变量（只能用 var）
var globalVar = "我是全局变量"
var (
    appName    = "LeetCode练习"
    appVersion = "1.0.0"
)

func main() {
    // 场景1：需要零值初始化
    var count int        // 0
    var message string   // ""
    var isReady bool     // false
    
    // 场景2：快速声明并初始化（推荐）
    name := "小猫"
    age := 18
    
    // 场景3：函数返回值接收
    result, err := divide(10, 2)
    if err != nil {
        fmt.Println("错误:", err)
        return
    }
    
    // 场景4：重新赋值
    name = "大猫"  // 修改已存在的变量
    age += 1       // 复合赋值
    
    // 场景5：类型转换时需要明确类型
    var num int64 = 100
    var floatNum float64 = float64(num)
    
    fmt.Printf("结果: %v, 名字: %s, 年龄: %d\n", result, name, age)
}

func divide(a, b int) (int, error) {
    if b == 0 {
        return 0, fmt.Errorf("除数不能为零")
    }
    return a / b, nil
}
```

## 3. 高级变量操作

### 3.1 指针变量

```go
// 指针声明
var ptr *int        // 声明一个指向 int 的指针，初值为 nil
num := 42
ptr = &num          // 获取 num 的地址

// 短声明指针
value := 100
pointer := &value   // pointer 是指向 value 的指针

// 解引用
fmt.Println(*pointer)  // 输出 100
*pointer = 200         // 修改 value 的值
fmt.Println(value)     // 输出 200

// new 函数创建指针
ptr2 := new(int)    // 创建一个 int 类型的指针，指向零值
*ptr2 = 50
```

### 3.2 切片和映射

```go
// 切片声明
var slice1 []int           // nil 切片
slice2 := []int{}          // 空切片
slice3 := []int{1, 2, 3}   // 有初值的切片
slice4 := make([]int, 5)   // 长度为5的切片
slice5 := make([]int, 3, 10) // 长度3，容量10

// 映射声明
var map1 map[string]int           // nil 映射
map2 := map[string]int{}          // 空映射
map3 := map[string]int{           // 有初值的映射
    "apple":  5,
    "banana": 3,
}
map4 := make(map[string]int)      // 使用 make 创建
```

### 3.3 结构体变量

```go
// 定义结构体
type Person struct {
    Name string
    Age  int
}

// 结构体变量声明
var p1 Person                    // 零值初始化
p2 := Person{"小猫", 18}         // 按顺序初始化
p3 := Person{                    // 按字段名初始化
    Name: "大猫",
    Age:  20,
}
p4 := &Person{"指针猫", 22}      // 创建指针

// 匿名结构体
student := struct {
    Name  string
    Grade int
}{"学生猫", 95}
```

## 4. 变量作用域和生命周期

### 4.1 作用域规则

```go
package main

import "fmt"

// 包级别作用域
var globalVar = "全局变量"

func main() {
    // 函数作用域
    localVar := "局部变量"
    
    if true {
        // 块作用域
        blockVar := "块变量"
        fmt.Println(globalVar, localVar, blockVar) // 都可以访问
    }
    
    // fmt.Println(blockVar) // ❌ 错误：blockVar 超出作用域
    
    for i := 0; i < 3; i++ {
        // 循环作用域
        loopVar := fmt.Sprintf("循环变量_%d", i)
        fmt.Println(loopVar)
    }
    
    // fmt.Println(i, loopVar) // ❌ 错误：超出作用域
}
```

### 4.2 变量遮蔽（Shadowing）

```go
func demonstrateShadowing() {
    name := "外层变量"
    fmt.Println("外层:", name) // 外层变量
    
    if true {
        name := "内层变量"  // 遮蔽外层变量
        fmt.Println("内层:", name) // 内层变量
    }
    
    fmt.Println("外层:", name) // 外层变量（未被修改）
    
    // 使用 := 时要小心遮蔽
    result, err := someFunction()
    if err != nil {
        // 这里的 err 是新变量，遮蔽了上面的 err
        err := fmt.Errorf("包装错误: %w", err)
        fmt.Println(err)
    }
}
```

## 5. 常见陷阱和最佳实践

### 5.1 := 的常见陷阱

```go
func commonPitfalls() {
    var err error
    
    // ❌ 陷阱1：意外创建新变量
    if true {
        result, err := someFunction() // 这里的 err 是新变量！
        _ = result
    }
    // err 仍然是 nil，不是 someFunction 返回的错误
    
    // ✅ 正确做法
    var result int
    if true {
        result, err = someFunction() // 使用 = 而不是 :=
    }
    
    // ❌ 陷阱2：在包级别使用 :=
    // name := "错误" // 编译错误
    
    // ✅ 正确做法
    var name = "正确"
    _ = name
}

func someFunction() (int, error) {
    return 42, fmt.Errorf("示例错误")
}
```

### 5.2 零值的妙用

```go
func zeroValueBenefits() {
    // Go 的零值设计很巧妙
    var slice []int    // nil，但可以直接 append
    slice = append(slice, 1, 2, 3)
    
    var m map[string]int // nil，但可以读取（返回零值）
    value := m["key"]    // 返回 0，不会 panic
    
    // 但写入 nil map 会 panic
    // m["key"] = 1  // ❌ panic
    
    // 需要初始化后才能写入
    m = make(map[string]int)
    m["key"] = 1  // ✅ 正确
}
```

### 5.3 最佳实践总结

```go
// 1. 优先使用 := 进行局部变量声明
func bestPractices() {
    // ✅ 推荐
    name := "小猫"
    age := 18
    
    // ❌ 不推荐（除非需要零值）
    var name2 string
    name2 = "小猫"
    
    // 2. 需要零值时使用 var
    var count int     // 需要从 0 开始计数
    var buffer []byte // 需要 nil 切片
    
    // 3. 包级别变量使用 var
    // var globalConfig = loadConfig()
    
    // 4. 批量声明使用 var ()
    var (
        maxRetries = 3
        timeout    = time.Second * 30
        debug      = false
    )
    
    // 5. 明确类型时使用 var
    var userID int64 = 12345  // 明确需要 int64
    
    _ = name
    _ = age
    _ = count
    _ = buffer
    _ = maxRetries
    _ = timeout
    _ = debug
    _ = userID
}
```

## 6. 实战示例：LeetCode 中的变量使用

### 6.1 两数之和问题

```go
func twoSum(nums []int, target int) []int {
    // 使用 := 快速声明 map
    numMap := make(map[int]int)
    
    for i, num := range nums {
        // 计算补数
        complement := target - num
        
        // 检查补数是否存在
        if index, exists := numMap[complement]; exists {
            return []int{index, i}
        }
        
        // 存储当前数字和索引
        numMap[num] = i
    }
    
    // 返回空切片（零值）
    return nil
}
```

### 6.2 动态规划问题

```go
func climbStairs(n int) int {
    if n <= 2 {
        return n
    }
    
    // 使用 := 声明 DP 数组
    dp := make([]int, n+1)
    
    // 初始化边界条件
    dp[1], dp[2] = 1, 2
    
    // DP 转移
    for i := 3; i <= n; i++ {
        dp[i] = dp[i-1] + dp[i-2]
    }
    
    return dp[n]
}

// 空间优化版本
func climbStairsOptimized(n int) int {
    if n <= 2 {
        return n
    }
    
    // 只需要两个变量
    prev1, prev2 := 1, 2
    
    for i := 3; i <= n; i++ {
        // 多重赋值，优雅地更新变量
        prev1, prev2 = prev2, prev1+prev2
    }
    
    return prev2
}
```

## 7. 总结 🎯

### 变量声明速查表

| 场景 | 推荐方式 | 示例 |
|------|----------|------|
| 函数内快速声明 | `:=` | `name := "小猫"` |
| 需要零值初始化 | `var` | `var count int` |
| 包级别变量 | `var` | `var globalVar = "value"` |
| 明确指定类型 | `var` | `var id int64 = 123` |
| 批量声明 | `var ()` | `var (a = 1; b = 2)` |
| 重新赋值 | `=` | `name = "新值"` |
| 复合赋值 | `+=, -=` 等 | `count += 1` |

### 🐱 记忆口诀：
- 🚀 **函数内用 :=，快速又简洁**
- 🎯 **零值初始化，var 是首选**
- 🌍 **全局变量声明，var 不能少**
- 🔄 **重新赋值用 =，简单又明了**
- ⚡ **复合赋值 +=，效率更高效**

希望这个教程能帮你彻底掌握 Go 的变量操作！😸✨