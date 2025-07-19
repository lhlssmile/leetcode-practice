import collections
import heapq
from typing import List


class Solution:
    # 方法1：小根堆（推荐）
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        """
        使用小根堆维护前k个高频元素
        时间复杂度：O(n log k)
        空间复杂度：O(n + k)
        """
        # 统计频率
        cnt = collections.Counter(nums)
        
        # 使用小根堆维护前k个高频元素
        # 堆中存储 (频率, 元素值)
        heap = []
        
        for num, freq in cnt.items():
            heapq.heappush(heap, (freq, num))
            if len(heap) > k:
                heapq.heappop(heap)  # 弹出频率最小的
        
        # 提取结果
        return [num for freq, num in heap]
    
    # 方法2：大根堆
    def topKFrequent2(self, nums: List[int], k: int) -> List[int]:
        """
        使用大根堆，取前k个元素
        时间复杂度：O(n log n)
        空间复杂度：O(n)
        """
        cnt = collections.Counter(nums)
        
        # Python的heapq是小根堆，使用负数模拟大根堆
        heap = [(-freq, num) for num, freq in cnt.items()]
        heapq.heapify(heap)
        
        result = []
        for _ in range(k):
            neg_freq, num = heapq.heappop(heap)
            result.append(num)
        
        return result
    
    # 方法3：桶排序（最优）
    def topKFrequent3(self, nums: List[int], k: int) -> List[int]:
        """
        使用桶排序，线性时间复杂度
        时间复杂度：O(n)
        空间复杂度：O(n)
        """
        cnt = collections.Counter(nums)
        
        # 创建桶，索引为频率，值为该频率的元素列表
        bucket = [[] for _ in range(len(nums) + 1)]
        
        for num, freq in cnt.items():
            bucket[freq].append(num)
        
        result = []
        # 从高频率到低频率遍历
        for i in range(len(bucket) - 1, -1, -1):
            for num in bucket[i]:
                result.append(num)
                if len(result) == k:
                    return result
        
        return result
    
    # 方法4：使用内置排序
    def topKFrequent4(self, nums: List[int], k: int) -> List[int]:
        """
        直接排序，简单但效率较低
        时间复杂度：O(n log n)
        空间复杂度：O(n)
        """
        cnt = collections.Counter(nums)
        
        # 按频率降序排序
        sorted_items = sorted(cnt.items(), key=lambda x: x[1], reverse=True)
        
        return [num for num, freq in sorted_items[:k]]


def test_solutions():
    """测试所有解法"""
    solution = Solution()
    
    # 测试用例1
    nums1 = [1, 1, 1, 2, 2, 3]
    k1 = 2
    print(f"测试用例1: nums = {nums1}, k = {k1}")
    print(f"方法1（小根堆）: {solution.topKFrequent(nums1, k1)}")
    print(f"方法2（大根堆）: {solution.topKFrequent2(nums1, k1)}")
    print(f"方法3（桶排序）: {solution.topKFrequent3(nums1, k1)}")
    print(f"方法4（排序）: {solution.topKFrequent4(nums1, k1)}")
    print()
    
    # 测试用例2
    nums2 = [1]
    k2 = 1
    print(f"测试用例2: nums = {nums2}, k = {k2}")
    print(f"方法1（小根堆）: {solution.topKFrequent(nums2, k2)}")
    print(f"方法2（大根堆）: {solution.topKFrequent2(nums2, k2)}")
    print(f"方法3（桶排序）: {solution.topKFrequent3(nums2, k2)}")
    print(f"方法4（排序）: {solution.topKFrequent4(nums2, k2)}")
    print()
    
    # 测试用例3
    nums3 = [4, 1, -1, 2, -1, 2, 3]
    k3 = 2
    print(f"测试用例3: nums = {nums3}, k = {k3}")
    print(f"方法1（小根堆）: {solution.topKFrequent(nums3, k3)}")
    print(f"方法2（大根堆）: {solution.topKFrequent2(nums3, k3)}")
    print(f"方法3（桶排序）: {solution.topKFrequent3(nums3, k3)}")
    print(f"方法4（排序）: {solution.topKFrequent4(nums3, k3)}")


if __name__ == "__main__":
    test_solutions()
    
    print("""
    算法分析：前K个高频元素
    
    四种解法对比：
    
    方法1：小根堆（推荐）
    - 时间复杂度：O(n log k)
    - 空间复杂度：O(n + k)
    - 优点：空间效率高，只维护k个元素的堆
    - 核心：维护大小为k的小根堆，堆顶是第k大的频率
    
    方法2：大根堆
    - 时间复杂度：O(n log n)
    - 空间复杂度：O(n)
    - 优点：思路简单直观
    - 缺点：需要存储所有元素，空间开销大
    
    方法3：桶排序（最优）
    - 时间复杂度：O(n)
    - 空间复杂度：O(n)
    - 优点：线性时间复杂度
    - 核心：频率作为桶的索引，从高频到低频遍历
    
    方法4：直接排序
    - 时间复杂度：O(n log n)
    - 空间复杂度：O(n)
    - 优点：代码简洁，易于理解
    - 缺点：效率不如前三种方法
    
    关键洞察：
    1. 小根堆维护前K大：堆顶是第K大的元素
    2. 桶排序利用频率范围有限的特点
    3. Python的heapq是小根堆，用负数模拟大根堆
    4. Counter是统计频率的最佳工具
    
    面试建议：
    - 首选小根堆解法（平衡了时间和空间）
    - 可以提及桶排序作为优化方案
    - 注意Python堆的使用技巧
    """)

