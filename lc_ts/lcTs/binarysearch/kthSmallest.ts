/**
 * LeetCode 378: Kth Smallest Element in a Sorted Matrix
 * 在一个n x n的矩阵中，每行和每列元素均按升序排序，找到矩阵中第k小的元素
 */

// 二分查找解法
function kthSmallest(matrix: number[][], k: number): number {
    const n: number = matrix.length;
    let lo: number = matrix[0][0];
    let hi: number = matrix[n-1][n-1];
    
    while (lo < hi) {
        const mid: number = Math.floor(lo + (hi - lo) / 2);
        const count: number = countLessEqual(matrix, mid);
        if (count < k) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

function countLessEqual(matrix: number[][], target: number): number {
    const n: number = matrix.length;
    let i: number = n - 1;
    let j: number = 0;
    let count: number = 0;
    
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

// 堆元素接口
interface HeapElement {
    value: number;
    row: number;
    col: number;
}

// 最小堆解法
function kthSmallestHeap(matrix: number[][], k: number): number {
    const n: number = matrix.length;
    const minHeap: MinPriorityQueue<HeapElement> = new MinPriorityQueue<HeapElement>(
        (a, b) => a.value - b.value
    );
    
    // 将第一列的元素加入堆
    for (let i = 0; i < Math.min(n, k); i++) {
        minHeap.enqueue({ value: matrix[i][0], row: i, col: 0 });
    }
    
    // 弹出k-1个元素
    for (let i = 1; i < k; i++) {
        const { value, row, col } = minHeap.dequeue()!;
        
        if (col + 1 < n) {
            minHeap.enqueue({ value: matrix[row][col + 1], row, col: col + 1 });
        }
    }
    
    return minHeap.dequeue()!.value;
}

// 简单的最小优先队列实现
class MinPriorityQueue<T> {
    private elements: T[] = [];
    private comparator: (a: T, b: T) => number;
    
    constructor(comparator: (a: T, b: T) => number) {
        this.comparator = comparator;
    }
    
    enqueue(element: T): void {
        this.elements.push(element);
        this.bubbleUp(this.elements.length - 1);
    }
    
    dequeue(): T | null {
        if (this.isEmpty()) return null;
        
        const first = this.elements[0];
        const last = this.elements.pop()!;
        
        if (this.elements.length > 0) {
            this.elements[0] = last;
            this.sinkDown(0);
        }
        
        return first;
    }
    
    isEmpty(): boolean {
        return this.elements.length === 0;
    }
    
    private bubbleUp(index: number): void {
        const element = this.elements[index];
        
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            const parent = this.elements[parentIndex];
            
            if (this.comparator(element, parent) >= 0) break;
            
            this.elements[parentIndex] = element;
            this.elements[index] = parent;
            index = parentIndex;
        }
    }
    
    private sinkDown(index: number): void {
        const length = this.elements.length;
        const element = this.elements[index];
        
        while (true) {
            const leftChildIndex = 2 * index + 1;
            const rightChildIndex = 2 * index + 2;
            let swapIndex: number | null = null;
            
            if (leftChildIndex < length) {
                const leftChild = this.elements[leftChildIndex];
                
                if (this.comparator(leftChild, element) < 0) {
                    swapIndex = leftChildIndex;
                }
            }
            
            if (rightChildIndex < length) {
                const rightChild = this.elements[rightChildIndex];
                
                if (
                    (swapIndex === null && this.comparator(rightChild, element) < 0) ||
                    (swapIndex !== null && this.comparator(rightChild, this.elements[swapIndex]) < 0)
                ) {
                    swapIndex = rightChildIndex;
                }
            }
            
            if (swapIndex === null) break;
            
            this.elements[index] = this.elements[swapIndex];
            this.elements[swapIndex] = element;
            index = swapIndex;
        }
    }
}

// 测试函数
function testKthSmallest(): void {
    // 测试用例1
    const matrix1: number[][] = [
        [1, 5, 9],
        [10, 11, 13],
        [12, 13, 15]
    ];
    const k1: number = 8;
    console.log("Binary Search:", kthSmallest(matrix1, k1));
    console.log("Heap:", kthSmallestHeap(matrix1, k1));
    
    // 测试用例2
    const matrix2: number[][] = [
        [1, 2],
        [1, 3]
    ];
    const k2: number = 2;
    console.log("Binary Search:", kthSmallest(matrix2, k2));
    console.log("Heap:", kthSmallestHeap(matrix2, k2));
}

testKthSmallest();

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