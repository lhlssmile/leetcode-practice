'''
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。



示例 1：

输入：root = [1,2,3,null,5,null,4]

输出：[1,3,4]

解释：



示例 2：

输入：root = [1,2,3,4,null,null,null,5]

输出：[1,3,4,5]

解释：



示例 3：

输入：root = [1,null,3]

输出：[1,3]

示例 4：

输入：root = []

输出：[]



提示:

二叉树的节点个数的范围是 [0,100]
-100 <= Node.val <= 100
'''
from collections import deque
from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val  # 修正为标准的val属性
        self.left = left
        self.right = right


class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        # DFS
        if not root:
            return []

        result = []

        def dfs(node, depth):
            if not node:
                return

            # 如果是第一次访问这一层，记录右侧节点
            if depth == len(result):
                result.append(node.val)

            # 先访问右子树，再访问左子树
            dfs(node.right, depth + 1)
            dfs(node.left, depth + 1)

        dfs(root, 0)
        return result

    def rightSideViewBFS(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []

        queue = deque([root])
        res = []
        while queue:
            level_size = len(queue)
            for i in range(level_size):
                node = queue.popleft()

                if i == level_size - 1:
                    res.append(node.val)  # 修正为标准的val属性
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        return res


def create_tree_from_list(values):
    """从列表创建二叉树，支持None值"""
    if not values:
        return None
    
    root = TreeNode(values[0])
    queue = deque([root])
    i = 1
    
    while queue and i < len(values):
        node = queue.popleft()
        
        # 添加左子节点
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1
        
        # 添加右子节点
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1
    
    return root

def print_tree_level_order(root):
    """层序打印树结构，便于调试"""
    if not root:
        print("空树")
        return
    
    queue = deque([root])
    level = 0
    
    while queue:
        level_size = len(queue)
        print(f"第{level}层: ", end="")
        
        for i in range(level_size):
            node = queue.popleft()
            print(f"{node.val}", end="")
            
            if i < level_size - 1:
                print(" -> ", end="")
            
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        
        print()  # 换行
        level += 1

class SolutionDebug(Solution):
    def rightSideViewBFS_Debug(self, root: Optional[TreeNode]) -> List[int]:
        """带调试信息的BFS版本"""
        if not root:
            print("输入为空树")
            return []

        queue = deque([root])
        res = []
        level = 0
        
        print("=== BFS调试过程 ===")
        
        while queue:
            level_size = len(queue)
            print(f"\n第{level}层，队列中有{level_size}个节点:")
            
            # 显示当前层的所有节点
            current_level_nodes = []
            for node in queue:
                current_level_nodes.append(node.val)
            print(f"当前层节点值: {current_level_nodes}")
            
            for i in range(level_size):
                node = queue.popleft()
                print(f"  处理节点{node.val} (第{i+1}/{level_size}个)")
                
                # 如果是这一层的最后一个节点，加入结果
                if i == level_size - 1:
                    res.append(node.val)
                    print(f"    -> 这是第{level}层最右边的节点，加入结果: {node.val}")
                
                # 添加子节点到队列
                if node.left:
                    queue.append(node.left)
                    print(f"    -> 左子节点{node.left.val}加入队列")
                if node.right:
                    queue.append(node.right)
                    print(f"    -> 右子节点{node.right.val}加入队列")
            
            print(f"第{level}层处理完毕，当前结果: {res}")
            level += 1
        
        print(f"\n=== 最终结果: {res} ===")
        return res

if __name__ == '__main__':
    s = SolutionDebug()
    
    # 测试用例1: [1,2,3,null,5,null,4]
    print("测试用例1: [1,2,3,null,5,null,4]")
    tree1 = create_tree_from_list([1, 2, 3, None, 5, None, 4])
    print("\n树结构:")
    print_tree_level_order(tree1)
    
    print("\nDFS结果:", s.rightSideView(tree1))
    print("\nBFS调试过程:")
    bfs_result = s.rightSideViewBFS_Debug(tree1)
    
    print("\n" + "="*50)
    
    # 测试用例2: [1,2,3,4,null,null,null,5]
    print("\n测试用例2: [1,2,3,4,null,null,null,5]")
    tree2 = create_tree_from_list([1, 2, 3, 4, None, None, None, 5])
    print("\n树结构:")
    print_tree_level_order(tree2)
    
    print("\nDFS结果:", s.rightSideView(tree2))
    print("\nBFS调试过程:")
    bfs_result2 = s.rightSideViewBFS_Debug(tree2)
    