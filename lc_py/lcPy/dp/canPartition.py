'''
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。



示例 1：

输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
示例 2：

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。


提示：

1 <= nums.length <= 200
1 <= nums[i] <= 100
'''
from functools import cache
from typing import List

import pytest


class Solution:
    def canPartition(self, nums: List[int]) -> bool:

        if len(nums) <= 1:
            return False
        num_sum = sum(x for x in nums)

        if num_sum % 2 != 0:
            return False

        target_sum = num_sum // 2

        @cache
        def dfs(idx: int, curr_sum: int):
            if curr_sum == target_sum:
                return True
            if idx >= len(nums) or curr_sum > target_sum:
                return False
            # 选当前数字 或是不选?
            result = (dfs(idx + 1, curr_sum + nums[idx]) or
                      dfs(idx + 1, curr_sum))
            return result
        return dfs(0, 0)


@pytest.mark.parametrize("nums, expected", [
    ([1, 5, 11, 5], True),  # 示例 1：可以分割成 [1, 5, 5] 和 [11]
    ([1, 2, 3, 5], False),  # 示例 2：无法分割成和相等的子集
    ([1], False),  # 边界用例：单个元素，无法分割
    ([2, 2], True),  # 简单用例：可以分割成 [2] 和 [2]
    ([100, 100], True),  # 大数字用例：可以分割
    ([1, 2, 5], False),  # 无法分割的非偶数和
    ([], False),  # 空数组
    ([1, 1, 1, 1], True),  # 多个小数字，可以分割
    ([100, 1, 1, 1], False),  # 大数字和小数字混合，无法分割
])
def test_can_partition(nums, expected):
    solution = Solution()
    result = solution.canPartition(nums)
    assert result == expected, f"Failed for input {nums}: expected {expected}, got {result}"


if __name__ == "__main__":
    s = Solution()
    nums1 = [1, 5, 11, 5]
    s.canPartition([1, 5, 11, 5])