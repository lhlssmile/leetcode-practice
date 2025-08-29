// 力扣第3301题：高度互不相同的最大塔高和
// 题目描述：给定一个数组 maximumHeight，求高度互不相同的最大塔高和

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 比较函数，用于qsort降序排序
 */
int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a; // 降序排序
}

/**
 * 计算高度互不相同的最大塔高和
 * 
 * @param maximumHeight 塔的高度数组
 * @param heightSize 数组大小
 * @return 高度互不相同的最大塔高和，如果无法满足条件则返回-1
 */
long long maximumTotalSum(int* maximumHeight, int heightSize) {
    // 对数组进行降序排序
    qsort(maximumHeight, heightSize, sizeof(int), compare);
    
    int prev = INT_MAX;
    long long ans = 0;
    
    for (int i = 0; i < heightSize; i++) {
        // 确保当前高度严格小于前一个高度
        int curr = maximumHeight[i] < prev - 1 ? maximumHeight[i] : prev - 1;
        if (curr <= 0) return -1;
        ans += curr;
        prev = curr;
    }
    
    return ans;
}

/**
 * 优化版本：一次遍历解决问题
 * 不需要排序，直接找到最大值，然后依次递减
 * 时间复杂度：O(n)，空间复杂度：O(1)
 */
long long maximumTotalSumOptimized(int* maximumHeight, int heightSize) {
    // 找到数组中的最大值
    int maxHeight = 0;
    for (int i = 0; i < heightSize; i++) {
        if (maximumHeight[i] > maxHeight) {
            maxHeight = maximumHeight[i];
        }
    }
    
    // 检查是否可以构建互不相同的塔
    if (maxHeight < heightSize) {
        return -1; // 最大高度小于塔的数量，无法构建互不相同的塔
    }
    
    // 计算最大塔高和：从maxHeight开始，依次递减
    long long sum = 0;
    for (int i = 0; i < heightSize; i++) {
        sum += (maxHeight - i);
    }
    
    return sum;
}

/**
 * 测试函数
 */
void testMaximumTotalSum() {
    // 测试用例1
    int heights1[] = {5, 3, 4, 1, 1};
    int size1 = sizeof(heights1) / sizeof(heights1[0]);
    printf("测试用例1 (原始方法): %lld\n", maximumTotalSum(heights1, size1));
    
    // 重置数组（因为qsort会修改原数组）
    int heights1_copy[] = {5, 3, 4, 1, 1};
    printf("测试用例1 (优化方法): %lld\n", maximumTotalSumOptimized(heights1_copy, size1));
    
    // 测试用例2
    int heights2[] = {6, 5, 3, 9, 2, 7};
    int size2 = sizeof(heights2) / sizeof(heights2[0]);
    printf("测试用例2 (原始方法): %lld\n", maximumTotalSum(heights2, size2));
    
    // 重置数组
    int heights2_copy[] = {6, 5, 3, 9, 2, 7};
    printf("测试用例2 (优化方法): %lld\n", maximumTotalSumOptimized(heights2_copy, size2));
    
    // 测试用例3
    int heights3[] = {3, 2, 1};
    int size3 = sizeof(heights3) / sizeof(heights3[0]);
    printf("测试用例3 (原始方法): %lld\n", maximumTotalSum(heights3, size3));
    
    // 重置数组
    int heights3_copy[] = {3, 2, 1};
    printf("测试用例3 (优化方法): %lld\n", maximumTotalSumOptimized(heights3_copy, size3));
    
    // 测试用例4 - 无法满足条件
    int heights4[] = {1, 1, 1};
    int size4 = sizeof(heights4) / sizeof(heights4[0]);
    printf("测试用例4 (原始方法): %lld\n", maximumTotalSum(heights4, size4));
    
    // 重置数组
    int heights4_copy[] = {1, 1, 1};
    printf("测试用例4 (优化方法): %lld\n", maximumTotalSumOptimized(heights4_copy, size4));
}

/**
 * 主函数
 */
int main() {
    testMaximumTotalSum();
    return 0;
}