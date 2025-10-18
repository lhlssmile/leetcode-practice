#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 计算结果数组的大小
 * 对于每个字母字符，有两种选择（大写或小写）
 * 对于数字字符，只有一种选择
 */
int calculateResultSize(char* s) {
    int letterCount = 0;
    for (int i = 0; s[i]; i++) {
        if (isalpha(s[i])) {
            letterCount++;
        }
    }
    return 1 << letterCount; // 2^letterCount
}

void backtrack(char* s, int index, char* path, char** result, int* resultIndex) {
    if (s[index] == '\0') {
        // 到达字符串末尾，保存当前路径
        path[index] = '\0';
        result[*resultIndex] = strdup(path);
        (*resultIndex)++;
        return;
    }
    
    char ch = s[index];
    if (isdigit(ch)) {
        // 数字字符只有一种选择
        path[index] = ch;
        backtrack(s, index + 1, path, result, resultIndex);
    } else {
        // 字母字符有两种选择：小写和大写
        path[index] = tolower(ch);
        backtrack(s, index + 1, path, result, resultIndex);
        
        path[index] = toupper(ch);
        backtrack(s, index + 1, path, result, resultIndex);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCasePermutation(char* s, int* returnSize) {
    int resultSize = calculateResultSize(s);
    char** result = (char**)malloc(resultSize * sizeof(char*));
    char* path = (char*)malloc((strlen(s) + 1) * sizeof(char));
    
    int resultIndex = 0;
    backtrack(s, 0, path, result, &resultIndex);
    
    *returnSize = resultSize;
    free(path);
    return result;
}

// 测试函数
int main() {
    // 测试用例1
    char s1[] = "a1b2";
    int returnSize1;
    char** result1 = letterCasePermutation(s1, &returnSize1);
    
    printf("Input: %s\n", s1);
    printf("Output: [");
    for (int i = 0; i < returnSize1; i++) {
        printf("\"%s\"%s", result1[i], i < returnSize1 - 1 ? ", " : "");
        free(result1[i]);
    }
    printf("]\n");
    free(result1);
    
    // 测试用例2
    char s2[] = "3z4";
    int returnSize2;
    char** result2 = letterCasePermutation(s2, &returnSize2);
    
    printf("Input: %s\n", s2);
    printf("Output: [");
    for (int i = 0; i < returnSize2; i++) {
        printf("\"%s\"%s", result2[i], i < returnSize2 - 1 ? ", " : "");
        free(result2[i]);
    }
    printf("]\n");
    free(result2);
    
    return 0;
}

/*
算法思路：递归回溯生成所有可能的字母大小写排列
时间复杂度：O(2^n)，其中n是字符串中字母的数量
空间复杂度：O(n)，递归栈的深度和临时字符串的空间
*/