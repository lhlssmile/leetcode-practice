import heapq


class Solution:
    def findKthLargest(self,nums,k):
        min_heap = []

        for num in nums:
            if len(min_heap) < k:
                heapq.heappush(min_heap,num)
            elif num > min_heap[0]:
                heapq.heappop(min_heap)
                heapq.heappush(min_heap, num)
        return min_heap[0]


if __name__ == '__main__':
    s = Solution()
    nums = [3, 2, 1, 5, 6, 4]
    print(s.findKthLargest(nums, 2))