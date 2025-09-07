# LeetCode 459: 重复的子字符串
# 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

def repeated_substring_pattern_kmp(s: str) -> bool:
    """KMP算法实现"""
    n = len(s)
    if n <= 1:
        return False
    
    # 构建KMP的next数组
    next_arr = [0] * (n + 1)
    next_arr[0] = -1
    j = -1
    
    for i in range(n):
        while j >= 0 and s[i] != s[j]:
            j = next_arr[j]
        j += 1
        next_arr[i + 1] = j
    
    period_len = n - next_arr[n]
    return n % period_len == 0 and period_len != n

def repeated_substring_pattern_concat(s: str) -> bool:
    """字符串拼接方法"""
    # 将字符串与自身拼接，然后去掉首尾字符
    # 如果原字符串是重复模式，那么在新字符串中一定能找到原字符串
    double_s = s + s
    return s in double_s[1:-1]

def repeated_substring_pattern_brute(s: str) -> bool:
    """暴力枚举方法"""
    n = len(s)
    if n <= 1:
        return False
    
    for i in range(1, n // 2 + 1):
        if n % i == 0:
            pattern = s[:i]
            if pattern * (n // i) == s:
                return True
    return False

def repeated_substring_pattern_regex(s: str) -> bool:
    """正则表达式方法"""
    import re
    # 使用正则表达式匹配重复模式
    pattern = r'^(.+)\1+$'
    return bool(re.match(pattern, s))

def repeated_substring_pattern_gcd(s: str) -> bool:
    """最大公约数方法"""
    import math
    n = len(s)
    if n <= 1:
        return False
    
    # 找到所有可能的周期长度
    for period_len in range(1, n // 2 + 1):
        if n % period_len == 0:
            # 检查是否为重复模式
            pattern = s[:period_len]
            if all(s[i] == pattern[i % period_len] for i in range(n)):
                return True
    return False

def main():
    test_cases = [
        "abab",
        "aba",
        "abcabcabcabc",
        "a",
        "aa"
    ]
    
    print("=== 重复的子字符串模式检测 ===")
    
    for i, s in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}: \"{s}\"")
        
        result1 = repeated_substring_pattern_kmp(s)
        result2 = repeated_substring_pattern_concat(s)
        result3 = repeated_substring_pattern_brute(s)
        result4 = repeated_substring_pattern_regex(s)
        result5 = repeated_substring_pattern_gcd(s)
        
        print(f"KMP算法: {result1}")
        print(f"字符串拼接: {result2}")
        print(f"暴力枚举: {result3}")
        print(f"正则表达式: {result4}")
        print(f"GCD方法: {result5}")
        
        # 验证结果一致性
        results = [result1, result2, result3, result4, result5]
        if not all(r == results[0] for r in results):
            print("警告: 结果不一致!")

if __name__ == "__main__":
    main()