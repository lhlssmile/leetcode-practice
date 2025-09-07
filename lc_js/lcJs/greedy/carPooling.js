// JavaScript版本 - 拼车问题 (LeetCode 1094)

// 标准实现 - 事件排序法
function carPooling(trips, capacity) {
    const events = [];
    
    // 构建事件列表
    for (const [passengers, from, to] of trips) {
        events.push([from, passengers]);   // 上车事件
        events.push([to, -passengers]);    // 下车事件
    }
    
    // 排序事件：先按位置，再按变化量（下车优先）
    events.sort((a, b) => {
        if (a[0] === b[0]) {
            return a[1] - b[1];
        }
        return a[0] - b[0];
    });
    
    let currentPassengers = 0;
    
    // 处理所有事件
    for (const [location, change] of events) {
        currentPassengers += change;
        if (currentPassengers > capacity) {
            return false;
        }
    }
    
    return true;
}

// 差分数组法
function carPoolingDiffArray(trips, capacity) {
    const diff = new Map();
    
    // 构建差分数组
    for (const [passengers, from, to] of trips) {
        diff.set(from, (diff.get(from) || 0) + passengers);
        diff.set(to, (diff.get(to) || 0) - passengers);
    }
    
    // 按位置排序
    const sortedPositions = Array.from(diff.keys()).sort((a, b) => a - b);
    
    let currentPassengers = 0;
    
    // 按位置顺序处理
    for (const pos of sortedPositions) {
        currentPassengers += diff.get(pos);
        if (currentPassengers > capacity) {
            return false;
        }
    }
    
    return true;
}

function main() {
    // 测试用例
    const testCases = [
        [[[2,1,5],[3,3,7]], 4, false],      // 测试用例1
        [[[2,1,5],[3,3,7]], 5, true],       // 测试用例2
        [[[2,1,5],[3,5,7]], 3, true],       // 测试用例3
        [[[3,2,7],[3,7,9],[8,3,9]], 11, true]  // 测试用例4
    ];
    
    console.log("=== 拼车问题测试 ===");
    
    testCases.forEach(([trips, capacity, expected], i) => {
        const result1 = carPooling(trips, capacity);
        const result2 = carPoolingDiffArray(trips, capacity);
        
        console.log(`测试用例 ${i + 1}: trips = ${JSON.stringify(trips)}, capacity = ${capacity}`);
        console.log(`事件排序法: ${result1}`);
        console.log(`差分数组法: ${result2}`);
        console.log(`预期结果: ${expected}`);
        console.log(`结果: ${result1 === expected && result2 === expected ? '✓' : '✗'}`);
        console.log();
    });
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    main();
}

// 导出函数
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        carPooling,
        carPoolingDiffArray
    };
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