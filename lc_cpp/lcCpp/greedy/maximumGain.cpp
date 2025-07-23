//
// Created by 24276 on 2025/7/23.
//
// 删除子字符串 - 贪心算法 + 栈
// 关键思路：优先删除分数更高的子串，用栈模拟删除过程

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    // 标准贪心+栈解法
    int maximumGain(std::string s, int x, int y) {
        // 贪心策略：优先删除分数更高的子串
        if (x >= y) {
            // ab分数更高，先删ab再删ba
            int score1 = removeSubstring(s, 'a', 'b', x);
            int score2 = removeSubstring(s, 'b', 'a', y);
            return score1 + score2;
        } else {
            // ba分数更高，先删ba再删ab
            int score1 = removeSubstring(s, 'b', 'a', y);
            int score2 = removeSubstring(s, 'a', 'b', x);
            return score1 + score2;
        }
    }
    
    // 优化版本 - 一次性处理
    int maximumGainOptimized(std::string s, int x, int y) {
        // 确保x >= y，简化逻辑
        char first = 'a', second = 'b';
        if (x < y) {
            std::swap(x, y);
            std::swap(first, second);
        }
        
        std::stack<char> st;
        int score = 0;
        
        // 第一次遍历：删除高分子串
        for (char c : s) {
            if (!st.empty() && st.top() == first && c == second) {
                st.pop();
                score += x;  // 高分
            } else {
                st.push(c);
            }
        }
        
        // 第二次遍历：删除低分子串
        std::string remaining;
        while (!st.empty()) {
            remaining += st.top();
            st.pop();
        }
        std::reverse(remaining.begin(), remaining.end());
        
        for (char c : remaining) {
            if (!st.empty() && st.top() == second && c == first) {
                st.pop();
                score += y;  // 低分
            } else {
                st.push(c);
            }
        }
        
        return score;
    }
    
    // 详细版本 - 带调试信息
    int maximumGainDetailed(std::string s, int x, int y) {
        std::cout << "输入字符串: " << s << std::endl;
        std::cout << "ab得分: " << x << ", ba得分: " << y << std::endl;
        
        if (x >= y) {
            std::cout << "策略: ab分数更高，先删ab再删ba" << std::endl;
            int score1 = removeSubstringDebug(s, 'a', 'b', x, "ab");
            int score2 = removeSubstringDebug(s, 'b', 'a', y, "ba");
            std::cout << "最终结果: " << score1 << " + " << score2 << " = " << (score1 + score2) << std::endl;
            return score1 + score2;
        } else {
            std::cout << "策略: ba分数更高，先删ba再删ab" << std::endl;
            int score1 = removeSubstringDebug(s, 'b', 'a', y, "ba");
            int score2 = removeSubstringDebug(s, 'a', 'b', x, "ab");
            std::cout << "最终结果: " << score1 << " + " << score2 << " = " << (score1 + score2) << std::endl;
            return score1 + score2;
        }
    }

private:
    // 删除指定子串的辅助函数
    int removeSubstring(std::string& s, char first, char second, int points) {
        std::stack<char> st;
        int score = 0;
        
        for (char c : s) {
            if (!st.empty() && st.top() == first && c == second) {
                st.pop();
                score += points;
            } else {
                st.push(c);
            }
        }
        
        // 更新字符串为剩余字符
        s.clear();
        std::string temp;
        while (!st.empty()) {
            temp += st.top();
            st.pop();
        }
        std::reverse(temp.begin(), temp.end());
        s = temp;
        
        return score;
    }
    
    // 带调试信息的删除函数
    int removeSubstringDebug(std::string& s, char first, char second, int points, const std::string& name) {
        std::stack<char> st;
        int score = 0;
        int removedCount = 0;
        
        std::cout << "\n开始删除 " << name << " (分数: " << points << ")" << std::endl;
        std::cout << "处理字符串: " << s << std::endl;
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (!st.empty() && st.top() == first && c == second) {
                st.pop();
                score += points;
                removedCount++;
                std::cout << "  位置" << i << ": 删除" << first << second 
                         << ", 得分+" << points << ", 总分:" << score << std::endl;
            } else {
                st.push(c);
            }
        }
        
        // 更新字符串
        s.clear();
        std::string temp;
        while (!st.empty()) {
            temp += st.top();
            st.pop();
        }
        std::reverse(temp.begin(), temp.end());
        s = temp;
        
        std::cout << "删除" << removedCount << "个" << name << ", 得分:" << score << std::endl;
        std::cout << "剩余字符串: " << s << std::endl;
        
        return score;
    }
};

// 测试函数
void testMaximumGain() {
    Solution solution;
    
    std::vector<std::tuple<std::string, int, int>> testCases = {
        {"cdbcbbaaabab", 4, 5},     // 示例1
        {"aabbaaxybbaabb", 5, 4},   // 示例2
        {"aabb", 1, 2},
        {"abab", 3, 4},
        {"baba", 2, 5}
    };
    
    std::cout << "=== 最大得分测试 ===" << std::endl;
    for (auto& testCase : testCases) {
        std::string s = std::get<0>(testCase);
        int x = std::get<1>(testCase);
        int y = std::get<2>(testCase);
        int result = solution.maximumGain(s, x, y);
        std::cout << "输入: s='" << std::get<0>(testCase) << "', x=" << x 
                 << ", y=" << y << " -> 输出: " << result << std::endl;
    }
    
    std::cout << "\n=== 详细过程演示 ===" << std::endl;
    std::string s = "aabbaaxybbaabb";
    solution.maximumGainDetailed(s, 5, 4);
}

// 算法复杂度分析
void analyzeComplexity() {
    std::cout << "\n=== 算法复杂度分析 ===" << std::endl;
    std::cout << "时间复杂度: O(n)" << std::endl;
    std::cout << "  - 两次遍历字符串: 2 * O(n)" << std::endl;
    std::cout << "  - 栈操作: O(1)" << std::endl;
    std::cout << "\n空间复杂度: O(n)" << std::endl;
    std::cout << "  - 栈空间: 最坏情况O(n)" << std::endl;
    std::cout << "\n关键优化:" << std::endl;
    std::cout << "  - 贪心策略避免了动态规划的O(n²)复杂度" << std::endl;
    std::cout << "  - 栈操作比字符串删除更高效" << std::endl;
}

int main() {
    testMaximumGain();
    analyzeComplexity();
    return 0;
}
