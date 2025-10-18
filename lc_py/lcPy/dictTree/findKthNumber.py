class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        def count_prefix(prefix: int, n: int) -> int:
            """统计 <= n 的、以 prefix 开头的数字个数"""
            count = 0
            cur, nxt = prefix, prefix + 1
            while cur <= n:
                count += min(n + 1, nxt) - cur
                cur *= 10
                nxt *= 10
            return count

        prefix = 1
        k -= 1  # 第一个是1已经算了
        while k > 0:
            cnt = count_prefix(prefix, n)
            if k >= cnt:
                k -= cnt
                prefix += 1  # 下一个兄弟前缀
            else:
                k -= 1
                prefix *= 10  # 往子树更深一层
        return prefix


if __name__ == '__main__':
    s = Solution()
    s.findKthNumber(13, 3)