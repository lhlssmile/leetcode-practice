/**
 * LeetCode 1854. 人口最多的年份
 * 
 * 给你一个二维整数数组 logs，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。
 * 年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在区间 [birthi, deathi - 1] 内。
 * 注意，人在死亡当年不被计入人口内。
 * 返回 人口最多 的年份。
 * 
 * 算法思路：差分数组
 * 1. 使用差分数组记录每年人口变化
 * 2. 出生年份+1，死亡年份-1
 * 3. 通过前缀和还原每年实际人口
 * 4. 找到人口最多的年份
 * 
 * 时间复杂度：O(n + 101) = O(n)
 * 空间复杂度：O(101) = O(1)
 */

// 差分数组解法
function maximumPopulation(logs) {
    const diff = new Array(101).fill(0);  // 1950-2050年的差分数组
    
    // 构建差分数组
    for (const [birth, death] of logs) {
        diff[birth - 1950] += 1;   // 出生年份人口+1
        diff[death - 1950] -= 1;   // 死亡年份人口-1
    }
    
    let maxPop = 0, year = 1950, curr = 0;
    
    // 通过前缀和还原实际人口，同时找最大值
    for (let i = 0; i < 101; i++) {
        curr += diff[i];
        if (curr > maxPop) {
            maxPop = curr;
            year = 1950 + i;
        }
    }
    
    return year;
}

// 暴力解法（用于对比）
function maximumPopulationBruteForce(logs) {
    let maxPop = 0, resultYear = 1950;
    
    // 枚举每一年
    for (let year = 1950; year <= 2050; year++) {
        let population = 0;
        
        // 统计这一年的人口
        for (const [birth, death] of logs) {
            if (year >= birth && year < death) {
                population++;
            }
        }
        
        // 更新最大人口年份
        if (population > maxPop) {
            maxPop = population;
            resultYear = year;
        }
    }
    
    return resultYear;
}

// 优化版本：使用事件排序
function maximumPopulationEvents(logs) {
    const events = [];  // {year, change}
    
    // 收集所有事件
    for (const [birth, death] of logs) {
        events.push({ year: birth, change: 1 });   // 出生事件
        events.push({ year: death, change: -1 });  // 死亡事件
    }
    
    // 按年份排序，同年份死亡事件在前
    events.sort((a, b) => {
        if (a.year === b.year) {
            return a.change - b.change;  // 死亡事件(-1)在出生事件(1)前
        }
        return a.year - b.year;
    });
    
    let maxPop = 0, resultYear = 1950, currentPop = 0;
    
    // 处理事件
    for (const event of events) {
        currentPop += event.change;
        if (currentPop > maxPop) {
            maxPop = currentPop;
            resultYear = event.year;
        }
    }
    
    return resultYear;
}

// 使用Map的解法
function maximumPopulationMap(logs) {
    const changes = new Map();
    
    // 记录每年的人口变化
    for (const [birth, death] of logs) {
        changes.set(birth, (changes.get(birth) || 0) + 1);   // 出生年份+1
        changes.set(death, (changes.get(death) || 0) - 1);   // 死亡年份-1
    }
    
    // 获取所有年份并排序
    const years = Array.from(changes.keys()).sort((a, b) => a - b);
    
    let maxPop = 0, resultYear = 1950, currentPop = 0;
    
    // 按年份顺序处理变化
    for (const year of years) {
        currentPop += changes.get(year);
        if (currentPop > maxPop) {
            maxPop = currentPop;
            resultYear = year;
        }
    }
    
    return resultYear;
}

// 函数式编程风格解法
function maximumPopulationFunctional(logs) {
    // 构建差分数组
    const diff = logs.reduce((acc, [birth, death]) => {
        acc[birth - 1950] = (acc[birth - 1950] || 0) + 1;
        acc[death - 1950] = (acc[death - 1950] || 0) - 1;
        return acc;
    }, new Array(101).fill(0));
    
    // 计算前缀和并找最大值
    return diff.reduce((result, change, index) => {
        result.curr += change;
        if (result.curr > result.maxPop) {
            result.maxPop = result.curr;
            result.year = 1950 + index;
        }
        return result;
    }, { curr: 0, maxPop: 0, year: 1950 }).year;
}

// 现代JavaScript特性解法
function maximumPopulationModern(logs) {
    // 使用解构和扩展运算符
    const diff = Array(101).fill(0);
    
    // 使用forEach和解构
    logs.forEach(([birth, death]) => {
        diff[birth - 1950]++;
        diff[death - 1950]--;
    });
    
    // 使用reduce计算结果
    const { year } = diff.reduce(
        (acc, change, index) => {
            acc.curr += change;
            if (acc.curr > acc.maxPop) {
                return { ...acc, maxPop: acc.curr, year: 1950 + index };
            }
            return acc;
        },
        { curr: 0, maxPop: 0, year: 1950 }
    );
    
    return year;
}

