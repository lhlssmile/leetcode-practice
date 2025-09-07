class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        m = len(nums)
        mod_map = defaultdict(int)
        mod_map[0] = -1
        prefix_s = 0
        
        for i in range(m):
            prefix_s += nums[i]
            
            mod = prefix_s % k
            
            if mod in mod_map:
                if i - mod_map[mod] >= 2:
                    return True
            else:
                mod_map[mod] = i
        return False