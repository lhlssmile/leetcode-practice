# Python 遍历方法大全 🐍

作为C++程序员转Python的完整指南！

## 1. 基础遍历方法

### 1.1 `range()` - 数字范围遍历
```python
# 基本用法
for i in range(5):          # 0, 1, 2, 3, 4
    print(i)

for i in range(2, 8):       # 2, 3, 4, 5, 6, 7
    print(i)

for i in range(0, 10, 2):   # 0, 2, 4, 6, 8 (步长为2)
    print(i)

for i in range(10, 0, -1):  # 10, 9, 8, ..., 1 (倒序)
    print(i)
```
**对比C++**: 类似于 `for(int i = 0; i < 5; i++)`

### 1.2 直接遍历容器
```python
# 遍历列表
nums = [1, 2, 3, 4, 5]
for num in nums:
    print(num)  # 直接获取值，不需要索引

# 遍历字符串
s = "hello"
for char in s:
    print(char)  # h, e, l, l, o

# 遍历字典的键
dict_data = {'a': 1, 'b': 2}
for key in dict_data:
    print(key)  # a, b
```
**对比C++**: Python可以直接遍历值，C++需要迭代器或索引

## 2. 高级遍历方法

### 2.1 `enumerate()` - 同时获取索引和值
```python
nums = ['apple', 'banana', 'cherry']

# 基本用法
for i, value in enumerate(nums):
    print(f"索引{i}: {value}")
# 输出: 索引0: apple, 索引1: banana, 索引2: cherry

# 指定起始索引
for i, value in enumerate(nums, start=1):
    print(f"第{i}个: {value}")
# 输出: 第1个: apple, 第2个: banana, 第3个: cherry
```
**对比C++**: 相当于同时维护索引和访问元素

### 2.2 `zip()` - 并行遍历多个容器
```python
names = ['Alice', 'Bob', 'Charlie']
ages = [25, 30, 35]
scores = [85, 92, 78]

# 并行遍历两个列表
for name, age in zip(names, ages):
    print(f"{name} is {age} years old")

# 并行遍历三个列表
for name, age, score in zip(names, ages, scores):
    print(f"{name}({age}): {score}分")

# zip会在最短列表结束时停止
short_list = [1, 2]
long_list = [10, 20, 30, 40]
for a, b in zip(short_list, long_list):
    print(a, b)  # 只输出 (1,10) 和 (2,20)
```
**对比C++**: 避免了手动管理多个索引

### 2.3 `zip_longest()` - 不等长列表的并行遍历
```python
from itertools import zip_longest

short = [1, 2]
long = [10, 20, 30, 40]

# 用None填充短列表
for a, b in zip_longest(short, long):
    print(a, b)  # (1,10), (2,20), (None,30), (None,40)

# 自定义填充值
for a, b in zip_longest(short, long, fillvalue=0):
    print(a, b)  # (1,10), (2,20), (0,30), (0,40)
```

## 3. 字典遍历方法

### 3.1 字典的三种遍历方式
```python
data = {'name': 'Alice', 'age': 25, 'city': 'Beijing'}

# 遍历键
for key in data:
    print(key)  # name, age, city

# 遍历值
for value in data.values():
    print(value)  # Alice, 25, Beijing

# 遍历键值对
for key, value in data.items():
    print(f"{key}: {value}")
```

### 3.2 带索引的字典遍历
```python
data = {'a': 1, 'b': 2, 'c': 3}

# 给字典项编号
for i, (key, value) in enumerate(data.items()):
    print(f"第{i+1}项: {key} = {value}")
```

## 4. 特殊遍历技巧

### 4.1 `reversed()` - 反向遍历
```python
nums = [1, 2, 3, 4, 5]

# 反向遍历
for num in reversed(nums):
    print(num)  # 5, 4, 3, 2, 1

# 反向遍历带索引
for i, num in enumerate(reversed(nums)):
    print(f"倒数第{i+1}个: {num}")
```

### 4.2 `sorted()` - 排序后遍历
```python
nums = [3, 1, 4, 1, 5]

# 排序后遍历（不改变原列表）
for num in sorted(nums):
    print(num)  # 1, 1, 3, 4, 5

# 倒序排序
for num in sorted(nums, reverse=True):
    print(num)  # 5, 4, 3, 1, 1

# 按自定义规则排序
words = ['apple', 'pie', 'a']
for word in sorted(words, key=len):  # 按长度排序
    print(word)  # a, pie, apple
```

### 4.3 `itertools.product()` - 笛卡尔积遍历
```python
from itertools import product

colors = ['red', 'blue']
sizes = ['S', 'M', 'L']

# 生成所有组合
for color, size in product(colors, sizes):
    print(f"{color}-{size}")
# red-S, red-M, red-L, blue-S, blue-M, blue-L
```

