// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;
    
    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            int b = stack[top--];  // 右操作数
            int a = stack[top--];  // 左操作数
            
            if (strcmp(token, "+") == 0) {
                stack[++top] = a + b;
            } else if (strcmp(token, "-") == 0) {
                stack[++top] = a - b;
            } else if (strcmp(token, "*") == 0) {
                stack[++top] = a * b;
            } else {  // 除法
                stack[++top] = a / b;
            }
        } else {
            stack[++top] = atoi(token);
        }
    }
    
    int result = stack[top];
    free(stack);
    return result;
}

void testEvalRPN() {
    printf("=== 逆波兰表达式求值测试 ===\n");
    
    // 测试用例1: ["2","1","+","3","*"] = 9
    char* tokens1[] = {"2", "1", "+", "3", "*"};
    int result1 = evalRPN(tokens1, 5);
    printf("测试用例1: [\"2\",\"1\",\"+\",\"3\",\"*\"]\n");
    printf("结果: %d, 期望: 9, 正确: %s\n\n", result1, result1 == 9 ? "是" : "否");
    
    // 测试用例2: ["4","13","5","/","+"] = 6
    char* tokens2[] = {"4", "13", "5", "/", "+"};
    int result2 = evalRPN(tokens2, 5);
    printf("测试用例2: [\"4\",\"13\",\"5\",\"/\",\"+\"]\n");
    printf("结果: %d, 期望: 6, 正确: %s\n\n", result2, result2 == 6 ? "是" : "否");
    
    // 测试用例3: ["10","6","9","3","+","-11","*","/","*","17","+","5","+"] = 22
    char* tokens3[] = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    int result3 = evalRPN(tokens3, 13);
    printf("测试用例3: 复杂表达式\n");
    printf("结果: %d, 期望: 22, 正确: %s\n\n", result3, result3 == 22 ? "是" : "否");
    
    printf("=== C语言特性说明 ===\n");
    printf("1. 手动内存管理: malloc/free\n");
    printf("2. 指针操作: 数组和字符串处理\n");
    printf("3. 字符串比较: strcmp函数\n");
    printf("4. 类型转换: atoi函数\n");
    printf("5. 过程式编程: 函数和结构化代码\n");
}

int main() {
    testEvalRPN();
    return 0;
}

/*
C语言实现特点:

1. **内存管理**:
   - 手动malloc/free管理内存
   - 指针操作直接访问内存
   - 需要careful处理内存泄漏

2. **字符串处理**:
   - strcmp进行字符串比较
   - atoi转换字符串为整数
   - 字符数组操作

3. **数组操作**:
   - 手动实现栈结构
   - 索引操作访问元素
   - 边界检查需要程序员保证

4. **性能特点**:
   - 接近硬件的性能
   - 无垃圾回收开销
   - 编译器优化友好

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/