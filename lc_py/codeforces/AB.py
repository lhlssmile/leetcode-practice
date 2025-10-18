def solve(s: str, c: str) -> int:
    pos = [i for i, ch in enumerate(s) if ch == c]
    if not pos:
        return 0
    shifted = [p - i for i, p in enumerate(pos)]
    shifted.sort()
    m = shifted[len(shifted) // 2]
    return sum(abs(x - m) for x in shifted)

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        s = input().strip()
        ans = min(solve(s, 'a'), solve(s, 'b'))
        print(ans)

if __name__ == "__main__":
    main()


'''
让所有 'a'（或 'b'）聚成一块连续的区间
假设a的出现位置pos = [p1, p2, p3, ..., pk]
把它们排成一个连续区间 [x, x+1, ..., x+k-1] 第 i 个 'a' 希望被放到新位置 x + (i - 1)
                cost(x)=i=1∑k ​∣pi​−(x+i−1)∣ -> |pi - (i - 1) - x| -> |qi - x| x的qi中位数

'''