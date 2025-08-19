from typing import List


class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        n = len(words)
        ans = [0] * n

        def get_lcp(s1, s2):
            min_len = min(len(s1), len(s2))
            for j in range(min_len):
                if s1[j] != s2[j]:
                    return j
            return min_len

        if n <= 1:
            return [0]

        lcp = [0] * (n - 1)
        for i in range(n - 1):
            lcp[i] = get_lcp(words[i], words[i + 1])

        for i in range(n):
            candidates = []

            # 左边部分
            if i >= 2:
                candidates.append(max(lcp[:i-1]))
            elif i == 1:
                # 只保留 lcp[0:i-1] 不存在
                pass

            # 右边部分
            if i <= n-3:
                candidates.append(max(lcp[i+1:]))
            elif i == n-2:
                # 只保留 lcp[i+1:] 不存在
                pass

            # 跨过 i 的相邻对
            if 0 < i < n-1:
                candidates.append(get_lcp(words[i-1], words[i+1]))

            ans[i] = max(candidates) if candidates else 0

        return ans


if __name__ == '__main__':
    s = Solution()
    s.longestCommonPrefix(["jump","run","run","jump","run"])