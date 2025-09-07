// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

// 标准二分查找实现
int minEatingSpeedBinarySearch(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    // 找到最大堆
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    int left = 1, right = maxPile;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        long long totalHours = 0;
        
        for (int i = 0; i < pilesSize; i++) {
            totalHours += (piles[i] + mid - 1) / mid; // ceil(piles[i] / mid)
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 使用math.h库的ceil函数
int minEatingSpeedWithCeil(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    int left = 1, right = maxPile;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        long long totalHours = 0;
        
        for (int i = 0; i < pilesSize; i++) {
            totalHours += (long long)ceil((double)piles[i] / mid);
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 暴力枚举版本
int minEatingSpeedBruteForce(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    for (int k = 1; k <= maxPile; k++) {
        long long totalHours = 0;
        for (int i = 0; i < pilesSize; i++) {
            totalHours += (piles[i] + k - 1) / k;
        }
        
        if (totalHours <= h) {
            return k;
        }
    }
    
    return maxPile;
}

// 辅助函数：检查是否能在指定时间内完成
int canFinishInTime(int* piles, int pilesSize, int h, int k) {
    long long totalHours = 0;
    for (int i = 0; i < pilesSize; i++) {
        totalHours += (piles[i] + k - 1) / k;
        if (totalHours > h) {
            return 0; // 提前退出，返回false
        }
    }
    return 1; // 返回true
}

// 优化版本 - 计算理论最小值
int minEatingSpeedOptimized(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    // 计算总香蕉数和最大堆
    long long totalBananas = 0;
    int maxPile = piles[0];
    
    for (int i = 0; i < pilesSize; i++) {
        totalBananas += piles[i];
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    // 理论最小速度
    int minSpeed = (int)((totalBananas + h - 1) / h);
    
    // 如果最小速度就能完成，直接返回
    if (canFinishInTime(piles, pilesSize, h, minSpeed)) {
        return minSpeed;
    }
    
    int left = minSpeed, right = maxPile;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canFinishInTime(piles, pilesSize, h, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 使用函数指针的版本
typedef int (*CalculateHoursFunc)(int pile, int k);

int calculateHoursStandard(int pile, int k) {
    return (pile + k - 1) / k;
}

int calculateHoursWithCeil(int pile, int k) {
    return (int)ceil((double)pile / k);
}

int minEatingSpeedWithFunctionPointer(int* piles, int pilesSize, int h, CalculateHoursFunc calcFunc) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    int left = 1, right = maxPile;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        long long totalHours = 0;
        
        for (int i = 0; i < pilesSize; i++) {
            totalHours += calcFunc(piles[i], mid);
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 使用宏的版本
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CEIL_DIV(a, b) (((a) + (b) - 1) / (b))

int minEatingSpeedWithMacros(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        maxPile = MAX(maxPile, piles[i]);
    }
    
    int left = 1, right = maxPile;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        long long totalHours = 0;
        
        for (int i = 0; i < pilesSize; i++) {
            totalHours += CEIL_DIV(piles[i], mid);
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 递归版本的二分查找
int binarySearchRecursive(int* piles, int pilesSize, int h, int left, int right) {
    if (left >= right) {
        return left;
    }
    
    int mid = left + (right - left) / 2;
    long long totalHours = 0;
    
    for (int i = 0; i < pilesSize; i++) {
        totalHours += (piles[i] + mid - 1) / mid;
    }
    
    if (totalHours <= h) {
        return binarySearchRecursive(piles, pilesSize, h, left, mid);
    } else {
        return binarySearchRecursive(piles, pilesSize, h, mid + 1, right);
    }
}

int minEatingSpeedRecursive(int* piles, int pilesSize, int h) {
    if (piles == NULL || pilesSize == 0) {
        return 0;
    }
    
    int maxPile = piles[0];
    for (int i = 1; i < pilesSize; i++) {
        if (piles[i] > maxPile) {
            maxPile = piles[i];
        }
    }
    
    return binarySearchRecursive(piles, pilesSize, h, 1, maxPile);
}

// 测试函数
void testCase(int* piles, int pilesSize, int h, int caseNum) {
    printf("\n测试用例 %d: piles=[", caseNum);
    for (int i = 0; i < pilesSize; i++) {
        printf("%d", piles[i]);
        if (i < pilesSize - 1) printf(", ");
    }
    printf("], h=%d\n", h);
    
    int result1 = minEatingSpeedBinarySearch(piles, pilesSize, h);
    int result2 = minEatingSpeedWithCeil(piles, pilesSize, h);
    int result3 = minEatingSpeedBruteForce(piles, pilesSize, h);
    int result4 = minEatingSpeedOptimized(piles, pilesSize, h);
    int result5 = minEatingSpeedWithFunctionPointer(piles, pilesSize, h, calculateHoursStandard);
    int result6 = minEatingSpeedWithFunctionPointer(piles, pilesSize, h, calculateHoursWithCeil);
    int result7 = minEatingSpeedWithMacros(piles, pilesSize, h);
    int result8 = minEatingSpeedRecursive(piles, pilesSize, h);
    
    printf("标准二分查找: %d\n", result1);
    printf("使用ceil函数: %d\n", result2);
    printf("暴力枚举: %d\n", result3);
    printf("优化版本: %d\n", result4);
    printf("函数指针(标准): %d\n", result5);
    printf("函数指针(ceil): %d\n", result6);
    printf("宏版本: %d\n", result7);
    printf("递归版本: %d\n", result8);
    
    // 验证结果一致性
    int results[] = {result1, result2, result3, result4, result5, result6, result7, result8};
    int numResults = sizeof(results) / sizeof(results[0]);
    
    for (int i = 1; i < numResults; i++) {
        assert(results[i] == results[0]);
    }
    printf("✓ 所有实现结果一致\n");
}

int main() {
    printf("=== 爱吃香蕉的珂珂 ===\n");
    
    // 测试用例1
    int piles1[] = {3, 6, 7, 11};
    testCase(piles1, 4, 8, 1);
    
    // 测试用例2
    int piles2[] = {30, 11, 23, 4, 20};
    testCase(piles2, 5, 5, 2);
    
    // 测试用例3
    int piles3[] = {30, 11, 23, 4, 20};
    testCase(piles3, 5, 6, 3);
    
    // 测试用例4
    int piles4[] = {1, 1, 1, 1};
    testCase(piles4, 4, 4, 4);
    
    // 测试用例5
    int piles5[] = {312884470};
    testCase(piles5, 1, 312884469, 5);
    
    printf("\n=== C语言特性说明 ===\n");
    printf("1. 指针操作: 直接内存访问和操作\n");
    printf("2. 手动内存管理: malloc/free\n");
    printf("3. 函数指针: 实现回调和多态\n");
    printf("4. 宏定义: 代码生成和条件编译\n");
    printf("5. 结构体: 数据封装\n");
    printf("6. 递归: 函数自调用\n");
    printf("7. 位操作: 高效的位级运算\n");
    printf("8. 预处理器: #include, #define, #ifdef\n");
    printf("9. 静态/动态链接: 代码复用\n");
    printf("10. 系统调用: 与操作系统交互\n");
    
    return 0;
}

/*
C语言特性详解:

1. **指针系统**:
   - 直接内存访问和操作
   - 指针算术运算
   - 多级指针和指针数组
   - 函数指针实现回调

2. **内存管理**:
   - 手动内存分配: malloc, calloc, realloc
   - 手动内存释放: free
   - 栈内存 vs 堆内存
   - 内存泄漏和悬空指针

3. **预处理器**:
   - 宏定义: #define
   - 条件编译: #ifdef, #ifndef, #if
   - 文件包含: #include
   - 宏函数和内联展开

4. **数据结构**:
   - 结构体: struct
   - 联合体: union
   - 枚举: enum
   - 位字段: bit fields

5. **函数特性**:
   - 函数指针和回调
   - 可变参数函数: va_list
   - 递归函数
   - 内联函数: inline

6. **类型系统**:
   - 基本数据类型
   - 类型转换和强制转换
   - const和volatile修饰符
   - typedef类型别名

7. **编译和链接**:
   - 编译过程: 预处理->编译->汇编->链接
   - 静态链接 vs 动态链接
   - 头文件和源文件分离
   - 外部链接和内部链接

8. **位操作**:
   - 位运算符: &, |, ^, ~, <<, >>
   - 位字段操作
   - 掩码和标志位
   - 高效的数值计算

9. **标准库**:
   - stdio.h: 输入输出
   - stdlib.h: 内存管理和工具函数
   - string.h: 字符串操作
   - math.h: 数学函数

10. **系统编程**:
    - 系统调用接口
    - 文件操作
    - 进程和线程
    - 网络编程
*/