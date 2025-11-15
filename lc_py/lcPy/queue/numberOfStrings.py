def numberOfSubstrings(s: str) -> int:
    n = len(s)
    a = [i for i, x in enumerate(s) if x == '0']  # 0的下标列表
    tot1 = n - len(a)  # 1的数目
    a.append(n)
    ans = 0
    cnt_pass0 = 0  # 表示左端点前的0的数目，正好a[pass0]表示左端点后第一个0
    for left, x in enumerate(s):  # 枚举子串的左端点
        if x == '1':  # 首先枚举子串中没有0的情况，只有当起点为1时才有
            ans += a[cnt_pass0] - left  # 下1个0到当前位置一定都是1，将左端点为left且不含0的子串都加进去
        for k in range(cnt_pass0, len(a) - 1):  # 枚举子串中有0的情况，用0的位置（即第几个0)去判定，终点写len(a) - 1是因为a的长度再前面加了1，后边会解释有啥用
            cnt0 = k - cnt_pass0 + 1
            if cnt0 * cnt0 > tot1:  # 之后的0一定也不满足，故跳出
                break
            cnt1 = a[k] - left + 1 - (k - cnt_pass0 + 1)  # 当前子串长度减去cnt0
            if cnt0 * cnt0 <= cnt1:  # 这种情况下, 将后续的cnt0不变的情况都考虑进去，因为cnt1不会变小
                ans += a[k + 1] - a[k]
                # 这里当k为s中0的最后一个下标时，正好后续的字符都是1，即后续的都满足，所以要在a的最后加一个n，正好不用特殊处理
            else:
                # 这种情况下，再不增加cnt0的基础上，需要补cnt0*cnt0 - cnt1个1才满足，即前cnt0*cnt0 - cnt1个1不在答案里
                # 但若到下一个0之间没有这么多1，则答案的增加数是0（因为不满足cnt0不变，但cnt1变为cnt0*cnt0及以上）
                ans += max(a[k + 1] - a[k] - (cnt0 * cnt0 - cnt1), 0)
            # ans += max(a[k + 1] - a[k] - max(cnt0 * cnt0 - cnt1, 0), 0)
            # 灵神代码把上文的if else合成一行
        if x == '0':
            # 更新pass0
            cnt_pass0 += 1
    return ans


if __name__ == '__main__':
    print(numberOfSubstrings("101101"))
