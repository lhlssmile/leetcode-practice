class countCompleteSubarrays:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        freq = defaultdict(int)


        ans = left = 0

        total_kinds = len(set(nums))

        for right,num in enumerate(nums):
            freq[num] += 1
            while len(freq) == total_kinds:
                ans += len(nums) - right
                freq[nums[left]] -= 1
                if freq[nums[left]] == 0:
                    del freq[nums[left]]
                left += 1

        return ans


if __name__ == '__main__':
    nums = [5,5,5,5]
    sol = countCompleteSubarrays()
    print(sol.countCompleteSubarrays(nums))