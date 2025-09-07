// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (const string& c : tokens) {
            if (c == "+" || c == "-" || c == "*" || c == "/") {
                int b = st.top(); st.pop();  // 右操作数
                int a = st.top(); st.pop();  // 左操作数
                if (c == "+") {
                    st.push(a + b);
                } else if (c == "-") {
                    st.push(a - b);
                } else if (c == "*") {
                    st.push(a * b);
                } else {  // 除法
                    st.push(a / b);
                }
            } else {
                st.push(stoi(c));
            }
        }
        return st.top();
    }
};

void testEvalRPN() {
    cout << "=== 逆波兰表达式求值测试 ===" << endl;
    
    Solution solution;
    
    // 测试用例
    vector<vector<string>> testCases = {
        {"2", "1", "+", "3", "*"},  // ((2 + 1) * 3) = 9
        {"4", "13", "5", "/", "+"},  // (4 + (13 / 5)) = 6
        {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}  // 22
    };
    
    vector<int> expected = {9, 6, 22};
    
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.evalRPN(testCases[i]);
        cout << "测试用例 " << i + 1 << ": ";
        for (const string& token : testCases[i]) {
            cout << token << " ";
        }
        cout << endl;
        cout << "结果: " << result << ", 期望: " << expected[i] << ", 正确: " << (result == expected[i]) << endl;
        cout << endl;
    }
    
    cout << "=== C++特性说明 ===" << endl;
    cout << "1. STL容器: stack和vector" << endl;
    cout << "2. 字符串处理: stoi函数转换" << endl;
    cout << "3. 引用传递: 避免拷贝开销" << endl;
    cout << "4. 面向对象: 类和方法" << endl;
    cout << "5. 范围for循环: 简洁的遍历" << endl;
}

int main() {
    testEvalRPN();
    return 0;
}

/*
C++实现特点:

1. **STL容器**:
   - stack提供后进先出操作
   - vector动态数组
   - string字符串处理

2. **性能优化**:
   - 引用传递避免拷贝
   - 内联函数优化
   - 编译时优化

3. **类型安全**:
   - 强类型系统
   - 编译时类型检查
   - 模板支持

4. **内存管理**:
   - RAII资源管理
   - 自动析构
   - 智能指针支持

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/