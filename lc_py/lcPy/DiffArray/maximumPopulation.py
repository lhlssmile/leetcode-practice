from typing import List


class Solution:
    def maximumPopulation(self, logs: List[List[int]]) -> int:
        diff = [0] * 101

        for b, d in logs:
            diff[b - 1950] += 1
            diff[d - 1950] -= 1

        max_pop, year, curr = 0, 1950, 0

        for i in range(101):
            curr += diff[i]
            if curr > max_pop:
                max_pop = curr
                year = 1950 + i
        return year


if __name__ == '__main__':
    s = Solution()

    logs = [[1950, 1961], [1960, 1971], [1970, 1981]]
    print(s.maximumPopulation(logs))
