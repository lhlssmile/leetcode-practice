from typing import List


class Solution:
    def canEat(self, candiesCount: List[int], queries: List[List[int]]):
        ans = [False] * len(queries)

        prefix = [0] * (len(candiesCount) + 1)

        for i, x in enumerate(candiesCount):
            prefix[i + 1] = prefix[i] + x

        for i in range(len(queries)):
            min_taking = queries[i][1] + 1
            max_taking = min_taking * queries[i][2]

            curr_candy = prefix[queries[i][0]] + 1
            nxt_candy = prefix[queries[i][0] + 1]

            ans[i] = not (min_taking > nxt_candy or max_taking < curr_candy)
        return ans
