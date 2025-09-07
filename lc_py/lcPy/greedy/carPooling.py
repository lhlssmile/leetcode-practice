# Python版本 - 拼车问题 (LeetCode 1094)
from typing import List
from collections import defaultdict

class Solution:
    def carPooling(self, trips: List[List[int]], capacity: int) -> bool:
        """事件排序法"""
        events = []
        
        # 构建事件列表
        for passengers, start, end in trips:
            events.append((start, passengers))   # 上车事件
            events.append((end, -passengers))    # 下车事件
        
        # 排序事件：先按位置，再按变化量（下车优先）
        events.sort(key=lambda x: (x[0], x[1]))
        
        current_passengers = 0
        
        # 处理所有事件
        for location, change in events:
            current_passengers += change
            if current_passengers > capacity:
                return False
        
        return True
    
    def carPoolingDiffArray(self, trips: List[List[int]], capacity: int) -> bool:
        """差分数组法"""
        diff = defaultdict(int)
        
        # 构建差分数组
        for passengers, start, end in trips:
            diff[start] += passengers
            diff[end] -= passengers
        current_passengers = 0
        
        # 按位置顺序处理
        for pos in sorted(diff.keys()):
            current_passengers += diff[pos]
            if current_passengers > capacity:
                return False
        
        return True

def main():
    solution = Solution()
    
    # 测试用例
    test_cases = [
        ([[2,1,5],[3,3,7]], 4, False),      # 测试用例1
        ([[2,1,5],[3,3,7]], 5, True),       # 测试用例2
        ([[2,1,5],[3,5,7]], 3, True),       # 测试用例3
        ([[3,2,7],[3,7,9],[8,3,9]], 11, True)  # 测试用例4
    ]
    
    print("=== 拼车问题测试 ===")
    
    for i, (trips, capacity, expected) in enumerate(test_cases, 1):
        result1 = solution.carPooling(trips, capacity)
        result2 = solution.carPoolingDiffArray(trips, capacity)
        
        print(f"测试用例 {i}: trips = {trips}, capacity = {capacity}")
        print(f"事件排序法: {result1}")
        print(f"差分数组法: {result2}")
        print(f"预期结果: {expected}")
        print(f"结果: {'✓' if result1 == expected and result2 == expected else '✗'}")
        print()

if __name__ == "__main__":
    main()

"""
算法说明：
1. 事件排序法：
   - 将每个行程转换为上车和下车事件
   - 按位置排序，同位置时下车优先
   - 模拟整个过程，检查是否超载
   
2. 差分数组法：
   - 使用差分思想，记录每个位置的乘客变化
   - 按位置顺序累加，检查是否超载
   
时间复杂度: O(n log n)
空间复杂度: O(n)
"""