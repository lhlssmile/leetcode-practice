class Solution {
    // 方法1: 二分扩展法
    findClosestElements(arr: number[], k: number, x: number): number[] {
        const n = arr.length;
        let idx = this.binarySearch(arr, x);
        
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
    }
    
    // 方法2: 滑动窗口法
    findClosestElementsSlidingWindow(arr: number[], k: number, x: number): number[] {
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
    }
    
    // 方法3: 大根堆法
    findClosestElementsMaxHeap(arr: number[], k: number, x: number): number[] {
        const heap = new MaxHeap<[number, number, number]>((a, b) => {
            if (a[0] !== b[0]) return a[0] - b[0];
            return a[1] - b[1];
        });
        
        for (let i = 0; i < arr.length; i++) {
            const distance = Math.abs(arr[i] - x);
            if (heap.size() < k) {
                heap.push([distance, arr[i], i]);
            } else {
                const top = heap.peek();
                if (top && (distance < top[0] || (distance === top[0] && arr[i] < top[1]))) {
                    heap.pop();
                    heap.push([distance, arr[i], i]);
                }
            }
        }
        
        const temp: [number, number][] = [];
        while (heap.size() > 0) {
            const item = heap.pop()!;
            temp.push([item[2], item[1]]);
        }
        
        temp.sort((a, b) => a[0] - b[0]);
        return temp.map(item => item[1]);
    }
    
    private binarySearch(arr: number[], target: number): number {
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
}

// 泛型大根堆实现
class MaxHeap<T> {
    private heap: T[] = [];
    private compare: (a: T, b: T) => number;
    
    constructor(compareFn: (a: T, b: T) => number) {
        this.compare = compareFn;
    }
    
    push(val: T): void {
        this.heap.push(val);
        this.bubbleUp(this.heap.length - 1);
    }
    
    pop(): T | null {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop()!;
        
        const top = this.heap[0];
        this.heap[0] = this.heap.pop()!;
        this.bubbleDown(0);
        return top;
    }
    
    peek(): T | null {
        return this.heap[0] || null;
    }
    
    size(): number {
        return this.heap.length;
    }
    
    private bubbleUp(index: number): void {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.compare(this.heap[index], this.heap[parentIndex]) <= 0) break;
            [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
            index = parentIndex;
        }
    }
    
    private bubbleDown(index: number): void {
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

// 函数式编程解法
const findClosestElementsFunctional = (arr: number[], k: number, x: number): number[] => {
    // 计算所有元素到x的距离
    const distances = arr.map((num, index) => ({
        value: num,
        distance: Math.abs(num - x),
        index
    }));
    
    // 排序并取前k个
    distances.sort((a, b) => {
        if (a.distance !== b.distance) return a.distance - b.distance;
        return a.value - b.value;
    });
    
    // 按原数组顺序返回
    const result = distances.slice(0, k);
    result.sort((a, b) => a.index - b.index);
    return result.map(item => item.value);
};

// 测试
const sol = new Solution();
const arr = [1, 2, 3, 4, 5];
const k = 4, x = 3;

console.log("二分扩展法:", sol.findClosestElements(arr, k, x));
console.log("滑动窗口法:", sol.findClosestElementsSlidingWindow(arr, k, x));
console.log("大根堆法:", sol.findClosestElementsMaxHeap(arr, k, x));
console.log("函数式编程:", findClosestElementsFunctional(arr, k, x));