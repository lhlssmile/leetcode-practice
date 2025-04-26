from typing import List
class MaxProduct:
    def maxProduct(self,nums: List[int]) -> int:
        n = len(nums)
        # 初始化动态规划数组
        dp_max = [0] * n
        dp_min = [0] * n
        # 设置初始值
        dp_max[0] = dp_min[0] = nums[0]
        max_product = nums[0]
        
        # 遍历数组，计算每个位置的最大和最小乘积
        for i in range(1, n):
            # 计算当前位置的最大乘积
            dp_max[i] = max(nums[i], dp_max[i-1] * nums[i], dp_min[i-1] * nums[i])
            # 计算当前位置的最小乘积
            dp_min[i] = min(nums[i], dp_max[i-1] * nums[i], dp_min[i-1] * nums[i])
            # 更新全局最大乘积
            max_product = max(max_product, dp_max[i])
            
        return max_product