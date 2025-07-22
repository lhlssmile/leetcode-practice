class Solution:
    def makeFancyString(self, s: str) -> str:
        ans = []

        cnt = 0

        for i, ch in enumerate(s):
            cnt += 1

            if cnt < 3:
                ans.append(ch)

            if i < len(s) - 1 and ch != s[i + 1]:
                cnt = 0

        return ''.join(ans)
