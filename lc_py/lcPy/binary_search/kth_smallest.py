from typing import List
import heapq

class Solution:
    # 二分查找解法
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
        n = len(matrix)
        
        def countLessEqual(x: int) -> int:
            i, j = n - 1, 0
            count = 0
            while i >= 0 and j < n:
                if matrix[i][j] <= x:
                    count += i + 1  # 当前列中有i+1个元素小于等于target
                    j += 1
                else:
                    i -= 1
            return count
        
        lo, hi = matrix[0][0], matrix[-1][-1]
        
        while lo < hi:
            mid = lo + (hi - lo) // 2
            if countLessEqual(mid) < k:
                lo = mid + 1
            else:
                hi = mid
        
        return lo
    
    # 最小堆解法
    def kthSmallestHeap(self, matrix: List[List[int]], k: int) -> int:
        n = len(matrix)
        heap = []
        
        # 将第一列的元素加入堆
        for i in range(min(n, k)):
            heapq.heappush(heap, (matrix[i][0], i, 0))
        
        # 弹出k-1个元素
        for _ in range(k - 1):
            val, row, col = heapq.heappop(heap)
            
            if col + 1 < n:
                heapq.heappush(heap, (matrix[row][col + 1], row, col + 1))
        
        return heapq.heappop(heap)[0]

# 测试函数
def test_kth_smallest():
    solution = Solution()
    
    # 测试用例1
    matrix1 = [
        [1, 5, 9],
        [10, 11, 13],
        [12, 13, 15]
    ]
    k1 = 8
    print(f"Binary Search: {solution.kthSmallest(matrix1, k1)}")
    print(f"Heap: {solution.kthSmallestHeap(matrix1, k1)}")
    
    # 测试用例2
    matrix2 = [
        [1, 2],
        [1, 3]
    ]
    k2 = 2
    print(f"Binary Search: {solution.kthSmallest(matrix2, k2)}")
    print(f"Heap: {solution.kthSmallestHeap(matrix2, k2)}")

if __name__ == "__main__":
    test_kth_smallest()

"""
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
"""