// 差分数组工具类
class DifferenceArray {
    constructor(start, end) {
        this.diff = new Array(end - start + 1).fill(0);
        this.offset = start;
    }
    
    // 区间更新
    update(left, right, delta) {
        this.diff[left - this.offset] += delta;
        if (right + 1 - this.offset < this.diff.length) {
            this.diff[right + 1 - this.offset] -= delta;
        }
    }
    
    // 获取前缀和数组
    getPrefixSum() {
        const result = new Array(this.diff.length);
        result[0] = this.diff[0];
        for (let i = 1; i < this.diff.length; i++) {
            result[i] = result[i - 1] + this.diff[i];
        }
        return result;
    }
    
    // 找到最大值的索引
    findMaxIndex() {
        const prefixSum = this.getPrefixSum();
        let maxVal = prefixSum[0], maxIdx = 0;
        for (let i = 1; i < prefixSum.length; i++) {
            if (prefixSum[i] > maxVal) {
                maxVal = prefixSum[i];
                maxIdx = i;
            }
        }
        return maxIdx + this.offset;
    }
}

// 使用工具类的解法
function maximumPopulationWithUtil(logs) {
    const diffArray = new DifferenceArray(1950, 2050);
    
    for (const [birth, death] of logs) {
        diffArray.update(birth, death - 1, 1);
    }
    
    return diffArray.findMaxIndex();
}

// 使用生成器的解法
function* populationGenerator(logs) {
    const diff = new Array(101).fill(0);
    
    // 构建差分数组
    for (const [birth, death] of logs) {
        diff[birth - 1950] += 1;
        diff[death - 1950] -= 1;
    }
    
    let curr = 0;
    // 逐年生成人口数据
    for (let i = 0; i < 101; i++) {
        curr += diff[i];
        yield { year: 1950 + i, population: curr };
    }
}

function maximumPopulationGenerator(logs) {
    let maxPop = 0, resultYear = 1950;
    
    for (const { year, population } of populationGenerator(logs)) {
        if (population > maxPop) {
            maxPop = population;
            resultYear = year;
        }
    }
    
    return resultYear;
}

// 异步版本（模拟大数据处理）
async function maximumPopulationAsync(logs) {
    return new Promise((resolve) => {
        // 模拟异步处理
        setTimeout(() => {
            const result = maximumPopulation(logs);
            resolve(result);
        }, 0);
    });
}

// 使用Worker的并行版本（需要Web Workers环境）
function maximumPopulationParallel(logs) {
    if (typeof Worker === 'undefined') {
        // 降级到普通版本
        return maximumPopulation(logs);
    }
    
    return new Promise((resolve, reject) => {
        const worker = new Worker(URL.createObjectURL(new Blob([
            `
            self.onmessage = function(e) {
                const logs = e.data;
                const diff = new Array(101).fill(0);
                
                for (const [birth, death] of logs) {
                    diff[birth - 1950] += 1;
                    diff[death - 1950] -= 1;
                }
                
                let maxPop = 0, year = 1950, curr = 0;
                
                for (let i = 0; i < 101; i++) {
                    curr += diff[i];
                    if (curr > maxPop) {
                        maxPop = curr;
                        year = 1950 + i;
                    }
                }
                
                self.postMessage(year);
            };
            `
        ], { type: 'application/javascript' })));
        
        worker.onmessage = (e) => {
            resolve(e.data);
            worker.terminate();
        };
        
        worker.onerror = reject;
        worker.postMessage(logs);
    });
}

// 链式操作版本
function maximumPopulationChain(logs) {
    return logs
        .reduce((diff, [birth, death]) => {
            diff[birth - 1950] = (diff[birth - 1950] || 0) + 1;
            diff[death - 1950] = (diff[death - 1950] || 0) - 1;
            return diff;
        }, Array(101).fill(0))
        .reduce((acc, change, index) => {
            acc.curr += change;
            return acc.curr > acc.maxPop 
                ? { curr: acc.curr, maxPop: acc.curr, year: 1950 + index }
                : acc;
        }, { curr: 0, maxPop: 0, year: 1950 })
        .year;
}

