
#### 2. 线段树的核心操作
- **构建**：
- 从数组递归构造树。
- 每个节点存储区间的某种信息（比如和）。
- 时间：`O(n)`。
- **查询**：
- 查询区间 `[L, R]` 的信息。
- 从根节点递归，分三种情况：
- 当前区间 `[l, r]` 完全在 `[L, R]` 内：返回节点信息。
- 当前区间完全在 `[L, R]` 外：忽略。
- 部分重叠：递归查询左右子节点，合并结果。
- 时间：`O(log n)`。
- **更新**：
- 修改某个位置或区间的值，递归更新相关节点。
- 时间：`O(log n)`（单点更新），`O(log n + k)`（区间更新，k 是更新范围）。

#### 3. 官方解法和线段树的关系
官方解法**不是标准的线段树**，但借用了线段树的思想：
- **相似点**：
- **区间分解**：像线段树一样，把数组分成 `[l, mid]` 和 `[mid+1, r]`，递归处理。
- **信息维护**：`Status` 结构类似线段树节点的“信息”，存储 `lSum`, `rSum`, `mSum`, `iSum`。
- **合并操作**：`pushUp` 函数类似线段树的节点合并，左右子区间的 `Status` 合并成父节点的 `Status`。
- **不同点**：
- **动态性**：线段树通常支持动态查询和更新（多次操作），而官方解法是一次性计算整个数组的 `mSum`。
- **存储**：线段树显式存储树结构（数组或指针），官方解法通过递归栈隐式实现。
- **时间复杂度**：
- 官方解法：`O(n)`（构建树的一次性过程）。
- 标准线段树：构建 `O(n)`，查询/更新 `O(log n)`。
- **为什么像线段树？**：
- 官方解法维护了区间的**前缀和**、**后缀和**等信息，类似线段树为区间查询设计的节点信息。
- `pushUp` 的合并逻辑模拟了线段树如何从子节点信息推导父节点信息。

#### 4. 线段树基础代码（以区间和为例）
为了让你彻底懂线段树，我写一个简单的线段树实现，维护区间和，支持查询和单点更新：
```cpp
#include <vector>

class SegmentTree {
private:
std::vector<int> tree; // 线段树数组
int n; // 数组大小

// 构建树，node 是当前节点，[l, r] 是区间
void build(const std::vector<int>& nums, int node, int l, int r) {
    if (l == r) {
        tree[node] = nums[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(nums, 2 * node + 1, l, mid); // 左子节点
    build(nums, 2 * node + 2, mid + 1, r); // 右子节点
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // 合并
}

// 查询 [ql, qr] 的和
int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node]; // 完全覆盖
    if (r < ql || qr < l) return 0; // 无交集
    int mid = (l + r) >> 1;
    return query(2 * node + 1, l, mid, ql, qr) +
           query(2 * node + 2, mid + 1, r, ql, qr); // 部分重叠
}

// 更新位置 pos 的值为 val
void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(2 * node + 1, l, mid, pos, val);
    else update(2 * node + 2, mid + 1, r, pos, val);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; // 维护父节点
}

public:
SegmentTree(const std::vector<int>& nums) {
    n = nums.size();
    tree.resize(4 * n); // 线段树大小约为 4n
    build(nums, 0, 0, n - 1);
}

int query(int left, int right) {
    return query(0, 0, n - 1, left, right);
}

void update(int pos, int val) {
    update(0, 0, n - 1, pos, val);
}
};