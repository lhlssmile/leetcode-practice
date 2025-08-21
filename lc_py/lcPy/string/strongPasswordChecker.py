class Solution:
    def strongPasswordCheckerII(self, password: str) -> bool:
        n = len(password)
        # size 8
        if n < 8: return False
        ss = "!@#$%^&*()-+"
        sp, lower, upper, digit = False, False, False, False

        for i, c in enumerate(password):
            if i > 0 and c == password[i - 1]:
                return False
            # 小写
            elif c.islower(): lower = True
            elif c.isupper(): upper = True
            elif c.isdigit(): digit = True
            elif c in ss: sp = True
        return lower and upper and digit and sp