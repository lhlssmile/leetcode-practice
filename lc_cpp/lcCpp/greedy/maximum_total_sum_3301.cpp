// 力扣第3301题：高度互不相同的最大塔高和
// 题目描述：给定一个数组 maximumHeight，求高度互不相同的最大塔高和

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    long long maximumTotalSum(vector<int>& maximumHeight) {
        sort(maximumHeight.begin(), maximumHeight.end(), greater<int>());
        int n = maximumHeight.size();
        int prev = INT_MAX;
        long long ans = 0;
        for (int h : maximumHeight) {
            // 如果这个值和下一个值一样 让其减1直接修改数组
            int curr = min(h, prev - 1);
            if (curr <= 0) return -1;
            ans += curr;
            prev = curr;
        }
        return ans;
    }
};

// 测试代码
#include <iostream>

void testMaximumTotalSum() {
    // 测试用例1
    vector<int> heights1 = {5, 3, 4, 1, 1};
    Solution sol1;
    cout << "Test Case 1: " << sol1.maximumTotalSum(heights1) << endl; // 预期输出：13
    
    // 测试用例2
    vector<int> heights2 = {6, 5, 3, 9, 2, 7};
    Solution sol2;
    cout << "Test Case 2: " << sol2.maximumTotalSum(heights2) << endl; // 预期输出：29
    
    // 测试用例3
    vector<int> heights3 = {3, 2, 1};
    Solution sol3;
    cout << "Test Case 3: " << sol3.maximumTotalSum(heights3) << endl; // 预期输出：6
}

// 主函数
int main() {
    testMaximumTotalSum();
    return 0;
}