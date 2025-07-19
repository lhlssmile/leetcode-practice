/*
LeetCode 279. 完全平方数
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
你需要让组成和的完全平方数的个数最少。

示例 1:
输入: n = 12
输出: 3 
解释: 12 = 4 + 4 + 4.

示例 2:
输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    // 方法1: 递归 + 记忆化 (C++版本)
    int numSquares(int n) {
        unordered_map<int, int> memo;
        return dfs(n, memo);
    }
    
private:
    int dfs(int remaining, unordered_map<int, int>& memo) {
        // 基础情况
        if (remaining == 0) return 0;
        if (remaining < 0) return INT_MAX;
        
        // 记忆化检查
        if (memo.find(remaining) != memo.end()) {
            return memo[remaining];
        }
        
        // 找到所有可能的完全平方数
        int maxSqrt = (int)sqrt(remaining);
        int minCount = INT_MAX;
        
        // 尝试所有可能的完全平方数：1², 2², 3², ..., maxSqrt²
        for (int i = 1; i <= maxSqrt; i++) {
            int square = i * i;
            int count = dfs(remaining - square, memo);
            if (count != INT_MAX) {
                minCount = min(minCount, 1 + count);
            }
        }
        
        // 记忆化存储
        memo[remaining] = minCount;
        return minCount;
    }
    
public:
    // 方法2: 动态规划 (递推)
    int numSquaresDP(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                int square = j * j;
                if (dp[i - square] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - square] + 1);
                }
            }
        }
        
        return dp[n];
    }
    
    // 方法3: 空间优化版本 (只用必要的空间)
    int numSquaresOptimized(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        // 预计算所有可能的完全平方数
        vector<int> squares;
        for (int i = 1; i * i <= n; i++) {
            squares.push_back(i * i);
        }
        
        for (int i = 1; i <= n; i++) {
            for (int square : squares) {
                if (square > i) break;
                if (dp[i - square] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - square] + 1);
                }
            }
        }
        
        return dp[n];
    }
};

// 测试和性能对比
void testAndCompare() {
    Solution solution;
    vector<int> testCases = {12, 13, 1, 4, 7, 100};
    
    cout << "=== C++ 完全平方数问题测试 ===\n\n";
    
    for (int n : testCases) {
        cout << "n = " << n << ":\n";
        
        // 测试三种方法
        int result1 = solution.numSquares(n);        // 递归+记忆化
        int result2 = solution.numSquaresDP(n);      // 动态规划
        int result3 = solution.numSquaresOptimized(n); // 优化版
        
        cout << "  递归+记忆化: " << result1 << "\n";
        cout << "  动态规划:     " << result2 << "\n";
        cout << "  优化版本:     " << result3 << "\n";
        
        // 验证结果一致性
        if (result1 == result2 && result2 == result3) {
            cout << "  ✅ 所有方法结果一致\n";
        } else {
            cout << "  ❌ 结果不一致！\n";
        }
        cout << "\n";
    }
    
    cout << "=== 方法对比 ===\n";
    cout << "🎯 递归+记忆化:\n";
    cout << "   - 时间复杂度: O(n * sqrt(n))\n";
    cout << "   - 空间复杂度: O(n) [递归栈 + 哈希表]\n";
    cout << "   - 特点: 自顶向下，思路直观\n\n";
    
    cout << "🚀 动态规划:\n";
    cout << "   - 时间复杂度: O(n * sqrt(n))\n";
    cout << "   - 空间复杂度: O(n) [DP数组]\n";
    cout << "   - 特点: 自底向上，效率高\n\n";
    
    cout << "⚡ 优化版本:\n";
    cout << "   - 时间复杂度: O(n * sqrt(n))\n";
    cout << "   - 空间复杂度: O(n + sqrt(n))\n";
    cout << "   - 特点: 预计算平方数，减少重复计算\n\n";
    
    cout << "💡 核心洞察:\n";
    cout << "   - 记忆化 = 递归 + 缓存\n";
    cout << "   - DP = 记忆化的迭代版本\n";
    cout << "   - 优化 = 减少不必要的计算\n";
}

int main() {
    testAndCompare();
    return 0;
}

/*
编译和运行:
g++ -o numSquares numSquares.cpp
./numSquares

或者在Windows:
g++ -o numSquares.exe numSquares.cpp
numSquares.exe
*/