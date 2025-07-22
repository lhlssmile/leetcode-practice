from typing import List


def combinationSum(candidates: List[int], target: int) -> List[List[int]]:
    # 一个数字可以被重复选取
    candidates.sort()
    ans = path = []

    def dfs(idx, left):
        if left == 0:
            ans.append(path.copy())
            return
        if idx == len(candidates) or left < candidates[i]:
            return

        dfs(idx + 1, left)

        path.append(candidates[idx])
        dfs(idx + 1, left - candidates[idx])
        path.pop()

    dfs(0, target)
    return ans


class Solution:
    pass
