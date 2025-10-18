#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二分查找解法
int countLessEqual(int** matrix, int matrixSize, int target) {
    int n = matrixSize;
    int i = n - 1;
    int j = 0;
    int count = 0;
    
    while (i >= 0 && j < n) {
        if (matrix[i][j] <= target) {
            count += i + 1; // 当前列中有i+1个元素小于等于target
            j++;
        } else {
            i--;
        }
    }
    return count;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int n = matrixSize;
    int lo = matrix[0][0];
    int hi = matrix[n-1][n-1];
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = countLessEqual(matrix, n, mid);
        if (count < k) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

// 最小堆解法
// 堆元素结构
typedef struct {
    int value;
    int row;
    int col;
} HeapNode;

// 最小堆结构
typedef struct {
    HeapNode* nodes;
    int size;
    int capacity;
} MinHeap;

// 创建最小堆
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 释放最小堆
void freeMinHeap(MinHeap* heap) {
    free(heap->nodes);
    free(heap);
}

// 交换堆中两个节点
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 向上调整堆
void heapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    
    while (index > 0 && heap->nodes[parent].value > heap->nodes[index].value) {
        swap(&heap->nodes[parent], &heap->nodes[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// 向下调整堆
void heapifyDown(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
        smallest = left;
    }
    
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&heap->nodes[index], &heap->nodes[smallest]);
        heapifyDown(heap, smallest);
    }
}

// 插入元素到堆
void insert(MinHeap* heap, int value, int row, int col) {
    if (heap->size == heap->capacity) {
        return; // 堆已满
    }
    
    HeapNode newNode = {value, row, col};
    heap->nodes[heap->size] = newNode;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// 从堆中弹出最小元素
HeapNode extractMin(MinHeap* heap) {
    HeapNode minNode = heap->nodes[0];
    
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapifyDown(heap, 0);
    }
    
    return minNode;
}

int kthSmallestHeap(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int n = matrixSize;
    MinHeap* heap = createMinHeap(k);
    
    // 将第一列的元素加入堆
    for (int i = 0; i < n && i < k; i++) {
        insert(heap, matrix[i][0], i, 0);
    }
    
    // 弹出k-1个元素
    HeapNode node;
    for (int i = 1; i < k; i++) {
        node = extractMin(heap);
        int row = node.row;
        int col = node.col;
        
        if (col + 1 < n) {
            insert(heap, matrix[row][col + 1], row, col + 1);
        }
    }
    
    // 返回第k小的元素
    node = extractMin(heap);
    int result = node.value;
    
    freeMinHeap(heap);
    return result;
}

// 测试函数
int main() {
    // 创建测试矩阵1
    int rows1 = 3;
    int cols1 = 3;
    int** matrix1 = (int**)malloc(rows1 * sizeof(int*));
    for (int i = 0; i < rows1; i++) {
        matrix1[i] = (int*)malloc(cols1 * sizeof(int));
    }
    
    // 填充测试矩阵1
    matrix1[0][0] = 1; matrix1[0][1] = 5; matrix1[0][2] = 9;
    matrix1[1][0] = 10; matrix1[1][1] = 11; matrix1[1][2] = 13;
    matrix1[2][0] = 12; matrix1[2][1] = 13; matrix1[2][2] = 15;
    
    int k1 = 8;
    int* colSizes1 = (int*)malloc(rows1 * sizeof(int));
    for (int i = 0; i < rows1; i++) {
        colSizes1[i] = cols1;
    }
    
    printf("Binary Search: %d\n", kthSmallest(matrix1, rows1, colSizes1, k1));
    printf("Heap: %d\n", kthSmallestHeap(matrix1, rows1, colSizes1, k1));
    
    // 创建测试矩阵2
    int rows2 = 2;
    int cols2 = 2;
    int** matrix2 = (int**)malloc(rows2 * sizeof(int*));
    for (int i = 0; i < rows2; i++) {
        matrix2[i] = (int*)malloc(cols2 * sizeof(int));
    }
    
    // 填充测试矩阵2
    matrix2[0][0] = 1; matrix2[0][1] = 2;
    matrix2[1][0] = 1; matrix2[1][1] = 3;
    
    int k2 = 2;
    int* colSizes2 = (int*)malloc(rows2 * sizeof(int));
    for (int i = 0; i < rows2; i++) {
        colSizes2[i] = cols2;
    }
    
    printf("Binary Search: %d\n", kthSmallest(matrix2, rows2, colSizes2, k2));
    printf("Heap: %d\n", kthSmallestHeap(matrix2, rows2, colSizes2, k2));
    
    // 释放内存
    for (int i = 0; i < rows1; i++) {
        free(matrix1[i]);
    }
    free(matrix1);
    free(colSizes1);
    
    for (int i = 0; i < rows2; i++) {
        free(matrix2[i]);
    }
    free(matrix2);
    free(colSizes2);
    
    return 0;
}

/*
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
*/