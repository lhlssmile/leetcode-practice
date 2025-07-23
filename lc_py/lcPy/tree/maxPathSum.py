'''
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。



示例 1：


输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
示例 2：


输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42


提示：

树中节点数目范围是 [1, 3 * 104]
-1000 <= Node.val <= 1000
'''
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        """
        二叉树最大路径和 - 树上DP经典题目
        
        核心思想：
        对于每个节点，路径有两种情况：
        1. 经过该节点的路径（该节点作为路径的"转折点"）
        2. 从该节点向下延伸的路径（该节点作为路径的起点）
        
        关键洞察：
        - 每个节点都可能是最优路径的"最高点"（转折点）
        - 从每个节点向下，我们只能选择一条路径继续向上传递
        - 但在计算全局最优时，可以考虑左右两条路径都选择
        """
        self.max_sum = float('-inf')  # 全局最大路径和
        
        def max_gain(node):
            """
            返回从当前节点向下能获得的最大路径和
            同时更新全局最大路径和
            
            返回值：从node开始向下的单边最大路径和
            副作用：更新self.max_sum（考虑以node为转折点的路径）
            """
            if not node:
                return 0
            
            # 递归计算左右子树的最大贡献值
            # 如果贡献值为负，我们选择不要这条路径（用0代替）
            left_gain = max(max_gain(node.left), 0)
            right_gain = max(max_gain(node.right), 0)
            
            # 以当前节点为转折点的路径和
            current_max = node.val + left_gain + right_gain
            
            # 更新全局最大值
            self.max_sum = max(self.max_sum, current_max)
            
            # 返回从当前节点开始的单边最大路径和
            # 只能选择左边或右边，不能两边都选（因为要向上传递）
            return node.val + max(left_gain, right_gain)
        
        max_gain(root)
        return self.max_sum
    
    def maxPathSum_v2_detailed(self, root: Optional[TreeNode]) -> int:
        """
        详细版本 - 更容易理解的实现
        
        思路分解：
        1. 对于每个节点，计算两个值：
           - 向下延伸的最大路径和（用于向上传递）
           - 经过该节点的最大路径和（用于更新全局答案）
        2. 递归处理所有节点
        """
        if not root:
            return 0
        
        self.result = float('-inf')
        
        def dfs(node):
            if not node:
                return 0
            
            # 计算左右子树向下延伸的最大路径和
            left_max = dfs(node.left)
            right_max = dfs(node.right)
            
            # 如果子树路径和为负，不如不选择
            left_max = max(left_max, 0)
            right_max = max(right_max, 0)
            
            # 经过当前节点的最大路径和（可以连接左右子树）
            path_through_node = node.val + left_max + right_max
            
            # 更新全局最大值
            self.result = max(self.result, path_through_node)
            
            # 返回从当前节点开始向下的最大路径和
            # 只能选择一边，因为要向父节点传递
            return node.val + max(left_max, right_max)
        
        dfs(root)
        return self.result
    
    def maxPathSum_v3_with_explanation(self, root: Optional[TreeNode]) -> int:
        """
        带详细注释的版本 - 解释每一步的含义
        """
        # 用于记录全局最大路径和
        self.global_max = float('-inf')
        
        def helper(node):
            """
            功能：计算以node为根的子树中，从node开始向下的最大路径和
            副作用：更新全局最大路径和
            
            返回值含义：从node开始，向其子树方向延伸的最大路径和
            这个值可以被node的父节点使用
            """
            # 基础情况：空节点贡献0
            if not node:
                return 0
            
            # 递归计算左右子树的贡献
            left_contribution = helper(node.left)
            right_contribution = helper(node.right)
            
            # 负贡献我们不要，选择0（即不走这条路径）
            left_contribution = max(left_contribution, 0)
            right_contribution = max(right_contribution, 0)
            
            # 情况1：以当前节点为"桥梁"的路径
            # 这种路径连接了左子树、当前节点、右子树
            bridge_path_sum = left_contribution + node.val + right_contribution
            
            # 更新全局最大值
            self.global_max = max(self.global_max, bridge_path_sum)
            
            # 情况2：从当前节点开始向下的路径
            # 只能选择左边或右边，因为要向上传递给父节点
            downward_path_sum = node.val + max(left_contribution, right_contribution)
            
            return downward_path_sum
        
        helper(root)
        return self.global_max


def create_test_tree1():
    """
    创建测试树1: [1,2,3]
         1
        / \
       2   3
    最优路径: 2 -> 1 -> 3, 路径和 = 6
    """
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    return root


def create_test_tree2():
    """
    创建测试树2: [-10,9,20,null,null,15,7]
           -10
          /   \
         9     20
              /  \
             15   7
    最优路径: 15 -> 20 -> 7, 路径和 = 42
    """
    root = TreeNode(-10)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)
    return root


def create_test_tree3():
    """
    创建测试树3: 全负数情况
         -3
        /   \
      -2    -1
    最优路径: 选择单个节点-1, 路径和 = -1
    """
    root = TreeNode(-3)
    root.left = TreeNode(-2)
    root.right = TreeNode(-1)
    return root


