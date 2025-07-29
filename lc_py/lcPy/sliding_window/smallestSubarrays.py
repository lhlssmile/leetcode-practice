'''
给你一个长度为 n 下标从 0 开始的数组 nums ，数组中所有数字均为非负整数。对于 0 到 n - 1 之间的每一个下标 i ，你需要找出 nums 中一个 最小 非空子数组，它的起始位置为 i （包含这个位置），同时有 最大 的 按位或运算值 。

换言之，令 Bij 表示子数组 nums[i...j] 的按位或运算的结果，你需要找到一个起始位置为 i 的最小子数组，这个子数组的按位或运算的结果等于 max(Bik) ，其中 i <= k <= n - 1 。
一个数组的按位或运算值是这个数组里所有数字按位或运算的结果。

请你返回一个大小为 n 的整数数组 answer，其中 answer[i]是开始位置为 i ，按位或运算结果最大，且 最短 子数组的长度。

子数组 是数组里一段连续非空元素组成的序列。



示例 1：

输入：nums = [1,0,2,1,3]
输出：[3,3,2,2,1]
解释：
任何位置开始，最大按位或运算的结果都是 3 。
- 下标 0 处，能得到结果 3 的最短子数组是 [1,0,2] 。
- 下标 1 处，能得到结果 3 的最短子数组是 [0,2,1] 。
- 下标 2 处，能得到结果 3 的最短子数组是 [2,1] 。
- 下标 3 处，能得到结果 3 的最短子数组是 [1,3] 。
- 下标 4 处，能得到结果 3 的最短子数组是 [3] 。
所以我们返回 [3,3,2,2,1] 。
示例 2：

输入：nums = [1,2]
输出：[2,1]
解释：
下标 0 处，能得到最大按位或运算值的最短子数组长度为 2 。
下标 1 处，能得到最大按位或运算值的最短子数组长度为 1 。
所以我们返回 [2,1] 。


提示：

n == nums.length
1 <= n <= 105
0 <= nums[i] <= 109
'''
from functools import reduce
from operator import or_
from typing import List


class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [0] * n
        ans[-1] = 1
        if n == 1:
            return ans

        # 保证栈中至少有两个数，方便判断窗口右端点是否要缩小
        nums[-1] |= nums[-2]
        left_or, right, bottom = 0, n - 1, n - 2
        for left in range(n - 2, -1, -1):
            left_or |= nums[left]
            # 子数组 [left,right] 的或值 = 子数组 [left,right-1] 的或值，说明窗口右端点可以缩小
            while right > left and (left_or | nums[right]) == (left_or | nums[right - 1]):
                right -= 1
                # 栈中只剩一个数
                if bottom >= right:
                    # 重新构建一个栈，栈底为 left，栈顶为 right
                    for i in range(left + 1, right + 1):
                        nums[i] |= nums[i - 1]
                    bottom = left
                    left_or = 0
            ans[left] = right - left + 1
        return ans


if __name__ == '__main__':
    s = Solution()
    print(s.smallestSubarrays([1, 0, 2, 1, 3]))
