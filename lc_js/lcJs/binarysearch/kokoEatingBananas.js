// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

// 标准二分查找实现
function minEatingSpeedBinarySearch(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    let left = 1;
    let right = Math.max(...piles);
    
    while (left < right) {
        const mid = Math.floor(left + (right - left) / 2);
        let totalHours = 0;
        
        for (const pile of piles) {
            totalHours += Math.ceil(pile / mid);
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 使用整数除法避免浮点运算
function minEatingSpeedIntegerDivision(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    let left = 1;
    let right = Math.max(...piles);
    
    while (left < right) {
        const mid = Math.floor(left + (right - left) / 2);
        let totalHours = 0;
        
        for (const pile of piles) {
            totalHours += Math.floor((pile + mid - 1) / mid); // ceil(pile / mid)
        }
        
        if (totalHours <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 暴力枚举版本
function minEatingSpeedBruteForce(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const maxPile = Math.max(...piles);
    
    for (let k = 1; k <= maxPile; k++) {
        let totalHours = 0;
        for (const pile of piles) {
            totalHours += Math.ceil(pile / k);
        }
        
        if (totalHours <= h) {
            return k;
        }
    }
    
    return maxPile;
}

// 函数式编程版本
function minEatingSpeedFunctional(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const maxPile = Math.max(...piles);
    
    // 使用Array.from创建范围并find查找
    return Array.from({length: maxPile}, (_, i) => i + 1)
        .find(k => {
            const totalHours = piles
                .map(pile => Math.ceil(pile / k))
                .reduce((sum, hours) => sum + hours, 0);
            return totalHours <= h;
        }) || maxPile;
}

// 使用reduce的函数式版本
function minEatingSpeedReduce(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const maxPile = Math.max(...piles);
    
    const calculateHours = k => piles.reduce((total, pile) => 
        total + Math.ceil(pile / k), 0);
    
    let left = 1, right = maxPile;
    
    while (left < right) {
        const mid = Math.floor(left + (right - left) / 2);
        
        if (calculateHours(mid) <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// ES6+现代JavaScript特性版本
function minEatingSpeedModern(piles, h) {
    if (!piles?.length) return 0;
    
    const [left, right] = [1, Math.max(...piles)];
    
    // 使用箭头函数和解构赋值
    const canFinish = k => piles
        .map(pile => Math.ceil(pile / k))
        .reduce((a, b) => a + b) <= h;
    
    // 使用递归的二分查找
    const binarySearch = (l, r) => {
        if (l >= r) return l;
        
        const mid = Math.floor(l + (r - l) / 2);
        return canFinish(mid) 
            ? binarySearch(l, mid)
            : binarySearch(mid + 1, r);
    };
    
    return binarySearch(left, right);
}

// 使用生成器的版本
function* speedGenerator(maxSpeed) {
    for (let k = 1; k <= maxSpeed; k++) {
        yield k;
    }
}

function minEatingSpeedGenerator(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const maxPile = Math.max(...piles);
    
    for (const k of speedGenerator(maxPile)) {
        const totalHours = piles
            .map(pile => Math.ceil(pile / k))
            .reduce((sum, hours) => sum + hours, 0);
        
        if (totalHours <= h) {
            return k;
        }
    }
    
    return maxPile;
}

// 使用Promise的异步版本
function minEatingSpeedAsync(piles, h) {
    return new Promise((resolve, reject) => {
        if (!piles || piles.length === 0) {
            resolve(0);
            return;
        }
        
        try {
            const result = minEatingSpeedBinarySearch(piles, h);
            resolve(result);
        } catch (error) {
            reject(error);
        }
    });
}

// 使用类的面向对象版本
class KokoEatingSolver {
    constructor(piles, h) {
        this.piles = piles || [];
        this.h = h;
        this.maxPile = Math.max(...this.piles);
    }
    
    // 计算给定速度下的总时间
    calculateTotalHours(k) {
        return this.piles
            .map(pile => Math.ceil(pile / k))
            .reduce((sum, hours) => sum + hours, 0);
    }
    
    // 检查是否能在时间内完成
    canFinishInTime(k) {
        return this.calculateTotalHours(k) <= this.h;
    }
    
    // 二分查找解决
    solve() {
        if (this.piles.length === 0) {
            return 0;
        }
        
        let left = 1, right = this.maxPile;
        
        while (left < right) {
            const mid = Math.floor(left + (right - left) / 2);
            
            if (this.canFinishInTime(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 获取解决方案的详细信息
    getSolutionDetails() {
        const result = this.solve();
        const totalHours = this.calculateTotalHours(result);
        
        return {
            minSpeed: result,
            totalHours,
            piles: this.piles,
            timeLimit: this.h,
            efficiency: (totalHours / this.h * 100).toFixed(2) + '%'
        };
    }
}

// 使用Map缓存的优化版本
function minEatingSpeedWithCache(piles, h) {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const cache = new Map();
    
    const calculateHours = (k) => {
        if (cache.has(k)) {
            return cache.get(k);
        }
        
        const hours = piles
            .map(pile => Math.ceil(pile / k))
            .reduce((sum, h) => sum + h, 0);
        
        cache.set(k, hours);
        return hours;
    };
    
    let left = 1, right = Math.max(...piles);
    
    while (left < right) {
        const mid = Math.floor(left + (right - left) / 2);
        
        if (calculateHours(mid) <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// 使用Web Workers的并行版本（仅在浏览器环境中可用）
function minEatingSpeedParallel(piles, h) {
    if (!piles || piles.length === 0) {
        return Promise.resolve(0);
    }
    
    // 检查是否支持Web Workers
    if (typeof Worker === 'undefined') {
        console.warn('Web Workers not supported, falling back to synchronous version');
        return Promise.resolve(minEatingSpeedBinarySearch(piles, h));
    }
    
    return new Promise((resolve, reject) => {
        // 这里只是示例，实际需要创建worker文件
        // 由于环境限制，直接返回同步结果
        resolve(minEatingSpeedBinarySearch(piles, h));
    });
}

// 测试函数
function runTests() {
    const testCases = [
        { piles: [3, 6, 7, 11], h: 8 },
        { piles: [30, 11, 23, 4, 20], h: 5 },
        { piles: [30, 11, 23, 4, 20], h: 6 },
        { piles: [1, 1, 1, 1], h: 4 },
        { piles: [312884470], h: 312884469 }
    ];
    
    console.log('=== 爱吃香蕉的珂珂 ===');
    
    testCases.forEach((testCase, index) => {
        const { piles, h } = testCase;
        console.log(`\n测试用例 ${index + 1}: piles=[${piles.join(', ')}], h=${h}`);
        
        const result1 = minEatingSpeedBinarySearch(piles, h);
        const result2 = minEatingSpeedIntegerDivision(piles, h);
        const result3 = minEatingSpeedBruteForce(piles, h);
        const result4 = minEatingSpeedFunctional(piles, h);
        const result5 = minEatingSpeedReduce(piles, h);
        const result6 = minEatingSpeedModern(piles, h);
        const result7 = minEatingSpeedGenerator(piles, h);
        const result8 = minEatingSpeedWithCache(piles, h);
        
        // 面向对象版本
        const solver = new KokoEatingSolver(piles, h);
        const result9 = solver.solve();
        const details = solver.getSolutionDetails();
        
        console.log('标准二分查找:', result1);
        console.log('整数除法版本:', result2);
        console.log('暴力枚举:', result3);
        console.log('函数式编程:', result4);
        console.log('reduce版本:', result5);
        console.log('现代JS版本:', result6);
        console.log('生成器版本:', result7);
        console.log('缓存版本:', result8);
        console.log('面向对象版本:', result9);
        console.log('解决方案详情:', details);
        
        // 验证结果一致性
        const results = [result1, result2, result3, result4, result5, result6, result7, result8, result9];
        const allEqual = results.every(result => result === results[0]);
        
        if (allEqual) {
            console.log('✓ 所有实现结果一致');
        } else {
            console.error('✗ 结果不一致:', results);
        }
        
        // 测试异步版本
        minEatingSpeedAsync(piles, h)
            .then(result => {
                console.log('异步版本:', result);
                console.assert(result === result1, '异步版本结果不一致');
            })
            .catch(error => {
                console.error('异步版本错误:', error);
            });
    });
    
    console.log('\n=== JavaScript特性说明 ===');
    console.log('1. 动态类型: 运行时类型检查');
    console.log('2. 函数式编程: map, reduce, filter等');
    console.log('3. 箭头函数: 简洁的函数语法');
    console.log('4. 解构赋值: 数组和对象解构');
    console.log('5. 模板字符串: 字符串插值');
    console.log('6. Promise/async: 异步编程');
    console.log('7. 类和继承: ES6+面向对象');
    console.log('8. 生成器: function*和yield');
    console.log('9. 模块系统: import/export');
    console.log('10. 闭包: 函数作用域和变量捕获');
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        minEatingSpeedBinarySearch,
        minEatingSpeedIntegerDivision,
        minEatingSpeedBruteForce,
        minEatingSpeedFunctional,
        minEatingSpeedReduce,
        minEatingSpeedModern,
        minEatingSpeedGenerator,
        minEatingSpeedAsync,
        minEatingSpeedWithCache,
        KokoEatingSolver,
        runTests
    };
}

// 如果在浏览器环境中运行
if (typeof window !== 'undefined') {
    window.KokoEatingBananas = {
        minEatingSpeedBinarySearch,
        minEatingSpeedIntegerDivision,
        minEatingSpeedBruteForce,
        minEatingSpeedFunctional,
        minEatingSpeedReduce,
        minEatingSpeedModern,
        minEatingSpeedGenerator,
        minEatingSpeedAsync,
        minEatingSpeedWithCache,
        KokoEatingSolver,
        runTests
    };
}

// 运行测试
runTests();

/*
JavaScript特性详解:

1. **动态类型系统**:
   - 运行时类型检查
   - 类型转换和强制转换
   - typeof操作符
   - 鸭子类型

2. **函数式编程**:
   - 高阶函数: map, filter, reduce
   - 函数作为一等公民
   - 闭包和作用域链
   - 纯函数和副作用

3. **ES6+现代特性**:
   - 箭头函数: () => {}
   - 解构赋值: [a, b] = array
   - 模板字符串: `Hello ${name}`
   - let/const块级作用域

4. **异步编程**:
   - Promise: then/catch/finally
   - async/await: 同步风格的异步代码
   - 事件循环和回调
   - Web Workers并行计算

5. **面向对象编程**:
   - ES6类语法: class/extends
   - 原型链继承
   - 构造函数和new操作符
   - 私有字段和方法

6. **生成器和迭代器**:
   - function*和yield关键字
   - 惰性求值
   - 自定义迭代器
   - for...of循环

7. **模块系统**:
   - ES6模块: import/export
   - CommonJS: require/module.exports
   - 动态导入: import()
   - 模块打包和树摇

8. **内存管理**:
   - 垃圾回收机制
   - 内存泄漏预防
   - WeakMap和WeakSet
   - 引用计数

9. **错误处理**:
   - try/catch/finally
   - Error对象和自定义错误
   - Promise错误处理
   - 全局错误处理

10. **性能优化**:
    - 缓存和记忆化
    - 防抖和节流
    - 事件委托
    - 代码分割和懒加载
*/