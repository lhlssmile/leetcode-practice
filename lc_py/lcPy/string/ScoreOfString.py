# 3110 字符串的分数
class ScoreOfString:
    def scoreOfString(self,s:str) -> int:
        n = len(s)
        score = 0
        for i in range(n - 1):
            score += abs(ord(s[i]) - ord(s[i + 1]))
        return score


if __name__ == '__main__':
    sol = ScoreOfString()
    s = "hanayuki"
    print(sol.scoreOfString(s))
