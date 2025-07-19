#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

#define V vector
#define pb push_back

class Solution {
public:
    // 方法1：使用小根堆（推荐）
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 统计频率
        unordered_map<int, int> count;
        for (int num : nums) {
            ++count[num];
        }
        
        // 使用小根堆维护前k个高频元素
        // pair<频率, 元素值>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        
        for (auto& p : count) {
            minHeap.push({p.second, p.first}); // {频率, 元素}
            if (minHeap.size() > k) {
                minHeap.pop(); // 弹出频率最小的
            }
        }
        
        vector<int> ans;
        while (!minHeap.empty()) {
            ans.pb(minHeap.top().second);
            minHeap.pop();
        }
        
        return ans;
    }
    
    // 方法2：使用大根堆
    vector<int> topKFrequent2(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            ++count[num];
        }
        
        // 使用大根堆，按频率排序
        priority_queue<pair<int, int>> maxHeap; // pair<频率, 元素值>
        
        for (auto& p : count) {
            maxHeap.push({p.second, p.first});
        }
        
        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            ans.pb(maxHeap.top().second);
            maxHeap.pop();
        }
        
        return ans;
    }
    
    // 方法3：使用桶排序（最优解）
    vector<int> topKFrequent3(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            ++count[num];
        }
        
        // 桶排序：频率作为索引
        vector<vector<int>> bucket(nums.size() + 1);
        for (auto& p : count) {
            bucket[p.second].pb(p.first);
        }
        
        vector<int> ans;
        // 从高频率到低频率遍历
        for (int i = bucket.size() - 1; i >= 0 && ans.size() < k; --i) {
            for (int num : bucket[i]) {
                ans.pb(num);
                if (ans.size() == k) break;
            }
        }
        
        return ans;
    }
};

// 测试函数
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1
    vector<int> nums1 = {1, 1, 1, 2, 2, 3,4,4,3,2,1,2,5,6,6,7,7,7,7};
    int k1 = 2;
    cout << "测试用例1: nums = [1,1,1,2,2,3], k = 2" << endl;
    
    auto result1_1 = solution.topKFrequent(nums1, k1);
    cout << "方法1（小根堆）: ";
    printVector(result1_1);
    
    auto result1_2 = solution.topKFrequent2(nums1, k1);
    cout << "方法2（大根堆）: ";
    printVector(result1_2);
    
    auto result1_3 = solution.topKFrequent3(nums1, k1);
    cout << "方法3（桶排序）: ";
    printVector(result1_3);
    
    cout << endl;
    
    // 测试用例2
    vector<int> nums2 = {1};
    int k2 = 1;
    cout << "测试用例2: nums = [1], k = 1" << endl;
    
    auto result2_1 = solution.topKFrequent(nums2, k2);
    cout << "方法1（小根堆）: ";
    printVector(result2_1);
    
    auto result2_2 = solution.topKFrequent2(nums2, k2);
    cout << "方法2（大根堆）: ";
    printVector(result2_2);
    
    auto result2_3 = solution.topKFrequent3(nums2, k2);
    cout << "方法3（桶排序）: ";
    printVector(result2_3);
    
    return 0;
}

/*
题目分析：前K个高频元素

核心思路：
1. 统计每个元素的频率
2. 找出频率前K高的元素

三种解法对比：

方法1：小根堆（推荐）
- 时间复杂度：O(n log k)
- 空间复杂度：O(n + k)
- 优点：空间效率高，只维护k个元素的堆
- 核心：维护大小为k的小根堆，堆顶是第k大的频率

方法2：大根堆
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)
- 优点：思路简单直观
- 缺点：需要存储所有元素，空间开销大

方法3：桶排序（最优）
- 时间复杂度：O(n)
- 空间复杂度：O(n)
- 优点：线性时间复杂度
- 核心：频率作为桶的索引，从高频到低频遍历

关键洞察：
1. 小根堆维护前K大：堆顶是第K大的元素
2. 桶排序利用频率范围有限的特点
3. 频率统计是所有方法的基础步骤

面试建议：
- 首选小根堆解法（平衡了时间和空间）
- 可以提及桶排序作为优化方案
- 注意堆中存储的是(频率, 元素)对
*/