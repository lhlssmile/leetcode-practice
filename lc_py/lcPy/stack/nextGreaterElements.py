from typing import List


class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        ans = [-1] * len(nums)
        n = len(nums)
        st = []

        for i in range(2 * n - 1, -1 , -1):
            curr = nums[i % n]
            while st and nums[st[-1]] <= curr:
                st.pop()
            if st and i < n: ans[i] = nums[st[-1]]
            st.append(i % n)
        return ans