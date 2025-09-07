#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

class Solution {
public:
    // 原版实现
    string removeKdigits(string num, int k) {
        string st;
        for (char d : num) {
            while (!st.empty() && k > 0 && st.back() > d) {
                st.pop_back();
                k--;
            }
            st.push_back(d);
        }
        // 如果还没删完，从后面删
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }
        // 去掉前导零
        int i = 0;
        while (i < st.size() && st[i] == '0') i++;
        string ans = st.substr(i);
        return ans.empty() ? "0" : ans;
    }
    
    // 使用现代C++特性的版本
    string removeKdigitsModern(string num, int k) {
        string stack;
        
        // 使用range-based for loop和lambda
        for_each(num.begin(), num.end(), [&](char digit) {
            // 移除比当前数字大的栈顶元素
            while (!stack.empty() && k > 0 && stack.back() > digit) {
                stack.pop_back();
                k--;
            }
            stack.push_back(digit);
        });
        
        // 如果还有剩余删除次数，从后面删除
        if (k > 0) {
            stack.erase(stack.end() - min(k, (int)stack.size()), stack.end());
        }
        
        // 去掉前导零
        auto first_non_zero = find_if(stack.begin(), stack.end(), 
                                     [](char c) { return c != '0'; });
        
        string result(first_non_zero, stack.end());
        return result.empty() ? "0" : result;
    }
    
    // 函数式编程风格版本
    string removeKdigitsFunctional(string num, int k) {
        // 使用accumulate进行函数式处理
        auto result_pair = accumulate(num.begin(), num.end(), 
                                    make_pair(string(), k),
                                    [](auto acc, char digit) {
                                        auto& [stack, remaining_k] = acc;
                                        
                                        // 移除比当前数字大的栈顶元素
                                        while (!stack.empty() && remaining_k > 0 && 
                                               stack.back() > digit) {
                                            stack.pop_back();
                                            remaining_k--;
                                        }
                                        stack.push_back(digit);
                                        
                                        return make_pair(stack, remaining_k);
                                    });
        
        auto [stack, remaining_k] = result_pair;
        
        // 如果还有剩余删除次数，从后面删除
        if (remaining_k > 0) {
            stack.erase(stack.end() - min(remaining_k, (int)stack.size()), 
                       stack.end());
        }
        
        // 去掉前导零
        auto first_non_zero = find_if(stack.begin(), stack.end(), 
                                     [](char c) { return c != '0'; });
        
        string result(first_non_zero, stack.end());
        return result.empty() ? "0" : result;
    }
};

int main() {
    Solution sol;
    
    // 测试用例
    vector<pair<string, int>> testCases = {
        {"1432219", 3},  // "1219"
        {"10200", 1},    // "200"
        {"10", 2},       // "0"
        {"9", 1},        // "0"
        {"112", 1}       // "11"
    };
    
    cout << "=== 原版实现 ===" << endl;
    for (const auto& [num, k] : testCases) {
        string result = sol.removeKdigits(num, k);
        cout << "removeKdigits('" << num << "', " << k << ") = '" << result << "'" << endl;
    }
    
    cout << "\n=== 现代C++版本 ===" << endl;
    for (const auto& [num, k] : testCases) {
        string result = sol.removeKdigitsModern(num, k);
        cout << "removeKdigitsModern('" << num << "', " << k << ") = '" << result << "'" << endl;
    }
    
    cout << "\n=== 函数式版本 ===" << endl;
    for (const auto& [num, k] : testCases) {
        string result = sol.removeKdigitsFunctional(num, k);
        cout << "removeKdigitsFunctional('" << num << "', " << k << ") = '" << result << "'" << endl;
    }
    
    return 0;
}