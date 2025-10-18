from typing import List
class Solution:
    def findSmallestInteger(self, nums: List[int], value: int) -> int:
        cnt = {}
        for x in nums:
            cnt[(x % value + value) % value] += 1
        mex = 0
        while cnt[mex % value]:
            cnt[mex % value] += 1
            mex += 1
        return mex


if __name__ == "__main__":
    nums = [1,-10,7,13,6,8]
    s = Solution()
    print(s.findSmallestInteger(nums, 5))  
    
            
