# Go & Python 数组访问完全指南 🐹🐍

## 目录
1. [基础数组/切片声明](#基础声明)
2. [索引访问](#索引访问)
3. [切片操作 (冒号语法)](#切片操作)
4. [常用切片模式](#常用模式)
5. [边界处理](#边界处理)
6. [性能对比](#性能对比)
7. [实战示例](#实战示例)

---

## 基础声明 {#基础声明}

### Python 列表
```python
# 创建列表
arr = [1, 2, 3, 4, 5]
print(f"Python列表: {arr}")
print(f"长度: {len(arr)}")

# 动态添加
arr.append(6)
print(f"添加后: {arr}")
```

### Go 切片
```go
// 创建切片
arr := []int{1, 2, 3, 4, 5}
fmt.Printf("Go切片: %v\n", arr)
fmt.Printf("长度: %d, 容量: %d\n", len(arr), cap(arr))

// 动态添加
arr = append(arr, 6)
fmt.Printf("添加后: %v\n", arr)
```

**关键区别:**
- Python: 列表是动态数组，自动扩容
- Go: 切片有长度(len)和容量(cap)概念

---

## 索引访问 {#索引访问}

### 正向索引
```python
# Python
arr = [10, 20, 30, 40, 50]
print(arr[0])   # 10 (第一个)
print(arr[1])   # 20 (第二个)
print(arr[-1])  # 50 (最后一个) ✨ Python特色
print(arr[-2])  # 40 (倒数第二个)
```

```go
// Go
arr := []int{10, 20, 30, 40, 50}
fmt.Println(arr[0])           // 10 (第一个)
fmt.Println(arr[1])           // 20 (第二个)
fmt.Println(arr[len(arr)-1])  // 50 (最后一个)
fmt.Println(arr[len(arr)-2])  // 40 (倒数第二个)
```

**关键区别:**
- Python: 支持负数索引 `arr[-1]`
- Go: 不支持负数索引，需要 `arr[len(arr)-1]`

---

## 切片操作 (冒号语法) {#切片操作}

这是最重要的部分！🎯

### 基本语法对比

| 操作 | Python | Go | 说明 |
|------|--------|----|------|
| 全部 | `arr[:]` | `arr[:]` | 完整拷贝 |
| 前n个 | `arr[:n]` | `arr[:n]` | 从开头到n-1 |
| 后n个 | `arr[-n:]` | `arr[len(arr)-n:]` | 最后n个元素 |
| 中间段 | `arr[i:j]` | `arr[i:j]` | 从i到j-1 |
| 跳步 | `arr[::step]` | ❌ 不支持 | Python独有 |

### 详细示例

```python
# Python 切片示例
arr = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

print("=== Python 切片操作 ===")
print(f"原数组: {arr}")
print(f"arr[:]:     {arr[:]}     # 全部")
print(f"arr[:5]:    {arr[:5]}    # 前5个 [0,5)")
print(f"arr[3:]:    {arr[3:]}    # 从索引3开始")
print(f"arr[2:7]:   {arr[2:7]}   # 从2到6 [2,7)")
print(f"arr[-3:]:   {arr[-3:]}   # 最后3个")
print(f"arr[:-2]:   {arr[:-2]}   # 除了最后2个")
print(f"arr[::2]:   {arr[::2]}   # 每隔一个")
print(f"arr[::-1]:  {arr[::-1]}  # 反转")
```

```go
// Go 切片示例
arr := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

fmt.Println("=== Go 切片操作 ===")
fmt.Printf("原数组: %v\n", arr)
fmt.Printf("arr[:]:           %v  # 全部\n", arr[:])
fmt.Printf("arr[:5]:          %v     # 前5个 [0,5)\n", arr[:5])
fmt.Printf("arr[3:]:          %v  # 从索引3开始\n", arr[3:])
fmt.Printf("arr[2:7]:         %v     # 从2到6 [2,7)\n", arr[2:7])
fmt.Printf("arr[len(arr)-3:]: %v        # 最后3个\n", arr[len(arr)-3:])
fmt.Printf("arr[:len(arr)-2]: %v  # 除了最后2个\n", arr[:len(arr)-2])
// Go 不支持步长，需要手动实现
```

### 🔥 重要规则记忆法

**切片语法: `arr[start:end:step]`**

1. **左闭右开**: `[start, end)` - 包含start，不包含end
2. **默认值**:
   - `start` 默认为 0
   - `end` 默认为 len(arr)
   - `step` 默认为 1 (仅Python)

3. **边界安全**: 超出范围不会报错，自动截断

```python
# Python 边界测试
arr = [1, 2, 3]
print(arr[:100])    # [1, 2, 3] - 自动截断
print(arr[10:])     # [] - 空列表
print(arr[-100:])   # [1, 2, 3] - 从头开始
```

```go
// Go 边界测试
arr := []int{1, 2, 3}
fmt.Println(arr[:100])  // 编译错误！Go更严格
// 正确做法:
if 100 <= len(arr) {
    fmt.Println(arr[:100])
} else {
    fmt.Println(arr[:])
}
```

---

## 常用切片模式 {#常用模式}

### 1. 数组拷贝
```python
# Python
original = [1, 2, 3, 4, 5]
copy_arr = original[:]  # 浅拷贝
deep_copy = original.copy()  # 也是浅拷贝
```

```go
// Go
original := []int{1, 2, 3, 4, 5}
copyArr := make([]int, len(original))
copy(copyArr, original)  // 深拷贝
// 或者
copyArr2 := append([]int(nil), original...)  // 惯用法
```

### 2. 删除元素
```python
# Python - 删除索引i的元素
arr = [1, 2, 3, 4, 5]
i = 2
arr = arr[:i] + arr[i+1:]  # [1, 2, 4, 5]
# 或者使用 del
del arr[i]
```

```go
// Go - 删除索引i的元素
arr := []int{1, 2, 3, 4, 5}
i := 2
arr = append(arr[:i], arr[i+1:]...)  // [1, 2, 4, 5]
```

### 3. 插入元素
```python
# Python - 在索引i插入元素
arr = [1, 2, 4, 5]
i, val = 2, 3
arr = arr[:i] + [val] + arr[i:]  # [1, 2, 3, 4, 5]
# 或者使用 insert
arr.insert(i, val)
```

```go
// Go - 在索引i插入元素
arr := []int{1, 2, 4, 5}
i, val := 2, 3
arr = append(arr[:i], append([]int{val}, arr[i:]...)...)  // [1, 2, 3, 4, 5]
```

### 4. 反转数组
```python
# Python
arr = [1, 2, 3, 4, 5]
reversed_arr = arr[::-1]  # [5, 4, 3, 2, 1]
# 原地反转
arr.reverse()
```

```go
// Go - 需要手动实现
arr := []int{1, 2, 3, 4, 5}
// 原地反转
for i, j := 0, len(arr)-1; i < j; i, j = i+1, j-1 {
    arr[i], arr[j] = arr[j], arr[i]
}
```

---

## 边界处理 {#边界处理}

### Python - 宽松边界
```python
arr = [1, 2, 3]

# 这些都不会报错
print(arr[10:])     # []
print(arr[:10])     # [1, 2, 3]
print(arr[-10:])    # [1, 2, 3]
print(arr[:-10])    # []

# 但索引访问会报错
try:
    print(arr[10])  # IndexError
except IndexError:
    print("索引超出范围")
```

### Go - 严格边界
```go
arr := []int{1, 2, 3}

// 这些会 panic
// fmt.Println(arr[10:])  // panic: runtime error
// fmt.Println(arr[:10])  // panic: runtime error

// 安全访问
if 10 <= len(arr) {
    fmt.Println(arr[10:])
} else {
    fmt.Println("索引超出范围")
}
```

---

## 性能对比 {#性能对比}

| 操作 | Python | Go | 说明 |
|------|--------|----|----- |
| 切片创建 | O(n) | O(1) | Go切片只是引用 |
| 元素访问 | O(1) | O(1) | 都很快 |
| 动态扩容 | 摊销O(1) | 摊销O(1) | 都有优化 |
| 内存占用 | 较高 | 较低 | Go更紧凑 |

### 内存模型差异
```python
# Python - 切片创建新对象
arr = [1, 2, 3, 4, 5]
sub = arr[1:4]  # 创建新列表
sub[0] = 999
print(arr)      # [1, 2, 3, 4, 5] - 原数组不变
```

```go
// Go - 切片共享底层数组
arr := []int{1, 2, 3, 4, 5}
sub := arr[1:4]  // 共享底层数组
sub[0] = 999
fmt.Println(arr)  // [1, 999, 3, 4, 5] - 原数组改变！
```

---

## 实战示例 {#实战示例}

### 示例1: 滑动窗口
```python
# Python - 找最大子数组和
def max_subarray_sum(arr, k):
    """长度为k的子数组最大和"""
    max_sum = float('-inf')
    for i in range(len(arr) - k + 1):
        current_sum = sum(arr[i:i+k])  # 切片很方便
        max_sum = max(max_sum, current_sum)
    return max_sum

arr = [1, 4, 2, 9, 5]
print(max_subarray_sum(arr, 3))  # 16
```

```go
// Go - 找最大子数组和
func maxSubarraySum(arr []int, k int) int {
    maxSum := math.MinInt32
    for i := 0; i <= len(arr)-k; i++ {
        currentSum := 0
        for _, v := range arr[i:i+k] {  // 切片遍历
            currentSum += v
        }
        if currentSum > maxSum {
            maxSum = currentSum
        }
    }
    return maxSum
}

arr := []int{1, 4, 2, 9, 5}
fmt.Println(maxSubarraySum(arr, 3))  // 16
```

### 示例2: 快速排序分区
```python
# Python - 快排分区
def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

# 使用切片递归
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quicksort(left) + middle + quicksort(right)
```

```go
// Go - 快排分区
func partition(arr []int, low, high int) int {
    pivot := arr[high]
    i := low - 1
    
    for j := low; j < high; j++ {
        if arr[j] <= pivot {
            i++
            arr[i], arr[j] = arr[j], arr[i]
        }
    }
    
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i + 1
}

// 原地快排
func quicksort(arr []int, low, high int) {
    if low < high {
        pi := partition(arr, low, high)
        quicksort(arr, low, pi-1)
        quicksort(arr, pi+1, high)
    }
}
```

---

## 🎯 总结与最佳实践

### Python 优势
- ✅ 负数索引很方便: `arr[-1]`
- ✅ 步长切片强大: `arr[::2]`, `arr[::-1]`
- ✅ 边界宽松，不易崩溃
- ✅ 语法简洁直观

### Go 优势  
- ✅ 性能更好，内存效率高
- ✅ 类型安全，编译时检查
- ✅ 切片共享底层数组，节省内存
- ✅ 并发安全性更好

### 最佳实践

1. **Python**: 充分利用切片语法糖
   ```python
   # 好的做法
   last_three = arr[-3:]
   reversed_arr = arr[::-1]
   every_second = arr[::2]
   ```

2. **Go**: 注意边界检查和内存共享
   ```go
   // 好的做法
   if i < len(arr) {
       sub := arr[i:]
   }
   
   // 避免意外修改
   sub := make([]int, len(arr[i:j]))
   copy(sub, arr[i:j])
   ```

3. **通用原则**:
   - 切片操作是左闭右开区间 `[start, end)`
   - 理解语言的内存模型差异
   - 在性能敏感场景选择Go，在快速开发场景选择Python

---

## 🔗 相关资源

- [Python 切片详解](https://docs.python.org/3/tutorial/introduction.html#lists)
- [Go 切片详解](https://go.dev/blog/slices-intro)
- [算法题中的切片技巧](./slice_tricks.md)

**Happy Coding! 🚀**