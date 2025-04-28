import collections
from typing import List
class MaxSlidingWindow:
    def maxSlidingWindow(self,nums:List[int],k:int) -> List[int]:
        ans = []
        n = len(nums)
        if n < k:
            ans.append(max(nums))
            return ans
        dq = collections.deque()
        for i in range(0,k):
            # 单调队列 小于队头的值永远不可能为结果
            while dq and nums[dq[-1]] < nums[i]:
                dq.pop()
            dq.append(i)
        # 第一个窗口的最大值
        ans.append(nums[dq[0]])
        for i in range(k,n):
            if dq and dq[0] <= i - k:
                dq.popleft()    # 这个最大值已经不是当前窗口
            while dq and nums[dq[-1]] < nums[i]:
                dq.pop()    #保持单调
            dq.append(i)
            ans.append(nums[dq[0]])
        return ans

if __name__ == '__main__':
   max_sliding_window = MaxSlidingWindow()
   res = max_sliding_window.maxSlidingWindow(nums=[1,3,-1,-3,5,3,6,7],k = 3)
   print(res)
