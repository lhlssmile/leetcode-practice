class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def lcaDeepestLeaves(self, root: TreeNode) -> TreeNode:
        def helper(node: TreeNode) -> tuple[int, TreeNode]:
            if not node:
                return (-1, None)
            # 如果是叶子节点
            if not node.left and not node.right:
                return (0, node)

            # 递归处理左右子树
            left_depth, left_lca = helper(node.left)
            right_depth, right_lca = helper(node.right)

            # 如果左右深度相等，当前节点是最深叶子节点的LCA
            if left_depth == right_depth:
                return (left_depth + 1, node)
            # 左子树更深，返回左子树的结果
            elif left_depth > right_depth:
                return (left_depth + 1, left_lca)
            # 右子树更深，返回右子树的结果
            else:
                return (right_depth + 1, right_lca)

        depth, lca = helper(root)
        return lca

# 测试代码
def create_tree(values):
    if not values or values[0] == -1:
        return None
    root = TreeNode(values[0])
    queue = [root]
    index = 1
    while queue and index < len(values):
        current = queue.pop(0)
        if index < len(values) and values[index] != -1:
            current.left = TreeNode(values[index])
            queue.append(current.left)
        index += 1
        if index < len(values) and values[index] != -1:
            current.right = TreeNode(values[index])
            queue.append(current.right)
        index += 1
    return root

values = [3,5,1,6,2,0,8,None,None,7,4]
tree = create_tree(values)
solution = Solution()
result = solution.lcaDeepestLeaves(tree)
print(result.val)  # 输出结果节点的值