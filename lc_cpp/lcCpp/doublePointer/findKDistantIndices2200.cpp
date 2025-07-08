/**
* 给你一个下标从 0 开始的整数数组 nums 和两个整数 key 和 k 。K 近邻下标 是 nums 中的一个下标 i ，并满足至少存在一个下标 j 使得 |i - j| <= k 且 nums[j] == key 。

以列表形式返回按 递增顺序 排序的所有 K 近邻下标。



示例 1：

输入：nums = [3,4,9,1,3,9,5], key = 9, k = 1
输出：[1,2,3,4,5,6]
解释：因此，nums[2] == key 且 nums[5] == key 。
- 对下标 0 ，|0 - 2| > k 且 |0 - 5| > k ，所以不存在 j 使得 |0 - j| <= k 且 nums[j] == key 。所以 0 不是一个 K 近邻下标。
- 对下标 1 ，|1 - 2| <= k 且 nums[2] == key ，所以 1 是一个 K 近邻下标。
- 对下标 2 ，|2 - 2| <= k 且 nums[2] == key ，所以 2 是一个 K 近邻下标。
- 对下标 3 ，|3 - 2| <= k 且 nums[2] == key ，所以 3 是一个 K 近邻下标。
- 对下标 4 ，|4 - 5| <= k 且 nums[5] == key ，所以 4 是一个 K 近邻下标。
- 对下标 5 ，|5 - 5| <= k 且 nums[5] == key ，所以 5 是一个 K 近邻下标。
- 对下标 6 ，|6 - 5| <= k 且 nums[5] == key ，所以 6 是一个 K 近邻下标。
因此，按递增顺序返回 [1,2,3,4,5,6] 。
示例 2：

输入：nums = [2,2,2,2,2], key = 2, k = 2
输出：[0,1,2,3,4]
解释：对 nums 的所有下标 i ，总存在某个下标 j 使得 |i - j| <= k 且 nums[j] == key ，所以每个下标都是一个 K 近邻下标。
因此，返回 [0,1,2,3,4] 。
*/

#define V vector
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class find_k_distant_indices2200 {
public:
    /*
    解题思路：
    1. 题目要求找到所有K近邻下标i，满足存在下标j使得|i-j|<=k且nums[j]==key
    2. 可以分两步：
       - 第一步：找到所有nums[j]==key的位置j
       - 第二步：对每个这样的j，将[j-k, j+k]范围内的所有有效下标都加入结果
    3. 为了避免重复，可以用set或者boolean数组来标记
    
    方法一：暴力法 - 对每个i检查是否存在满足条件的j
    时间复杂度：O(n²)，空间复杂度：O(1)
    
    方法二：优化法 - 先找key位置，再扩展范围
    时间复杂度：O(n)，空间复杂度：O(n)
    */

    //case when i < j: j - i <= k -> i >= j - k
    //case when i > j: i - j <= k -> i <= j + k

    // 方法一：暴力法（简单直观）
    static vector<int> findKDistantIndices_bruteforce(V<int>& nums, int key, int k) {
        V<int> res;
        int n = nums.size();
        
        // 对每个下标i，检查是否存在j使得|i-j|<=k且nums[j]==key
        for (int i = 0; i < n; i++) {
            bool found = false;
            // 检查所有可能的j
            for (int j = 0; j < n; j++) {
                if (nums[j] == key && abs(i - j) <= k) {
                    found = true;
                    break;
                }
            }
            if (found) {
                res.push_back(i);
            }
        }
        return res;
    }
    
    // 方法二：优化法（推荐）
    static vector<int> findKDistantIndices(V<int>& nums, int key, int k) {
        V<int> keyIndices; // 存储所有key的位置
        int n = nums.size();
        
        // 第一步：找到所有key的位置
        for (int i = 0; i < n; i++) {
            if (nums[i] == key) {
                keyIndices.push_back(i);
            }
        }
        
        // 第二步：用boolean数组标记K近邻下标，避免重复
        vector<bool> isKDistant(n, false);
        
        // 对每个key位置，标记其k距离内的所有位置
        for (int keyPos : keyIndices) {
            // 计算范围[left, right]
            int left = max(0, keyPos - k);
            int right = min(n - 1, keyPos + k);
            
            // 标记范围内的所有位置
            for (int i = left; i <= right; i++) {
                isKDistant[i] = true;
            }
        }
        
        // 第三步：收集所有标记为true的下标
        V<int> res;
        for (int i = 0; i < n; i++) {
            if (isKDistant[i]) {
                res.push_back(i);
            }
        }
        
        return res; // 结果天然有序，因为是按下标顺序添加的
    }
    
    // 方法三：进一步优化（双指针思想）
    static vector<int> findKDistantIndices_optimized(V<int>& nums, int key, int k) {
        V<int> keyIndices;
        int n = nums.size();
        
        // 找到所有key的位置
        for (int i = 0; i < n; i++) {
            if (nums[i] == key) {
                keyIndices.push_back(i);
            }
        }
        
        if (keyIndices.empty()) return {};
        
        V<int> res;
        int keyIdx = 0; // 指向当前考虑的key位置
        
        for (int i = 0; i < n; i++) {
            // 移动keyIdx到第一个可能影响位置i的key
            while (keyIdx < keyIndices.size() && keyIndices[keyIdx] < i - k) {
                keyIdx++;
            }
            
            // 检查是否存在key在k距离内
            if (keyIdx < keyIndices.size() && keyIndices[keyIdx] <= i + k) {
                res.push_back(i);
            }
        }
        
        return res;
    }
};

int main() {
    find_k_distant_indices2200 ps;
    V<int> nums = {3,4,9,1,3,9,5};
    int k = 1,key = 9;
    auto res = ps.findKDistantIndices_optimized(nums,key,k);
    for (int ele : res) {
        std::cout << ele << " ";
    }
    return 0;
}
