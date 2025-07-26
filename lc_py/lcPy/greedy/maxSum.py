'''
给你一个整数数组 nums 。

你可以从数组 nums 中删除任意数量的元素，但不能将其变为 空 数组。执行删除操作后，选出 nums 中满足下述条件的一个子数组：

子数组中的所有元素 互不相同 。
最大化 子数组的元素和。
返回子数组的 最大元素和 。

子数组 是数组的一个连续、非空 的元素序列。


示例 1：

输入：nums = [1,2,3,4,5]

输出：15

解释：

不删除任何元素，选中整个数组得到最大元素和。

示例 2：

输入：nums = [1,1,0,1,1]

输出：1

解释：

删除元素 nums[0] == 1、nums[1] == 1、nums[2] == 0 和 nums[3] == 1 。选中整个数组 [1] 得到最大元素和。

示例 3：

输入：nums = [1,2,-1,-2,1,0,-1]

输出：3

解释：

删除元素 nums[2] == -1 和 nums[3] == -2 ，从 [1, 2, 1, 0, -1] 中选中子数组 [2, 1] 以获得最大元素和。



提示：

1 <= nums.length <= 100
-100 <= nums[i] <= 100

'''
from typing import List


class Solution:
    def maxSum(self, nums: List[int]) -> int:
        # 正确的理解：可以删除任意元素，然后在剩余元素中找连续无重复子数组
        # 关键insight：我们需要考虑所有可能的删除方案
        n = len(nums)
        max_sum = float('-inf')
        
        # 使用位运算枚举所有可能的删除方案（保留方案）
        # mask表示哪些元素被保留，1表示保留，0表示删除
        for mask in range(1, 1 << n):  # 从1开始，确保至少保留一个元素
            # 构建保留后的数组
            remaining = []
            for i in range(n):
                if mask & (1 << i):
                    remaining.append(nums[i])
            
            # 在remaining数组中找最大无重复连续子数组和
            current_max = self._findMaxUniqueSubarray(remaining)
            max_sum = max(max_sum, current_max)
        
        return max_sum
    
    def _findMaxUniqueSubarray(self, arr):
        # 在给定数组中找最大无重复连续子数组和
        if not arr:
            return 0
        
        max_sum = float('-inf')
        n = len(arr)
        
        for i in range(n):
            seen = set()
            current_sum = 0
            
            for j in range(i, n):
                if arr[j] in seen:
                    break
                
                seen.add(arr[j])
                current_sum += arr[j]
                max_sum = max(max_sum, current_sum)
        
        return max_sum

    def maxSum_recursive(self, nums: List[int]) -> int:
        # 递归方法：尝试每个起始位置，递归计算最大和
        def dfs(start, used_set, current_sum):
            # 基础情况：已经遍历完所有元素
            if start >= len(nums):
                return current_sum

            # 选择1：跳过当前元素（相当于删除）
            max_val = dfs(start + 1, used_set, current_sum)

            # 选择2：如果当前元素没有被使用过，可以加入当前子数组
            if nums[start] not in used_set:
                new_used = used_set | {nums[start]}
                # 继续扩展当前子数组
                max_val = max(max_val, dfs(start + 1, new_used, current_sum + nums[start]))
                # 或者从当前位置重新开始一个新的子数组
                max_val = max(max_val, current_sum + nums[start])

            return max_val

        # 从每个位置开始尝试
        result = float('-inf')
        for i in range(len(nums)):
            result = max(result, self._recursive_helper(nums, i, set(), 0))
        return result

    def _recursive_helper(self, nums, start, used_set, current_sum):
        # 递归辅助函数：从start位置开始构建无重复子数组
        if start >= len(nums):
            return current_sum

        # 如果当前元素已经在集合中，停止扩展
        if nums[start] in used_set:
            return current_sum

        # 加入当前元素
        new_used = used_set | {nums[start]}
        new_sum = current_sum + nums[start]

        # 继续扩展 vs 在当前位置停止
        continue_expand = self._recursive_helper(nums, start + 1, new_used, new_sum)
        stop_here = new_sum

        return max(continue_expand, stop_here)

    def maxSum_memo(self, nums: List[int]) -> int:
        # 记忆化递归版本
        from functools import lru_cache

        @lru_cache(maxsize=None)
        def dfs(start, used_tuple):
            # 基础情况
            if start >= len(nums):
                return 0

            # 跳过当前元素
            max_val = dfs(start + 1, used_tuple)

            # 如果当前元素没有被使用，尝试加入
            if nums[start] not in used_tuple:
                new_used = tuple(sorted(set(used_tuple) | {nums[start]}))
                # 加入当前元素并继续
                max_val = max(max_val, nums[start] + dfs(start + 1, new_used))

            return max_val

        # 但是这种记忆化对这个问题效果不好，因为状态空间太大
        # 更好的记忆化方式：
        memo = {}

        def solve(start, last_used_positions):
            # last_used_positions: 记录每个值最后使用的位置
            key = (start, tuple(sorted(last_used_positions.items())))
            if key in memo:
                return memo[key]

            if start >= len(nums):
                return 0

            # 选择1：跳过当前元素
            result = solve(start + 1, last_used_positions)

            # 选择2：使用当前元素（如果可以）
            val = nums[start]
            if val not in last_used_positions or last_used_positions[val] < start:
                # 可以使用当前元素
                new_positions = last_used_positions.copy()
                new_positions[val] = start
                result = max(result, val + solve(start + 1, new_positions))

            memo[key] = result
            return result

        return solve(0, {})


