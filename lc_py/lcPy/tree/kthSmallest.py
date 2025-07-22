'''
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。



示例 1：


输入：root = [3,1,4,null,2], k = 1
输出：1
示例 2：


输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3




提示：

树中的节点数为 n 。
1 <= k <= n <= 104
0 <= Node.val <= 104
'''
from typing import Optional


class TreeNode:
    def __init__(self, val = 0, left  = None, right = None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        # 方法1：基础中序遍历（完整遍历）
        def inorder_basic(node):
            if not node:
                return []
            return inorder_basic(node.left) + [node.val] + inorder_basic(node.right)
        
        result = inorder_basic(root)
        return result[k-1]
    
    def kthSmallest_optimized(self, root: Optional[TreeNode], k: int) -> int:
        # 方法2：提前终止的中序遍历（推荐）
        self.count = 0
        self.result = None
        
        def inorder_early_stop(node):
            if not node or self.result is not None:
                return
            
            # 遍历左子树
            inorder_early_stop(node.left)
            
            # 处理当前节点
            self.count += 1
            if self.count == k:
                self.result = node.val
                return
            
            # 遍历右子树
            inorder_early_stop(node.right)
        
        inorder_early_stop(root)
        return self.result
    
    def kthSmallest_iterative(self, root: Optional[TreeNode], k: int) -> int:
        # 方法3：迭代版本中序遍历（空间优化）
        stack = []
        current = root
        count = 0
        
        while stack or current:
            # 一直向左走到底
            while current:
                stack.append(current)
                current = current.left
            
            # 处理栈顶节点
            current = stack.pop()
            count += 1
            
            if count == k:
                return current.val
            
            # 转向右子树
            current = current.right
        
        return -1  # 不应该到达这里
    
    def kthSmallest_with_count(self, root: Optional[TreeNode], k: int) -> int:
        # 方法4：带节点计数的优化版本（适合频繁查询）
        # 如果需要频繁查询，可以预先计算每个节点的左子树大小
        
        def count_nodes(node):
            """计算节点数量"""
            if not node:
                return 0
            return 1 + count_nodes(node.left) + count_nodes(node.right)
        
        def kth_helper(node, k):
            if not node:
                return None
            
            left_count = count_nodes(node.left)
            
            if k == left_count + 1:
                # 当前节点就是第k小的
                return node.val
            elif k <= left_count:
                # 第k小的在左子树
                return kth_helper(node.left, k)
            else:
                # 第k小的在右子树
                return kth_helper(node.right, k - left_count - 1)
        
        return kth_helper(root, k)


# 优化版TreeNode（如果可以修改数据结构）
class TreeNodeWithCount:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        self.left_count = 0  # 左子树节点数量

class SolutionWithCount:
    """如果可以修改数据结构，预先计算左子树大小"""
    
    def build_tree_with_count(self, root: Optional[TreeNode]) -> Optional[TreeNodeWithCount]:
        """构建带计数的树"""
        if not root:
            return None
        
        new_node = TreeNodeWithCount(root.val)
        new_node.left = self.build_tree_with_count(root.left)
        new_node.right = self.build_tree_with_count(root.right)
        
        # 计算左子树大小
        new_node.left_count = self.count_nodes(new_node.left)
        return new_node
    
    def count_nodes(self, node: Optional[TreeNodeWithCount]) -> int:
        if not node:
            return 0
        return 1 + self.count_nodes(node.left) + self.count_nodes(node.right)
    
    def kthSmallest(self, root: Optional[TreeNodeWithCount], k: int) -> int:
        """O(log n)时间复杂度查找第k小元素"""
        if not root:
            return -1
        
        if k == root.left_count + 1:
            return root.val
        elif k <= root.left_count:
            return self.kthSmallest(root.left, k)
        else:
            return self.kthSmallest(root.right, k - root.left_count - 1)


if __name__ == '__main__':
    # 测试用例
    print("=== BST第k小元素测试 ===")
    
    # 构建测试树: [5,3,6,2,4,null,null,1]
    #       5
    #      / \
    #     3   6
    #    / \
    #   2   4
    #  /
    # 1
    root = TreeNode(5)
    root.left = TreeNode(3)
    root.right = TreeNode(6)
    root.left.left = TreeNode(2)
    root.left.right = TreeNode(4)
    root.left.left.left = TreeNode(1)
    
    s = Solution()
    
    print("\n测试树的中序遍历应该是: [1, 2, 3, 4, 5, 6]")
    
    # 测试不同方法
    for k in [1, 3, 6]:
        print(f"\nk = {k}:")
        print(f"基础中序遍历: {s.kthSmallest(root, k)}")
        print(f"提前终止版本: {s.kthSmallest_optimized(root, k)}")
        print(f"迭代版本: {s.kthSmallest_iterative(root, k)}")
        print(f"节点计数版本: {s.kthSmallest_with_count(root, k)}")
    
    # 测试优化版数据结构
    print("\n=== 优化数据结构测试 ===")
    s_count = SolutionWithCount()
    root_with_count = s_count.build_tree_with_count(root)
    
    for k in [1, 3, 6]:
         result = s_count.kthSmallest(root_with_count, k)
         print(f"k = {k}, 结果: {result}")

"""
=== BST第k小元素算法分析与优化策略 ===

【题目核心】
利用BST的性质：中序遍历得到有序序列，找第k小元素

【四种解法对比】

1. 基础中序遍历
   思路：完整中序遍历，返回第k-1个元素
   时间复杂度：O(n)
   空间复杂度：O(n) - 存储所有节点值
   优点：简单直观
   缺点：浪费时间和空间，遍历了不必要的节点

2. 提前终止的中序遍历（推荐）
   思路：中序遍历过程中计数，找到第k个就停止
   时间复杂度：O(H + k) - H是树高，最坏O(n)
   空间复杂度：O(H) - 递归栈深度
   优点：
   - 找到答案立即停止，避免不必要遍历
   - 平均情况下比完整遍历快很多
   - 代码清晰易懂
   缺点：仍然是递归实现

3. 迭代版本中序遍历
   思路：用栈模拟递归，避免递归开销
   时间复杂度：O(H + k)
   空间复杂度：O(H) - 显式栈
   优点：
   - 避免递归调用开销
   - 空间使用更可控
   - 可以处理更深的树
   缺点：代码稍微复杂

4. 节点计数优化版本
   思路：利用左子树大小快速定位
   时间复杂度：O(H * H) - 每层都要计算子树大小
   空间复杂度：O(H)
   优点：思路巧妙，利用BST结构
   缺点：重复计算子树大小，实际可能更慢

5. 预计算版本（终极优化）
   思路：预先计算每个节点的左子树大小
   预处理：O(n)时间，O(n)空间
   查询时间：O(H) ≈ O(log n)（平衡树）
   适用场景：需要频繁查询第k小元素
   优点：查询极快，适合多次查询
   缺点：需要额外空间，修改数据结构

【性能优化关键点】

1. 提前终止策略
   - 核心思想：找到目标立即停止
   - 避免遍历不必要的节点
   - 特别是当k较小时，效果显著

2. 空间优化
   - 迭代 vs 递归：避免递归栈溢出
   - 不存储完整序列：节省内存
   - 只维护必要的状态信息

3. 数据结构增强
   - 预计算左子树大小：O(log n)查询
   - 适合频繁查询的场景
   - 类似于线段树的思想

【算法选择建议】

1. 单次查询：使用提前终止的中序遍历
   - 代码简洁，性能良好
   - 平均情况下只需遍历k个节点

2. 多次查询：考虑预计算版本
   - 一次预处理，多次O(log n)查询
   - 空间换时间的经典策略

3. 内存受限：使用迭代版本
   - 避免递归栈开销
   - 更好的空间控制

【扩展思考】

1. 动态BST：支持插入删除的第k小查询
   - 需要维护子树大小信息
   - 可以用平衡树（如AVL、红黑树）实现

2. 第k大元素：反向中序遍历（右-根-左）

3. 范围查询：找第i小到第j小的所有元素
   - 可以在中序遍历中设置起止条件

4. 近似查询：当k很大时，可以考虑采样策略

【复杂度总结】
最优解法（提前终止中序遍历）：
- 时间复杂度：平均O(log n + k)，最坏O(n)
- 空间复杂度：O(log n)（平衡树的递归深度）
- 实际性能：当k << n时，性能接近O(log n)

【面试要点】
1. 先说基础思路：BST中序遍历的有序性
2. 提出优化：提前终止避免不必要遍历
3. 进一步优化：迭代版本、预计算等
4. 分析复杂度：时间空间权衡
5. 讨论适用场景：单次vs多次查询
"""