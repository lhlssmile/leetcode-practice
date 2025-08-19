from typing import List


class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        odd_start, even_start, even_pos, odd_pos, even_cnt, odd_cnt = 0, 0, [], [], 0, 0
        for i, x in enumerate(nums):
            if x % 2:
                odd_cnt += 1
                odd_pos.append(i)
            else:
                even_cnt += 1
                even_pos.append(i)
        if abs(even_cnt - odd_cnt) > 1: return -1
        # 偶数开头
        res = inf
        if even_cnt >= odd_cnt:
            target = [i * 2 for i in range(even_cnt)]
            cost = sum(abs(even_pos[i] - target[i]) for i in range(even_cnt))
            res = min(res, cost)
        if odd_cnt >= even_cnt:
            target = [i * 2 for i in range(odd_cnt)]
            cost = sum(abs(odd_pos[i] - target[i]) for i in range(odd_cnt))
            res = min(res, cost)
        return res