// 测试函数
function testMaximumPopulation() {
    // 测试用例1
    const logs1 = [[1950, 1961], [1960, 1971], [1970, 1981]];
    console.log('测试用例1 - 差分数组:', maximumPopulation(logs1));        // 期望: 1960
    console.log('测试用例1 - 暴力解法:', maximumPopulationBruteForce(logs1));
    console.log('测试用例1 - 事件解法:', maximumPopulationEvents(logs1));
    console.log('测试用例1 - Map解法:', maximumPopulationMap(logs1));
    console.log('测试用例1 - 函数式:', maximumPopulationFunctional(logs1));
    console.log('测试用例1 - 现代JS:', maximumPopulationModern(logs1));
    console.log('测试用例1 - 工具类:', maximumPopulationWithUtil(logs1));
    console.log('测试用例1 - 生成器:', maximumPopulationGenerator(logs1));
    console.log('测试用例1 - 链式:', maximumPopulationChain(logs1));
    
    // 测试用例2
    const logs2 = [[1993, 1999], [2000, 2010]];
    console.log('测试用例2:', maximumPopulation(logs2));  // 期望: 1993
    
    // 测试用例3：边界情况
    const logs3 = [[1950, 1951], [1951, 1952], [1952, 1953]];
    console.log('测试用例3:', maximumPopulation(logs3));  // 期望: 1950
    
    // 测试用例4：重叠区间
    const logs4 = [[1950, 1960], [1955, 1965], [1958, 1968]];
    console.log('测试用例4:', maximumPopulation(logs4));  // 期望: 1958
    
    // 异步测试
    maximumPopulationAsync(logs1).then(result => {
        console.log('异步版本结果:', result);
    });
}

// 性能测试
function performanceTest() {
    // 生成大量测试数据
    const largeLogs = Array.from({ length: 100000 }, () => {
        const birth = 1950 + Math.floor(Math.random() * 80);
        const death = Math.min(birth + 1 + Math.floor(Math.random() * 20), 2050);
        return [birth, death];
    });
    
    // 测试不同算法的性能
    const algorithms = {
        '差分数组': maximumPopulation,
        '事件排序': maximumPopulationEvents,
        'Map解法': maximumPopulationMap,
        '函数式': maximumPopulationFunctional,
        '现代JS': maximumPopulationModern,
        '链式操作': maximumPopulationChain
    };
    
    for (const [name, algorithm] of Object.entries(algorithms)) {
        const start = performance.now();
        const result = algorithm(largeLogs);
        const duration = performance.now() - start;
        console.log(`${name}耗时: ${duration.toFixed(2)} ms, 结果: ${result}`);
    }
}

// 内存使用分析
function memoryAnalysis() {
    if (typeof performance !== 'undefined' && performance.memory) {
        const before = performance.memory.usedJSHeapSize;
        
        const logs = Array.from({ length: 10000 }, () => {
            const birth = 1950 + Math.floor(Math.random() * 80);
            const death = Math.min(birth + 1 + Math.floor(Math.random() * 20), 2050);
            return [birth, death];
        });
        
        maximumPopulation(logs);
        
        const after = performance.memory.usedJSHeapSize;
        console.log(`内存使用: ${((after - before) / 1024 / 1024).toFixed(2)} MB`);
    } else {
        console.log('内存分析不可用');
    }
}

// 主函数
function main() {
    console.log('=== LeetCode 1854: 人口最多的年份 ===');
    testMaximumPopulation();
    console.log('\n=== 性能测试 ===');
    performanceTest();
    console.log('\n=== 内存分析 ===');
    memoryAnalysis();
}

// 导出函数（Node.js环境）
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        maximumPopulation,
        maximumPopulationBruteForce,
        maximumPopulationEvents,
        maximumPopulationMap,
        maximumPopulationFunctional,
        maximumPopulationModern,
        maximumPopulationWithUtil,
        maximumPopulationGenerator,
        maximumPopulationAsync,
        maximumPopulationChain,
        DifferenceArray,
        testMaximumPopulation,
        performanceTest
    };
}

// 浏览器环境直接运行
if (typeof window !== 'undefined') {
    main();
}

/*
算法特点分析：

1. 差分数组解法 (推荐)
   - 时间复杂度：O(n + 101)
   - 空间复杂度：O(101)
   - 适用于区间更新问题
   - 代码简洁，效率最高

2. 暴力解法
   - 时间复杂度：O(101 * n)
   - 空间复杂度：O(1)
   - 思路直观，但效率较低

3. 事件排序解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 适用于年份范围很大的情况

4. Map解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 自动去重，代码简洁

5. 函数式编程解法
   - 声明式编程风格
   - 代码简洁易读
   - 函数组合

6. 现代JavaScript特性
   - 解构赋值
   - 扩展运算符
   - 箭头函数
   - 模板字符串

7. 异步和并行版本
   - 适用于大数据处理
   - 非阻塞执行
   - Web Workers并行计算

JavaScript特性应用：
- ES6+语法：解构、箭头函数、类
- 数组方法：reduce、forEach、map
- 生成器：yield、迭代器
- 异步编程：Promise、async/await
- Web Workers：并行计算
- 模块系统：import/export
- 性能API：performance.now()
- 内存分析：performance.memory
*/