from typing import Optional, List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None

        left = self.invertTree(root.left)
        right = self.invertTree(root.right)

        root.left = right
        root.right = left
        return root

    def diameterOfBinaryTree(self,root: Optional[TreeNode]) -> int:
        return 0

    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        def helper(left, right):
            if left > right:
                return None
            mid = (left + right) // 2
            node = TreeNode(nums[mid])
            node.left = helper(left, mid - 1)
            node.right = helper(mid + 1, right)
            return node

        return helper(0, len(nums) - 1)



if __name__ == '__main__':
    nums = [-10, -3, 0, 5, 9]
    s = Solution()
    print(s.sortedArrayToBST(nums))

