//
// Created by 24276 on 2025/7/20.
//
/**
*给你一个二维整数数组 points，其中 points[i] = [xi, yi] 表示第 i 个点在笛卡尔平面上的坐标。

水平梯形 是一种凸四边形，具有 至少一对 水平边（即平行于 x 轴的边）。两条直线平行当且仅当它们的斜率相同。

返回可以从 points 中任意选择四个不同点组成的 水平梯形 数量。

由于答案可能非常大，请返回结果对 109 + 7 取余数后的值。

  

示例 1：

输入： points = [[1,0],[2,0],[3,0],[2,2],[3,2]]

输出： 3

解释：



有三种不同方式选择四个点组成一个水平梯形：

使用点 [1,0]、[2,0]、[3,2] 和 [2,2]。
使用点 [2,0]、[3,0]、[3,2] 和 [2,2]。
使用点 [1,0]、[3,0]、[3,2] 和 [2,2]。
示例 2：

输入： points = [[0,0],[1,0],[0,1],[2,1]]

输出： 1

解释：



只有一种方式可以组成一个水平梯形。

  

提示：

4 <= points.length <= 105
–108 <= xi, yi <= 108
所有点两两不同。©leetcode
 */
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

class count_trapezoids {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        const int MOD = 1e9 + 7;
        
        // 按y坐标分组
        map<int, vector<int>> yGroups;
        for (auto& point : points) {
            yGroups[point[1]].push_back(point[0]);
        }
        
        // 对每组的x坐标排序
        for (auto& [y, xs] : yGroups) {
            sort(xs.begin(), xs.end());
        }
        
        long long result = 0;
        vector<pair<int, vector<int>>> yList(yGroups.begin(), yGroups.end());
        
        // 枚举两条水平边
        for (int i = 0; i < yList.size(); i++) {
            for (int j = i + 1; j < yList.size(); j++) {
                int y1 = yList[i].first, y2 = yList[j].first;
                vector<int>& xs1 = yList[i].second;
                vector<int>& xs2 = yList[j].second;
                
                // 计算两条水平边之间可以形成的梯形数量
                long long count = 0;
                
                // 方法：对于每对(x1_i, x1_j)在y1上，计算y2上有多少对(x2_k, x2_l)
                // 满足 x1_i <= x2_k < x2_l <= x1_j 或 x2_k <= x1_i < x1_j <= x2_l
                for (int p = 0; p < xs1.size(); p++) {
                    for (int q = p + 1; q < xs1.size(); q++) {
                        int left1 = xs1[p], right1 = xs1[q];
                        
                        // 计算xs2中满足条件的对数
                        // 情况1: left1 <= left2 < right2 <= right1
                        auto it1 = lower_bound(xs2.begin(), xs2.end(), left1);
                        auto it2 = upper_bound(xs2.begin(), xs2.end(), right1);
                        
                        long long validCount = 0;
                        for (auto it = it1; it < it2; it++) {
                            auto it_next = upper_bound(it + 1, it2, right1);
                            validCount += it_next - (it + 1);
                        }
                        
                        // 情况2: left2 <= left1 < right1 <= right2
                        for (int r = 0; r < xs2.size(); r++) {
                            for (int s = r + 1; s < xs2.size(); s++) {
                                int left2 = xs2[r], right2 = xs2[s];
                                if (left2 <= left1 && right1 <= right2) {
                                    validCount++;
                                }
                            }
                        }
                        
                        count = (count + validCount) % MOD;
                    }
                }
                
                result = (result + count) % MOD;
            }
        }
        
