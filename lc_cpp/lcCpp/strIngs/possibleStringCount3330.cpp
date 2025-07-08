//
// Created by 24276 on 2025/7/1.
//

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class possible_string_count3330 {
public:
    /*
    问题分析：
    原代码错误：只统计了每个字符的总出现次数，没有考虑连续性
    
    正确理解：
    - Alice最多犯一次错误，即某个字符可能连续输入多次
    - 只有连续相同的字符才算是"打字错误"
    - 对于"ere"，虽然'e'出现2次，但不连续，所以没有错误
    
    解题思路：
    1. 找到所有连续相同字符的段
    2. 对每个长度为n的连续段，可以删除0到n-1个字符
    3. 总方案数 = 所有连续段的可能删除数之和 + 1
    */
    
    // 原始错误代码（保留用于对比）
    static int possibleStringCount_wrong(std::pmr::string word) {
        //错误：只统计字符总数，忽略了连续性要求
        if(word.length() == 1) return 1;

        int res = 1;
        unordered_map<char,int> cnt;
        for(auto c : word) {
            cnt[c]++;
        }
        for(auto& [c,count] : cnt) {
            res += count - 1;  // 这里错误：非连续字符也被计算了
        }
        return res;
    }
    
    // 正确解法：统计连续相同字符段
    static int possibleStringCount(std::pmr::string word) {
        if(word.length() == 1) return 1;
        
        int result = 1;  // 原始字符串本身算一种方案
        int i = 0;
        
        while(i < word.length()) {
            int j = i;
            // 找到连续相同字符的结束位置
            while(j < word.length() && word[j] == word[i]) {
                j++;
            }
            
            // 连续段长度
            int segmentLength = j - i;
            
            // 如果连续段长度 > 1，说明可能是打字错误
            if(segmentLength > 1) {
                // 可以删除1到segmentLength-1个字符
                result += segmentLength - 1;
            }
            
            i = j;  // 移动到下一个不同字符
        }
        
        return result;
    }
    
    // 另一种写法：更清晰的逻辑
    static int possibleStringCount_v2(std::pmr::string word) {
        int n = word.length();
        if(n == 1) return 1;
        
        int totalWays = 1;  // 不删除任何字符的方案
        
        for(int i = 0; i < n; ) {
            int count = 1;
            // 统计连续相同字符的个数
            while(i + count < n && word[i + count] == word[i]) {
                count++;
            }
            
            // 对于连续的count个相同字符，可以删除1到count-1个
            if(count > 1) {
                totalWays += count - 1;
            }
            
            i += count;  // 跳到下一组不同的字符
        }
        
        return totalWays;
    }
};

int main() {
    possible_string_count3330 ps;
    
    // 测试用例1: "abbcccc"
    std::pmr::string s1 = "abbcccc";
    cout << "测试1: \"" << s1 << "\"" << endl;
    cout << "错误方法结果: " << ps.possibleStringCount_wrong(s1) << endl;
    cout << "正确方法结果: " << ps.possibleStringCount(s1) << endl;
    cout << "方法v2结果: " << ps.possibleStringCount_v2(s1) << endl;
    cout << "期望结果: 5 (abbcccc, abbccc, abbcc, abbc, abcccc)" << endl;
    cout << endl;
    
    // 测试用例2: "ere" (用户提到的特殊情况)
    std::pmr::string s2 = "ere";
    cout << "测试2: \"" << s2 << "\"" << endl;
    cout << "错误方法结果: " << ps.possibleStringCount_wrong(s2) << endl;
    cout << "正确方法结果: " << ps.possibleStringCount(s2) << endl;
    cout << "方法v2结果: " << ps.possibleStringCount_v2(s2) << endl;
    cout << "期望结果: 1 (只有ere本身，因为e不连续)" << endl;
    cout << endl;
    
    // 测试用例3: "abcd"
    std::pmr::string s3 = "abcd";
    cout << "测试3: \"" << s3 << "\"" << endl;
    cout << "错误方法结果: " << ps.possibleStringCount_wrong(s3) << endl;
    cout << "正确方法结果: " << ps.possibleStringCount(s3) << endl;
    cout << "方法v2结果: " << ps.possibleStringCount_v2(s3) << endl;
    cout << "期望结果: 1 (只有abcd本身)" << endl;
    cout << endl;
    
    // 测试用例4: "aaaa"
    std::pmr::string s4 = "aaaa";
    cout << "测试4: \"" << s4 << "\"" << endl;
    cout << "错误方法结果: " << ps.possibleStringCount_wrong(s4) << endl;
    cout << "正确方法结果: " << ps.possibleStringCount(s4) << endl;
    cout << "方法v2结果: " << ps.possibleStringCount_v2(s4) << endl;
    cout << "期望结果: 4 (aaaa, aaa, aa, a)" << endl;
    
    return 0;
}
