# LeetCode 1371. 每个元音包含偶数次的最长子字符串
# 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。

def findTheLongestSubstring(s: str) -> int:
    """
    使用前缀和+状态压缩的方法
    时间复杂度: O(n)，其中n是字符串长度
    空间复杂度: O(1)，状态数最多为2^5=32种
    """
    n = len(s)
    first = {0: -1}  # 记录状态第一次出现的位置，空字符串状态为0，位置-1
    state = 0  # 当前前缀的元音奇偶状态
    max_len = 0  # 最长子字符串长度
    
    # 元音映射：a=0, e=1, i=2, o=3, u=4
    vowel_pos = {}
    for c in 'aeiou':
        vowel_pos[c] = "aeiou".index(c)
    
    # 遍历字符串
    for i in range(n):
        # 如果是元音，更新状态（翻转对应位的奇偶性）
        if s[i] in vowel_pos:
            pos = vowel_pos[s[i]]
            state ^= (1 << pos)  # 翻转第pos位
        
        # 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if state in first:
            max_len = max(max_len, i - first[state])
        else:
            # 记录状态第一次出现的位置
            first[state] = i
    
    return max_len

# 更简洁的Python实现
def findTheLongestSubstring_concise(s: str) -> int:
    """
    使用前缀和+状态压缩的方法（更简洁的Python实现）
    时间复杂度: O(n)，其中n是字符串长度
    空间复杂度: O(1)，状态数最多为2^5=32种
    """
    vowels = {'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4}
    seen = {0: -1}  # 状态->位置映射
    state = 0
    max_len = 0
    
    for i, char in enumerate(s):
        if char in vowels:
            state ^= (1 << vowels[char])
        
        if state in seen:
            max_len = max(max_len, i - seen[state])
        else:
            seen[state] = i
    
    return max_len

# 测试函数
def test_solution():
    test_cases = [
        ("eleetminicoworoep", 13),
        ("leetcodeisgreat", 5),
        ("bcbcbc", 6)
    ]
    
    for s, expected in test_cases:
        result = findTheLongestSubstring(s)
        assert result == expected, f"For input '{s}', expected {expected} but got {result}"
        
        result_concise = findTheLongestSubstring_concise(s)
        assert result_concise == expected, f"For input '{s}', expected {expected} but got {result_concise} (concise version)"
    
    print("All test cases passed!")

if __name__ == "__main__":
    test_solution()
    
    # 示例输出
    s = "eleetminicoworoep"
    print(findTheLongestSubstring(s))  # 输出13