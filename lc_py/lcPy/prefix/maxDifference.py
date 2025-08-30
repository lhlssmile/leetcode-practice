from typing import List

class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        inf = float('inf') // 2
        ans = -inf
        for x in range(5):
            for y in range(5):
                if y == x:
                    continue
                cur_s = [0] * 5
                pre_s = [0] * 5
                min_s = [[inf, inf], [inf, inf]]
                left = 0
                for i in range(len(s)):
                    cur_s[int(s[i])] += 1
                    r = i + 1
                    while r - left >= k and cur_s[x] > pre_s[x] and cur_s[y] > pre_s[y]:
                        p = min_s[pre_s[x] & 1][pre_s[y] & 1]
                        min_s[pre_s[x] & 1][pre_s[y] & 1] = min(p, pre_s[x] - pre_s[y])
                        pre_s[int(s[left])] += 1
                        left += 1
                    ans = max(ans, cur_s[x] - cur_s[y] - min_s[(cur_s[x] & 1) ^ 1][cur_s[y] & 1])
        return ans
    
    # 优化版本：使用更具描述性的变量名和注释
    def maxDifferenceOptimized(self, s: str, k: int) -> int:
        INF = float('inf') // 2
        max_difference = -INF
        
        # 枚举所有可能的字符对(x,y)，其中x!=y
        for x in range(5):
            for y in range(5):
                if y == x:
                    continue
                
                # 当前窗口中各字符的计数
                current_count = [0] * 5
                # 前缀窗口中各字符的计数
                prefix_count = [0] * 5
                # 存储最小差值，按奇偶性分类
                min_difference = [[INF, INF], [INF, INF]]
                
                left = 0
                for i in range(len(s)):
                    # 更新当前窗口计数
                    current_count[int(s[i])] += 1
                    right = i + 1
                    
                    # 当窗口大小>=k且满足条件时，更新最小差值
                    while (right - left >= k and 
                           current_count[x] > prefix_count[x] and 
                           current_count[y] > prefix_count[y]):
                        # 根据x和y的奇偶性选择对应的最小差值
                        parity_x = prefix_count[x] & 1  # x的奇偶性
                        parity_y = prefix_count[y] & 1  # y的奇偶性
                        min_difference[parity_x][parity_y] = min(
                            min_difference[parity_x][parity_y],
                            prefix_count[x] - prefix_count[y]
                        )
                        
                        # 移动左指针，更新前缀计数
                        prefix_count[int(s[left])] += 1
                        left += 1
                    
                    # 计算当前最大差值
                    # 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
                    current_parity_x = (current_count[x] & 1) ^ 1
                    current_parity_y = current_count[y] & 1
                    max_difference = max(
                        max_difference,
                        current_count[x] - current_count[y] - min_difference[current_parity_x][current_parity_y]
                    )
                    
        return max_difference
    
    # Pythonic版本：使用更多Python特性
    def maxDifferencePythonic(self, s: str, k: int) -> int:
        INF = float('inf') // 2
        max_difference = -INF
        
        # 将字符串转换为数字列表，避免重复转换
        digits = [int(ch) for ch in s]
        
        for x, y in [(x, y) for x in range(5) for y in range(5) if x != y]:
            current_count = [0] * 5
            prefix_count = [0] * 5
            min_difference = [[INF, INF], [INF, INF]]
            
            left = 0
            for i, digit in enumerate(digits):
                current_count[digit] += 1
                right = i + 1
                
                while (right - left >= k and 
                       current_count[x] > prefix_count[x] and 
                       current_count[y] > prefix_count[y]):
                    parity_x, parity_y = prefix_count[x] & 1, prefix_count[y] & 1
                    min_difference[parity_x][parity_y] = min(
                        min_difference[parity_x][parity_y],
                        prefix_count[x] - prefix_count[y]
                    )
                    prefix_count[digits[left]] += 1
                    left += 1
                
                current_parity_x = (current_count[x] & 1) ^ 1
                current_parity_y = current_count[y] & 1
                max_difference = max(
                    max_difference,
                    current_count[x] - current_count[y] - min_difference[current_parity_x][current_parity_y]
                )
                    
        return max_difference

# 测试代码
if __name__ == "__main__":
    solution = Solution()
    
    # 测试用例
    s1 = "01234"
    k1 = 2
    print(f"测试用例1结果: {solution.maxDifference(s1, k1)}")
    print(f"测试用例1结果(优化版): {solution.maxDifferenceOptimized(s1, k1)}")
    print(f"测试用例1结果(Pythonic版): {solution.maxDifferencePythonic(s1, k1)}")
    
    s2 = "00110"
    k2 = 2
    print(f"测试用例2结果: {solution.maxDifference(s2, k2)}")
    print(f"测试用例2结果(优化版): {solution.maxDifferenceOptimized(s2, k2)}")
    print(f"测试用例2结果(Pythonic版): {solution.maxDifferencePythonic(s2, k2)}")