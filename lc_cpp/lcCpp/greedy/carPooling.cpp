// C++版本 - 拼车问题 (LeetCode 1094)
// 使用差分数组或事件排序解决

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    // 方法1: 事件排序法
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<pair<int, int>> events;
        
        // 构建事件列表
        for (const auto& trip : trips) {
            int passengers = trip[0], from = trip[1], to = trip[2];
            events.push_back({from, passengers});   // 上车事件
            events.push_back({to, -passengers});    // 下车事件
        }
        
        // 排序事件：先按位置，再按变化量（下车优先）
        sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });
        
        int currentPassengers = 0;
        
        // 处理所有事件
        for (const auto& [location, change] : events) {
            currentPassengers += change;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
    
    // 方法2: 差分数组法（适用于位置范围较小的情况）
    bool carPoolingDiffArray(vector<vector<int>>& trips, int capacity) {
        map<int, int> diff;
        
        // 构建差分数组
        for (const auto& trip : trips) {
            int passengers = trip[0], from = trip[1], to = trip[2];
            diff[from] += passengers;
            diff[to] -= passengers;
        }
        
        int currentPassengers = 0;
        
        // 按位置顺序处理
        for (const auto& [pos, change] : diff) {
            currentPassengers += change;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
};

int main() {
    Solution solution;
    
    // 测试用例
    vector<vector<vector<int>>> testCases = {
        {{2,1,5},{3,3,7}},      // capacity = 4, expected: false
        {{2,1,5},{3,3,7}},      // capacity = 5, expected: true
        {{2,1,5},{3,5,7}},      // capacity = 3, expected: true
        {{3,2,7},{3,7,9},{8,3,9}} // capacity = 11, expected: true
    };
    
    vector<int> capacities = {4, 5, 3, 11};
    vector<bool> expected = {false, true, true, true};
    
    cout << "=== 拼车问题测试 ===" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        auto trips = testCases[i];
        int capacity = capacities[i];
        
        bool result1 = solution.carPooling(trips, capacity);
        bool result2 = solution.carPoolingDiffArray(trips, capacity);
        
        cout << "测试用例 " << (i + 1) << ": ";
        cout << "trips = [";
        for (int j = 0; j < trips.size(); j++) {
            cout << "[" << trips[j][0] << "," << trips[j][1] << "," << trips[j][2] << "]";
            if (j < trips.size() - 1) cout << ",";
        }
        cout << "], capacity = " << capacity << endl;
        cout << "事件排序法: " << (result1 ? "true" : "false") << endl;
        cout << "差分数组法: " << (result2 ? "true" : "false") << endl;
        cout << "预期结果: " << (expected[i] ? "true" : "false") << endl;
        cout << "结果: " << (result1 == expected[i] && result2 == expected[i] ? "✓" : "✗") << endl;
        cout << endl;
    }
    
    return 0;
}

/*
算法说明：
1. 事件排序法：
   - 将每个行程转换为上车和下车事件
   - 按位置排序，同位置时下车优先
   - 模拟整个过程，检查是否超载
   
2. 差分数组法：
   - 使用差分思想，记录每个位置的乘客变化
   - 按位置顺序累加，检查是否超载
   
时间复杂度: O(n log n)
空间复杂度: O(n)
*/