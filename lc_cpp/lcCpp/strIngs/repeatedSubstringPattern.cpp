// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

class Solution {
public:
    // KMP算法实现
    bool repeatedSubstringPatternKMP(string s) {
        int n = s.length();
        if (n <= 1) return false;
        
        // 构建KMP的next数组
        vector<int> next(n + 1);
        next[0] = -1;
        int j = -1;
        
        for (int i = 0; i < n; i++) {
            while (j >= 0 && s[i] != s[j]) {
                j = next[j];
            }
            j++;
            next[i + 1] = j;
        }
        
        int periodLen = n - next[n];
        return n % periodLen == 0 && periodLen != n;
    }
    
    // 字符串拼接方法
    bool repeatedSubstringPatternConcat(string s) {
        // 将字符串与自身拼接，然后去掉首尾字符
        // 如果原字符串是重复模式，那么在新字符串中一定能找到原字符串
        string doubleS = s + s;
        return doubleS.substr(1, doubleS.length() - 2).find(s) != string::npos;
    }
    
    // 暴力枚举方法
    bool repeatedSubstringPatternBrute(string s) {
        int n = s.length();
        if (n <= 1) return false;
        
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string pattern = s.substr(0, i);
                string constructed = "";
                for (int j = 0; j < n / i; j++) {
                    constructed += pattern;
                }
                if (constructed == s) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // 正则表达式方法
    bool repeatedSubstringPatternRegex(string s) {
        // 使用正则表达式匹配重复模式
        regex pattern(R"(^(.+)\1+$)");
        return regex_match(s, pattern);
    }
    
    // STL算法优化方法
    bool repeatedSubstringPatternSTL(string s) {
        int n = s.length();
        if (n <= 1) return false;
        
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string pattern = s.substr(0, i);
                bool isRepeating = true;
                
                for (int j = i; j < n; j += i) {
                    if (!equal(pattern.begin(), pattern.end(), s.begin() + j)) {
                        isRepeating = false;
                        break;
                    }
                }
                
                if (isRepeating) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Solution solution;
    vector<string> testCases = {
        "abab",
        "aba",
        "abcabcabcabc",
        "a",
        "aa"
    };
    
    cout << "=== 重复的子字符串模式检测 ===" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        string s = testCases[i];
        cout << "\n测试用例 " << i + 1 << ": \"" << s << "\"" << endl;
        
        bool result1 = solution.repeatedSubstringPatternKMP(s);
        bool result2 = solution.repeatedSubstringPatternConcat(s);
        bool result3 = solution.repeatedSubstringPatternBrute(s);
        bool result4 = solution.repeatedSubstringPatternRegex(s);
        bool result5 = solution.repeatedSubstringPatternSTL(s);
        
        cout << "KMP算法: " << (result1 ? "true" : "false") << endl;
        cout << "字符串拼接: " << (result2 ? "true" : "false") << endl;
        cout << "暴力枚举: " << (result3 ? "true" : "false") << endl;
        cout << "正则表达式: " << (result4 ? "true" : "false") << endl;
        cout << "STL算法: " << (result5 ? "true" : "false") << endl;
        
        // 验证结果一致性
        if (result1 != result2 || result2 != result3 || 
            result3 != result4 || result4 != result5) {
            cout << "警告: 结果不一致!" << endl;
        }
    }
    
    return 0;
}