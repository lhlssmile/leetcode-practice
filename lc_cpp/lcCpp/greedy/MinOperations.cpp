/**
 * 给你一个大小为 n 的 非负 整数数组 nums 。你的任务是对该数组执行若干次（可能为 0 次）操作，使得 所有 元素都变为 0。

在一次操作中，你可以选择一个子数组 [i, j]（其中 0 <= i <= j < n），将该子数组中所有 最小的非负整数 的设为 0。

返回使整个数组变为 0 所需的最少操作次数。

一个 子数组 是数组中的一段连续元素。
 

示例 1：

输入: nums = [0,2]

输出: 1

解释:

选择子数组 [1,1]（即 [2]），其中最小的非负整数是 2。将所有 2 设为 0，结果为 [0,0]。
因此，所需的最少操作次数为 1。
示例 2：

输入: nums = [3,1,2,1]

输出: 3

解释:

选择子数组 [1,3]（即 [1,2,1]），最小非负整数是 1。将所有 1 设为 0，结果为 [3,0,2,0]。
选择子数组 [2,2]（即 [2]），将 2 设为 0，结果为 [3,0,0,0]。
选择子数组 [0,0]（即 [3]），将 3 设为 0，结果为 [0,0,0,0]。
因此，最少操作次数为 3。
示例 3：

输入: nums = [1,2,1,2,1,2]

输出: 4

解释:

选择子数组 [0,5]（即 [1,2,1,2,1,2]），最小非负整数是 1。将所有 1 设为 0，结果为 [0,2,0,2,0,2]。
选择子数组 [1,1]（即 [2]），将 2 设为 0，结果为 [0,0,0,2,0,2]。
选择子数组 [3,3]（即 [2]），将 2 设为 0，结果为 [0,0,0,0,0,2]。
选择子数组 [5,5]（即 [2]），将 2 设为 0，结果为 [0,0,0,0,0,0]。
因此，最少操作次数为 4。
 

提示:

1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
 */
#include <bits/stdc++.h>
using namespace std;

// 从mylib.h中提取需要的模板
#define ALL(v) (v).begin(), (v).end()
#define For(i, _) for (int i = 0, i##end = (_); i < i##end; ++i)
#define FOR(i, a, b) for (int i = (a), i##end = (b); i < i##end; ++i)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef vector<int> vi;

// 输入输出加速
int fastio_init = [](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // 使用map记录每个数字出现的位置
        map<int, vector<int>> pos;
        For(i, n) {
            if (nums[i] > 0) {
                pos[nums[i]].pb(i);
            }
        }
        
        int operations = 0;
        // 从小到大处理每个数字
        for (auto& [val, positions] : pos) {
            // 对于每个数字，找到所有连续的位置
            vector<pair<int, int>> ranges;
            int start = positions[0];
            int end = start;
            
            FOR(i, 1, positions.size()) {
                if (positions[i] == end + 1) {
                    end = positions[i];
                } else {
                    ranges.pb({start, end});
                    start = positions[i];
                    end = start;
                }
            }
            ranges.pb({start, end});
            
            // 处理每个连续范围
            for (auto& [s, e] : ranges) {
                // 检查这个范围是否是一个有效的子数组
                bool valid = true;
                FOR(i, s, e + 1) {
                    if (nums[i] < val) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    operations++;
                    // 将这个范围内的val都设为0
                    FOR(i, s, e + 1) {
                        if (nums[i] == val) {
                            nums[i] = 0;
                        }
                    }
                }
            }
        }
        
        return operations;
    }
};

int main() {
    Solution solution;
    
    // 测试用例1
    vector<int> nums1 = {0, 2};
    cout << "测试用例1 [0,2] 的结果: " << solution.minOperations(nums1) << endl;
    
    // 测试用例2
    vector<int> nums2 = {3, 1, 2, 1};
    cout << "测试用例2 [3,1,2,1] 的结果: " << solution.minOperations(nums2) << endl;
    
    // 测试用例3
    vector<int> nums3 = {1, 2, 1, 2, 1, 2};
    cout << "测试用例3 [1,2,1,2,1,2] 的结果: " << solution.minOperations(nums3) << endl;
    
    return 0;
}
