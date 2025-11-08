
class Solution:
    def minimumOneBitOperations(self, n: int)-> int:
        ans = 0
        while n:
            ans ^= n
            n >>= 1
        return ans


if __name__ == '__main__':
    s = Solution()
    s.minimumOneBitOperations(6)