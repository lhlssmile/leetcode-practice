#include <string>
#include <iostream>
#include <vector>
using namespace std;
class min_window76 {
public:
    string minWindow(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        if (sLen < tLen) return "";  // s 长度不够，直接返回空
        
        // 用数组代替 map，假设只处理 ASCII 字符（128 够用）
        vector<int> tCount(128, 0);  // t 的字符频率
        vector<int> windowCount(128, 0);  // 窗口内的字符频率
        
        // 统计 t 中字符频率
        for (char c : t) {
            tCount[c]++;
        }
        
        int required = tLen;  // 需要匹配的字符总数
        int left = 0, right = 0;  // 窗口左右指针
        int minLen = INT_MAX, minLeft = 0;  // 记录最小窗口的长度和起始位置
        
        // 开始滑动窗口
        while (right < sLen) {
            char c = s[right];
            windowCount[c]++;
            
            // 如果当前字符是 t 需要的，且窗口内数量不超过 t 的要求
            if (tCount[c] > 0 && windowCount[c] <= tCount[c]) {
                required--;
            }
            
            // 当窗口包含所有 t 的字符时
            while (required == 0 && left <= right) {
                // 更新最小窗口
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                // 尝试缩小窗口
                char leftChar = s[left];
                windowCount[leftChar]--;
                if (tCount[leftChar] > 0 && windowCount[leftChar] < tCount[leftChar]) {
                    required++;
                }
                left++;
            }
            
            right++;
        }
        
        // 如果没找到，返回空字符串
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};
int main() {
    min_window76 solution;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string result = solution.minWindow(s, t);
    cout << "Result: " << result << endl;  // 应该输出 "BANC"
    return 0;
}