## 5. 列表推导式中的遍历

### 5.1 基础列表推导式
```python
# 传统方式
result = []
for i in range(5):
    result.append(i * 2)

# 列表推导式
result = [i * 2 for i in range(5)]  # [0, 2, 4, 6, 8]

# 带条件的列表推导式
even_squares = [x**2 for x in range(10) if x % 2 == 0]
# [0, 4, 16, 36, 64]
```

### 5.2 嵌套列表推导式
```python
# 二维列表展平
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
flat = [num for row in matrix for num in row]
# [1, 2, 3, 4, 5, 6, 7, 8, 9]

# 等价于:
flat = []
for row in matrix:
    for num in row:
        flat.append(num)
```

## 6. 性能对比和使用建议

### 6.1 性能对比
```python
# 最快：直接遍历
for item in items:
    process(item)

# 较快：enumerate（需要索引时）
for i, item in enumerate(items):
    process(i, item)

# 较慢：range + len（不推荐）
for i in range(len(items)):
    process(items[i])
```

### 6.2 使用建议

| 场景 | 推荐方法 | 示例 |
|------|----------|------|
| 只需要值 | 直接遍历 | `for item in items:` |
| 需要索引和值 | enumerate | `for i, item in enumerate(items):` |
| 并行遍历 | zip | `for a, b in zip(list1, list2):` |
| 遍历字典 | items() | `for k, v in dict.items():` |
| 反向遍历 | reversed | `for item in reversed(items):` |
| 排序遍历 | sorted | `for item in sorted(items):` |

## 7. 常见陷阱和注意事项

### 7.1 修改正在遍历的列表
```python
# ❌ 错误：遍历时修改列表
nums = [1, 2, 3, 4, 5]
for i, num in enumerate(nums):
    if num % 2 == 0:
        nums.remove(num)  # 危险！

# ✅ 正确：遍历副本
nums = [1, 2, 3, 4, 5]
for num in nums[:]:
    if num % 2 == 0:
        nums.remove(num)

# ✅ 更好：使用列表推导式
nums = [num for num in nums if num % 2 != 0]
```

### 7.2 字典遍历时修改
```python
# ❌ 错误：遍历时修改字典
data = {'a': 1, 'b': 2, 'c': 3}
for key in data:
    if data[key] % 2 == 0:
        del data[key]  # 运行时错误！

# ✅ 正确：遍历键的副本
for key in list(data.keys()):
    if data[key] % 2 == 0:
        del data[key]
```

## 8. 实际应用示例

### 8.1 LeetCode常用模式
```python
# 双指针遍历
def two_sum(nums, target):
    for i, num1 in enumerate(nums):
        for j, num2 in enumerate(nums[i+1:], i+1):
            if num1 + num2 == target:
                return [i, j]

# 滑动窗口
def max_subarray_sum(nums, k):
    max_sum = sum(nums[:k])
    current_sum = max_sum
    
    for i in range(k, len(nums)):
        current_sum = current_sum - nums[i-k] + nums[i]
        max_sum = max(max_sum, current_sum)
    
    return max_sum

# 矩阵遍历
def matrix_traverse(matrix):
    rows, cols = len(matrix), len(matrix[0])
    
    # 按行遍历
    for i in range(rows):
        for j in range(cols):
            print(matrix[i][j])
    
    # 使用enumerate
    for i, row in enumerate(matrix):
        for j, val in enumerate(row):
            print(f"({i},{j}): {val}")
```

### 8.2 数据处理示例
```python
# 处理CSV数据
data = [
    ['Name', 'Age', 'Score'],
    ['Alice', '25', '85'],
    ['Bob', '30', '92']
]

# 跳过表头，处理数据
for i, row in enumerate(data[1:], 1):
    name, age, score = row
    print(f"学生{i}: {name}({age}岁) - {score}分")

# 字典格式处理
headers = data[0]
for row in data[1:]:
    student = dict(zip(headers, row))
    print(f"{student['Name']}: {student['Score']}分")
```

## 总结

作为C++程序员，Python的遍历方式更加简洁和直观：

1. **优先使用直接遍历**：`for item in items`
2. **需要索引时用enumerate**：`for i, item in enumerate(items)`
3. **并行遍历用zip**：`for a, b in zip(list1, list2)`
4. **避免用range(len())**：除非特殊需求
5. **善用列表推导式**：代码更简洁
6. **注意遍历时修改容器**：使用副本或推导式

Python的遍历哲学：**简洁、直观、Pythonic！** 🐍✨