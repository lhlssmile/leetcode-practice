/**
 * @param {number[]} arr
 * @param {number} k
 * @param {number} x
 * @return {number[]}
 */
// 方法1: 二分扩展法
var findClosestElements = function(arr, k, x) {
    const n = arr.length;
    let idx = binarySearch(arr, x);
    
    let left = idx - 1, right = idx;
    
    while (right - left - 1 < k) {
        if (left < 0) {
            right++;
        } else if (right >= n) {
            left--;
        } else {
            if (x - arr[left] <= arr[right] - x) {
                left--;
            } else {
                right++;
            }
        }
    }
    
    return arr.slice(left + 1, right);
};

function binarySearch(arr, target) {
    let left = 0, right = arr.length;
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// 方法2: 滑动窗口法
var findClosestElementsSlidingWindow = function(arr, k, x) {
    let left = 0, right = arr.length - k;
    
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (x - arr[mid] > arr[mid + k] - x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return arr.slice(left, left + k);
};

// 大根堆实现
class MaxHeap {
    constructor(compareFn) {
        this.heap = [];
        this.compare = compareFn || ((a, b) => a - b);
    }
    
    push(val) {
        this.heap.push(val);
        this.bubbleUp(this.heap.length - 1);
    }
    
    pop() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();
        
        const top = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.bubbleDown(0);
        return top;
    }
    
    peek() {
        return this.heap[0] || null;
    }
    
    size() {
        return this.heap.length;
    }
    
    bubbleUp(index) {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.compare(this.heap[index], this.heap[parentIndex]) <= 0) break;
            [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
            index = parentIndex;
        }
    }
    
    bubbleDown(index) {
        while (true) {
            let largest = index;
            const leftChild = 2 * index + 1;
            const rightChild = 2 * index + 2;
            
            if (leftChild < this.heap.length && 
                this.compare(this.heap[leftChild], this.heap[largest]) > 0) {
                largest = leftChild;
            }
            
            if (rightChild < this.heap.length && 
                this.compare(this.heap[rightChild], this.heap[largest]) > 0) {
                largest = rightChild;
            }
            
            if (largest === index) break;
            [this.heap[index], this.heap[largest]] = [this.heap[largest], this.heap[index]];
            index = largest;
        }
    }
}

// 方法3: 大根堆法
var findClosestElementsMaxHeap = function(arr, k, x) {
    const heap = new MaxHeap((a, b) => {
        if (a[0] !== b[0]) return a[0] - b[0]; // 距离大的在前
        return a[1] - b[1]; // 距离相同时值大的在前
    });
    
    for (let i = 0; i < arr.length; i++) {
        const distance = Math.abs(arr[i] - x);
        if (heap.size() < k) {
            heap.push([distance, arr[i], i]);
        } else {
            const top = heap.peek();
            if (distance < top[0] || (distance === top[0] && arr[i] < top[1])) {
                heap.pop();
                heap.push([distance, arr[i], i]);
            }
        }
    }
    
    const temp = [];
    while (heap.size() > 0) {
        const item = heap.pop();
        temp.push([item[2], item[1]]); // [index, value]
    }
    
    temp.sort((a, b) => a[0] - b[0]);
    return temp.map(item => item[1]);
};

// 方法3优化: 大根堆法 - 提前终止
var findClosestElementsOptimizedHeap = function(arr, k, x) {
    const heap = new MaxHeap((a, b) => {
        if (a[0] !== b[0]) return a[0] - b[0];
        return a[1] - b[1];
    });
    
    for (let i = 0; i < arr.length; i++) {
        const distance = Math.abs(arr[i] - x);
        if (heap.size() < k) {
            heap.push([distance, arr[i], i]);
        } else {
            const top = heap.peek();
            if (distance < top[0] || (distance === top[0] && arr[i] < top[1])) {
                heap.pop();
                heap.push([distance, arr[i], i]);
            } else if (distance > top[0]) {
                break; // 提前终止
            }
        }
    }
    
    const temp = [];
    while (heap.size() > 0) {
        const item = heap.pop();
        temp.push([item[2], item[1]]);
    }
    
    temp.sort((a, b) => a[0] - b[0]);
    return temp.map(item => item[1]);
};

// 测试
const arr = [1, 2, 3, 4, 5];
const k = 4, x = 3;

console.log("二分扩展法:", findClosestElements(arr, k, x));
console.log("滑动窗口法:", findClosestElementsSlidingWindow(arr, k, x));
console.log("大根堆法:", findClosestElementsMaxHeap(arr, k, x));
console.log("优化堆法:", findClosestElementsOptimizedHeap(arr, k, x));