class CountSubarrays:
    def countSubarrays(self,nums: List[int],minK: int,maxK: int) -> int:
        ans = 0
        n = len(nums)
        minK_pos = maxK_pos = left = -1

        for i in range(n):
            if nums[i] < minK or nums[i] > maxK:
                left = i
            if nums[i] == minK:
                minK_pos = i
            if nums[i] == maxK:
                maxK_pos = i
            valid_start = min(minK_pos,maxK_pos)
            if valid_start > left:
                ans += valid_start - left
        return ans