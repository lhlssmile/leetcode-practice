class maxVowels:
    """
    1456. 定长子字符串中元音的最大数目
    
    给你字符串 s 和整数 k 。
    请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。
    英文中的 元音字母 为（a, e, i, o, u）。
    
    示例 1：
    输入：s = "abciiidef", k = 3
    输出：3
    解释：子字符串 "iii" 包含 3 个元音字母。
    
    示例 2：
    输入：s = "aeiou", k = 2
    输出：2
    解释：任意长度为 2 的子字符串都包含 2 个元音字母。
    
    示例 3：
    输入：s = "leetcode", k = 3
    输出：2
    解释："lee"、"eet" 和 "ode" 都包含 2 个元音字母。
    """
    
    def maxVowels(self, s: str, k: int) -> int:
        # 定义元音字母集合
        vowels = set('aeiou')
        
        # 初始化答案和当前窗口中的元音数量
        ans = vowel = 0
        
        # 定长滑动窗口
        for i in range(len(s)):
            # 右边界进入窗口
            if s[i] in vowels:
                vowel += 1
            
            # 窗口大小超过k时，左边界移出窗口
            if i >= k:
                if s[i - k] in vowels:
                    vowel -= 1
            
            # 更新答案（窗口大小达到k时才开始更新）
            if i >= k - 1:
                ans = max(ans, vowel)
        
        return ans
    
    def maxVowels_v2(self, s: str, k: int) -> int:
        """
        另一种写法：先计算第一个窗口，然后滑动
        """
        vowels = set('aeiou')
        
        # 计算第一个窗口的元音数量
        current_vowels = 0
        for i in range(k):
            if s[i] in vowels:
                current_vowels += 1
        
        max_vowels = current_vowels
        
        # 滑动窗口
        for i in range(k, len(s)):
            # 新字符进入窗口
            if s[i] in vowels:
                current_vowels += 1
            # 旧字符离开窗口
            if s[i - k] in vowels:
                current_vowels -= 1
            
            max_vowels = max(max_vowels, current_vowels)
        
        return max_vowels


# 测试用例
def test_solution():
    solution = maxVowels()
    
    # 测试用例1
    s1, k1 = "abciiidef", 3
    result1 = solution.maxVowels(s1, k1)
    print(f"测试1: s='{s1}', k={k1} => 结果: {result1}, 期望: 3")
    
    # 测试用例2
    s2, k2 = "aeiou", 2
    result2 = solution.maxVowels(s2, k2)
    print(f"测试2: s='{s2}', k={k2} => 结果: {result2}, 期望: 2")
    
    # 测试用例3
    s3, k3 = "leetcode", 3
    result3 = solution.maxVowels(s3, k3)
    print(f"测试3: s='{s3}', k={k3} => 结果: {result3}, 期望: 2")
    
    # 边界测试
    s4, k4 = "a", 1
    result4 = solution.maxVowels(s4, k4)
    print(f"测试4: s='{s4}', k={k4} => 结果: {result4}, 期望: 1")
    
    # 测试第二种方法
    print("\n=== 测试第二种方法 ===")
    result1_v2 = solution.maxVowels_v2(s1, k1)
    result2_v2 = solution.maxVowels_v2(s2, k2)
    result3_v2 = solution.maxVowels_v2(s3, k3)
    print(f"方法2 - 测试1: {result1_v2}, 测试2: {result2_v2}, 测试3: {result3_v2}")


if __name__ == "__main__":
    test_solution()