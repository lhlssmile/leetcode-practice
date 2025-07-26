# 线段树 (Segment Tree) 学习笔记 🌳

## 1. 什么是线段树？

线段树是一种二叉树数据结构，用于高效地处理区间查询和区间更新问题。它将一个数组分解成多个区间，每个节点代表一个区间，叶子节点代表单个元素。

### 核心特点：
- **区间查询**：O(log n) 时间复杂度
- **单点/区间更新**：O(log n) 时间复杂度
- **空间复杂度**：O(4n) ≈ O(n)

## 2. 什么时候使用线段树？🤔

### 适用场景：
1. **频繁的区间查询 + 更新操作**
   - 区间求和、最大值、最小值
   - 区间更新（单点更新或区间更新）

2. **具体问题类型：**
   - 区间求和问题（Range Sum Query）
   - 区间最值问题（Range Min/Max Query）
   - 区间更新问题（Range Update）
   - 动态数组问题

3. **判断标准：**
   ```
   如果你需要：
   - 多次区间查询 AND
   - 多次更新操作 AND
   - 查询/更新次数 > √n
   
   那么考虑使用线段树！
   ```

### 不适用场景：
- 只有查询没有更新 → 用前缀和
- 更新次数很少 → 用暴力或前缀和
- 只有单点查询 → 用普通数组

## 3. 线段树基本结构

```python
class SegmentTree:
    def __init__(self, arr):
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)  # 4倍空间保证够用
        self.build(arr, 0, 0, self.n - 1)
    
    def build(self, arr, node, start, end):
        """构建线段树"""
        if start == end:
            # 叶子节点
            self.tree[node] = arr[start]
        else:
            mid = (start + end) // 2
            # 递归构建左右子树
            self.build(arr, 2*node+1, start, mid)
            self.build(arr, 2*node+2, mid+1, end)
            # 合并子节点信息
            self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
```

## 4. 核心操作实现

### 4.1 区间查询（求和）
```python
def query(self, node, start, end, l, r):
    """查询区间[l,r]的和"""
    if r < start or end < l:
        return 0  # 完全不重叠
    if l <= start and end <= r:
        return self.tree[node]  # 完全包含
    
    # 部分重叠，递归查询
    mid = (start + end) // 2
    left_sum = self.query(2*node+1, start, mid, l, r)
    right_sum = self.query(2*node+2, mid+1, end, l, r)
    return left_sum + right_sum
```

### 4.2 单点更新
```python
def update(self, node, start, end, idx, val):
    """将位置idx的值更新为val"""
    if start == end:
        self.tree[node] = val
    else:
        mid = (start + end) // 2
        if idx <= mid:
            self.update(2*node+1, start, mid, idx, val)
        else:
            self.update(2*node+2, mid+1, end, idx, val)
        # 更新当前节点
        self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
```

## 5. 完整实现示例

```python
class SegmentTree:
    def __init__(self, arr):
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)
        self.build(arr, 0, 0, self.n - 1)
    
    def build(self, arr, node, start, end):
        if start == end:
            self.tree[node] = arr[start]
        else:
            mid = (start + end) // 2
            self.build(arr, 2*node+1, start, mid)
            self.build(arr, 2*node+2, mid+1, end)
            self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
    
    def update(self, node, start, end, idx, val):
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if idx <= mid:
                self.update(2*node+1, start, mid, idx, val)
            else:
                self.update(2*node+2, mid+1, end, idx, val)
            self.tree[node] = self.tree[2*node+1] + self.tree[2*node+2]
    
    def query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        
        mid = (start + end) // 2
        left_sum = self.query(2*node+1, start, mid, l, r)
        right_sum = self.query(2*node+2, mid+1, end, l, r)
        return left_sum + right_sum
    
    # 对外接口
    def range_sum(self, l, r):
        return self.query(0, 0, self.n-1, l, r)
    
    def point_update(self, idx, val):
        self.update(0, 0, self.n-1, idx, val)
```

## 6. 使用示例

```python
# 创建线段树
arr = [1, 3, 5, 7, 9, 11]
st = SegmentTree(arr)

# 区间查询
print(st.range_sum(1, 3))  # 查询[1,3]区间和: 3+5+7=15

# 单点更新
st.point_update(1, 10)     # 将位置1的值改为10
print(st.range_sum(1, 3))  # 现在[1,3]区间和: 10+5+7=22
```

## 7. 线段树变种

### 7.1 区间最值线段树
```python
# 只需要修改合并操作
def build(self, arr, node, start, end):
    if start == end:
        self.tree[node] = arr[start]
    else:
        mid = (start + end) // 2
        self.build(arr, 2*node+1, start, mid)
        self.build(arr, 2*node+2, mid+1, end)
        # 改为求最大值
        self.tree[node] = max(self.tree[2*node+1], self.tree[2*node+2])
```

### 7.2 懒惰传播（Lazy Propagation）
用于区间更新，避免每次都更新到叶子节点。

```python
class LazySegmentTree:
    def __init__(self, arr):
        self.n = len(arr)
        self.tree = [0] * (4 * self.n)
        self.lazy = [0] * (4 * self.n)  # 懒惰标记
        self.build(arr, 0, 0, self.n - 1)
    
    def push(self, node, start, end):
        """下推懒惰标记"""
        if self.lazy[node] != 0:
            self.tree[node] += self.lazy[node] * (end - start + 1)
            if start != end:  # 不是叶子节点
                self.lazy[2*node+1] += self.lazy[node]
                self.lazy[2*node+2] += self.lazy[node]
            self.lazy[node] = 0
```

## 8. 经典题目类型

### 8.1 基础题目
- **Range Sum Query - Mutable** (LeetCode 307)
- **Range Minimum Query** 
- **Count of Range Sum** (LeetCode 327)

### 8.2 进阶题目
- **The Skyline Problem** (LeetCode 218)
- **Falling Squares** (LeetCode 699)
- **Rectangle Area II** (LeetCode 850)

## 9. 线段树 vs 其他数据结构

| 操作 | 数组 | 前缀和 | 线段树 | 树状数组 |
|------|------|--------|--------|----------|
| 构建 | O(1) | O(n) | O(n) | O(n) |
| 单点更新 | O(1) | O(n) | O(log n) | O(log n) |
| 区间查询 | O(n) | O(1) | O(log n) | O(log n) |
| 区间更新 | O(n) | O(n) | O(log n) | O(log n) |
| 空间复杂度 | O(n) | O(n) | O(4n) | O(n) |

## 10. 实战技巧 💡

### 10.1 节点编号技巧
- 根节点：0
- 左子节点：2*i + 1
- 右子节点：2*i + 2
- 父节点：(i-1) // 2

### 10.2 空间分配
- 一般分配 4*n 的空间就够用
- 如果要精确计算：2^(⌈log₂n⌉+1) - 1

### 10.3 调试技巧
```python
def print_tree(self):
    """打印线段树结构（调试用）"""
    def dfs(node, start, end, depth=0):
        if start <= end:
            print("  " * depth + f"[{start},{end}]: {self.tree[node]}")
            if start != end:
                mid = (start + end) // 2
                dfs(2*node+1, start, mid, depth+1)
                dfs(2*node+2, mid+1, end, depth+1)
    dfs(0, 0, self.n-1)
```

## 11. 总结

线段树是处理区间问题的强大工具，特别适合：
- 需要频繁区间查询和更新的场景
- 动态数组问题
- 需要维护区间信息的问题

**记住口诀**：
> 区间查询要更新，线段树来帮你忙！
> 构建查询都log n，效率高来空间省！

希望这份笔记能帮助你理解和掌握线段树！🚀