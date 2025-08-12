from functools import cache
from typing import List

class Solution:
    """
    给你一个下标从 0 开始的整数数组 nums 和一个整数 target 。
    返回和为 target 的 nums 子序列中，子序列 长度的最大值 。如果不存在和为 target 的子序列，返回 -1 。
    子序列 指的是从原数组中删除一些或者不删除任何元素后，剩余元素保持原来的顺序构成的数组。
    """
    def lengthOfLongestSubsequence(self, nums: List[int], target: int) -> int:
        """
        使用自顶向下的动态规划（记忆化搜索）解决。

        定义 dfs(i, t) 为考虑前 i+1 个数（从 nums[0] 到 nums[i]），
        组成和为 t 的子序列的最大长度。

        状态转移方程：
        对于第 i 个数 nums[i]，我们有两个选择：
        1. 不选 nums[i]：最大长度为 dfs(i - 1, t)
        2. 选 nums[i]：最大长度为 1 + dfs(i - 1, t - nums[i])

        我们取两者的最大值。

        Args:
            nums: 整数数组
            target: 目标和

        Returns:
            最长子序列的长度，如果不存在则返回 -1
        """
        n = len(nums)
        
        # 使用一个无法达到的值来表示“不可能”的情况
        # 因为 nums 的长度最多为 1000，所以最长子序列长度不会超过 1000
        # -1001 是一个安全的“负无穷”值
        NEGINF = -1001

        @cache
        def dfs(i: int, t: int) -> int:
            # Base Case 1: 目标和达成
            if t == 0:
                return 0
            
            # Base Case 2: 数组越界或目标和为负，说明此路不通
            if i < 0 or t < 0:
                return NEGINF

            # 不选 nums[i]
            res_not_chosen = dfs(i - 1, t)
            
            # 选 nums[i]
            res_chosen = 1 + dfs(i - 1, t - nums[i])
            
            return max(res_not_chosen, res_chosen)

        # 从最后一个元素开始，目标和为 target
        ans = dfs(n - 1, target)

        # 如果结果为负数，说明没有找到任何符合条件的子序列
        return ans if ans >= 0 else -1

    def lengthOfLongestSubsequence2(self, nums: List[int], target: int) -> int:
        '''
        使用自底向上的动态规划解决。
        定义 f[i][j] 为考虑前 i+1 个数（从 nums[0] 到 nums[i]），
        '''
        dp = [[0] * (target + 1) for _ in range(len(nums))]

        for i in range(len(nums)):
            for j in range(target + 1):
                if j == 0:
                    dp[i][j] = 0
                elif nums[i] > j:
                    dp[i][j] = dp[i - 1][j]
                else:
                    dp[i][j] = max(dp[i - 1][j], 1 + dp[i - 1][j - nums[i]])
        return dp[-1][-1] if dp[-1][-1] > 0 else -1
        
# 示例测试
if __name__ == '__main__':
    sol = Solution()
    
    # 示例 1
    nums1 = [1, 2, 3, 4, 5]
    target1 = 9
    print(f"nums = {nums1}, target = {target1}, Output: {sol.lengthOfLongestSubsequence(nums1, target1)}") # 应该输出 3

    # 示例 2
    nums2 = [4, 1, 3, 2, 1, 5]
    target2 = 7
    print(f"nums = {nums2}, target = {target2}, Output: {sol.lengthOfLongestSubsequence(nums2, target2)}") # 应该输出 4

    # 示例 3
    nums3 = [1, 1, 5, 4, 5]
    target3 = 3
    print(f"nums = {nums3}, target = {target3}, Output: {sol.lengthOfLongestSubsequence(nums3, target3)}") # 应该输出 -1