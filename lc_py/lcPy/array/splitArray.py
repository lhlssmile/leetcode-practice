'''
给你一个整数数组 nums。

根据以下规则将 nums 分割成两个数组 A 和 B：

nums 中位于 质数 下标的元素必须放入数组 A。
所有其他元素必须放入数组 B。
返回两个数组和的 绝对 差值：|sum(A) - sum(B)|。

质数 是一个大于 1 的自然数，它只有两个因子，1和它本身。

注意：空数组的和为 0。

 

示例 1:

输入: nums = [2,3,4]

输出: 1

解释:

数组中唯一的质数下标是 2，所以 nums[2] = 4 被放入数组 A。
其余元素 nums[0] = 2 和 nums[1] = 3 被放入数组 B。
sum(A) = 4，sum(B) = 2 + 3 = 5。
绝对差值是 |4 - 5| = 1。
示例 2:

输入: nums = [-1,5,7,0]

输出: 3

解释:

数组中的质数下标是 2 和 3，所以 nums[2] = 7 和 nums[3] = 0 被放入数组 A。
其余元素 nums[0] = -1 和 nums[1] = 5 被放入数组 B。
sum(A) = 7 + 0 = 7，sum(B) = -1 + 5 = 4。
绝对差值是 |7 - 4| = 3。
 

提示:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
'''
from typing import List


class Solution:
    def splitArray(self, nums: List[int]) -> int:
        """方法1: 直接计算 - 最优解法"""
        def is_prime(n):
            if n < 2:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True
        
        sum_a = sum_b = 0
        for i in range(len(nums)):
            if is_prime(i):
                sum_a += nums[i]
            else:
                sum_b += nums[i]
        
        return abs(sum_a - sum_b)
    
    def splitArrayVerbose(self, nums: List[int]) -> int:
        """方法2: 详细版本 - 便于理解"""
        def is_prime(n):
            if n < 2:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True
        
        array_a = []
        array_b = []
        
        for i in range(len(nums)):
            if is_prime(i):
                array_a.append(nums[i])
            else:
                array_b.append(nums[i])
        
        sum_a = sum(array_a)
        sum_b = sum(array_b)
        
        return abs(sum_a - sum_b)
    
    def splitArrayOptimized(self, nums: List[int]) -> int:
        """方法3: 预计算质数 - 适合多次调用"""
        n = len(nums)
        
        # 埃拉托斯特尼筛法预计算质数
        is_prime = [True] * n
        if n > 0:
            is_prime[0] = False
        if n > 1:
            is_prime[1] = False
        
        for i in range(2, int(n**0.5) + 1):
            if is_prime[i]:
                for j in range(i*i, n, i):
                    is_prime[j] = False
        
        sum_a = sum_b = 0
        for i in range(n):
            if is_prime[i]:
                sum_a += nums[i]
            else:
                sum_b += nums[i]
        
        return abs(sum_a - sum_b)


if __name__ == "__main__":
    solution = Solution()
    
    print("=== 数组分割问题 ===")
    
    # 测试用例
    test_cases = [
        [2, 3, 4],           # 示例1: 输出1
        [-1, 5, 7, 0],       # 示例2: 输出3
        [1],                 # 边界: 只有一个元素
        [1, 2],              # 边界: 两个元素
        [1, 2, 3, 4, 5],     # 更多元素
    ]
    
    for i, nums in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}: {nums}")
        
        # 方法1: 直接计算
        result1 = solution.splitArray(nums)
        print(f"方法1 (直接计算): {result1}")
        
        # 方法2: 详细版本
        result2 = solution.splitArrayVerbose(nums)
        print(f"方法2 (详细版本): {result2}")
        
        # 方法3: 预计算质数
        result3 = solution.splitArrayOptimized(nums)
        print(f"方法3 (预计算质数): {result3}")
        
        # 详细分析过程
        print("分析过程:")
        array_a = []
        array_b = []
        for j in range(len(nums)):
            if j >= 2:  # 简单质数判断用于展示
                is_prime = True
                for k in range(2, int(j**0.5) + 1):
                    if j % k == 0:
                        is_prime = False
                        break
            else:
                is_prime = (j == 2)
            
            if is_prime:
                array_a.append(f"nums[{j}]={nums[j]}")
            else:
                array_b.append(f"nums[{j}]={nums[j]}")
        
        print(f"  质数下标(A): {', '.join(array_a) if array_a else '空'}")
        print(f"  非质数下标(B): {', '.join(array_b) if array_b else '空'}")
    
    print("\n=== 核心思路分析 ===")
    print("1. 题目要求: 根据下标是否为质数分割数组")
    print("2. 质数定义: 大于1且只有1和自身两个因子的自然数")
    print("3. 分割规则:")
    print("   - 质数下标的元素 → 数组A")
    print("   - 非质数下标的元素 → 数组B")
    print("4. 返回: |sum(A) - sum(B)|")
    
    print("\n=== 质数判断优化 ===")
    print("基础版本: O(n) 判断每个数")
    print("优化版本: O(√n) 只检查到平方根")
    print("筛法版本: O(n log log n) 预计算所有质数")
    
    print("\n=== 示例详解: [2,3,4] ===")
    print("下标分析:")
    print("  - 下标0: 非质数 → nums[0]=2 放入B")
    print("  - 下标1: 非质数 → nums[1]=3 放入B")
    print("  - 下标2: 质数 → nums[2]=4 放入A")
    print("结果: sum(A)=4, sum(B)=2+3=5, |4-5|=1")
    
    print("\n=== 三种方法对比 ===")
    print("直接计算:")
    print("  - 时间复杂度: O(n√n)")
    print("  - 空间复杂度: O(1)")
    print("  - 优点: 简洁，空间最优")
    
    print("\n详细版本:")
    print("  - 时间复杂度: O(n√n)")
    print("  - 空间复杂度: O(n)")
    print("  - 优点: 逻辑清晰，便于调试")
    
    print("\n预计算质数:")
    print("  - 时间复杂度: O(n log log n)")
    print("  - 空间复杂度: O(n)")
    print("  - 优点: 适合多次调用，大数据量优势明显")
    
    print("\n=== 关键要点 ===")
    print("- 注意是下标的质数性，不是元素值")
    print("- 0和1都不是质数")
    print("- 2是最小的质数")
    print("- 空数组的和为0")
    print("- 可以原地计算，无需真正分割数组")