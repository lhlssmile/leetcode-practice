//
// Created by 24276 on 2025/8/19.
//
#include <vector>
#include <unordered_map>
using namespace std;
#define V vector
typedef unordered_map<int, int> uii;
// key V<int> mp key:digitSum
typedef long long ll;
int digitSum (int a) {
    int s = 0;
    while (a > 0) {
        s += a % 10;
        a /= 10;
    }
    return s;
}
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef unordered_map<int, int> uii;
typedef long long ll;

inline int digitSum(int a) {
    int s = 0;
    while (a > 0) {
        s += a % 10;
        a /= 10;
    }
    return s;
}

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted_nums = nums;

        // 自定义排序
        sort(sorted_nums.begin(), sorted_nums.end(), [](int a, int b) {
            int s_a = digitSum(a), s_b = digitSum(b);
            if (s_a != s_b) return s_a < s_b;
            return a < b;
        });

        // 映射值到目标位置
        uii mp;
        for (int i = 0; i < n; i++) {
            mp[sorted_nums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        // 置换分解
        for (int i = 0; i < n; i++) {
            if (visited[i] || mp[nums[i]] == i) continue;
            int cycle_len = 0, j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = mp[nums[j]];
                cycle_len++;
            }
            swaps += cycle_len - 1;
        }
        return swaps;
    }
};


int main() {
    Solution s;
    V<int> nums = {18, 43, 34, 16};
    s.minSwaps(nums);
    return 0;
}
