class Solution:
    def letterCasePermutation(self, s: str) -> list[str]:
        ans = []
        path = []
        
        def dfs(i: int) -> None:
            if i == len(s):
                ans.append(''.join(path))
                return
            
            ch = s[i]
            if ch.isdigit():
                path.append(ch)
                dfs(i + 1)
                path.pop()
            else:
                # 小写
                path.append(ch.lower())
                dfs(i + 1)
                path.pop()
                
                # 大写
                path.append(ch.upper())
                dfs(i + 1)
                path.pop()
        
        dfs(0)
        return ans

# 测试函数
def main():
    solution = Solution()
    
    # 测试用例1
    s1 = "a1b2"
    result1 = solution.letterCasePermutation(s1)
    print(f"Input: {s1}")
    print(f"Output: {result1}")
    
    # 测试用例2
    s2 = "3z4"
    result2 = solution.letterCasePermutation(s2)
    print(f"Input: {s2}")
    print(f"Output: {result2}")

if __name__ == "__main__":
    main()

"""
算法思路：递归回溯生成所有可能的字母大小写排列
时间复杂度：O(2^n)，其中n是字符串中字母的数量
空间复杂度：O(n)，递归栈的深度和临时字符串的空间
"""