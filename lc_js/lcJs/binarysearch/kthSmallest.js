/**
 * @param {number[][]} matrix
 * @param {number} k
 * @return {number}
 */

// 二分查找解法
var kthSmallest = function(matrix, k) {
    const n = matrix.length;
    let lo = matrix[0][0];
    let hi = matrix[n-1][n-1];
    
    while (lo < hi) {
        const mid = Math.floor(lo + (hi - lo) / 2);
        const count = countLessEqual(matrix, mid);
        if (count < k) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
};

function countLessEqual(matrix, target) {
    const n = matrix.length;
    let i = n - 1;
    let j = 0;
    let count = 0;
    
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

// 最小堆解法
var kthSmallestHeap = function(matrix, k) {
    const n = matrix.length;
    
    // 创建最小堆
    const minHeap = new MinPriorityQueue({ 
        priority: (element) => element.value 
    });
    
    // 将第一列的元素加入堆
    for (let i = 0; i < Math.min(n, k); i++) {
        minHeap.enqueue({ value: matrix[i][0], row: i, col: 0 });
    }
    
    // 弹出k-1个元素
    for (let i = 1; i < k; i++) {
        const { value, row, col } = minHeap.dequeue().element;
        
        if (col + 1 < n) {
            minHeap.enqueue({ value: matrix[row][col + 1], row, col: col + 1 });
        }
    }
    
    return minHeap.dequeue().element.value;
};

// 简单的最小优先队列实现（如果不使用外部库）
class MinPriorityQueue {
    constructor(options) {
        this.elements = [];
        this.priorityFn = options.priority || (x => x);
    }
    
    enqueue(element) {
        this.elements.push(element);
        this._bubbleUp(this.elements.length - 1);
    }
    
    dequeue() {
        if (this.isEmpty()) return null;
        
        const first = this.elements[0];
        const last = this.elements.pop();
        
        if (this.elements.length > 0) {
            this.elements[0] = last;
            this._sinkDown(0);
        }
        
        return { element: first };
    }
    
    isEmpty() {
        return this.elements.length === 0;
    }
    
    _bubbleUp(index) {
        const element = this.elements[index];
        const priority = this.priorityFn(element);
        
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            const parent = this.elements[parentIndex];
            
            if (priority >= this.priorityFn(parent)) break;
            
            this.elements[parentIndex] = element;
            this.elements[index] = parent;
            index = parentIndex;
        }
    }
    
    _sinkDown(index) {
        const length = this.elements.length;
        const element = this.elements[index];
        const priority = this.priorityFn(element);
        
        while (true) {
            const leftChildIndex = 2 * index + 1;
            const rightChildIndex = 2 * index + 2;
            let swapIndex = null;
            let leftChildPriority, rightChildPriority;
            
            if (leftChildIndex < length) {
                const leftChild = this.elements[leftChildIndex];
                leftChildPriority = this.priorityFn(leftChild);
                
                if (leftChildPriority < priority) {
                    swapIndex = leftChildIndex;
                }
            }
            
            if (rightChildIndex < length) {
                const rightChild = this.elements[rightChildIndex];
                rightChildPriority = this.priorityFn(rightChild);
                
                if (
                    (swapIndex === null && rightChildPriority < priority) ||
                    (swapIndex !== null && rightChildPriority < leftChildPriority)
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
function testKthSmallest() {
    // 测试用例1
    const matrix1 = [
        [1, 5, 9],
        [10, 11, 13],
        [12, 13, 15]
    ];
    const k1 = 8;
    console.log("Binary Search:", kthSmallest(matrix1, k1));
    console.log("Heap:", kthSmallestHeap(matrix1, k1));
    
    // 测试用例2
    const matrix2 = [
        [1, 2],
        [1, 3]
    ];
    const k2 = 2;
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