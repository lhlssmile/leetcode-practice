class Solution:
    def isValid(self,word: str) -> bool:
        if len(word) < 3:
            return False
        f = [False] * 2

        for c in word:
            if c.isalpha():
                f[c.lower() in "aeiou"] = True
            elif not c.isdigit():
                return False
        return all(f)