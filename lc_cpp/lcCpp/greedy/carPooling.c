// C语言版本 - 拼车问题 (LeetCode 1094)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 事件结构体
typedef struct {
    int location;
    int change;
} Event;

// 比较函数，用于排序
int compareEvents(const void* a, const void* b) {
    Event* eventA = (Event*)a;
    Event* eventB = (Event*)b;
    
    if (eventA->location == eventB->location) {
        return eventA->change - eventB->change; // 下车优先（负数在前）
    }
    return eventA->location - eventB->location;
}

// 事件排序法
bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity) {
    // 创建事件数组
    Event* events = (Event*)malloc(tripsSize * 2 * sizeof(Event));
    int eventCount = 0;
    
    // 构建事件列表
    for (int i = 0; i < tripsSize; i++) {
        int passengers = trips[i][0];
        int from = trips[i][1];
        int to = trips[i][2];
        
        events[eventCount++] = (Event){from, passengers};   // 上车事件
        events[eventCount++] = (Event){to, -passengers};    // 下车事件
    }
    
    // 排序事件
    qsort(events, eventCount, sizeof(Event), compareEvents);
    
    int currentPassengers = 0;
    
    // 处理所有事件
    for (int i = 0; i < eventCount; i++) {
        currentPassengers += events[i].change;
        if (currentPassengers > capacity) {
            free(events);
            return false;
        }
    }
    
    free(events);
    return true;
}

// 差分数组法（使用简单数组，假设位置范围不超过1000）
bool carPoolingDiffArray(int** trips, int tripsSize, int* tripsColSize, int capacity) {
    int diff[1001] = {0}; // 假设位置范围[0, 1000]
    
    // 构建差分数组
    for (int i = 0; i < tripsSize; i++) {
        int passengers = trips[i][0];
        int from = trips[i][1];
        int to = trips[i][2];
        
        diff[from] += passengers;
        if (to <= 1000) {
            diff[to] -= passengers;
        }
    }
    
    int currentPassengers = 0;
    
    // 按位置顺序处理
    for (int i = 0; i <= 1000; i++) {
        currentPassengers += diff[i];
        if (currentPassengers > capacity) {
            return false;
        }
    }
    
    return true;
}

// 辅助函数：创建测试用例
int** createTrips(int data[][3], int size, int** colSizes) {
    int** trips = (int**)malloc(size * sizeof(int*));
    *colSizes = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        trips[i] = (int*)malloc(3 * sizeof(int));
        (*colSizes)[i] = 3;
        for (int j = 0; j < 3; j++) {
            trips[i][j] = data[i][j];
        }
    }
    
    return trips;
}

// 释放内存
void freeTrips(int** trips, int size) {
    for (int i = 0; i < size; i++) {
        free(trips[i]);
    }
    free(trips);
}

int main() {
    printf("=== 拼车问题测试 ===\n");
    
    // 测试用例1
    int testData1[][3] = {{2, 1, 5}, {3, 3, 7}};
    int* colSizes1;
    int** trips1 = createTrips(testData1, 2, &colSizes1);
    int capacity1 = 4;
    bool result1_1 = carPooling(trips1, 2, colSizes1, capacity1);
    bool result1_2 = carPoolingDiffArray(trips1, 2, colSizes1, capacity1);
    printf("测试用例 1: trips = [[2,1,5],[3,3,7]], capacity = %d\n", capacity1);
    printf("事件排序法: %s\n", result1_1 ? "true" : "false");
    printf("差分数组法: %s\n", result1_2 ? "true" : "false");
    printf("预期结果: false\n");
    printf("结果: %s\n\n", (!result1_1 && !result1_2) ? "✓" : "✗");
    freeTrips(trips1, 2);
    free(colSizes1);
    
    // 测试用例2
    int testData2[][3] = {{2, 1, 5}, {3, 3, 7}};
    int* colSizes2;
    int** trips2 = createTrips(testData2, 2, &colSizes2);
    int capacity2 = 5;
    bool result2_1 = carPooling(trips2, 2, colSizes2, capacity2);
    bool result2_2 = carPoolingDiffArray(trips2, 2, colSizes2, capacity2);
    printf("测试用例 2: trips = [[2,1,5],[3,3,7]], capacity = %d\n", capacity2);
    printf("事件排序法: %s\n", result2_1 ? "true" : "false");
    printf("差分数组法: %s\n", result2_2 ? "true" : "false");
    printf("预期结果: true\n");
    printf("结果: %s\n\n", (result2_1 && result2_2) ? "✓" : "✗");
    freeTrips(trips2, 2);
    free(colSizes2);
    
    // 测试用例3
    int testData3[][3] = {{2, 1, 5}, {3, 5, 7}};
    int* colSizes3;
    int** trips3 = createTrips(testData3, 2, &colSizes3);
    int capacity3 = 3;
    bool result3_1 = carPooling(trips3, 2, colSizes3, capacity3);
    bool result3_2 = carPoolingDiffArray(trips3, 2, colSizes3, capacity3);
    printf("测试用例 3: trips = [[2,1,5],[3,5,7]], capacity = %d\n", capacity3);
    printf("事件排序法: %s\n", result3_1 ? "true" : "false");
    printf("差分数组法: %s\n", result3_2 ? "true" : "false");
    printf("预期结果: true\n");
    printf("结果: %s\n\n", (result3_1 && result3_2) ? "✓" : "✗");
    freeTrips(trips3, 2);
    free(colSizes3);
    
    // 测试用例4
    int testData4[][3] = {{3, 2, 7}, {3, 7, 9}, {8, 3, 9}};
    int* colSizes4;
    int** trips4 = createTrips(testData4, 3, &colSizes4);
    int capacity4 = 11;
    bool result4_1 = carPooling(trips4, 3, colSizes4, capacity4);
    bool result4_2 = carPoolingDiffArray(trips4, 3, colSizes4, capacity4);
    printf("测试用例 4: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = %d\n", capacity4);
    printf("事件排序法: %s\n", result4_1 ? "true" : "false");
    printf("差分数组法: %s\n", result4_2 ? "true" : "false");
    printf("预期结果: true\n");
    printf("结果: %s\n\n", (result4_1 && result4_2) ? "✓" : "✗");
    freeTrips(trips4, 3);
    free(colSizes4);
    
    return 0;
}

/*
算法说明：
1. 事件排序法：
   - 将每个行程转换为上车和下车事件
   - 按位置排序，同位置时下车优先
   - 模拟整个过程，检查是否超载
   
2. 差分数组法：
   - 使用差分思想，记录每个位置的乘客变化
   - 按位置顺序累加，检查是否超载
   
时间复杂度: O(n log n)
空间复杂度: O(n)
*/