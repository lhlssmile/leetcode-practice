from collections import Counter
from typing import List


class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        # 统计两个数组的元素频次
        cnt1 = Counter(basket1)
        cnt2 = Counter(basket2)
        total_cnt = cnt1 + cnt2  # 合并频次

        # 检查是否可均分（总频次必须为偶数）
        for val in total_cnt:
            if total_cnt[val] % 2 != 0:
                return -1

        # 计算需要交换的元素
        swaps = []
        for val in total_cnt:
            diff = cnt1[val] - cnt2[val]
            if diff > 0:  # basket1多出的元素，需移到basket2
                swaps.extend([val] * (diff // 2))
            elif diff < 0:  # basket2多出的元素，需移到basket1
                swaps.extend([val] * (-diff // 2))

        # 如果没有需要交换的元素，直接返回0
        if not swaps:
            return 0

        # 排序swaps，模拟交换过程
        swaps.sort()
        n = len(swaps) // 2
        min_val = min(min(basket1), min(basket2))  # 全局最小元素
        total_cost = 0

        # 贪心：从大到小处理交换，每次选最小成本
        for i in range(n):
            x = swaps[n - 1 - i]  # basket1的元素
            y = swaps[n + i]  # basket2的元素
            # 直接交换x和y的成本 vs 用min_val作为媒介的成本
            cost = min(x, y, 2 * min_val)
            total_cost += cost

        return total_cost


if __name__ == '__main__':
    s = Solution()
    s.minCost([84, 80, 43, 8, 80, 88, 43, 14, 100, 88], [32, 32, 42, 68, 68, 100, 42, 84, 14, 8])
