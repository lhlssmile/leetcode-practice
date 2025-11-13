# -*- coding: utf-8 -*-
import sys, math

def read_bigint_from_stdin():
    # 读取所有行，去掉非数字（如空行），拼成一个连续的十进制字符串
    s = ''.join(line.strip() for line in sys.stdin if line.strip())
    # 有时样例给了多行数字，中间有空格或其它符号，保守处理只保留0-9
    s = ''.join(ch for ch in s if ch.isdigit())
    if not s:
        return None
    return s.lstrip('0') or '0'

def precompute_logs(maxn):
    L = [0.0] * (maxn + 1)
    for i in range(1, maxn + 1):
        L[i] = L[i-1] + math.log10(i)
    return L

def estimate_log10_from_decimal_str(s):
    # s: decimal big integer string without leading zeros (or "0")
    if s == '0':
        return -float('inf')  # not expected in this problem
    d = len(s)
    head = s[:30]  # 取前若干位保证浮点精度
    head_val = int(head)
    # log10(X) = (d - len(head)) + log10(head_val)
    # 更精确写作： log10(X) = (d - len(head)) + log10(head_val)
    return (d - len(head)) + math.log10(head_val)

def find_candidate_n(L, logX):
    # 找第一个 L[n] > logX
    lo, hi = 1, len(L)-1
    while lo < hi:
        mid = (lo + hi) // 2
        if L[mid] > logX:
            hi = mid
        else:
            lo = mid + 1
    return lo

def main():
    s = int(input())
    if s is None:
        return
    # 预处理上界（可调整）
    MAXN = 10**6
    L = precompute_logs(MAXN)

    logX = estimate_log10_from_decimal_str(s)

    n = find_candidate_n(L, logX)

    # 因为浮点误差或边界，我们在 n 的附近做小范围搜索
    candidate_ns = []
    for cand in range(max(1, n-3), min(MAXN, n+3)+1):
        # 检查下界： L[cand] - log10(cand-1) <= logX < L[cand]
        lower = L[cand] - (math.log10(cand-1) if cand-1 >= 1 else 0.0)
        if lower - 1e-12 <= logX < L[cand] + 1e-12:
            candidate_ns.append(cand)

    # 把输入转换成 Python int（大整数）
    X = int(s)

    for cand in candidate_ns:
        # 计算 cand! 并判断是否能整除 X
        fact = 1
        for i in range(2, cand+1):
            fact *= i
        # 要求 fact % X == 0 且 m = fact // X satisfies 1 <= m < cand
        if fact % X != 0:
            continue
        m = fact // X
        if 1 <= m < cand and X * m == fact:
            print(f"{cand} {m}")
            return

    # 若未找到（极少数浮点误差或异常输入），可以扩大检索或退化为暴力：
    # 但通常上面已经足够；这里输出 nothing 表示失败
    print("No solution found")

if __name__ == "__main__":
    main()
