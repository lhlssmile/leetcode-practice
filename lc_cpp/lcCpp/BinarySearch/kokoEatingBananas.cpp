// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <cassert>

using namespace std;

class Solution {
public:
    // 标准二分查找实现
    int minEatingSpeedBinarySearch(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            long long totalHours = 0;
            
            for (int pile : piles) {
                totalHours += (pile + mid - 1) / mid; // ceil(pile / mid)
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 使用cmath库的ceil函数
    int minEatingSpeedWithCeil(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            long long totalHours = 0;
            
            for (int pile : piles) {
                totalHours += static_cast<long long>(ceil(static_cast<double>(pile) / mid));
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 暴力枚举版本
    int minEatingSpeedBruteForce(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        int maxPile = *max_element(piles.begin(), piles.end());
        
        for (int k = 1; k <= maxPile; k++) {
            long long totalHours = 0;
            for (int pile : piles) {
                totalHours += (pile + k - 1) / k;
            }
            
            if (totalHours <= h) {
                return k;
            }
        }
        
        return maxPile;
    }
    
    // 使用STL算法的版本
    int minEatingSpeedSTL(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        int maxPile = *max_element(piles.begin(), piles.end());
        
        // 使用lower_bound进行二分查找
        auto canFinish = [&](int k) -> bool {
            long long totalHours = 0;
            for (int pile : piles) {
                totalHours += (pile + k - 1) / k;
                if (totalHours > h) return false; // 提前退出优化
            }
            return totalHours <= h;
        };
        
        // 创建候选速度向量
        vector<int> speeds(maxPile);
        iota(speeds.begin(), speeds.end(), 1);
        
        // 使用lower_bound找到第一个满足条件的速度
        auto it = lower_bound(speeds.begin(), speeds.end(), true, 
                             [&](int k, bool) { return !canFinish(k); });
        
        return it != speeds.end() ? *it : maxPile;
    }
    
    // 使用函数式编程的版本
    int minEatingSpeedFunctional(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        int maxPile = *max_element(piles.begin(), piles.end());
        
        // 使用transform和accumulate计算总时间
        auto calculateHours = [&](int k) -> long long {
            vector<long long> hours(piles.size());
            transform(piles.begin(), piles.end(), hours.begin(),
                     [k](int pile) { return (pile + k - 1) / k; });
            return accumulate(hours.begin(), hours.end(), 0LL);
        };
        
        int left = 1, right = maxPile;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (calculateHours(mid) <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 优化版本 - 计算理论最小值
    int minEatingSpeedOptimized(vector<int>& piles, int h) {
        if (piles.empty()) return 0;
        
        // 计算总香蕉数
        long long totalBananas = accumulate(piles.begin(), piles.end(), 0LL);
        
        // 理论最小速度
        int minSpeed = static_cast<int>((totalBananas + h - 1) / h);
        int maxSpeed = *max_element(piles.begin(), piles.end());
        
        // 如果最小速度就能完成，直接返回
        if (canFinishInTime(piles, h, minSpeed)) {
            return minSpeed;
        }
        
        int left = minSpeed, right = maxSpeed;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canFinishInTime(piles, h, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 使用模板的泛型版本
    template<typename T>
    T minEatingSpeedGeneric(vector<T>& piles, T h) {
        if (piles.empty()) return 0;
        
        T left = 1;
        T right = *max_element(piles.begin(), piles.end());
        
        while (left < right) {
            T mid = left + (right - left) / 2;
            T totalHours = 0;
            
            for (T pile : piles) {
                totalHours += (pile + mid - 1) / mid;
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
private:
    // 辅助函数：检查是否能在指定时间内完成
    bool canFinishInTime(const vector<int>& piles, int h, int k) {
        long long totalHours = 0;
        for (int pile : piles) {
            totalHours += (pile + k - 1) / k;
            if (totalHours > h) return false; // 提前退出
        }
        return true;
    }
};

// 使用RAII和智能指针的版本
class AdvancedSolution {
public:
    using PileVector = vector<int>;
    using CalculatorFunc = function<long long(int)>;
    
    int minEatingSpeed(PileVector& piles, int h) {
        if (piles.empty()) return 0;
        
        // 创建计算器函数
        auto calculator = createHoursCalculator(piles);
        
        int maxPile = *max_element(piles.begin(), piles.end());
        
        return binarySearchWithPredicate(1, maxPile, 
                                       [&](int k) { return calculator(k) <= h; });
    }
    
private:
    CalculatorFunc createHoursCalculator(const PileVector& piles) {
        return [&piles](int k) -> long long {
            return accumulate(piles.begin(), piles.end(), 0LL,
                            [k](long long sum, int pile) {
                                return sum + (pile + k - 1) / k;
                            });
        };
    }
    
    template<typename Predicate>
    int binarySearchWithPredicate(int left, int right, Predicate pred) {
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (pred(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};

int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{3, 6, 7, 11}, 8},
        {{30, 11, 23, 4, 20}, 5},
        {{30, 11, 23, 4, 20}, 6},
        {{1, 1, 1, 1}, 4},
        {{312884470}, 312884469}
    };
    
    Solution solution;
    AdvancedSolution advancedSolution;
    
    cout << "=== 爱吃香蕉的珂珂 ===" << endl;
    
    for (size_t i = 0; i < testCases.size(); i++) {
        auto& [piles, h] = testCases[i];
        cout << "\n测试用例 " << i + 1 << ": piles=[";
        for (size_t j = 0; j < piles.size(); j++) {
            cout << piles[j];
            if (j < piles.size() - 1) cout << ", ";
        }
        cout << "], h=" << h << endl;
        
        // 创建副本用于不同的测试
        vector<int> piles1 = piles, piles2 = piles, piles3 = piles;
        vector<int> piles4 = piles, piles5 = piles, piles6 = piles;
        vector<int> piles7 = piles;
        
        int result1 = solution.minEatingSpeedBinarySearch(piles1, h);
        int result2 = solution.minEatingSpeedWithCeil(piles2, h);
        int result3 = solution.minEatingSpeedBruteForce(piles3, h);
        int result4 = solution.minEatingSpeedSTL(piles4, h);
        int result5 = solution.minEatingSpeedFunctional(piles5, h);
        int result6 = solution.minEatingSpeedOptimized(piles6, h);
        int result7 = solution.minEatingSpeedGeneric(piles7, h);
        int result8 = advancedSolution.minEatingSpeed(piles, h);
        
        cout << "标准二分查找: " << result1 << endl;
        cout << "使用ceil函数: " << result2 << endl;
        cout << "暴力枚举: " << result3 << endl;
        cout << "STL算法版本: " << result4 << endl;
        cout << "函数式编程: " << result5 << endl;
        cout << "优化版本: " << result6 << endl;
        cout << "泛型版本: " << result7 << endl;
        cout << "高级版本: " << result8 << endl;
        
        // 验证结果一致性
        vector<int> results = {result1, result2, result3, result4, 
                              result5, result6, result7, result8};
        
        for (size_t j = 1; j < results.size(); j++) {
            assert(results[j] == results[0]);
        }
        cout << "✓ 所有实现结果一致" << endl;
    }
    
    cout << "\n=== C++特性说明 ===" << endl;
    cout << "1. STL容器: vector, algorithm, numeric等" << endl;
    cout << "2. 范围for循环: for (auto& item : container)" << endl;
    cout << "3. Lambda表达式: [capture](params) { body }" << endl;
    cout << "4. 模板编程: template<typename T>" << endl;
    cout << "5. 智能指针: unique_ptr, shared_ptr" << endl;
    cout << "6. 函数对象: std::function" << endl;
    cout << "7. 结构化绑定: auto& [a, b] = pair" << endl;
    cout << "8. 类型推导: auto, decltype" << endl;
    cout << "9. 移动语义: std::move, 右值引用" << endl;
    cout << "10. RAII: 资源获取即初始化" << endl;
    
    return 0;
}

/*
C++特性详解:

1. **STL标准模板库**:
   - 容器: vector, list, map, set等
   - 算法: sort, find, transform, accumulate等
   - 迭代器: 统一的容器访问接口

2. **现代C++特性(C++11+)**:
   - auto关键字: 自动类型推导
   - 范围for循环: 简化容器遍历
   - Lambda表达式: 匿名函数
   - 智能指针: 自动内存管理

3. **模板编程**:
   - 函数模板和类模板
   - 模板特化和偏特化
   - SFINAE技术
   - 概念(C++20)

4. **函数式编程支持**:
   - std::function: 函数包装器
   - std::bind: 函数绑定
   - Lambda表达式捕获
   - 高阶函数

5. **内存管理**:
   - RAII原则: 资源获取即初始化
   - 智能指针: unique_ptr, shared_ptr, weak_ptr
   - 移动语义: 避免不必要的拷贝

6. **类型系统**:
   - 强类型检查
   - 类型推导: auto, decltype
   - 类型别名: using, typedef
   - 结构化绑定(C++17)

7. **性能优化**:
   - 内联函数: inline关键字
   - 编译时计算: constexpr
   - 移动语义: 减少拷贝开销
   - 零成本抽象

8. **异常处理**:
   - try-catch机制
   - RAII确保异常安全
   - noexcept说明符

9. **并发编程**:
   - std::thread: 线程支持
   - std::mutex: 互斥锁
   - std::atomic: 原子操作
   - std::future: 异步编程

10. **编译时编程**:
    - 模板元编程
    - constexpr函数
    - SFINAE技术
    - 概念和约束(C++20)
*/