class Solution:
    def countAsterisks(self, s: str)-> int:
        valid = True

        ans = 0
        for c in s:
            if c == '|': valid = not valid
            elif c == '*' and valid: ans += 1

        return ans