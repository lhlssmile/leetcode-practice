#include <stdio.h>
#include <string.h>

/**
 * LeetCode 1371. 每个元音包含偶数次的最长子字符串
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
 */

/**
 * 使用前缀和+状态压缩的方法
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 */
int findTheLongestSubstring(const char* s) {
    int n = strlen(s);
    int first[32]; // 记录状态第一次出现的位置，状态数最多为2^5=32种
    
    // 初始化first数组为-2（表示未出现过）
    for (int i = 0; i < 32; i++) {
        first[i] = -2;
    }
    first[0] = -1; // 空字符串状态为0，位置-1
    
    int state = 0; // 当前前缀的元音奇偶状态
    int maxLen = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    int vowelPos[128];
    memset(vowelPos, -1, sizeof(vowelPos));
    vowelPos['a'] = 0;
    vowelPos['e'] = 1;
    vowelPos['i'] = 2;
    vowelPos['o'] = 3;
    vowelPos['u'] = 4;
    
    // 遍历字符串
    for (int i = 0; i < n; i++) {
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        int pos = vowelPos[(unsigned char)s[i]];
        if (pos != -1) {
            state ^= (1 << pos); // 翻转第pos位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if (first[state] != -2) {
            int curLen = i - first[state];
            if (curLen > maxLen) {
                maxLen = curLen;
            }
        } else {
            // 记录状态第一次出现的位置
            first[state] = i;
        }
    }
    
    return maxLen;
}

/**
 * 优化版本：使用位运算优化判断是否为元音字母
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 */
int findTheLongestSubstring_optimized(const char* s) {
    int n = strlen(s);
    int first[32]; // 记录状态第一次出现的位置，状态数最多为2^5=32种
    
    // 初始化first数组为-2（表示未出现过）
    for (int i = 0; i < 32; i++) {
        first[i] = -2;
    }
    first[0] = -1; // 空字符串状态为0，位置-1
    
    int state = 0; // 当前前缀的元音奇偶状态
    int maxLen = 0; // 最长子字符串长度
    
    // 使用位掩码快速判断元音字母
    // 创建一个查找表，用于快速确定字符是否为元音以及对应的位置
    // 'a' -> 0, 'e' -> 1, 'i' -> 2, 'o' -> 3, 'u' -> 4
    char vowelMask[26] = {0};
    vowelMask['a' - 'a'] = 1;
    vowelMask['e' - 'a'] = 2;
    vowelMask['i' - 'a'] = 4;
    vowelMask['o' - 'a'] = 8;
    vowelMask['u' - 'a'] = 16;
    
    // 遍历字符串
    for (int i = 0; i < n; i++) {
        char c = s[i];
        // 如果是小写字母且是元音
        if (c >= 'a' && c <= 'z') {
            char mask = vowelMask[c - 'a'];
            if (mask) {
                // 计算位置（log2(mask)）
                int pos = 0;
                while (mask > 1) {
                    mask >>= 1;
                    pos++;
                }
                state ^= (1 << pos); // 翻转对应位
            }
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if (first[state] != -2) {
            int curLen = i - first[state];
            if (curLen > maxLen) {
                maxLen = curLen;
            }
        } else {
            // 记录状态第一次出现的位置
            first[state] = i;
        }
    }
    
    return maxLen;
}

// 测试函数
int main() {
    const char* s1 = "eleetminicoworoep";
    printf("%s: %d\n", s1, findTheLongestSubstring(s1)); // 应输出13
    printf("%s (optimized): %d\n\n", s1, findTheLongestSubstring_optimized(s1)); // 应输出13
    
    const char* s2 = "leetcodeisgreat";
    printf("%s: %d\n", s2, findTheLongestSubstring(s2)); // 应输出5
    printf("%s (optimized): %d\n\n", s2, findTheLongestSubstring_optimized(s2)); // 应输出5
    
    const char* s3 = "bcbcbc";
    printf("%s: %d\n", s3, findTheLongestSubstring(s3)); // 应输出6
    printf("%s (optimized): %d\n\n", s3, findTheLongestSubstring_optimized(s3)); // 应输出6
    
    return 0;
}