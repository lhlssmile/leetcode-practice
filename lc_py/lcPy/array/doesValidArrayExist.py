from typing import List


class Solution:
    def doesValidArrayExist(self, derived: List[int]) -> bool:
        ans = 0
        for _, x in enumerate(derived):
            ans ^= x
        return ans == 0
