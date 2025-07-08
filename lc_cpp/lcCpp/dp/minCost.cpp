//
// Created by 24276 on 2025/7/5.
//
/**
 * 给你两个整数 m 和 n，分别表示网格的行数和列数。

进入单元格 (i, j) 的成本定义为 (i + 1) * (j + 1)。

另外给你一个二维整数数组 waitCost，其中 waitCost[i][j] 定义了在该单元格 等待 的成本。

你从第 1 秒开始在单元格 (0, 0)。

每一步，你都遵循交替模式：

在 奇数秒 ，你必须向 右 或向 下 移动到 相邻 的单元格，并支付其进入成本。
在 偶数秒 ，你必须原地 等待 ，并支付 waitCost[i][j]。
返回到达 (m - 1, n - 1) 所需的 最小 总成本。

 

示例 1：

输入：m = 1, n = 2, waitCost = [[1,2]]

输出：3

解释：

最佳路径为：

从第 1 秒开始在单元格 (0, 0)，进入成本为 (0 + 1) * (0 + 1) = 1。
第 1 秒：向右移动到单元格 (0, 1)，进入成本为 (0 + 1) * (1 + 1) = 2。
因此，总成本为 1 + 2 = 3。

示例 2：

输入：m = 2, n = 2, waitCost = [[3,5],[2,4]]

输出：9

解释：

最佳路径为：

从第 1 秒开始在单元格 (0, 0)，进入成本为 (0 + 1) * (0 + 1) = 1。
第 1 秒：向下移动到单元格 (1, 0)，进入成本为 (1 + 1) * (0 + 1) = 2。
第 2 秒：在单元格 (1, 0) 等待，支付 waitCost[1][0] = 2。
第 3 秒：向右移动到单元格 (1, 1)，进入成本为 (1 + 1) * (1 + 1) = 4。
因此，总成本为 1 + 2 + 2 + 4 = 9。

示例 3：

输入：m = 2, n = 3, waitCost = [[6,1,4],[3,2,5]]

输出：16

解释：

最佳路径为：

从第 1 秒开始在单元格 (0, 0)，进入成本为 (0 + 1) * (0 + 1) = 1。
第 1 秒：向右移动到单元格 (0, 1)，进入成本为 (0 + 1) * (1 + 1) = 2。
第 2 秒：在单元格 (0, 1) 等待，支付 waitCost[0][1] = 1。
第 3 秒：向下移动到单元格 (1, 1)，进入成本为 (1 + 1) * (1 + 1) = 4。
第 4 秒：在单元格 (1, 1) 等待，支付 waitCost[1][1] = 2。
第 5 秒：向右移动到单元格 (1, 2)，进入成本为 (1 + 1) * (2 + 1) = 6。
因此，总成本为 1 + 2 + 1 + 4 + 2 + 6 = 16。

 

提示：

1 <= m, n <= 105
2 <= m * n <= 105
waitCost.length == m
waitCost[0].length == n
0 <= waitCost[i][j] <= 105©leetcode
 * 
 */
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
class Solution{
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        // dp[i][j][0] 表示在偶数秒结束时在(i,j)的最小成本
        // dp[i][j][1] 表示在奇数秒结束时在(i,j)的最小成本
        vector<vector<vector<long long>>> dp(m, vector<vector<long long>>(n, vector<long long>(2, LLONG_MAX)));
        
        // 初始状态：开始时在(0,0)，支付进入成本1
        dp[0][0][1] = 1; // 第1秒结束时在(0,0)，成本为1
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 从奇数秒结束状态转移到偶数秒结束状态（等待）
                if (dp[i][j][1] != LLONG_MAX) {
                    dp[i][j][0] = min(dp[i][j][0], dp[i][j][1] + waitCost[i][j]);
                }
                
                // 从偶数秒结束状态转移到奇数秒结束状态（移动）
                if (dp[i][j][0] != LLONG_MAX) {
                    // 向右移动
                    if (j + 1 < n) {
                        long long enterCost = (long long)(i + 1) * (j + 2);
                        dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][0] + enterCost);
                    }
                    // 向下移动
                    if (i + 1 < m) {
                        long long enterCost = (long long)(i + 2) * (j + 1);
                        dp[i + 1][j][1] = min(dp[i + 1][j][1], dp[i][j][0] + enterCost);
                    }
                }
            }
        }
        
        // 返回到达(m-1, n-1)的最小成本
        return min(dp[m-1][n-1][0], dp[m-1][n-1][1]);
    }
};

int main() {
    Solution solution;
    
    // 测试示例1
    vector<vector<int>> waitCost1 = {{1, 2}};
    long long result1 = solution.minCost(1, 2, waitCost1);
    cout << "Example 1 (m=1, n=2): " << result1 << endl;
    cout << "Expected: 3" << endl << endl;
    
    // 测试示例2
    vector<vector<int>> waitCost2 = {{3, 5}, {2, 4}};
    long long result2 = solution.minCost(2, 2, waitCost2);
    cout << "Example 2 (m=2, n=2): " << result2 << endl;
    cout << "Expected: 9" << endl << endl;
    
    // 测试示例3
    vector<vector<int>> waitCost3 = {{6, 1, 4}, {3, 2, 5}};
    long long result3 = solution.minCost(2, 3, waitCost3);
    cout << "Example 3 (m=2, n=3): " << result3 << endl;
    cout << "Expected: 16" << endl;
    
    return 0;
}