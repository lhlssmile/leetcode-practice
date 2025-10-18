class Solution:
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:
        MOD = 10**9 + 7
        
        # f[i]表示第i天新知道秘密的人数
        f = [0] * (n + 1)
        f[1] = 1  # 第1天有1个人知道秘密
        
        # 计算每天新知道秘密的人数
        for i in range(2, n + 1):
            # j表示在第j天知道秘密的人
            # 这些人在第i天仍然记得秘密(i-j < forget)且已经可以分享(i-j >= delay)
            for j in range(max(1, i - forget + 1), i - delay + 1):
                f[i] = (f[i] + f[j]) % MOD
        
        # 计算第n天仍然记得秘密的总人数
        ans = 0
        for i in range(max(1, n - forget + 1), n + 1):
            ans = (ans + f[i]) % MOD
        
        return ans

# 测试函数
def test_people_aware_of_secret():
    solution = Solution()
    
    # 测试用例1: n=6, delay=2, forget=4
    print(f"Test Case 1: {solution.peopleAwareOfSecret(6, 2, 4)}")  # 预期输出: 5
    
    # 测试用例2: n=4, delay=1, forget=3
    print(f"Test Case 2: {solution.peopleAwareOfSecret(4, 1, 3)}")  # 预期输出: 6
    
    # 测试用例3: n=10, delay=2, forget=5
    print(f"Test Case 3: {solution.peopleAwareOfSecret(10, 2, 5)}")

if __name__ == "__main__":
    test_people_aware_of_secret()

"""
算法思路：

1. 定义状态：f[i]表示第i天新知道秘密的人数

2. 初始条件：f[1] = 1，表示第1天有1个人知道秘密

3. 状态转移：
   - 对于第i天，新知道秘密的人数等于所有能够分享秘密的人分享的总和
   - 一个人在知道秘密的第j天，需要经过delay天才能分享，并且在forget天后会忘记
   - 因此，对于第i天，我们需要考虑在第j天知道秘密的人，其中j满足：
     * j >= i - forget + 1（这些人在第i天仍然记得秘密）
     * j <= i - delay（这些人在第i天已经可以分享秘密）

4. 最终答案：
   - 第n天仍然记得秘密的总人数，即在第[n-forget+1, n]天内知道秘密的人的总和

时间复杂度：O(n * forget)，其中n是总天数
空间复杂度：O(n)
"""