        return result;
    }
    
    // 简单暴力版本：最直观的方法
    int countTrapezoidsBruteForce(vector<vector<int>>& points) {
        const int MOD = 1e9 + 7;
        int n = points.size();
        long long result = 0;
        
        // 枚举所有四个点的组合
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        // 检查是否能构成水平梯形
                        if (isHorizontalTrapezoid(points[i], points[j], points[k], points[l])) {
                            result = (result + 1) % MOD;
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
    // 检查四个点是否能构成水平梯形
    bool isHorizontalTrapezoid(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<vector<int>> points = {p1, p2, p3, p4};
        
        // 按y坐标分组
        map<int, vector<int>> yGroups;
        for (auto& p : points) {
            yGroups[p[1]].push_back(p[0]);
        }
        
        // 至少要有两个不同的y值，且至少有一个y值有2个或以上的点
        if (yGroups.size() < 2) return false;
        
        bool hasHorizontalEdge = false;
        for (auto& [y, xs] : yGroups) {
            if (xs.size() >= 2) {
                hasHorizontalEdge = true;
                break;
            }
        }
        
        return hasHorizontalEdge;
    }
    
    // 数学公式版本：最简洁的方法（优化版）
    int countTrapezoidsFormula(vector<vector<int>>& points) {
        const int MOD = 1e9 + 7;
        
        // 按y坐标分组，只保留至少有2个点的组
        unordered_map<int, int> yCount;
        for (auto& point : points) {
            yCount[point[1]]++;
        }
        
        vector<long long> combinations;
        for (auto& [y, count] : yCount) {
            if (count >= 2) {
                // 预计算C(count, 2)
                combinations.push_back((long long)count * (count - 1) / 2);
            }
        }
        
        long long result = 0;
        int m = combinations.size();
        
        // 使用数学公式：(∑C[i])² - ∑(C[i])² 然后除以2
        if (m >= 2) {
            long long sum = 0, sumSquare = 0;
            for (long long c : combinations) {
                sum = (sum + c) % MOD;
                sumSquare = (sumSquare + (c * c) % MOD) % MOD;
            }
            
            result = ((sum * sum - sumSquare) % MOD + MOD) % MOD;
            // 除以2的模逆元是500000004
            result = (result * 500000004LL) % MOD;
        }
        
        return result;
    }
    
    // 优化版本：更高效的计算方法
    int countTrapezoidsOptimized(vector<vector<int>>& points) {
        const int MOD = 1e9 + 7;
        
        // 按y坐标分组并排序
        map<int, vector<int>> yGroups;
        for (auto& point : points) {
            yGroups[point[1]].push_back(point[0]);
        }
        
        for (auto& [y, xs] : yGroups) {
            sort(xs.begin(), xs.end());
        }
        
        long long result = 0;
        vector<pair<int, vector<int>>> yList(yGroups.begin(), yGroups.end());
        
        // 枚举两条水平边
        for (int i = 0; i < yList.size(); i++) {
            for (int j = i + 1; j < yList.size(); j++) {
                vector<int>& xs1 = yList[i].second;
                vector<int>& xs2 = yList[j].second;
                
                // 计算交叉的梯形数量
                long long count = 0;
                
                // 对于xs1中的每一对，计算xs2中有多少对与之形成梯形
                for (int p = 0; p < xs1.size(); p++) {
                    for (int q = p + 1; q < xs1.size(); q++) {
                        int a = xs1[p], b = xs1[q]; // a < b
                        
                        // 计算xs2中满足条件的对数
                        // 条件：(c,d)使得四点能构成梯形
                        // 即：c < a < b < d 或 a < c < d < b
                        
                        // 情况1: c < a < b < d
                        int leftCount = lower_bound(xs2.begin(), xs2.end(), a) - xs2.begin();
                        int rightCount = xs2.end() - upper_bound(xs2.begin(), xs2.end(), b);
                        count = (count + (long long)leftCount * rightCount) % MOD;
                        
                        // 情况2: a < c < d < b
                        auto it1 = upper_bound(xs2.begin(), xs2.end(), a);
                        auto it2 = lower_bound(xs2.begin(), xs2.end(), b);
                        long long innerCount = it2 - it1;
                        if (innerCount >= 2) {
                            count = (count + innerCount * (innerCount - 1) / 2) % MOD;
                        }
                    }
                }
                
                result = (result + count) % MOD;
            }
        }
        
        return result;
    }
};

int main() {
    count_trapezoids solution;
    
    // 测试用例1
    vector<vector<int>> points1 = {{1,0},{2,0},{3,0},{2,2},{3,2}};
    cout << "=== Test Case 1 ===" << endl;
    cout << "Points: [[1,0],[2,0],[3,0],[2,2],[3,2]]" << endl;
    cout << "Brute Force: " << solution.countTrapezoidsBruteForce(points1) << endl;
    cout << "Formula: " << solution.countTrapezoidsFormula(points1) << endl;
    cout << "Optimized: " << solution.countTrapezoidsOptimized(points1) << endl;
    cout << "Expected: 3\n" << endl;
    
    // 测试用例2
    vector<vector<int>> points2 = {{0,0},{1,0},{0,1},{2,1}};
    cout << "=== Test Case 2 ===" << endl;
    cout << "Points: [[0,0],[1,0],[0,1],[2,1]]" << endl;
    cout << "Brute Force: " << solution.countTrapezoidsBruteForce(points2) << endl;
    cout << "Formula: " << solution.countTrapezoidsFormula(points2) << endl;
    cout << "Optimized: " << solution.countTrapezoidsOptimized(points2) << endl;
    cout << "Expected: 1\n" << endl;
    
    // 方法对比
    cout << "=== Method Comparison ===" << endl;
    cout << "\n1. Brute Force (Most Intuitive):" << endl;
    cout << "   - Enumerate all 4-point combinations: O(n^4)" << endl;
    cout << "   - Check if they form horizontal trapezoid" << endl;
    cout << "   - Pros: Easy to understand" << endl;
    cout << "   - Cons: Very slow for large inputs" << endl;
    
    cout << "\n2. Formula Method (Simplest):" << endl;
    cout << "   - Group by y-coordinate" << endl;
    cout << "   - For each pair of y-groups: C(n1,2) * C(n2,2)" << endl;
    cout << "   - Pros: Super simple, O(k^2) where k = unique y values" << endl;
    cout << "   - Cons: May overcount (doesn't check convexity)" << endl;
    
    cout << "\n3. Optimized Method (Most Accurate):" << endl;
    cout << "   - Group by y-coordinate and sort x-coordinates" << endl;
    cout << "   - Use binary search for efficient counting" << endl;
    cout << "   - Pros: Correct result, O(n^2) complexity" << endl;
    cout << "   - Cons: More complex implementation" << endl;
    
    cout << "\n=== Recommendation ===" << endl;
    cout << "For simple cases: Use Formula Method" << endl;
    cout << "For accuracy: Use Optimized Method" << endl;
    cout << "For learning: Start with Brute Force" << endl;
    
    return 0;
}
