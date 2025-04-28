from typing import List
class NumberOfArrays:
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:
        n = len(differences)
        prefix = min_prefix = max_prefix = 0

        for i in range(n):
            prefix += differences[i]
            min_prefix = min(prefix, min_prefix)
            max_prefix = max(prefix, max_prefix)
        left = lower - min_prefix
        right = upper - max_prefix
        return 0 if left > right else right - left + 1



if __name__ == '__main__':
    differences = [1,  -3, 4]
    lower = 1
    upper = 6
    sol = NumberOfArrays()
    print(sol.numberOfArrays(differences,lower,upper))