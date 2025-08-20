from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        ans, res, n = [], [], len(nums)
        vis = [False] * n
        def backTrack(i: int) -> None:
            if i == n:
                ans.append(res[:])  # 创建 res 的副本
                return
            for j in range(n):  # 修复：用 j 遍历，避免覆盖 i
                if not vis[j]:
                    res.append(nums[j])
                    vis[j] = True
                    backTrack(i + 1)
                    res.pop()
                    vis[j] = False
        backTrack(0)
        return ans