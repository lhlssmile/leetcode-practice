from typing import List


class Solution:
    def change(self, coins: List[int], amount) -> int:
        f = [1] + amount * [0]

        for x in coins:
            for c in range(x, amount + 1):
                f[c] += f[c - x]
        return f[amount]


if __name__ == '__main__':
    s = Solution()
    s.change([1, 2, 5], 5)
