#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

/**
 * LeetCode 1371. 每个元音包含偶数次的最长子字符串
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
 */
class Solution {
public:
    /**
     * 使用前缀和+状态压缩的方法
     * 时间复杂度: O(n)，其中n是字符串长度
     * 空间复杂度: O(1)，状态数最多为2^5=32种
     */
    int findTheLongestSubstring(std::string s) {
        int n = s.length();
        std::unordered_map<int, int> first; // 记录状态第一次出现的位置
        first[0] = -1; // 空字符串状态为0，位置-1
        int state = 0; // 当前前缀的元音奇偶状态
        int maxLen = 0; // 最长子字符串长度
        
        // 元音映射：a=0, e=1, i=2, o=3, u=4
        std::vector<int> vowelPos(128, -1);
        vowelPos['a'] = 0;
        vowelPos['e'] = 1;
        vowelPos['i'] = 2;
        vowelPos['o'] = 3;
        vowelPos['u'] = 4;
        
        // 遍历字符串
        for (int i = 0; i < n; i++) {
            // 如果是元音，更新状态（翻转对应位的奇偶性）
            int pos = vowelPos[s[i]];
            if (pos != -1) {
                state ^= (1 << pos); // 翻转第pos位
            }
            
            // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
            if (first.count(state)) {
                maxLen = std::max(maxLen, i - first[state]);
            } else {
                // 记录状态第一次出现的位置
                first[state] = i;
            }
        }
        
        return maxLen;
    }
    
    /**
     * 优化版本：使用数组代替哈希表（因为状态数最多为2^5=32种）
     * 时间复杂度: O(n)，其中n是字符串长度
     * 空间复杂度: O(1)，状态数最多为2^5=32种
     */
    int findTheLongestSubstring_optimized(std::string s) {
        int n = s.length();
        std::vector<int> first(1 << 5, -2); // 记录状态第一次出现的位置，初始化为-2表示未出现过
        first[0] = -1; // 空字符串状态为0，位置-1
        int state = 0; // 当前前缀的元音奇偶状态
        int maxLen = 0; // 最长子字符串长度
        
        // 元音映射：a=0, e=1, i=2, o=3, u=4
        std::vector<int> vowelPos(128, -1);
        vowelPos['a'] = 0;
        vowelPos['e'] = 1;
        vowelPos['i'] = 2;
        vowelPos['o'] = 3;
        vowelPos['u'] = 4;
        
        // 遍历字符串
        for (int i = 0; i < n; i++) {
            // 如果是元音，更新状态（翻转对应位的奇偶性）
            int pos = vowelPos[s[i]];
            if (pos != -1) {
                state ^= (1 << pos); // 翻转第pos位
            }
            
            // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
            if (first[state] != -2) {
                maxLen = std::max(maxLen, i - first[state]);
            } else {
                // 记录状态第一次出现的位置
                first[state] = i;
            }
        }
        
        return maxLen;
    }
};

// 测试函数
int main() {
    Solution solution;
    
    std::string s1 = "eleetminicoworoep";
    std::cout << solution.findTheLongestSubstring(s1) << std::endl; // 应输出13
    std::cout << solution.findTheLongestSubstring_optimized(s1) << std::endl; // 应输出13
    
    std::string s2 = "leetcodeisgreat";
    std::cout << solution.findTheLongestSubstring(s2) << std::endl; // 应输出5
    std::cout << solution.findTheLongestSubstring_optimized(s2) << std::endl; // 应输出5
    
    std::string s3 = "bcbcbc";
    std::cout << solution.findTheLongestSubstring(s3) << std::endl; // 应输出6
    std::cout << solution.findTheLongestSubstring_optimized(s3) << std::endl; // 应输出6
    
    return 0;
}