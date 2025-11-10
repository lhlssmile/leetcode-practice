from typing import List


class Solution:
    def minOperations(self, a: List[int]) -> int:
        ans, top = 0, -1

        for _, x in enumerate(a):
            while top >= 0 and x < a[top]:
                ans += 1
                top -= 1
            if top < 0 or x != a[top]:
                top += 1
                a[top] = x
        return ans + top + (a[0] > 0)


if __name__ == '__main__':
    s = Solution()
    print(s.minOperations([3, 1, 2, 1]))
