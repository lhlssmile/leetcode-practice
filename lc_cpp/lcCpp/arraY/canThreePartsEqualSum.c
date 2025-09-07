#include <stdio.h>
#include <stdbool.h>

bool canThreePartsEqualSum(int* arr, int arrSize) {
    int sum = 0;
    for (int i = 0; i < arrSize; i++) {
        sum += arr[i];
    }
    if (sum % 3 != 0) {
        return false;
    }
    
    int part = 0, currentSum = 0;
    
    for (int i = 0; i < arrSize; i++) {
        currentSum += arr[i];
        if (currentSum == sum / 3) {
            currentSum = 0;
            part++;
        }
    }
    return part >= 3;
}

// 测试函数
void testCanThreePartsEqualSum() {
    printf("=== LeetCode 1013: 将数组分成和相等的三个部分 ===\n");
    
    // 测试用例1
    int arr1[] = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    bool result1 = canThreePartsEqualSum(arr1, size1);
    printf("测试用例1: [0,2,1,-6,6,7,9,-1,2,0,1] -> 结果: %s\n", result1 ? "true" : "false");
    
    // 测试用例2
    int arr2[] = {0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    bool result2 = canThreePartsEqualSum(arr2, size2);
    printf("测试用例2: [0,2,1,-6,6,6,7,9,-1,2,0,1] -> 结果: %s\n", result2 ? "true" : "false");
    
    // 测试用例3
    int arr3[] = {3, 3, 3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    bool result3 = canThreePartsEqualSum(arr3, size3);
    printf("测试用例3: [3,3,3] -> 结果: %s\n", result3 ? "true" : "false");
    
    // 测试用例4
    int arr4[] = {1, 1, 1, 1};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    bool result4 = canThreePartsEqualSum(arr4, size4);
    printf("测试用例4: [1,1,1,1] -> 结果: %s\n", result4 ? "true" : "false");
    
    // 测试用例5
    int arr5[] = {0, 0, 0, 0};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    bool result5 = canThreePartsEqualSum(arr5, size5);
    printf("测试用例5: [0,0,0,0] -> 结果: %s\n", result5 ? "true" : "false");
}

int main() {
    testCanThreePartsEqualSum();
    return 0;
}

/*
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回false
2. 遍历数组，累加当前和
3. 当累加和等于目标值(sum/3)时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)

C语言特性:
1. 手动内存管理
2. 指针操作
3. 结构化编程
4. 标准库函数
*/