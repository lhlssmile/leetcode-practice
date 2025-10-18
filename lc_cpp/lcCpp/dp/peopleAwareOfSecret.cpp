#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int MOD = 1000000007;
        
        // f[i]表示第i天新知道秘密的人数
        vector<int> f(n + 1, 0);
        f[1] = 1; // 第1天有1个人知道秘密
        
        // 计算每天新知道秘密的人数
        for (int i = 2; i <= n; i++) {
            // j表示在第j天知道秘密的人
            // 这些人在第i天仍然记得秘密(i-j < forget)且已经可以分享(i-j >= delay)
            for (int j = max(1, i - forget + 1); j <= i - delay; j++) {
                f[i] = (f[i] + f[j]) % MOD;
            }
        }
        
        // 计算第n天仍然记得秘密的总人数
        int ans = 0;
        for (int i = max(1, n - forget + 1); i <= n; i++) {
            ans = (ans + f[i]) % MOD;
        }
        
        return ans;
    }
};

// 测试函数
int main() {
    Solution sol;
    
    // 测试用例1: n=6, delay=2, forget=4
    cout << "Test Case 1: " << sol.peopleAwareOfSecret(6, 2, 4) << endl; // 预期输出: 5
    
    // 测试用例2: n=4, delay=1, forget=3
    cout << "Test Case 2: " << sol.peopleAwareOfSecret(4, 1, 3) << endl; // 预期输出: 6
    
    // 测试用例3: n=10, delay=2, forget=5
    cout << "Test Case 3: " << sol.peopleAwareOfSecret(10, 2, 5) << endl;
    
    return 0;
}

/*
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
*/