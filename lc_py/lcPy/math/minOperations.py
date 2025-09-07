def prefix(n):
    ans = 0
    base = 1
    k = 1
    
    while True:
        next_base = base * 4
        L = base
        R = next_base - 1
        if n >= R:
            ans += (R - L + 1) * k
        else:
            ans += (n - L + 1) * k
            break
        base = next_base
        k += 1
    
    return ans

class Solution:
    def minOperations(self, queries):
        total = 0
        for q in queries:
            l, r = q[0], q[1]
            S = prefix(r) - prefix(l - 1)
            total += (S + 1) // 2
        return total

def test_min_operations():
    solution = Solution()
    
    print("=== LeetCode 最小操作数问题 ===")
    
    # 测试用例1
    queries1 = [[1, 4], [2, 6], [3, 8]]
    result1 = solution.minOperations(queries1)
    print(f"测试用例1: {queries1} -> 结果: {result1}")
    
    # 测试用例2
    queries2 = [[1, 10], [5, 15]]
    result2 = solution.minOperations(queries2)
    print(f"测试用例2: {queries2} -> 结果: {result2}")
    
    # 测试用例3
    queries3 = [[1, 1], [2, 2], [3, 3]]
    result3 = solution.minOperations(queries3)
    print(f"测试用例3: {queries3} -> 结果: {result3}")
    
    # 测试prefix函数
    print("\nprefix函数测试:")
    for i in range(1, 11):
        print(f"prefix({i}) = {prefix(i)}")

if __name__ == "__main__":
    test_min_operations()

"""
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是(S+1)//2

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

Python特性:
1. 动态类型
2. 列表推导式
3. 简洁语法
4. 内置数据结构
"""