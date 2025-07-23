from functools import cache


class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        """编辑距离 - 动态规划解法"""
        m, n = len(word1), len(word2)
        
        # dp[i][j] 表示 word1 的前 i 个字符转换为 word2 的前 j 个字符所需的最少操作数
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        # 边界条件：空字符串转换
        for i in range(m + 1):
            dp[i][0] = i  # word1 前 i 个字符转换为空字符串，需要 i 次删除
        for j in range(n + 1):
            dp[0][j] = j  # 空字符串转换为 word2 前 j 个字符，需要 j 次插入
        
        # 状态转移
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    # 字符相同，不需要操作
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    # 字符不同，选择代价最小的操作
                    dp[i][j] = min(
                        dp[i - 1][j] + 1,      # 删除 word1[i-1]
                        dp[i][j - 1] + 1,      # 插入 word2[j-1]
                        dp[i - 1][j - 1] + 1   # 替换 word1[i-1] 为 word2[j-1]
                    )
        
        return dp[m][n]
    
    def minDistance_memo(self, word1: str, word2: str) -> int:
        """编辑距离 - 递归记忆化解法"""
        
        @cache  # Python 3.9+ 的装饰器，等价于 @lru_cache(maxsize=None)
        def dfs(i: int, j: int) -> int:
            """返回 word1[0:i] 转换为 word2[0:j] 的最少操作数"""
            # 边界条件
            if i == 0:
                return j  # 空字符串转换为 word2[0:j]，需要 j 次插入
            if j == 0:
                return i  # word1[0:i] 转换为空字符串，需要 i 次删除
            
            # 递归计算
            if word1[i - 1] == word2[j - 1]:
                # 字符相同，不需要操作
                return dfs(i - 1, j - 1)
            else:
                # 字符不同，选择代价最小的操作
                return min(
                    dfs(i - 1, j) + 1,      # 删除 word1[i-1]
                    dfs(i, j - 1) + 1,      # 插入 word2[j-1]
                    dfs(i - 1, j - 1) + 1   # 替换 word1[i-1] 为 word2[j-1]
                )
        
        return dfs(len(word1), len(word2))
    
    def minDistance_space_optimized(self, word1: str, word2: str) -> int:
        """编辑距离 - 空间优化版本"""
        m, n = len(word1), len(word2)
        
        # 只需要两行，当前行和上一行
        prev = list(range(n + 1))  # 上一行
        curr = [0] * (n + 1)       # 当前行
        
        for i in range(1, m + 1):
            curr[0] = i  # 边界条件
            
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    curr[j] = prev[j - 1]
                else:
                    curr[j] = min(
                        prev[j] + 1,      # 删除
                        curr[j - 1] + 1,  # 插入
                        prev[j - 1] + 1   # 替换
                    )
            
            prev, curr = curr, prev  # 交换行
        
        return prev[n]


def test_min_distance():
    """测试函数"""
    solution = Solution()
    
    # 测试用例1
    word1, word2 = "horse", "ros"
    result1 = solution.minDistance(word1, word2)
    result2 = solution.minDistance_memo(word1, word2)
    result3 = solution.minDistance_space_optimized(word1, word2)
    
    print(f"输入: word1='{word1}', word2='{word2}'")
    print(f"DP解法: {result1}")
    print(f"记忆化递归: {result2}")
    print(f"空间优化: {result3}")
    print(f"预期: 3 (horse -> rorse -> rose -> ros)")
    print()
    
    # 测试用例2
    word1, word2 = "intention", "execution"
    result = solution.minDistance(word1, word2)
    print(f"输入: word1='{word1}', word2='{word2}'")
    print(f"结果: {result}")
    print(f"预期: 5")
    print()


def visualize_dp_process():
    """可视化DP过程"""
    print("=== DP过程可视化 (word1='horse', word2='ros') ===")
    word1, word2 = "horse", "ros"
    m, n = len(word1), len(word2)
    
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 边界条件
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j
    
    print("初始化后的DP表:")
    print("    ", end="")
    for j in range(n + 1):
        if j == 0:
            print("  ε", end="")
        else:
            print(f"  {word2[j-1]}", end="")
    print()
    
    for i in range(m + 1):
        if i == 0:
            print("ε  ", end="")
        else:
            print(f"{word1[i-1]}  ", end="")
        for j in range(n + 1):
            print(f"{dp[i][j]:3}", end="")
        print()
    print()
    
    # 填充DP表
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
                operation = "匹配"
            else:
                delete_cost = dp[i - 1][j] + 1
                insert_cost = dp[i][j - 1] + 1
                replace_cost = dp[i - 1][j - 1] + 1
                
                dp[i][j] = min(delete_cost, insert_cost, replace_cost)
                
                if dp[i][j] == delete_cost:
                    operation = "删除"
                elif dp[i][j] == insert_cost:
                    operation = "插入"
                else:
                    operation = "替换"
            
            print(f"dp[{i}][{j}] = {dp[i][j]} ({operation} '{word1[i-1]}' -> '{word2[j-1]}')")
    
    print("\n最终DP表:")
    print("    ", end="")
    for j in range(n + 1):
        if j == 0:
            print("  ε", end="")
        else:
            print(f"  {word2[j-1]}", end="")
    print()
    
    for i in range(m + 1):
        if i == 0:
            print("ε  ", end="")
        else:
            print(f"{word1[i-1]}  ", end="")
        for j in range(n + 1):
            print(f"{dp[i][j]:3}", end="")
        print()


# 编辑距离学习要点
def edit_distance_learning_tips():
    """
    编辑距离（Levenshtein Distance）学习要点：
    
    1. 问题定义：
       - 将字符串 word1 转换为 word2 所需的最少操作数
       - 允许的操作：插入、删除、替换字符
    
    2. DP状态定义：
       dp[i][j] = word1 的前 i 个字符转换为 word2 的前 j 个字符的最少操作数
    
    3. 状态转移方程：
       if word1[i-1] == word2[j-1]:
           dp[i][j] = dp[i-1][j-1]  # 字符相同，不需要操作
       else:
           dp[i][j] = min(
               dp[i-1][j] + 1,      # 删除 word1[i-1]
               dp[i][j-1] + 1,      # 插入 word2[j-1]
               dp[i-1][j-1] + 1     # 替换 word1[i-1] 为 word2[j-1]
           )
    
    4. 边界条件：
       dp[i][0] = i  # word1 前 i 个字符转换为空字符串
       dp[0][j] = j  # 空字符串转换为 word2 前 j 个字符
    
    5. 三种解法对比：
       - 二维DP：时间 O(mn)，空间 O(mn)
       - 记忆化递归：时间 O(mn)，空间 O(mn) + 递归栈
       - 空间优化：时间 O(mn)，空间 O(min(m,n))
    
    6. 实际应用：
       - 拼写检查
       - DNA序列比对
       - 文本相似度计算
       - 版本控制中的diff算法
    """
    pass


if __name__ == "__main__":
    test_min_distance()
    print("\n" + "="*50 + "\n")
    visualize_dp_process()