def test_max_path_sum():
    """
    测试所有解法的正确性
    """
    solution = Solution()
    
    test_cases = [
        (create_test_tree1(), 6, "示例1: [1,2,3]"),
        (create_test_tree2(), 42, "示例2: [-10,9,20,null,null,15,7]"),
        (create_test_tree3(), -1, "全负数: [-3,-2,-1]")
    ]
    
    methods = [
        ("标准解法", solution.maxPathSum),
        ("详细版本", solution.maxPathSum_v2_detailed),
        ("注释版本", solution.maxPathSum_v3_with_explanation)
    ]
    
    for method_name, method in methods:
        print(f"\n=== {method_name} ===")
        all_passed = True
        
        for tree, expected, desc in test_cases:
            # 重新创建solution实例，避免实例变量污染
            fresh_solution = Solution()
            if method_name == "标准解法":
                result = fresh_solution.maxPathSum(tree)
            elif method_name == "详细版本":
                result = fresh_solution.maxPathSum_v2_detailed(tree)
            else:
                result = fresh_solution.maxPathSum_v3_with_explanation(tree)
            
            status = "✅" if result == expected else "❌"
            print(f"{status} {desc} -> {result} (期望: {expected})")
            if result != expected:
                all_passed = False
        
        print(f"结果: {'全部通过' if all_passed else '存在错误'}")


def explain_why_prefix_sum_doesnt_work():
    """
    解释为什么前缀和方法不适用于这个问题
    """
    print("\n🤔 为什么前缀和方法不适用？")
    print("=" * 50)
    
    print("""
📝 你的想法分析：
你提到让每个节点存储"前缀和数组"，比如节点20存储路径：
- (9, -10, 20)
- (-10, 20) 
- (20)
- (15, 20)

❌ 这个方法的问题：
1. **路径定义错误**: (9, -10, 20) 不是有效路径，因为9和-10不相邻
2. **存储爆炸**: 每个节点需要存储指数级数量的路径
3. **重复计算**: 大量重复的子路径计算
4. **无法处理分叉**: 树的分叉结构使得前缀和概念不适用

✅ 正确的树上DP思路：
1. **状态定义**: 每个节点只需要知道"从我开始向下的最大路径和"
2. **转移方程**: max_gain(node) = node.val + max(max_gain(left), max_gain(right), 0)
3. **全局更新**: 考虑以每个节点为"桥梁"的路径
4. **时间复杂度**: O(n) - 每个节点只访问一次

🎯 关键区别：
- 前缀和适用于线性结构（数组）
- 树上DP适用于树形结构，利用子问题的最优解
    """)


def visualize_dp_process():
    """
    可视化DP过程
    """
    print("\n🌳 树上DP过程可视化")
    print("=" * 50)
    
    print("""
以示例2为例: [-10,9,20,null,null,15,7]

           -10
          /   \
         9     20
              /  \
             15   7

🔄 DP过程（后序遍历）：

1️⃣ 处理叶子节点：
   - max_gain(15) = 15, global_max = 15
   - max_gain(7) = 7, global_max = 15

2️⃣ 处理节点20：
   - left_gain = max_gain(15) = 15
   - right_gain = max_gain(7) = 7  
   - 桥梁路径: 15 + 20 + 7 = 42
   - global_max = max(15, 42) = 42
   - 返回: 20 + max(15, 7) = 35

3️⃣ 处理节点9：
   - 无子节点，返回9
   - global_max = max(42, 9) = 42

4️⃣ 处理根节点-10：
   - left_gain = max_gain(9) = 9
   - right_gain = max_gain(20) = 35
   - 桥梁路径: 9 + (-10) + 35 = 34
   - global_max = max(42, 34) = 42
   - 返回: -10 + max(9, 35) = 25

🎯 最终答案: 42 (路径 15 -> 20 -> 7)
    """)


def dp_learning_tips():
    """
    树上DP学习要点
    """
    print("\n💡 树上DP学习要点")
    print("=" * 50)
    
    print("""
🎯 核心思想：
1. **子问题定义**: 明确每个节点需要返回什么信息
2. **状态转移**: 如何从子节点的信息计算当前节点的信息
3. **全局维护**: 在递归过程中维护全局最优解

🔧 解题模板：
```python
def tree_dp(root):
    self.global_answer = initial_value
    
    def dfs(node):
        if not node:
            return base_case
        
        # 递归处理子树
        left_info = dfs(node.left)
        right_info = dfs(node.right)
        
        # 计算当前节点的信息
        current_info = combine(node.val, left_info, right_info)
        
        # 更新全局答案
        self.global_answer = update(self.global_answer, current_info)
        
        # 返回给父节点的信息
        return info_for_parent
    
    dfs(root)
    return self.global_answer
```

📚 常见树上DP题目：
- 二叉树的直径
- 打家劫舍III
- 二叉树中的最大路径和（本题）
- 树的重心

🎓 学习建议：
1. 先理解递归的含义
2. 明确每个函数的返回值含义
3. 区分"局部最优"和"全局最优"
4. 多画图理解递归过程
    """)


if __name__ == "__main__":
    # 运行测试
    test_max_path_sum()
    
    # 解释前缀和方法的问题
    explain_why_prefix_sum_doesnt_work()
    
    # 可视化DP过程
    visualize_dp_process()
    
    # 学习要点
    dp_learning_tips()
    
    print("\n🎉 学习完成！")
    print("💡 记住：树上DP的关键是定义好子问题和状态转移！")
