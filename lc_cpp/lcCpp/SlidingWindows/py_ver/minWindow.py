import sys

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        m, n = len(s), len(t)
        if m < n:
            return ""

        t_count = [0] * 128  # t 的字符频率
        window_count = [0] * 128  # 窗口的字符频率

        for c in t:
            t_count[ord(c)] += 1

        required = n
        left, right = 0, 0
        minLen, start = sys.maxsize, 0

        while right < m:  # 遍历 s 的长度
            c = s[right]
            window_count[ord(c)] += 1
            if t_count[ord(c)] > 0 and window_count[ord(c)] <= t_count[ord(c)]:
                required -= 1

            while required == 0 and left <= right:
                if right - left + 1 < minLen:
                    minLen = right - left + 1
                    start = left
                left_char = s[left]
                window_count[ord(left_char)] -= 1
                if t_count[ord(left_char)] > 0 and window_count[ord(left_char)] < t_count[ord(left_char)]:
                    required += 1
                left += 1

            right += 1

        return "" if minLen == sys.maxsize else s[start:start + minLen]

if __name__ == '__main__':
    solution = Solution()
    res = solution.minWindow("ADOBECODEBANC", "ABC")
    print(res)  # 输出 "BANC"