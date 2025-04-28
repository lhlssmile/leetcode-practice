class ConcatenatedDivisibility3533:
    def concatenatedDivisibility(self, nums: List[int], k: int) -> List[int]:
        nums.sort()
        n = len(nums)

        pow10 = [10 ** len(str(x)) for x in nums]

        ans = []

        @cache
        def dfs(s: int,x: int) -> bool:
            if s == 0:
                return x == 0
            for i,(p10,v) in enumerate(zip(pow10,nums)):
                if s & (1 << i) and dfs(s ^ (1 << i),(x * p10 + v) % k):
                    ans.append(v)
                    return True
            return False
        
        if not dfs((1 << len(nums))- 1,0):
            return []
        ans.reverse()
        return ans


if __name__ == "__main__":
    sol = ConcatenatedDivisibility3533()
    nums = [3,12,45]
    k = 5
    print(sol.concatenatedDivisibility(nums,k))