from typing import List


class Solution:
    def vowelStrings(self, words: List[str], queries: List[List[int]]) -> List[int]:
        vowels = set("aeiou")

        def is_vowel_word(w: str) -> bool:
            return w[0] in vowels and w[-1] in vowels

        prefix = [0]

        for w in words:
            prefix.append(prefix[-1] + (1 if is_vowel_word(w) else 0))

        ans = []

        for l, r in queries:
            ans.append(prefix[r + 1] - prefix[l])
        return ans