#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * 计算满足条件的最大差值
 * @param s 输入字符串，只包含数字0-4
 * @param k 窗口大小下限
 * @return 满足条件的最大差值
 */
int maxDifference(char* s, int k) {
    const int inf = INT_MAX / 2;
    int ans = -inf;
    int len = strlen(s);
    
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (y == x) {
                continue;
            }
            
            int cur_s[5] = {0};
            int pre_s[5] = {0};
            int min_s[2][2] = {{inf, inf}, {inf, inf}};
            int left = 0;
            
            for (int i = 0; i < len; i++) {
                cur_s[s[i] - '0']++;
                int r = i + 1;
                
                while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
                    int parity_x = pre_s[x] & 1;
                    int parity_y = pre_s[y] & 1;
                    if (pre_s[x] - pre_s[y] < min_s[parity_x][parity_y]) {
                        min_s[parity_x][parity_y] = pre_s[x] - pre_s[y];
                    }
                    pre_s[s[left] - '0']++;
                    left++;
                }
                
                int current_parity_x = (cur_s[x] & 1) ^ 1;
                int current_parity_y = cur_s[y] & 1;
                int current_diff = cur_s[x] - cur_s[y] - min_s[current_parity_x][current_parity_y];
                if (current_diff > ans) {
                    ans = current_diff;
                }
            }
        }
    }
    
    return ans;
}

/**
 * 优化版本：使用更具描述性的变量名和注释
 * @param s 输入字符串，只包含数字0-4
 * @param k 窗口大小下限
 * @return 满足条件的最大差值
 */
int maxDifferenceOptimized(char* s, int k) {
    const int INF = INT_MAX / 2;
    int maxDiff = -INF;
    int len = strlen(s);
    
    // 将字符串转换为数字数组，避免重复转换
    int* digits = (int*)malloc(len * sizeof(int));
    if (digits == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return -1;
    }
    
    for (int i = 0; i < len; i++) {
        digits[i] = s[i] - '0';
    }
    
    // 枚举所有可能的字符对(x,y)，其中x!=y
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (y == x) {
                continue;
            }
            
            // 当前窗口中各字符的计数
            int currentCount[5] = {0};
            // 前缀窗口中各字符的计数
            int prefixCount[5] = {0};
            // 存储最小差值，按奇偶性分类
            int minDifference[2][2] = {{INF, INF}, {INF, INF}};
            
            int left = 0;
            for (int i = 0; i < len; i++) {
                // 更新当前窗口计数
                currentCount[digits[i]]++;
                int right = i + 1;
                
                // 当窗口大小>=k且满足条件时，更新最小差值
                while (right - left >= k && 
                       currentCount[x] > prefixCount[x] && 
                       currentCount[y] > prefixCount[y]) {
                    // 根据x和y的奇偶性选择对应的最小差值
                    int parityX = prefixCount[x] & 1; // x的奇偶性
                    int parityY = prefixCount[y] & 1; // y的奇偶性
                    
                    // 更新最小差值
                    if (prefixCount[x] - prefixCount[y] < minDifference[parityX][parityY]) {
                        minDifference[parityX][parityY] = prefixCount[x] - prefixCount[y];
                    }
                    
                    // 移动左指针，更新前缀计数
                    prefixCount[digits[left]]++;
                    left++;
                }
                
                // 计算当前最大差值
                // 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
                int currentParityX = (currentCount[x] & 1) ^ 1;
                int currentParityY = currentCount[y] & 1;
                int currentDiff = currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY];
                
                if (currentDiff > maxDiff) {
                    maxDiff = currentDiff;
                }
            }
        }
    }
    
    free(digits);
    return maxDiff;
}

/**
 * 高效版本：使用预计算和优化的数据结构
 * @param s 输入字符串，只包含数字0-4
 * @param k 窗口大小下限
 * @return 满足条件的最大差值
 */
int maxDifferenceEfficient(char* s, int k) {
    const int INF = INT_MAX / 2;
    int maxDiff = -INF;
    int len = strlen(s);
    
    // 预计算所有数字的位置
    int** positions = (int**)malloc(5 * sizeof(int*));
    int* counts = (int*)calloc(5, sizeof(int));
    
    if (positions == NULL || counts == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return -1;
    }
    
    // 第一次遍历，计算每个数字出现的次数
    for (int i = 0; i < len; i++) {
        counts[s[i] - '0']++;
    }
    
    // 为每个数字分配足够的空间
    for (int i = 0; i < 5; i++) {
        positions[i] = (int*)malloc(counts[i] * sizeof(int));
        if (positions[i] == NULL) {
            fprintf(stderr, "内存分配失败\n");
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(positions[j]);
            }
            free(positions);
            free(counts);
            return -1;
        }
        counts[i] = 0; // 重置计数器，用于下一步
    }
    
    // 第二次遍历，记录每个数字的位置
    for (int i = 0; i < len; i++) {
        int digit = s[i] - '0';
        positions[digit][counts[digit]++] = i;
    }
    
    // 枚举所有可能的字符对(x,y)，其中x!=y
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (y == x) {
                continue;
            }
            
            int currentCount[5] = {0};
            int prefixCount[5] = {0};
            int minDifference[2][2] = {{INF, INF}, {INF, INF}};
            int left = 0;
            
            for (int i = 0; i < len; i++) {
                currentCount[s[i] - '0']++;
                int right = i + 1;
                
                while (right - left >= k && 
                       currentCount[x] > prefixCount[x] && 
                       currentCount[y] > prefixCount[y]) {
                    int parityX = prefixCount[x] & 1;
                    int parityY = prefixCount[y] & 1;
                    
                    if (prefixCount[x] - prefixCount[y] < minDifference[parityX][parityY]) {
                        minDifference[parityX][parityY] = prefixCount[x] - prefixCount[y];
                    }
                    
                    prefixCount[s[left] - '0']++;
                    left++;
                }
                
                int currentParityX = (currentCount[x] & 1) ^ 1;
                int currentParityY = currentCount[y] & 1;
                int currentDiff = currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY];
                
                if (currentDiff > maxDiff) {
                    maxDiff = currentDiff;
                }
            }
        }
    }
    
    // 释放内存
    for (int i = 0; i < 5; i++) {
        free(positions[i]);
    }
    free(positions);
    free(counts);
    
    return maxDiff;
}

int main() {
    // 测试用例
    char* testCases[] = {
        "01234",
        "00110"
    };
    int testK[] = {2, 2};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        int result1 = maxDifference(testCases[i], testK[i]);
        int result2 = maxDifferenceOptimized(testCases[i], testK[i]);
        int result3 = maxDifferenceEfficient(testCases[i], testK[i]);
        
        printf("测试用例%d: s=%s, k=%d\n", i + 1, testCases[i], testK[i]);
        printf("  基本版本结果: %d\n", result1);
        printf("  优化版本结果: %d\n", result2);
        printf("  高效版本结果: %d\n", result3);
        printf("\n");
    }
    
    return 0;
}