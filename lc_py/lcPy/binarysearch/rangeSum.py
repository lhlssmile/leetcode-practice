from typing import List


from typing import List
import bisect

class Solution:
    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:
        MOD = 10**9 + 7

        # 前缀和 pre（长度 n+1）
        pre = [0] * (n + 1)
        for i in range(n):
            pre[i+1] = pre[i] + nums[i]

        # P2 是 pre 的前缀和：P2[k] = sum(pre[0..k-1])
        P2 = [0] * (n + 1)
        for i in range(1, n+1):
            P2[i] = P2[i-1] + pre[i-1]

        # 统计所有子数组和 <= x 的数量和它们的总和
        def count_and_sum(x: int):
            cnt = 0
            total = 0
            # 对每个右端 i（对应 pre 的索引 i），在 pre[0..i-1] 中找第一个 >= pre[i] - x
            for i in range(1, n+1):
                target = pre[i] - x
                # 在 pre[0:i] 中找第一个 >= target
                L = bisect.bisect_left(pre, target, 0, i)
                num = i - L
                if num > 0:
                    cnt += num
                    # 累加这些子数组和的和：
                    # sum_{t=L}^{i-1} (pre[i] - pre[t]) = num*pre[i] - sum(pre[L..i-1])
                    sum_pre_range = P2[i] - P2[L]
                    total += num * pre[i] - sum_pre_range
            return cnt, total

        # 求前 k 小子数组和之和
        def kth_sum(k: int):
            if k == 0:
                return 0
            lo, hi = 0, pre[n]  # 范围 [0, sum(nums)]
            while lo < hi:
                mid = (lo + hi) // 2
                cnt, _ = count_and_sum(mid)
                if cnt >= k:
                    hi = mid
                else:
                    lo = mid + 1
            x = lo
            cnt, total = count_and_sum(x)
            # 如果 cnt > k，多出来的（cnt - k）个值必然等于 x，
            # 从 total 中减去 (cnt - k) * x 即可得到前 k 小的和
            return total - (cnt - k) * x

        ans = (kth_sum(right) - kth_sum(left - 1)) % MOD
        return ans


if __name__ == '__main__':
    nums = [1, 2, 3, 4]
    n = 4
    left = 1
    right = 5
    s = Solution()
    print(s.rangeSum(nums, n, left, right))