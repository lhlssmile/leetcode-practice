from typing import List


class Solution:
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:
        # 自底向上
        value_map = {}

        for c in range(26):
            value_map[chr(ord('a') + c)] = c + 1
        for c, v in zip(chars, vals):
            value_map = v
        arr = [value_map[ch] for ch in range(s)]
        curr, ans = 0, 0
        for v in arr:
            curr = max(curr + v, v)
            ans = max(ans, curr)
        return ans
