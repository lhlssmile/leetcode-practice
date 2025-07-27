'''
给你一个整数数组 nums，其长度可以被 3 整除。

你需要通过多次操作将数组清空。在每一步操作中，你可以从数组中选择任意三个元素，计算它们的 中位数 ，并将这三个元素从数组中移除。

奇数长度数组的 中位数 定义为数组按非递减顺序排序后位于中间的元素。

返回通过所有操作得到的 中位数之和的最大值 。

 

示例 1：

输入： nums = [2,1,3,2,1,3]

输出： 5

解释：

第一步，选择下标为 2、4 和 5 的元素，它们的中位数是 3。移除这些元素后，nums 变为 [2, 1, 2]。
第二步，选择下标为 0、1 和 2 的元素，它们的中位数是 2。移除这些元素后，nums 变为空数组。
因此，中位数之和为 3 + 2 = 5。

示例 2：

输入： nums = [1,1,10,10,10,10]

输出： 20

解释：

第一步，选择下标为 0、2 和 3 的元素，它们的中位数是 10。移除这些元素后，nums 变为 [1, 10, 10]。
第二步，选择下标为 0、1 和 2 的元素，它们的中位数是 10。移除这些元素后，nums 变为空数组。
因此，中位数之和为 10 + 10 = 20。

 

提示：

1 <= nums.length <= 5 * 105
nums.length % 3 == 0
1 <= nums[i] <= 109©leetcode
'''
from typing import List


class Solution:
    def maximumMedianSum(self, nums: List[int]) -> int:
        """
        贪心算法解决最大中位数和问题
        
        核心思路：
        1. 要让中位数和最大，就要让尽可能大的数成为中位数
        2. 排序后，贪心选择：每次选择当前最大的三个数，让中间的作为中位数
        3. 更精确的贪心策略：排序后，从第2大的数开始，每隔2个数取一个作为中位数
        
        证明：
        - 排序后：a1 >= a2 >= a3 >= ... >= an
        - 我们需要选择n//3个中位数
        - 最优策略：选择a2, a5, a8, ..., a(3k-1)作为中位数
        - 这样可以保证每个中位数都是某个三元组中的最大可能中位数
        """
        # 降序排序
        nums.sort(reverse=True)
        n = len(nums)
        
        # 贪心策略：从索引1开始，每隔3个位置取一个数作为中位数
        # 即选择索引1, 4, 7, 10, ...的数作为中位数
        median_sum = 0
        
        # 从索引1开始，步长为3，这些位置的数将作为中位数
        for i in range(1, n, 3):
            median_sum += nums[i]
        
        return median_sum
    def findSum (self, nums: List[int]) -> int:
        nums.sort()
        n = len(nums)
        k = n // 3
        res = 0
        idx = n - 2  # 每组的中位数是倒数第2、5、8...个
        for _ in range(k):
            res += nums[idx]
            idx -= 2
        return res
    def maximumMedianSum_detailed(self, nums: List[int]) -> int:
        """
        详细版本：展示具体的三元组选择过程
        """
        nums.sort(reverse=True)
        n = len(nums)
        result = []
        median_sum = 0
        
        # 每次选择三个数：nums[i], nums[i+1], nums[i+2]
        # 其中 nums[i+1] 是中位数
        for i in range(0, n, 2):
            if i + 1 < n:
                # 选择三个数：最大值、中位数、最小值
                if i + 2 < n:
                    triplet = (nums[i], nums[i+1], nums[i+2])
                else:
                    # 最后可能只剩两个数，需要找第三个
                    triplet = (nums[i], nums[i+1], nums[-1])
                
                median = nums[i+1]
                median_sum += median
                result.append((triplet, median))
        
        return median_sum


# 测试用例
def test_maximumMedianSum():
    solution = Solution()
    
    # 测试用例1 - 详细分析
    nums1 = [2, 1, 3, 2, 1, 3]
    print(f"测试用例1分析: nums = {nums1}")
    sorted_nums1 = sorted(nums1, reverse=True)
    print(f"排序后: {sorted_nums1}")
    n = len(nums1)
    print(f"数组长度: {n}, n//3 = {n//3}")
    print(f"中位数索引范围: [{n//3}, {2*n//3})")
    print(f"选择的中位数: {sorted_nums1[n//3:2*n//3]}")
    print(f"中位数和: {sum(sorted_nums1[n//3:2*n//3])}")
    
    # 手动验证最优解
    print("\n手动验证最优解:")
    print("方案1: (3,3,2) -> 中位数3, (2,1,1) -> 中位数1, 总和=4")
    print("方案2: (3,2,1) -> 中位数2, (3,2,1) -> 中位数2, 总和=4")
    print("方案3: (3,3,1) -> 中位数3, (2,2,1) -> 中位数2, 总和=5")
    print("最优解应该是5")
    
    result1 = solution.findSum(nums1)
    print(f"\n算法结果: {result1} (期望: 5)")
    print()
    
    # 测试用例2
    nums2 = [1, 1, 10, 10, 10, 10]
    result2 = solution.findSum(nums2)
    print(f"测试用例2: nums = {nums2}")
    print(f"结果: {result2} (期望: 20)")
    print(f"排序后: {sorted(nums2, reverse=True)}")
    print(f"选择的中位数: {sorted(nums2, reverse=True)[1::2]}")
    print()
    
    # 额外测试用例
    nums3 = [1, 2, 3, 4, 5, 6]
    result3 = solution.findSum(nums3)
    print(f"测试用例3: nums = {nums3}")
    print(f"结果: {result3}")
    print(f"排序后: {sorted(nums3, reverse=True)}")
    print(f"选择的中位数: {sorted(nums3, reverse=True)[1::2]}")
    print()
    
    # 验证贪心策略的正确性
    print("=== 贪心策略验证 ===")
    nums4 = [6, 5, 4, 3, 2, 1]  # 已排序
    print(f"数组: {nums4}")
    print("最优选择:")
    print("  第一组: (6, 5, 4) -> 中位数: 5")
    print("  第二组: (3, 2, 1) -> 中位数: 2")
    print("  总和: 5 + 2 = 7")
    print(f"算法结果: {solution.maximumMedianSum(nums4.copy())}")


if __name__ == "__main__":
    test_maximumMedianSum()
