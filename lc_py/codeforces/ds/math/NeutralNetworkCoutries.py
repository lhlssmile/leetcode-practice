from collections import defaultdict
from typing import List
import sys
from collections import Counter

input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()

'''

li, lj层之间的任意城市到达代价均为cij
返回从0-exit的路径数(能被m整除)
start

li lici licj ... 
lj ljci ljcj
lk lkci lkcj ...
exit

构建邻接表? 不过是只有相邻的有向有权图
'''
def main():
    mod = 10 ** 9 + 7
    n, l, m = LII()

    in_ = LII()
    between = LII()
    out = LII()

    for i in range(n):
        in_[i] %= m
        between[i] %= m
        out[i] %= m
    """
    状态定义与求解：
    - 仅以“当前代价的模 m 余数”作为状态（向量长度 m）。
    - start -> 第一层：根据 in 的余数计数得到初始向量 V1。
    - 层间（l-1 次）：每次从余数 b 到余数 a 的转移数只取决于 between 的余数分布：
      T[a][b] = cnt_between[(a - b) mod m]，为循环矩阵。
    - 最后一跳（最后一层 -> exit）：与 out 的余数计数做卷积，取余数 0。
    使用矩阵快速幂计算 T^(l-1)。
    """


    def count_residues(arr, m):
        cnt = [0] * m
        for x in arr:
            cnt[x] = (cnt[x] + 1) % mod
        return cnt


    def mat_mul(A, B):
        nA = len(A)
        nB = len(B)
        assert nA == nB
        n = nA
        C = [[0] * n for _ in range(n)]
        for i in range(n):
            Ai = A[i]
            Ci = C[i]
            for k in range(n):
                aik = Ai[k]
                if aik:
                    Bk = B[k]
                    for j in range(n):
                        Ci[j] = (Ci[j] + aik * Bk[j]) % mod
        return C


    def mat_pow(A, e):
        n = len(A)
        # 单位矩阵
        R = [[0] * n for _ in range(n)]
        for i in range(n):
            R[i][i] = 1
        while e > 0:
            if e & 1:
                R = mat_mul(R, A)
            A = mat_mul(A, A)
            e >>= 1
        return R


    def mat_vec_mul(A, v):
        n = len(A)
        assert len(v) == n
        res = [0] * n
        for i in range(n):
            s = 0
            Ai = A[i]
            for j in range(n):
                s += Ai[j] * v[j]
            res[i] = s % mod
        return res


    # 1) 初始向量：start -> 第一层
    V1 = count_residues(in_, m)

    # 2) 转移矩阵：层间一步的循环矩阵
    cnt_between = count_residues(between, m)
    T = [[0] * m for _ in range(m)]
    for a in range(m):
        for b in range(m):
            T[a][b] = cnt_between[(a - b) % m]

    # 3) 中间 (l-2) 次层间转移（最后一步单独处理）
    steps_mid = l - 2
    if steps_mid > 0:
        Tp = mat_pow(T, steps_mid)
        Vprev = mat_vec_mul(Tp, V1)
    else:
        Vprev = V1

    # 4) 最后一跳：从最后一层到 exit
    # 若 l == 1：没有 between 步，只加 out[j]
    # 若 l >= 2：最后一步加 between[j] 与 out[j] 的和
    if l == 1:
        cnt_final = count_residues(out, m)
    else:
        cnt_final = [0] * m
        for j in range(n):
            s = (between[j] + out[j]) % m
            cnt_final[s] = (cnt_final[s] + 1) % mod

    ans = 0
    for r in range(m):
        ans = (ans + Vprev[r] * cnt_final[(-r) % m]) % mod

    print(ans)






if __name__ == '__main__':
    main()
