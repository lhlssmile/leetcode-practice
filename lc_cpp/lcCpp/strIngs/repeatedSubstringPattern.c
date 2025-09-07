// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// KMP算法实现
bool repeatedSubstringPatternKMP(char* s) {
    int n = strlen(s);
    if (n <= 1) return false;
    
    // 构建KMP的next数组
    int* next = (int*)malloc((n + 1) * sizeof(int));
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
    bool result = (n % periodLen == 0) && (periodLen != n);
    
    free(next);
    return result;
}

// 暴力枚举方法
bool repeatedSubstringPatternBrute(char* s) {
    int n = strlen(s);
    if (n <= 1) return false;
    
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            bool valid = true;
            for (int j = i; j < n; j++) {
                if (s[j] != s[j % i]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return true;
            }
        }
    }
    return false;
}

// 字符串拼接方法
bool repeatedSubstringPatternConcat(char* s) {
    int n = strlen(s);
    if (n <= 1) return false;
    
    // 创建双倍长度的字符串
    char* doubleS = (char*)malloc((2 * n + 1) * sizeof(char));
    strcpy(doubleS, s);
    strcat(doubleS, s);
    
    // 在去掉首尾字符的字符串中查找原字符串
    bool found = false;
    for (int i = 1; i < 2 * n - n; i++) {
        if (strncmp(doubleS + i, s, n) == 0) {
            found = true;
            break;
        }
    }
    
    free(doubleS);
    return found;
}

int main() {
    char* testCases[] = {
        "abab",
        "aba",
        "abcabcabcabc",
        "a",
        "aa"
    };
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    printf("=== 重复的子字符串模式检测 ===\n");
    
    for (int i = 0; i < numTests; i++) {
        printf("\n测试用例 %d: \"%s\"\n", i + 1, testCases[i]);
        
        bool result1 = repeatedSubstringPatternKMP(testCases[i]);
        bool result2 = repeatedSubstringPatternBrute(testCases[i]);
        bool result3 = repeatedSubstringPatternConcat(testCases[i]);
        
        printf("KMP算法: %s\n", result1 ? "true" : "false");
        printf("暴力枚举: %s\n", result2 ? "true" : "false");
        printf("字符串拼接: %s\n", result3 ? "true" : "false");
        
        // 验证结果一致性
        if (result1 != result2 || result2 != result3) {
            printf("警告: 结果不一致!\n");
        }
    }
    
    return 0;
}