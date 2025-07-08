//
// Created by 24276 on 2025/6/30.
//
#define V vector
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>  // 添加哈希表头文件
using namespace std;
class find_lhs594 {
public:
    /*
    原代码问题分析：
    1. 滑动窗口逻辑错误：内层while循环条件不对，应该扩展窗口直到差值>1
    2. 长度计算错误：curr_res = right - left 应该是 right - left + 1
    3. 结果更新错误：res = curr_res 会覆盖之前的最大值，应该用max
    4. 窗口移动错误：left = right 跳过了可能的解
    5. 边界条件处理不完整
    */
    
    // 原始错误代码（保留用于对比）
    static int findLHS_original_buggy(vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        if (nums.begin() == nums.end() || nums.size() == 1) return 0;
        int left = 0,right = 0;
        int res = 0;
        while(right < static_cast<int>(nums.size())) {
            int curr_res = 0;
            //问题1: 这个while条件不对，应该是扩展窗口而不是检查单个条件
            while (nums[right] - nums[left] == 1) {
                curr_res = right - left; //问题2: 长度计算错误，应该+1
                ++right;
            }
            res = curr_res; //问题3: 直接赋值会覆盖最大值
            left = right;   //问题4: 跳跃式移动可能错过解
            ++right;
        }
        return res;
    }
    
    // 方法一：修正的滑动窗口（推荐）
    static int findLHS(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        
        std::sort(nums.begin(), nums.end());
        int left = 0, right = 0;
        int maxLen = 0;
        
        while (right < nums.size()) {
            // 扩展右边界，直到差值超过1
            while (right < nums.size() && nums[right] - nums[left] <= 1) {
                right++;
            }
            
            // 检查当前窗口是否是和谐子序列
            // 和谐子序列要求：最大值-最小值=1，且至少包含两种不同的数
            if (nums[right-1] - nums[left] == 1) {
                maxLen = max(maxLen, right - left); // 正确的长度计算
            }
            
            // 移动左边界到下一个不同的数
            int currentLeft = nums[left];
            while (left < nums.size() && nums[left] == currentLeft) {
                left++;
            }
        }
        
        return maxLen;
    }
    
    // 方法二：哈希表解法（更直观）
    static int findLHS_hashmap(vector<int>& nums) {
        unordered_map<int, int> count;
        
        // 统计每个数字的出现次数
        for (int num : nums) {
            count[num]++;
        }
        
        int maxLen = 0;
        // 对每个数字，检查它和它+1是否都存在
        for (auto& pair : count) {
            int num = pair.first;
            int freq = pair.second;
            
            // 如果num+1也存在，那么可以组成和谐子序列
            if (count.find(num + 1) != count.end()) {
                maxLen = max(maxLen, freq + count[num + 1]);
            }
        }
        
        return maxLen;
    }
    
    // 方法三：优化的滑动窗口（处理重复元素）
    static int findLHS_optimized(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        
        sort(nums.begin(), nums.end());
        int maxLen = 0;
        int i = 0;
        
        while (i < nums.size()) {
            int j = i;
            // 找到第一个不同的数的位置
            while (j < nums.size() && nums[j] == nums[i]) {
                j++;
            }
            
            // 如果存在下一个数且差值为1
            if (j < nums.size() && nums[j] - nums[i] == 1) {
                int k = j;
                // 找到第二个数的结束位置
                while (k < nums.size() && nums[k] == nums[j]) {
                    k++;
                }
                // 更新最大长度：第一个数的个数 + 第二个数的个数
                maxLen = max(maxLen, k - i);
            }
            
            i = j; // 移动到下一个不同的数
        }
        
        return maxLen;
    }
};

int main() {
    //ex: {1,3,2,2,5,2,3,7} -> 排序后: {1,2,2,2,3,3,5,7}
    //最长和谐子序列: [2,2,2,3,3] 长度为5
    vector<int> nums = {1,3,2,2,5,2,3,7};
    find_lhs594 solution;
    
    cout << "测试数组: ";
    for(int x : nums) cout << x << " ";
    cout << endl;
    
    // 测试原始错误代码
    vector<int> nums1 = nums;
    cout << "原始错误代码结果: " << solution.findLHS_original_buggy(nums1) << endl;
    
    // 测试修正的滑动窗口
    vector<int> nums2 = nums;
    cout << "修正滑动窗口结果: " << solution.findLHS(nums2) << endl;
    
    // 测试哈希表方法
    vector<int> nums3 = nums;
    cout << "哈希表方法结果: " << solution.findLHS_hashmap(nums3) << endl;
    
    // 测试优化滑动窗口
    vector<int> nums4 = nums;
    cout << "优化滑动窗口结果: " << solution.findLHS_optimized(nums4) << endl;
    
    cout << "\n期望结果: 5 (子序列[2,2,2,3,3])" << endl;
    
    return 0;
}
