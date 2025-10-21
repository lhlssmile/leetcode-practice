from collections import defaultdict
from typing import List
import sys

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

def main():
    n = II()
    nums = LII()  # p = [p1, p2, ..., pn]，1-based 排列

    # 计算 q 的前两个元素（ans[0] 和 ans[1]），模拟字典序“对立”偏移
    tmp = [nums[0] - 1, nums[1] - 1]
    if tmp[1] > tmp[0]:
        tmp[1] -= 1
    tmp[1] += n * (n - 1) // 2  # 加总跳跃（(n-1)! / 2 的效果）
    tmp[0] += tmp[1] // (n - 1)
    tmp[1] %= n - 1
    tmp[0] %= n
    ans = [tmp[0] + 1, tmp[1] + 1]
    if ans[1] >= ans[0]: ans[1] += 1  # 调整避免重复

    # 这里开始你问的部分：准备后缀映射
    vis1 = [0] * (n + 1)  # vis1: 标记 p 后缀（位置 2~n）中出现的值
    vis2 = [1] * (n + 1)  # vis2: 标记 q 后缀可用位置（初始全可用）

    for i in range(2, n):  # 只标记 p[2:] 的值
        vis1[nums[i]] = 1

    for x in ans:  # q 前两个用了，标记为不可用
        vis2[x] = 0

    mapping = [0] * (n + 1)  # mapping: p 后缀值 -> q 后缀对应值（排序配对）
    p1, p2 = 1, 1  # p1: 扫描 p 后缀值（从小到大），p2: 扫描 q 可用位置（从小到大）

    for _ in range(n - 2):  # 为后 n-2 个位置配对
        while not vis1[p1]: p1 += 1  # 跳过不在 p 后缀的值，找到下一个 p 后缀值
        while not vis2[p2]: p2 += 1  # 跳过已被用的 q 位置，找到下一个可用 q 值
        mapping[p1] = p2  # 配对：p 后缀的第 k 小值 -> q 后缀的第 k 小可用值
        p1 += 1
        p2 += 1

    for i in range(2, n):  # 构建 q 后缀：每个 p[i] 替换为 mapping[p[i]]
        ans.append(mapping[nums[i]])

    print(' '.join(map(str, ans)))  # 输出 q

if __name__ == "__main__":
    main()