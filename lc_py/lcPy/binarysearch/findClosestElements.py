from bisect import bisect_left
from typing import List
import heapq


class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        """方法1: 二分扩展法"""
        n = len(arr)

        # 二分查找最接近 x 的位置
        idx = bisect_left(arr, x)

        left, right = idx - 1, idx

        # 扩展窗口，直到找到 k 个元素
        while right - left - 1 < k:
            if left < 0:
                right += 1
            elif right >= n:
                left -= 1
            else:
                if x - arr[left] <= arr[right] - x:
                    left -= 1
                else:
                    right += 1

        return arr[left + 1:right]
    
    def findClosestElementsSlidingWindow(self, arr: List[int], k: int, x: int) -> List[int]:
        """方法2: 滑动窗口法"""
        left, right = 0, len(arr) - k
        
        while left < right:
            mid = (left + right) // 2
            # 比较窗口两端到x的距离
            if x - arr[mid] > arr[mid + k] - x:
                left = mid + 1
            else:
                right = mid
        
        return arr[left:left + k]
    
    def findClosestElementsMaxHeap(self, arr: List[int], k: int, x: int) -> List[int]:
        """方法3: 大根堆法"""
        # 使用大根堆维护k个最接近的元素
        heap = []
        
        for num in arr:
            distance = abs(num - x)
            if len(heap) < k:
                heapq.heappush(heap, (-distance, -num))  # 负号实现大根堆
            else:
                # 如果当前元素更接近，替换堆顶
                if distance < -heap[0][0]:
                    heapq.heapreplace(heap, (-distance, -num))
        
        # 提取结果并排序
        result = [-item[1] for item in heap]
        return sorted(result)
    
    def findClosestElementsOptimizedHeap(self, arr: List[int], k: int, x: int) -> List[int]:
        """方法3优化: 大根堆法 - 只处理前面部分"""
        heap = []
        
        for i, num in enumerate(arr):
            distance = abs(num - x)
            if len(heap) < k:
                heapq.heappush(heap, (-distance, -num, i))
            else:
                if distance < -heap[0][0] or (distance == -heap[0][0] and num < -heap[0][1]):
                    heapq.heapreplace(heap, (-distance, -num, i))
                # 如果当前元素距离更远，且已经有k个元素，可以提前结束
                elif distance > -heap[0][0]:
                    break
        
        # 按索引排序保证结果有序
        indices = sorted([item[2] for item in heap])
        return [arr[i] for i in indices]


def test():
    s = Solution()
    arr = [1, 2, 3, 4, 5]
    k, x = 4, 3
    
    print("二分扩展法:", s.findClosestElements(arr, k, x))
    print("滑动窗口法:", s.findClosestElementsSlidingWindow(arr, k, x))
    print("大根堆法:", s.findClosestElementsMaxHeap(arr, k, x))
    print("优化堆法:", s.findClosestElementsOptimizedHeap(arr, k, x))


if __name__ == '__main__':
    test()
