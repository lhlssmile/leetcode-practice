from typing import List


def digit_sum(a: int) -> int:
    s = 0
    while a > 0:
        s += a % 10
        a //= 10
    return s


class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        n = len(nums)

        sorted_nums = sorted(nums, key=lambda x: (digit_sum(x), x))

        pos = {val: i for i, val in enumerate(sorted_nums)}

        visited = [False] * n

        swaps = 0

        for i in range(n):
            if visited[i] or pos[nums[i]] == i:
                continue
            cycle_len = 0

            j = i

            while not visited[j]:
                visited[j] = True
                j = pos[nums[j]]
                cycle_len += 1
            swaps += cycle_len - 1
        return swaps


if __name__ == '__main__':
    s = Solution()
    s.minSwaps([18, 43, 34, 16])