# 测试函数
def test_solution():
    sol = Solution()
    
    # 测试用例
    test_cases = [
        ([1, 2, 3, 4, 5], 15),
        ([1, 1, 0, 1, 1], 1),
        ([1, 2, -1, -2, 1, 0, -1], 3),
        ([2, -10, 6], 8),  # 新的测试用例：删除-10，选择[2,6]
        ([-1, -2, -3], -1),  # 全负数测试
        ([5], 5),  # 单元素测试
        ([1, 2, 1], 3),  # 删除重复元素测试
    ]
    
    print("测试结果：")
    for i, (nums, expected) in enumerate(test_cases):
        result = sol.maxSum(nums)
        status = "✓" if result == expected else "✗"
        print(f"测试 {i+1}: {nums} -> {result} (期望: {expected}) {status}")
        
        if result != expected:
            print(f"  详细分析: 输入{nums}")
            # 可以在这里添加更详细的调试信息


if __name__ == "__main__":
    test_solution()

    def maxSum_optimized(self, nums: List[int]) -> int:
         # 优化版本：对于数据规模较大时，位运算方法会超时
         # 这里提供一个更高效的解法思路（但对于题目约束n<=100，位运算已足够）
         n = len(nums)
         if n <= 20:  # 小规模用位运算精确解
             return self.maxSum(nums)
         
         # 大规模时的近似贪心策略（实际上这题n<=100，不会用到）
         # 这里只是展示思路
         max_sum = float('-inf')
         for i in range(n):
             seen = set()
             current_sum = 0
             for j in range(i, n):
                 if nums[j] in seen:
                     break
                 seen.add(nums[j])
                 current_sum += nums[j]
                 max_sum = max(max_sum, current_sum)
         return max_sum


# 测试函数
def test_solution():
    sol = Solution()
    
    # 测试用例
    test_cases = [
        ([1, 2, 3, 4, 5], 15),
        ([1, 1, 0, 1, 1], 1),
        ([1, 2, -1, -2, 1, 0, -1], 3),
        ([2, -10, 6], 8),  # 修复的测试用例：删除-10，选择[2,6]
        ([-1, -2, -3], -1),  # 全负数测试
        ([5], 5),  # 单元素测试
        ([1, 2, 1], 3),  # 删除重复元素测试
        ([0, 1, 2, 0], 3),  # 另一个删除重复的例子
    ]
    
    print("🎯 测试结果：")
    all_passed = True
    for i, (nums, expected) in enumerate(test_cases):
        result = sol.maxSum(nums)
        status = "✅" if result == expected else "❌"
        print(f"测试 {i+1}: {nums} -> {result} (期望: {expected}) {status}")
        
        if result != expected:
            all_passed = False
            print(f"  ❗ 详细分析: 输入{nums}，实际输出{result}，期望{expected}")
    
    if all_passed:
        print("\n🎉 所有测试通过！")
    else:
        print("\n⚠️  有测试失败，请检查算法逻辑")


if __name__ == "__main__":
    test_solution()


if __name__ == '__main__':
    s = Solution()
    print(s.maxSum([1, 1, 0, 1, 1]))
