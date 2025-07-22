'''
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。



示例 1：



输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
示例 2：

输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3


提示:

二叉树的节点个数的范围是 [0,1000]
-109 <= Node.val <= 109
-1000 <= targetSum <= 1000 
'''
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def pathSum(self, root: Optional[TreeNode], target_sum: int) -> int:
        """
        方法1: 前缀和 + 哈希表 (推荐)
        核心思想: 类似于数组中求子数组和等于target的问题
        如果 prefix_sum[j] - prefix_sum[i] = target_sum
        那么从节点i+1到节点j的路径和就等于target_sum
        """
        if not root:
            return 0
        
        # 前缀和计数器，记录从根到当前节点的路径上各个前缀和出现的次数
        prefix_count = {0: 1}  # 初始化：前缀和为0出现1次（空路径）
        
        def dfs(node: Optional[TreeNode], current_sum: int) -> int:
            if not node:
                return 0
            
            # 更新当前路径的前缀和
            current_sum += node.val
            
            # 查找是否存在前缀和，使得 current_sum - prefix_sum = target_sum
            # 即 prefix_sum = current_sum - target_sum
            target_prefix = current_sum - target_sum
            result = prefix_count.get(target_prefix, 0)
            
            # 将当前前缀和加入计数器
            prefix_count[current_sum] = prefix_count.get(current_sum, 0) + 1
            
            # 递归处理左右子树
            result += dfs(node.left, current_sum)
            result += dfs(node.right, current_sum)
            
            # 回溯：移除当前节点的前缀和（因为要回到父节点）
            prefix_count[current_sum] -= 1
            if prefix_count[current_sum] == 0:
                del prefix_count[current_sum]
            
            return result
        
        return dfs(root, 0)
    
    def pathSum_bruteforce(self, root: Optional[TreeNode], target_sum: int) -> int:
        """
        方法2: 暴力解法 - 对每个节点都尝试以它为起点的所有路径
        时间复杂度: O(n²)，空间复杂度: O(n)
        """
        if not root:
            return 0
        
        def count_paths_from_node(node: Optional[TreeNode], remaining: int) -> int:
            """计算从当前节点开始的路径数量"""
            if not node:
                return 0
            
            count = 0
            if node.val == remaining:
                count = 1
            
            # 继续向下搜索
            count += count_paths_from_node(node.left, remaining - node.val)
            count += count_paths_from_node(node.right, remaining - node.val)
            
            return count
        
        # 对每个节点都计算以它为起点的路径数
        result = count_paths_from_node(root, target_sum)
        result += self.pathSum_bruteforce(root.left, target_sum)
        result += self.pathSum_bruteforce(root.right, target_sum)
        
        return result
    
    def pathSum_debug(self, root: Optional[TreeNode], target_sum: int) -> int:
        """
        带调试信息的版本，帮助理解前缀和算法
        """
        if not root:
            return 0
        
        print(f"目标路径和: {target_sum}")
        prefix_count = {0: 1}
        print(f"初始前缀和计数器: {prefix_count}")
        
        def dfs_debug(node: Optional[TreeNode], current_sum: int, path: list, depth: int = 0) -> int:
            if not node:
                return 0
            
            indent = "  " * depth
            current_sum += node.val
            path.append(node.val)
            
            print(f"{indent}访问节点 {node.val}, 当前路径: {path}, 前缀和: {current_sum}")
            
            # 查找满足条件的路径
            target_prefix = current_sum - target_sum
            count = prefix_count.get(target_prefix, 0)
            
            if count > 0:
                print(f"{indent}找到 {count} 条路径! (需要前缀和: {target_prefix})")
                # 显示具体路径
                for i in range(len(path)):
                    path_sum = sum(path[i:])
                    if path_sum == target_sum:
                        print(f"{indent}  路径: {path[i:]} = {path_sum}")
            
            # 更新前缀和计数器
            prefix_count[current_sum] = prefix_count.get(current_sum, 0) + 1
            print(f"{indent}更新前缀和计数器: {prefix_count}")
            
            # 递归处理子树
            result = count
            if node.left:
                print(f"{indent}进入左子树")
                result += dfs_debug(node.left, current_sum, path[:], depth + 1)
            if node.right:
                print(f"{indent}进入右子树")
                result += dfs_debug(node.right, current_sum, path[:], depth + 1)
            
            # 回溯
            prefix_count[current_sum] -= 1
            if prefix_count[current_sum] == 0:
                del prefix_count[current_sum]
            print(f"{indent}回溯，恢复前缀和计数器: {prefix_count}")
            
            return result
        
        return dfs_debug(root, 0, [])


def create_tree_from_list(arr: list) -> Optional[TreeNode]:
    """从列表创建二叉树（层序遍历方式）"""
    if not arr or arr[0] is None:
        return None
    
    root = TreeNode(arr[0])
    queue = [root]
    i = 1
    
    while queue and i < len(arr):
        node = queue.pop(0)
        
        # 左子节点
        if i < len(arr) and arr[i] is not None:
            node.left = TreeNode(arr[i])
            queue.append(node.left)
        i += 1
        
        # 右子节点
        if i < len(arr) and arr[i] is not None:
            node.right = TreeNode(arr[i])
            queue.append(node.right)
        i += 1
    
    return root


if __name__ == '__main__':
    solution = Solution()
    
    # 测试用例1
    print("=== 测试用例1 ===")
    tree1 = [10, 5, -3, 3, 2, None, 11, 3, -2, None, 1]
    target1 = 8
    root1 = create_tree_from_list(tree1)
    
    print(f"输入: tree={tree1}, target={target1}")
    print("\n--- 前缀和算法 ---")
    result1 = solution.pathSum(root1, target1)
    print(f"结果: {result1}")
    
    print("\n--- 暴力算法验证 ---")
    result1_brute = solution.pathSum_bruteforce(root1, target1)
    print(f"暴力算法结果: {result1_brute}")
    
    print("\n--- 调试过程 ---")
    root1_debug = create_tree_from_list(tree1)  # 重新创建树用于调试
    result1_debug = solution.pathSum_debug(root1_debug, target1)
    print(f"调试结果: {result1_debug}")
    
    # 测试用例2
    print("\n=== 测试用例2 ===")
    tree2 = [5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1]
    target2 = 22
    root2 = create_tree_from_list(tree2)
    
    print(f"输入: tree={tree2}, target={target2}")
    result2 = solution.pathSum(root2, target2)
    result2_brute = solution.pathSum_bruteforce(root2, target2)
    print(f"前缀和算法: {result2}")
    print(f"暴力算法: {result2_brute}")
    
    # 算法分析
    print("\n=== 算法分析 ===")
    print("前缀和算法:")
    print("  时间复杂度: O(n) - 每个节点访问一次")
    print("  空间复杂度: O(n) - 哈希表存储前缀和 + 递归栈")
    print("\n暴力算法:")
    print("  时间复杂度: O(n²) - 对每个节点都要遍历其子树")
    print("  空间复杂度: O(n) - 递归栈")
    print("\n核心思想:")
    print("1. 前缀和: 如果 prefix[j] - prefix[i] = target，则路径[i+1...j]的和为target")
    print("2. 哈希表: 快速查找是否存在满足条件的前缀和")
    print("3. 回溯: 处理完子树后要恢复前缀和计数器的状态")
