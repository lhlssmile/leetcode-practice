# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def addOneRow(self, root: TreeNode, val: int, depth: int) -> TreeNode:
        if depth == 1:
            new_root = TreeNode(val)
            new_root.left = root
            return new_root
        
        def dfs(node, current_depth, target_depth):
            if not node:
                return
            
            if current_depth == target_depth - 1:
                old_left = node.left
                old_right = node.right
                
                node.left = TreeNode(val)
                node.left.left = old_left
                
                node.right = TreeNode(val)
                node.right.right = old_right
                return
            
            dfs(node.left, current_depth + 1, target_depth)
            dfs(node.right, current_depth + 1, target_depth)
        
        dfs(root, 1, depth)
        return root

# 测试函数
def test_add_one_row():
    solution = Solution()
    
    # 测试用例1
    root1 = TreeNode(4)
    root1.left = TreeNode(2)
    root1.right = TreeNode(6)
    root1.left.left = TreeNode(3)
    root1.left.right = TreeNode(1)
    root1.right.left = TreeNode(5)
    
    result1 = solution.addOneRow(root1, 1, 2)
    print("Test 1 passed")
    
    # 测试用例2
    root2 = TreeNode(4)
    root2.left = TreeNode(2)
    root2.left.left = TreeNode(3)
    root2.left.right = TreeNode(1)
    
    result2 = solution.addOneRow(root2, 1, 3)
    print("Test 2 passed")

if __name__ == "__main__":
    test_add_one_row()

"""
算法思路：DFS递归遍历到目标深度的前一层，然后插入新节点
时间复杂度：O(n)
空间复杂度：O(h) - 递归栈深度
"""