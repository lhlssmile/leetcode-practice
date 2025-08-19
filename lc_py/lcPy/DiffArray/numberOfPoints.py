class Solution:
    def numberOfPoints(self, nums: List[List[int]]) -> int:
        ans = 0
        max_end = max(end for _, end in nums)
        diff = [0] * (max_end + 2)

        for st, en in nums:
            diff[st] += 1
            diff[en + 1] -= 1
        return sum(s > 0 for s in accumulate(diff))