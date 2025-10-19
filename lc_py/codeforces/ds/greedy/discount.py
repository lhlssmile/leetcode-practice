import sys

def solve(prices, voucher):
    prices.sort()
    voucher.sort()
    s = sum(prices)
    nn = len(prices)
    for vi in voucher:
        if nn < vi: break
        s -= prices[nn - vi]
        nn -= vi
    return s

if __name__ == "__main__":
    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    for _ in range(t):
        n = int(data[idx])
        k = int(data[idx + 1])
        idx += 2
        prices = [int(x) for x in data[idx:idx + n]]
        idx += n
        vouchers = [int(x) for x in data[idx:idx + k]]
        idx += k
        print(solve(prices, vouchers))
