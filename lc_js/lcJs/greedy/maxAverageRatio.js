class MaxHeap {
    constructor() {
        this.heap = [];
    }
    
    push(item) {
        this.heap.push(item);
        this.heapifyUp(this.heap.length - 1);
    }
    
    pop() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();
        
        const max = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.heapifyDown(0);
        return max;
    }
    
    heapifyUp(index) {
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (this.heap[parentIndex].gain >= this.heap[index].gain) break;
            [this.heap[parentIndex], this.heap[index]] = [this.heap[index], this.heap[parentIndex]];
            index = parentIndex;
        }
    }
    
    heapifyDown(index) {
        while (true) {
            let maxIndex = index;
            const leftChild = 2 * index + 1;
            const rightChild = 2 * index + 2;
            
            if (leftChild < this.heap.length && this.heap[leftChild].gain > this.heap[maxIndex].gain) {
                maxIndex = leftChild;
            }
            if (rightChild < this.heap.length && this.heap[rightChild].gain > this.heap[maxIndex].gain) {
                maxIndex = rightChild;
            }
            
            if (maxIndex === index) break;
            [this.heap[index], this.heap[maxIndex]] = [this.heap[maxIndex], this.heap[index]];
            index = maxIndex;
        }
    }
    
    size() {
        return this.heap.length;
    }
}

function maxAverageRatio(classes, extraStudents) {
    const calculateGain = (pass, total) => {
        return (pass + 1) / (total + 1) - pass / total;
    };
    
    const heap = new MaxHeap();
    
    // 初始化堆
    for (const [pass, total] of classes) {
        const gain = calculateGain(pass, total);
        heap.push({ gain, pass, total });
    }
    
    // 分配额外学生
    for (let i = 0; i < extraStudents; i++) {
        const { pass, total } = heap.pop();
        const newPass = pass + 1;
        const newTotal = total + 1;
        const newGain = calculateGain(newPass, newTotal);
        heap.push({ gain: newGain, pass: newPass, total: newTotal });
    }
    
    // 计算平均通过率
    let totalRatio = 0;
    while (heap.size() > 0) {
        const { pass, total } = heap.pop();
        totalRatio += pass / total;
    }
    
    return totalRatio / classes.length;
}

// 测试用例
const classes1 = [[1, 2], [3, 5], [2, 2]];
const extraStudents1 = 2;
const result1 = maxAverageRatio(classes1, extraStudents1);
console.log(`测试用例1: ${result1.toFixed(5)}`);

const classes2 = [[2, 4], [3, 9], [4, 5], [2, 10]];
const extraStudents2 = 4;
const result2 = maxAverageRatio(classes2, extraStudents2);
console.log(`测试用例2: ${result2.toFixed(5)}`);