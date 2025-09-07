#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * LeetCode 1854. 人口最多的年份
 * 
 * 给你一个二维整数数组 logs，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。
 * 年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在区间 [birthi, deathi - 1] 内。
 * 注意，人在死亡当年不被计入人口内。
 * 返回 人口最多 的年份。
 * 
 * 算法思路：差分数组
 * 1. 使用差分数组记录每年人口变化
 * 2. 出生年份+1，死亡年份-1
 * 3. 通过前缀和还原每年实际人口
 * 4. 找到人口最多的年份
 * 
 * 时间复杂度：O(n + 101) = O(n)
 * 空间复杂度：O(101) = O(1)
 */

class Solution {
public:
    // 差分数组解法
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> diff(101, 0);  // 1950-2050年的差分数组
        
        // 构建差分数组
        for (const auto& log : logs) {
            int birth = log[0], death = log[1];
            diff[birth - 1950] += 1;   // 出生年份人口+1
            diff[death - 1950] -= 1;   // 死亡年份人口-1
        }
        
        int maxPop = 0, year = 1950, curr = 0;
        
        // 通过前缀和还原实际人口，同时找最大值
        for (int i = 0; i < 101; i++) {
            curr += diff[i];
            if (curr > maxPop) {
                maxPop = curr;
                year = 1950 + i;
            }
        }
        
        return year;
    }
    
    // 暴力解法（用于对比）
    int maximumPopulationBruteForce(vector<vector<int>>& logs) {
        int maxPop = 0, resultYear = 1950;
        
        // 枚举每一年
        for (int year = 1950; year <= 2050; year++) {
            int population = 0;
            
            // 统计这一年的人口
            for (const auto& log : logs) {
                int birth = log[0], death = log[1];
                if (year >= birth && year < death) {
                    population++;
                }
            }
            
            // 更新最大人口年份
            if (population > maxPop) {
                maxPop = population;
                resultYear = year;
            }
        }
        
        return resultYear;
    }
    
    // 优化版本：使用事件排序
    int maximumPopulationEvents(vector<vector<int>>& logs) {
        vector<pair<int, int>> events;  // {年份, 变化量}
        
        // 收集所有事件
        for (const auto& log : logs) {
            events.push_back({log[0], 1});   // 出生事件
            events.push_back({log[1], -1});  // 死亡事件
        }
        
        // 按年份排序，同年份死亡事件在前
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) {
                return a.second < b.second;  // 死亡事件(-1)在出生事件(1)前
            }
            return a.first < b.first;
        });
        
        int maxPop = 0, resultYear = 1950, currentPop = 0;
        
        // 处理事件
        for (const auto& event : events) {
            currentPop += event.second;
            if (currentPop > maxPop) {
                maxPop = currentPop;
                resultYear = event.first;
            }
        }
        
        return resultYear;
    }
};

// 测试函数
void testMaximumPopulation() {
    Solution solution;
    
    // 测试用例1
    vector<vector<int>> logs1 = {{1950, 1961}, {1960, 1971}, {1970, 1981}};
    cout << "测试用例1: " << solution.maximumPopulation(logs1) << endl;  // 期望: 1960
    cout << "暴力解法: " << solution.maximumPopulationBruteForce(logs1) << endl;
    cout << "事件解法: " << solution.maximumPopulationEvents(logs1) << endl;
    
    // 测试用例2
    vector<vector<int>> logs2 = {{1993, 1999}, {2000, 2010}};
    cout << "测试用例2: " << solution.maximumPopulation(logs2) << endl;  // 期望: 1993
    
    // 测试用例3：边界情况
    vector<vector<int>> logs3 = {{1950, 1951}, {1951, 1952}, {1952, 1953}};
    cout << "测试用例3: " << solution.maximumPopulation(logs3) << endl;  // 期望: 1950
    
    // 测试用例4：重叠区间
    vector<vector<int>> logs4 = {{1950, 1960}, {1955, 1965}, {1958, 1968}};
    cout << "测试用例4: " << solution.maximumPopulation(logs4) << endl;  // 期望: 1958
}

int main() {
    testMaximumPopulation();
    return 0;
}

/*
算法特点分析：

1. 差分数组解法 (推荐)
   - 时间复杂度：O(n + 101)
   - 空间复杂度：O(101)
   - 适用于区间更新问题
   - 代码简洁，效率高

2. 暴力解法
   - 时间复杂度：O(101 * n)
   - 空间复杂度：O(1)
   - 思路直观，但效率较低

3. 事件排序解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 适用于年份范围很大的情况
   - 处理离散化问题

C++特性应用：
- STL容器：vector, pair
- 算法库：sort
- Lambda表达式：自定义排序
- 引用传递：避免拷贝开销
- const关键字：保证数据安全
- 范围for循环：简化代码
*/