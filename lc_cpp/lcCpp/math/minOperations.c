#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll prefix(ll n) {
    ll ans = 0;
    ll base = 1;
    int k = 1;

    while (1) {
        ll nextBase = base * 4;
        ll L = base;
        ll R = nextBase - 1;
        if (n >= R) {
            ans += (R - L + 1) * 1LL * k;
        } else {
            ans += (n - L + 1) * 1LL * k;
            break;
        }
        base = nextBase;
        k++;
    }
    return ans;
}

long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    ll total = 0;
    for (int i = 0; i < queriesSize; i++) {
        ll l = queries[i][0];
        ll r = queries[i][1];
        ll S = prefix(r) - prefix(l - 1);
        total += (S + 1) / 2;
    }
    return total;
}

// 辅助函数：创建二维数组
int** createQueries(int rows, int cols) {
    int** queries = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        queries[i] = (int*)malloc(cols * sizeof(int));
    }
    return queries;
}

// 辅助函数：释放二维数组
void freeQueries(int** queries, int rows) {
    for (int i = 0; i < rows; i++) {
        free(queries[i]);
    }
    free(queries);
}

// 测试函数
void testMinOperations() {
    printf("=== LeetCode 最小操作数问题 ===\n");
    
    // 测试用例1
    int** queries1 = createQueries(3, 2);
    queries1[0][0] = 1; queries1[0][1] = 4;
    queries1[1][0] = 2; queries1[1][1] = 6;
    queries1[2][0] = 3; queries1[2][1] = 8;
    int queriesColSize1[] = {2, 2, 2};
    
    ll result1 = minOperations(queries1, 3, queriesColSize1);
    printf("测试用例1: [1,4] [2,6] [3,8] -> 结果: %lld\n", result1);
    freeQueries(queries1, 3);
    
    // 测试用例2
    int** queries2 = createQueries(2, 2);
    queries2[0][0] = 1; queries2[0][1] = 10;
    queries2[1][0] = 5; queries2[1][1] = 15;
    int queriesColSize2[] = {2, 2};
    
    ll result2 = minOperations(queries2, 2, queriesColSize2);
    printf("测试用例2: [1,10] [5,15] -> 结果: %lld\n", result2);
    freeQueries(queries2, 2);
    
    // 测试用例3
    int** queries3 = createQueries(3, 2);
    queries3[0][0] = 1; queries3[0][1] = 1;
    queries3[1][0] = 2; queries3[1][1] = 2;
    queries3[2][0] = 3; queries3[2][1] = 3;
    int queriesColSize3[] = {2, 2, 2};
    
    ll result3 = minOperations(queries3, 3, queriesColSize3);
    printf("测试用例3: [1,1] [2,2] [3,3] -> 结果: %lld\n", result3);
    freeQueries(queries3, 3);
    
    // 测试prefix函数
    printf("\nprefix函数测试:\n");
    for (int i = 1; i <= 10; i++) {
        printf("prefix(%d) = %lld\n", i, prefix(i));
    }
}

int main() {
    testMinOperations();
    return 0;
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是(S+1)/2

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

C语言特性:
1. 手动内存管理
2. 指针操作
3. 结构化编程
4. 标准库函数
*/