#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

/**
 * @brief LeetCode 1399. 统计最大组的数目
 *
 * 给你一个整数 n。
 * 请你先求出从 1 到 n 的每个整数 10 进制表示下的数位和（每一位上的数字相加）。
 * 然后把数位和相等的数字放到同一个组中。
 * 请你统计每个组中的数字数目，并返回数字数目并列最多的组有多少个。
 *
 * 示例 1：
 * 输入：n = 13
 * 输出：4
 * 解释：数位和为 1 的有 1、10，数位和为 2 的有 2、11，数位和为 3 的有 3、12，数位和为 4 的有 4、13，以此类推。
 * 共有 9 个组，将数位和相同的数字分为同一组：
 * [1, 10], [2, 11], [3, 12], [4, 13], [5], [6], [7], [8], [9]
 * 最多的组是数位和为 1, 2, 3, 4 的组，每个组中有 2 个数。
 * 所以最终答案是 4。
 *
 * 解题思路：
 * 使用数位 DP (Digit DP) 来解决。
 * 目标是计算对于每个可能的数位和 `target` (1 到 36，因为 n <= 10000，最大数位和是 9+9+9+9=36)，
 * 有多少个小于等于 n 的数字，其数位和等于 `target`。
 * 然后找到出现次数最多的数位和，并统计有多少个这样的数位和。
 */
class countLargestGroup1399 {
    // dp[pos][sum][tight]
    // pos: 当前处理到的数字位数（从左到右，0-indexed）
    // sum: 当前已经累加的数位和
    // tight: 布尔值，表示当前是否受到 n 的约束。
    //        true 表示当前位最大只能取到 digits[pos]，false 表示可以取到 9。
    // dp 值: 满足条件的数字个数
    int dp[5][37][2]; // n <= 10000，最多 5 位。最大数位和 9*4=36。
    vector<int> digits; // 存储 n 的每一位数字

public:
    /**
     * @brief 计算数字数目并列最多的组有多少个
     * @param n 上限整数
     * @return 数字数目并列最多的组的数量
     */
    int countLargestGroup(int n) {
        digits.clear();
        string s = to_string(n);
        for(char c : s){
            digits.push_back(c - '0');
        }

        int max_count = 0; // 记录最大的组内数字数目
        int ans = 0;       // 记录拥有最大数字数目的组的数量

        // 遍历所有可能的数位和 target (1 到 36)
        for (int target = 1; target <= 36; ++target) {
            memset(dp, -1, sizeof(dp)); // 每次计算新的 target 时重置 dp 数组
            int cnt = dfs(0, 0, true, target); // 计算数位和为 target 的数字个数

            if (cnt > max_count) { // 如果当前 target 的计数超过了之前的最大计数
                ans = 1;           // 重置答案为 1
                max_count = cnt;   // 更新最大计数
            } else if (cnt > 0 && cnt == max_count) { // 如果当前 target 的计数等于最大计数（且大于0）
                ans += 1;          // 答案加 1
            }
        }
        return ans;
    }

private:
    /**
     * @brief 数位 DP 的核心函数 (深度优先搜索)
     * @param pos 当前处理到的数字位数 (从左到右, 0-indexed)
     * @param sum 当前累加的数位和
     * @param tight 是否受到 n 的约束 (true 表示当前位最大只能取 digits[pos])
     * @param target 目标数位和
     * @return 从当前状态出发，能够构成数位和为 target 的数字个数
     */
    int dfs(int pos, int sum, bool tight, int target) {
        // 基本情况：所有位数都处理完毕
        if (pos == digits.size()) {
            return sum == target ? 1 : 0; // 如果数位和等于目标，返回 1，否则返回 0
        }

        // 记忆化搜索：如果当前状态已经计算过，直接返回结果
        // 注意：只有在 tight 为 false 时才能复用 dp 结果，因为 tight 为 true 时依赖于具体的 n
        // 但这里为了简化，将 tight 也作为状态的一部分，所以可以直接检查 dp[pos][sum][tight]
        if (dp[pos][sum][tight] != -1) {
            return dp[pos][sum][tight];
        }

        long long res = 0;
        // 确定当前位能取的最大数字 up
        int up = tight ? digits[pos] : 9;

        // 遍历当前位所有可能的数字 d (从 0 到 up)
        for (int d = 0; d <= up; ++d) {
            // 剪枝：如果当前和加上 d 已经超过 target，则后续无需继续
            // （虽然这里没加，但可以优化。不过对于 n<=10000 影响不大）
            if (sum + d > target) continue; // 优化：如果当前和加上可能的最小值（0）已经超过目标，则无需继续
                                        // 但这里是 d，所以是 sum + d > target

            // 递归计算下一位的状态
            // 下一位的 tight 状态：当且仅当当前位是 tight 且选择了最大值 up 时，下一位仍然是 tight
            res += dfs(pos + 1, sum + d, tight && (d == up), target);
        }

        // 存储结果到 dp 数组并返回
        return dp[pos][sum][tight] = res;
    }
};

// 主函数用于测试
int main() {
    countLargestGroup1399 sol;
    cout << sol.countLargestGroup(13) << endl; // 输出 4
    cout << sol.countLargestGroup(2) << endl;  // 输出 2
    cout << sol.countLargestGroup(1) << endl;  // 输出 1
    cout << sol.countLargestGroup(46) << endl; // 输出 6
    return 0;
}