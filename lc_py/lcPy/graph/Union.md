# 并查集 (Union-Find) 学习笔记 🌟

## 📚 基础概念

### 什么是并查集？
并查集是一种**树型的数据结构**，用于处理一些**不相交集合**的合并及查询问题。

### 🎯 主要功能
1. **Find（查找）**：确定元素属于哪一个子集
2. **Union（合并）**：将两个子集合并成同一个集合

### 💡 应用场景
- 判断图中两个节点是否连通
- 最小生成树算法（Kruskal）
- 社交网络中的朋友圈问题
- 岛屿数量问题
- 账户合并问题

---

## 🔧 基本实现原理

### 1. 数据结构设计
```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))  # 父节点数组
        self.rank = [0] * n          # 秩（树的高度）
        self.components = n          # 连通分量数量
```

### 2. 核心思想
- 每个元素都有一个**父节点**
- 初始时，每个元素的父节点是**自己**
- 通过**路径压缩**和**按秩合并**优化性能

---

## 🚀 详细实现解析

### 1. 初始化 `__init__`
```python
def __init__(self, n):
    self.parent = list(range(n))  # [0, 1, 2, 3, ...]
    self.rank = [0] * n          # [0, 0, 0, 0, ...]
    self.components = n          # 初始有n个独立的集合
```

**解释**：
- `parent[i] = i`：每个节点的父节点初始为自己
- `rank[i] = 0`：每棵树的初始高度为0
- `components = n`：初始时有n个独立的连通分量

### 2. 查找根节点 `find` 🔍
```python
def find(self, x):
    """查找根节点，带路径压缩优化"""
    if self.parent[x] != x:
        self.parent[x] = self.find(self.parent[x])  # 路径压缩
    return self.parent[x]
```

**路径压缩优化**：
- **目的**：让查找路径上的所有节点直接指向根节点
- **效果**：将树的高度压缩，后续查找更快
- **时间复杂度**：接近 O(1)

**图解示例**：
```
原始树：     压缩后：
   0           0
   |          /|\
   1         1 2 3
   |
   2
   |
   3
```

### 3. 合并集合 `union` 🔗
```python
def union(self, x, y):
    """合并两个集合，返回是否成功合并"""
    root_x, root_y = self.find(x), self.find(y)
    if root_x == root_y:
        return False  # 已经在同一个集合中
    
    # 按秩合并优化
    if self.rank[root_x] < self.rank[root_y]:
        self.parent[root_x] = root_y
    elif self.rank[root_x] > self.rank[root_y]:
        self.parent[root_y] = root_x
    else:
        self.parent[root_y] = root_x
        self.rank[root_x] += 1
    
    self.components -= 1  # 连通分量减1
    return True
```

**按秩合并优化**：
- **目的**：总是将较矮的树合并到较高的树下
- **效果**：避免树退化成链表，保持树的平衡
- **规则**：
  - 如果两树高度不同：矮树 → 高树
  - 如果两树高度相同：任选一个作为根，高度+1

---

## 🎮 实战演示

### 示例：5个节点的并查集操作

```python
# 初始化
uf = UnionFind(5)
# parent: [0, 1, 2, 3, 4]
# rank:   [0, 0, 0, 0, 0]
# components: 5

# 合并 0 和 1
uf.union(0, 1)
# parent: [0, 0, 2, 3, 4]  # 1的父节点变为0
# rank:   [1, 0, 0, 0, 0]  # 0的秩增加
# components: 4

# 合并 2 和 3
uf.union(2, 3)
# parent: [0, 0, 2, 2, 4]
# rank:   [1, 0, 1, 0, 0]
# components: 3

# 合并 0 和 2（实际是合并两个集合）
uf.union(0, 2)
# parent: [0, 0, 0, 2, 4]  # 2的父节点变为0
# rank:   [2, 0, 1, 0, 0]  # 0的秩增加
# components: 2
```

---

## ⚡ 性能分析

### 时间复杂度
- **不优化**：O(n) 每次操作
- **路径压缩**：O(log n)
- **按秩合并**：O(log n)
- **两种优化结合**：O(α(n)) ≈ O(1)
  - α(n) 是阿克曼函数的反函数，增长极慢

### 空间复杂度
- O(n)：需要存储parent和rank数组

---

## 🌟 在 minCost 题目中的应用

### 核心思路
1. **目标**：找到最小的最大边权，使得图有 ≤ k 个连通分量
2. **策略**：二分查找 + 并查集验证
3. **验证过程**：
   ```python
   def canAchieve(max_weight):
       uf = UnionFind(n)
       # 只添加权重 <= max_weight 的边
       for u, v, w in edges:
           if w <= max_weight:
               uf.union(u, v)
       return uf.components <= k
   ```

### 为什么用并查集？
- **动态连通性**：可以动态地添加边并维护连通分量数量
- **高效查询**：O(α(n)) 的时间复杂度
- **简洁实现**：代码简单，逻辑清晰

---

## 🎯 常见变种和技巧

### 1. 带权并查集
```python
class WeightedUnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.weight = [0] * n  # 到根节点的权重
```

### 2. 查询集合大小
```python
class UnionFindWithSize:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n  # 每个集合的大小
    
    def get_size(self, x):
        return self.size[self.find(x)]
```

### 3. 撤销操作（可持久化）
```python
class PersistentUnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        self.history = []  # 记录操作历史
    
    def rollback(self):
        # 撤销最后一次union操作
        pass
```

---

## 💡 学习建议

1. **理解核心思想**：树形结构 + 路径压缩 + 按秩合并
2. **多做练习**：
   - LeetCode 200: 岛屿数量
   - LeetCode 547: 省份数量
   - LeetCode 721: 账户合并
   - LeetCode 1584: 连接所有点的最小费用
3. **掌握变种**：带权并查集、可撤销并查集
4. **理解应用**：图论、最小生成树、动态连通性

---

## 🚀 总结

并查集是一个**简单而强大**的数据结构：
- **核心操作**：Find + Union
- **关键优化**：路径压缩 + 按秩合并
- **时间复杂度**：接近 O(1)
- **应用广泛**：图论、动态连通性问题的利器

记住：**并查集 = 森林 + 优化**！🌲🌲🌲