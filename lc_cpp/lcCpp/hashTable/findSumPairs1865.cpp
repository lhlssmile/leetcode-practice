//
// Created by 24276 on 2025/7/6.
//
/**
* 给你两个整数数组 nums1 和 nums2 ，请你实现一个支持下述两类查询的数据结构：

累加 ，将一个正整数加到 nums2 中指定下标对应元素上。
计数 ，统计满足 nums1[i] + nums2[j] 等于指定值的下标对 (i, j) 数目（0 <= i < nums1.length 且 0 <= j < nums2.length）。
实现 FindSumPairs 类：

FindSumPairs(int[] nums1, int[] nums2) 使用整数数组 nums1 和 nums2 初始化 FindSumPairs 对象。
void add(int index, int val) 将 val 加到 nums2[index] 上，即，执行 nums2[index] += val 。
int count(int tot) 返回满足 nums1[i] + nums2[j] == tot 的下标对 (i, j) 数目。


示例：

输入：
["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
[[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
输出：
[null, 8, null, 2, 1, null, null, 11]

解释：
FindSumPairs findSumPairs = new FindSumPairs([1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]);
findSumPairs.count(7);  // 返回 8 ; 下标对 (2,2), (3,2), (4,2), (2,4), (3,4), (4,4) 满足 2 + 5 = 7 ，下标对 (5,1), (5,5) 满足 3 + 4 = 7
findSumPairs.add(3, 2); // 此时 nums2 = [1,4,5,4,5,4]
findSumPairs.count(8);  // 返回 2 ；下标对 (5,2), (5,4) 满足 3 + 5 = 8
findSumPairs.count(4);  // 返回 1 ；下标对 (5,0) 满足 3 + 1 = 4
findSumPairs.add(0, 1); // 此时 nums2 = [2,4,5,4,5,4]
findSumPairs.add(1, 1); // 此时 nums2 = [2,5,5,4,5,4]
findSumPairs.count(7);  // 返回 11 ；下标对 (2,1), (2,2), (2,4), (3,1), (3,2), (3,4), (4,1), (4,2), (4,4) 满足 2 + 5 = 7 ，下标对 (5,3), (5,5) 满足 3 + 4 = 7


提示：

1 <= nums1.length <= 1000
1 <= nums2.length <= 105
1 <= nums1[i] <= 109
1 <= nums2[i] <= 105
0 <= index < nums2.length
1 <= val <= 105
1 <= tot <= 109
最多调用 add 和 count 函数各 1000 次
*/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class FindSumPairs {
private:
    vector<int> nums1;
    vector<int> nums2;
    unordered_map<int, int> nums1_freq;  // nums1的值频率映射
    unordered_map<int, int> nums2_freq;  // nums2的值频率映射

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this->nums1 = nums1;
        this->nums2 = nums2;

        // 统计nums1中每个值的频率（nums1不会改变）
        for (int num : nums1) {
            nums1_freq[num]++;
        }

        // 统计nums2中每个值的频率
        for (int num : nums2) {
            nums2_freq[num]++;
        }
    }

    void add(int index, int val) {
        // 更新nums2_freq：先减少旧值频率，再增加新值频率
        int oldVal = nums2[index];
        nums2_freq[oldVal]--;
        if (nums2_freq[oldVal] == 0) {
            nums2_freq.erase(oldVal);
        }

        // 更新nums2数组
        nums2[index] += val;
        int newVal = nums2[index];
        nums2_freq[newVal]++;
    }

    int count(int tot) {
        int result = 0;

        // 对于nums1中的每个值，查找nums2中需要的补数
        for (auto& [val1, freq1] : nums1_freq) {
            int target = tot - val1;  // 需要在nums2中找到的值

            if (nums2_freq.count(target)) {
                result += freq1 * nums2_freq[target];
            }
        }

        return result;
    }
};

int main() {
    vector<int> nums1 = {1, 1, 2, 2, 2, 3};
    vector<int> nums2 = {1, 4, 5, 2, 5, 4};

    FindSumPairs findSumPairs(nums1, nums2);

    cout << "count(7): " << findSumPairs.count(7) << endl;  // 期望: 8

    findSumPairs.add(3, 2);  // nums2 = [1,4,5,4,5,4]
    cout << "count(8): " << findSumPairs.count(8) << endl;  // 期望: 2
    cout << "count(4): " << findSumPairs.count(4) << endl;  // 期望: 1

    findSumPairs.add(0, 1);  // nums2 = [2,4,5,4,5,4]
    findSumPairs.add(1, 1);  // nums2 = [2,5,5,4,5,4]
    cout << "count(7): " << findSumPairs.count(7) << endl;  // 期望: 11

    return 0;
}