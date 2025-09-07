import heapq
from typing import List

class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        # 计算增益函数
        def gain(pass_count, total_count):
            return (pass_count + 1) / (total_count + 1) - pass_count / total_count
        
        # 使用最大堆（Python的heapq是最小堆，所以用负值）
        heap = []
        for pass_count, total_count in classes:
            heapq.heappush(heap, (-gain(pass_count, total_count), pass_count, total_count))
        
        # 分配额外学生
        for _ in range(extraStudents):
            neg_gain, pass_count, total_count = heapq.heappop(heap)
            pass_count += 1
            total_count += 1
            heapq.heappush(heap, (-gain(pass_count, total_count), pass_count, total_count))
        
        # 计算最终平均通过率
        total_ratio = 0
        for _, pass_count, total_count in heap:
            total_ratio += pass_count / total_count
        
        return total_ratio / len(classes)

# 测试用例
if __name__ == '__main__':
    s = Solution()
    
    # 测试用例1
    classes1 = [[1,2],[3,5],[2,2]]
    extraStudents1 = 2
    result1 = s.maxAverageRatio(classes1, extraStudents1)
    print(f"测试用例1: {result1:.5f}")
    
    # 测试用例2
    classes2 = [[2,4],[3,9],[4,5],[2,10]]
    extraStudents2 = 4
    result2 = s.maxAverageRatio(classes2, extraStudents2)
    print(f"测试用例2: {result2:.5f}")