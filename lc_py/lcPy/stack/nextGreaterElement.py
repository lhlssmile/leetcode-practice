from typing import List


class Solution:
    def nextGreaterElement(self, nums1, nums2: List[int]) -> List[int]:
        idx = {x: i for i, x in enumerate(nums1)}

        st = []

        ans = [-1] * len(nums1)

        for x in nums2:
            while st and x > st[-1]:
                ans[idx[st.pop()]] = x
            if x in idx:
                st.append(x)
        return ans


if __name__ == '__main__':
    s = Solution()
    s.nextGreaterElement([4, 1, 2], [1, 3, 4, 2])