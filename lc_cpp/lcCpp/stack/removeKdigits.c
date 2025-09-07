#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10000

char* removeKdigits(char* num, int k) {
    int len = strlen(num);
    char* stack = (char*)malloc((len + 1) * sizeof(char));
    int top = -1;  // 栈顶指针
    
    // 处理每个数字
    for (int i = 0; i < len; i++) {
        char digit = num[i];
        
        // 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
        while (top >= 0 && k > 0 && stack[top] > digit) {
            top--;
            k--;
        }
        
        // 将当前数字入栈
        stack[++top] = digit;
    }
    
    // 如果还没删完，从后面删
    while (k > 0 && top >= 0) {
        top--;
        k--;
    }
    
    // 栈为空的情况
    if (top < 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        free(stack);
        return result;
    }
    
    // 去掉前导零
    int start = 0;
    while (start <= top && stack[start] == '0') {
        start++;
    }
    
    // 如果全是零
    if (start > top) {
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        free(stack);
        return result;
    }
    
    // 构建结果字符串
    int result_len = top - start + 1;
    char* result = (char*)malloc((result_len + 1) * sizeof(char));
    
    for (int i = 0; i < result_len; i++) {
        result[i] = stack[start + i];
    }
    result[result_len] = '\0';
    
    free(stack);
    return result;
}

// 辅助函数：打印测试结果
void test_removeKdigits(char* num, int k) {
    char* result = removeKdigits(num, k);
    printf("removeKdigits('%s', %d) = '%s'\n", num, k, result);
    free(result);
}

int main() {
    printf("=== C语言版本测试 ===\n");
    
    // 测试用例
    test_removeKdigits("1432219", 3);  // "1219"
    test_removeKdigits("10200", 1);    // "200"
    test_removeKdigits("10", 2);       // "0"
    test_removeKdigits("9", 1);        // "0"
    test_removeKdigits("112", 1);      // "11"
    test_removeKdigits("54321", 2);    // "321"
    test_removeKdigits("1111", 3);     // "1"
    
    return 0;
}

/*
算法说明：
1. 使用数组模拟栈结构，top指针指向栈顶
2. 遍历数字字符串，对于每个数字：
   - 如果栈顶数字大于当前数字且还有删除次数，则删除栈顶
   - 将当前数字入栈
3. 如果删除次数还有剩余，从栈顶继续删除
4. 处理前导零，构建最终结果
5. 注意内存管理，及时释放分配的内存

时间复杂度：O(n)，其中n是数字字符串的长度
空间复杂度：O(n)，用于存储栈
*/