'''
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。



示例 1:


输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
示例 2:

输入: preorder = [-1], inorder = [-1]
输出: [-1]


提示:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder 和 inorder 均 无重复 元素
inorder 均出现在 preorder
preorder 保证 为二叉树的前序遍历序列
inorder 保证 为二叉树的中序遍历序列

'''
from typing import Optional, List


class TreeNode:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        # 为中序遍历创建索引映射，快速定位根节点在中序遍历中的位置
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        self.preorder_idx = 0  # 前序遍历的当前索引
        
        def build(left: int, right: int) -> Optional[TreeNode]:
            """
            递归构建二叉树
            left, right: 当前子树在中序遍历中的左右边界
            """
            if left > right:
                return None
            
            # 前序遍历的当前节点就是当前子树的根节点
            root_val = preorder[self.preorder_idx]
            self.preorder_idx += 1
            
            # 创建根节点
            root = TreeNode(root_val)
            
            # 在中序遍历中找到根节点的位置
            root_idx = inorder_map[root_val]
            
            # 递归构建左子树（注意：必须先构建左子树，因为前序遍历是根->左->右）
            root.left = build(left, root_idx - 1)
            # 递归构建右子树
            root.right = build(root_idx + 1, right)
            
            return root
        
        return build(0, len(inorder) - 1)
    
    def buildTree_debug(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        """
        带调试信息的版本，帮助理解算法过程
        """
        print(f"构建树: preorder={preorder}, inorder={inorder}")
        
        # 为中序遍历创建索引映射
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        print(f"中序遍历索引映射: {inorder_map}")
        
        self.preorder_idx = 0
        
        def build_debug(left: int, right: int, depth: int = 0) -> Optional[TreeNode]:
            indent = "  " * depth
            print(f"{indent}构建子树: 中序范围[{left}, {right}]")
            
            if left > right:
                print(f"{indent}范围无效，返回None")
                return None
            
            # 当前根节点
            root_val = preorder[self.preorder_idx]
            print(f"{indent}当前根节点: {root_val} (前序索引: {self.preorder_idx})")
            self.preorder_idx += 1
            
            root = TreeNode(root_val)
            root_idx = inorder_map[root_val]
            print(f"{indent}根节点在中序中的位置: {root_idx}")
            
            # 构建左子树
            if left <= root_idx - 1:
                print(f"{indent}构建左子树: 中序范围[{left}, {root_idx - 1}]")
                root.left = build_debug(left, root_idx - 1, depth + 1)
            
            # 构建右子树
            if root_idx + 1 <= right:
                print(f"{indent}构建右子树: 中序范围[{root_idx + 1}, {right}]")
                root.right = build_debug(root_idx + 1, right, depth + 1)
            
            return root
        
        return build_debug(0, len(inorder) - 1)


def print_tree_preorder(root: Optional[TreeNode]) -> List[int]:
    """前序遍历打印树（用于验证结果）"""
    if not root:
        return []
    result = [root.val]
    result.extend(print_tree_preorder(root.left))
    result.extend(print_tree_preorder(root.right))
    return result


def print_tree_inorder(root: Optional[TreeNode]) -> List[int]:
    """中序遍历打印树（用于验证结果）"""
    if not root:
        return []
    result = []
    result.extend(print_tree_inorder(root.left))
    result.append(root.val)
    result.extend(print_tree_inorder(root.right))
    return result


if __name__ == '__main__':
    solution = Solution()
    
    # 测试用例1
    print("=== 测试用例1 ===")
    preorder1 = [3, 9, 20, 15, 7]
    inorder1 = [9, 3, 15, 20, 7]
    print(f"输入: preorder={preorder1}, inorder={inorder1}")
    
    # 使用调试版本
    print("\n--- 调试过程 ---")
    root1 = solution.buildTree_debug(preorder1, inorder1)
    
    # 验证结果
    print("\n--- 验证结果 ---")
    result_preorder = print_tree_preorder(root1)
    result_inorder = print_tree_inorder(root1)
    print(f"构建后的前序遍历: {result_preorder}")
    print(f"构建后的中序遍历: {result_inorder}")
    print(f"前序遍历匹配: {result_preorder == preorder1}")
    print(f"中序遍历匹配: {result_inorder == inorder1}")
    
    # 测试用例2
    print("\n=== 测试用例2 ===")
    preorder2 = [-1]
    inorder2 = [-1]
    print(f"输入: preorder={preorder2}, inorder={inorder2}")
    
    root2 = solution.buildTree(preorder2, inorder2)
    result_preorder2 = print_tree_preorder(root2)
    result_inorder2 = print_tree_inorder(root2)
    print(f"构建后的前序遍历: {result_preorder2}")
    print(f"构建后的中序遍历: {result_inorder2}")
    print(f"前序遍历匹配: {result_preorder2 == preorder2}")
    print(f"中序遍历匹配: {result_inorder2 == inorder2}")
    
    # 算法分析
    print("\n=== 算法分析 ===")
    print("时间复杂度: O(n) - 每个节点访问一次")
    print("空间复杂度: O(n) - 哈希表存储中序遍历索引 + 递归栈空间")
    print("\n核心思想:")
    print("1. 前序遍历的第一个元素总是当前子树的根节点")
    print("2. 在中序遍历中找到根节点，左边是左子树，右边是右子树")
    print("3. 递归构建左右子树（注意先构建左子树）")
    print("4. 使用哈希表优化中序遍历中根节点位置的查找")
        