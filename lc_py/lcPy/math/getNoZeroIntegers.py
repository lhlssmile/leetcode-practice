from typing import List


def whetherNotContainsZero(n: int) -> bool:
    while n > 0:
        if n % 10 == 0: return False
        n //= 10
    return True


class Solution:
    def getNoZeroIntegers(self, n: int) -> List[int]:
        a = 1
        ans = []
        for a in range(1, n - a + 1):
            if whetherNotContainsZero(a) and whetherNotContainsZero(n - a):
                ans.append(a)
                ans.append(n - a)
                break
        return ans

    def getNoZeroIntegers1(self, n: int) -> List[int]:
        a = 0
        base = 1  # 10**k
        x = n
        while x > 1:
            x, d = divmod(x, 10)
            if d <= 1:
                d += 10
                x -= 1  # 借位
            # a 这一位填 d//2，比如百位数就是 d//2 * 100
            a += d // 2 * base
            base *= 10
        return [a, n - a]


if __name__ == '__main__':
    s = Solution()
    print(s.getNoZeroIntegers1(400))
