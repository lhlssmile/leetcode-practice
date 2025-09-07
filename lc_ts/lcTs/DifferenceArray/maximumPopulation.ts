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

// 类型定义
type LogEntry = [number, number];  // [birth, death]
type PopulationData = {
    year: number;
    population: number;
};

type AlgorithmResult = {
    year: number;
    maxPopulation: number;
    executionTime?: number;
};

interface PopulationCalculator {
    calculate(logs: LogEntry[]): number;
    getComplexity(): { time: string; space: string };
}

// 差分数组解法
function maximumPopulation(logs: LogEntry[]): number {
    const diff: number[] = new Array(101).fill(0);  // 1950-2050年的差分数组
    
    // 构建差分数组
    for (const [birth, death] of logs) {
        diff[birth - 1950] += 1;   // 出生年份人口+1
        diff[death - 1950] -= 1;   // 死亡年份人口-1
    }
    
    let maxPop: number = 0;
    let year: number = 1950;
    let curr: number = 0;
    
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

// 暴力解法类
class BruteForceCalculator implements PopulationCalculator {
    calculate(logs: LogEntry[]): number {
        let maxPop: number = 0;
        let resultYear: number = 1950;
        
        // 枚举每一年
        for (let year = 1950; year <= 2050; year++) {
            let population: number = 0;
            
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
    
    getComplexity(): { time: string; space: string } {
        return { time: 'O(101 * n)', space: 'O(1)' };
    }
}

// 差分数组计算器类
class DifferenceArrayCalculator implements PopulationCalculator {
    calculate(logs: LogEntry[]): number {
        return maximumPopulation(logs);
    }
    
    getComplexity(): { time: string; space: string } {
        return { time: 'O(n + 101)', space: 'O(101)' };
    }
}

// 事件排序解法
interface PopulationEvent {
    year: number;
    change: number;  // +1 for birth, -1 for death
}

class EventSortingCalculator implements PopulationCalculator {
    calculate(logs: LogEntry[]): number {
        const events: PopulationEvent[] = [];
        
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
        
        let maxPop: number = 0;
        let resultYear: number = 1950;
        let currentPop: number = 0;
        
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
    
    getComplexity(): { time: string; space: string } {
        return { time: 'O(n log n)', space: 'O(n)' };
    }
}

// Map解法
class MapBasedCalculator implements PopulationCalculator {
    calculate(logs: LogEntry[]): number {
        const changes = new Map<number, number>();
        
        // 记录每年的人口变化
        for (const [birth, death] of logs) {
            changes.set(birth, (changes.get(birth) || 0) + 1);   // 出生年份+1
            changes.set(death, (changes.get(death) || 0) - 1);   // 死亡年份-1
        }
        
        // 获取所有年份并排序
        const years: number[] = Array.from(changes.keys()).sort((a, b) => a - b);
        
        let maxPop: number = 0;
        let resultYear: number = 1950;
        let currentPop: number = 0;
        
        // 按年份顺序处理变化
        for (const year of years) {
            currentPop += changes.get(year)!;
            if (currentPop > maxPop) {
                maxPop = currentPop;
                resultYear = year;
            }
        }
        
        return resultYear;
    }
    
    getComplexity(): { time: string; space: string } {
        return { time: 'O(n log n)', space: 'O(n)' };
    }
}

// 泛型差分数组工具类
class DifferenceArray<T extends number> {
    private diff: number[];
    private readonly offset: T;
    private readonly size: number;
    
    constructor(start: T, end: T) {
        this.size = end - start + 1;
        this.diff = new Array(this.size).fill(0);
        this.offset = start;
    }
    
    // 区间更新
    update(left: T, right: T, delta: number): void {
        const leftIdx = left - this.offset;
        const rightIdx = right - this.offset;
        
        if (leftIdx >= 0 && leftIdx < this.size) {
            this.diff[leftIdx] += delta;
        }
        
        if (rightIdx + 1 < this.size) {
            this.diff[rightIdx + 1] -= delta;
        }
    }
    
    // 获取前缀和数组
    getPrefixSum(): number[] {
        const result: number[] = new Array(this.size);
        result[0] = this.diff[0];
        
        for (let i = 1; i < this.size; i++) {
            result[i] = result[i - 1] + this.diff[i];
        }
        
        return result;
    }
    
    // 找到最大值的索引
    findMaxIndex(): T {
        const prefixSum = this.getPrefixSum();
        let maxVal = prefixSum[0];
        let maxIdx = 0;
        
        for (let i = 1; i < prefixSum.length; i++) {
            if (prefixSum[i] > maxVal) {
                maxVal = prefixSum[i];
                maxIdx = i;
            }
        }
        
        return (maxIdx + this.offset) as T;
    }
    
    // 获取指定位置的值
    getValue(index: T): number {
        const prefixSum = this.getPrefixSum();
        const idx = index - this.offset;
        return idx >= 0 && idx < this.size ? prefixSum[idx] : 0;
    }
}

// 使用泛型工具类的解法
function maximumPopulationWithGeneric(logs: LogEntry[]): number {
    const diffArray = new DifferenceArray(1950 as const, 2050 as const);
    
    for (const [birth, death] of logs) {
        diffArray.update(birth as any, (death - 1) as any, 1);
    }
    
    return diffArray.findMaxIndex();
}

// 函数式编程解法
const maximumPopulationFunctional = (logs: LogEntry[]): number => {
    // 构建差分数组
    const diff: number[] = logs.reduce((acc: number[], [birth, death]: LogEntry) => {
        acc[birth - 1950] = (acc[birth - 1950] || 0) + 1;
        acc[death - 1950] = (acc[death - 1950] || 0) - 1;
        return acc;
    }, new Array(101).fill(0));
    
    // 计算前缀和并找最大值
    const result = diff.reduce(
        (acc: { curr: number; maxPop: number; year: number }, change: number, index: number) => {
            acc.curr += change;
            if (acc.curr > acc.maxPop) {
                acc.maxPop = acc.curr;
                acc.year = 1950 + index;
            }
            return acc;
        },
        { curr: 0, maxPop: 0, year: 1950 }
    );
    
    return result.year;
};

// 生成器函数
function* populationGenerator(logs: LogEntry[]): Generator<PopulationData, void, unknown> {
    const diff: number[] = new Array(101).fill(0);
    
    // 构建差分数组
    for (const [birth, death] of logs) {
        diff[birth - 1950] += 1;
        diff[death - 1950] -= 1;
    }
    
    let curr: number = 0;
    // 逐年生成人口数据
    for (let i = 0; i < 101; i++) {
        curr += diff[i];
        yield { year: 1950 + i, population: curr };
    }
}

function maximumPopulationGenerator(logs: LogEntry[]): number {
    let maxPop: number = 0;
    let resultYear: number = 1950;
    
    for (const { year, population } of populationGenerator(logs)) {
        if (population > maxPop) {
            maxPop = population;
            resultYear = year;
        }
    }
    
    return resultYear;
}

// 异步版本
async function maximumPopulationAsync(logs: LogEntry[]): Promise<number> {
    return new Promise<number>((resolve) => {
        // 模拟异步处理
        setTimeout(() => {
            const result = maximumPopulation(logs);
            resolve(result);
        }, 0);
    });
}

// 使用装饰器的性能监控版本
function performanceMonitor<T extends any[], R>(
    target: any,
    propertyName: string,
    descriptor: TypedPropertyDescriptor<(...args: T) => R>
): TypedPropertyDescriptor<(...args: T) => R> {
    const method = descriptor.value!;
    
    descriptor.value = function (...args: T): R {
        const start = performance.now();
        const result = method.apply(this, args);
        const duration = performance.now() - start;
        console.log(`${propertyName} 执行时间: ${duration.toFixed(2)} ms`);
        return result;
    };
    
    return descriptor;
}

// 算法管理器类
class PopulationAlgorithmManager {
    private algorithms: Map<string, PopulationCalculator> = new Map();
    
    constructor() {
        this.registerAlgorithm('brute-force', new BruteForceCalculator());
        this.registerAlgorithm('difference-array', new DifferenceArrayCalculator());
        this.registerAlgorithm('event-sorting', new EventSortingCalculator());
        this.registerAlgorithm('map-based', new MapBasedCalculator());
    }
    
    registerAlgorithm(name: string, calculator: PopulationCalculator): void {
        this.algorithms.set(name, calculator);
    }
    
    @performanceMonitor
    calculate(algorithmName: string, logs: LogEntry[]): AlgorithmResult {
        const calculator = this.algorithms.get(algorithmName);
        if (!calculator) {
            throw new Error(`算法 '${algorithmName}' 未找到`);
        }
        
        const start = performance.now();
        const year = calculator.calculate(logs);
        const executionTime = performance.now() - start;
        
        return {
            year,
            maxPopulation: this.getPopulationAtYear(logs, year),
            executionTime
        };
    }
    
    private getPopulationAtYear(logs: LogEntry[], year: number): number {
        return logs.filter(([birth, death]) => year >= birth && year < death).length;
    }
    
    compareAlgorithms(logs: LogEntry[]): Map<string, AlgorithmResult> {
        const results = new Map<string, AlgorithmResult>();
        
        for (const [name] of this.algorithms) {
            try {
                const result = this.calculate(name, logs);
                results.set(name, result);
            } catch (error) {
                console.error(`算法 ${name} 执行失败:`, error);
            }
        }
        
        return results;
    }
    
    getAlgorithmComplexity(algorithmName: string): { time: string; space: string } | null {
        const calculator = this.algorithms.get(algorithmName);
        return calculator ? calculator.getComplexity() : null;
    }
}

// 单例模式的算法管理器
class SingletonAlgorithmManager {
    private static instance: PopulationAlgorithmManager;
    
    static getInstance(): PopulationAlgorithmManager {
        if (!SingletonAlgorithmManager.instance) {
            SingletonAlgorithmManager.instance = new PopulationAlgorithmManager();
        }
        return SingletonAlgorithmManager.instance;
    }
}

// 工厂模式
type AlgorithmType = 'brute-force' | 'difference-array' | 'event-sorting' | 'map-based';

class AlgorithmFactory {
    static createCalculator(type: AlgorithmType): PopulationCalculator {
        switch (type) {
            case 'brute-force':
                return new BruteForceCalculator();
            case 'difference-array':
                return new DifferenceArrayCalculator();
            case 'event-sorting':
                return new EventSortingCalculator();
            case 'map-based':
                return new MapBasedCalculator();
            default:
                throw new Error(`不支持的算法类型: ${type}`);
        }
    }
}

// 策略模式
class PopulationContext {
    private strategy: PopulationCalculator;
    
    constructor(strategy: PopulationCalculator) {
        this.strategy = strategy;
    }
    
    setStrategy(strategy: PopulationCalculator): void {
        this.strategy = strategy;
    }
    
    execute(logs: LogEntry[]): number {
        return this.strategy.calculate(logs);
    }
    
    getComplexity(): { time: string; space: string } {
        return this.strategy.getComplexity();
    }
}

// 观察者模式
interface PopulationObserver {
    update(result: AlgorithmResult): void;
}

class PopulationSubject {
    private observers: PopulationObserver[] = [];
    
    addObserver(observer: PopulationObserver): void {
        this.observers.push(observer);
    }
    
    removeObserver(observer: PopulationObserver): void {
        const index = this.observers.indexOf(observer);
        if (index > -1) {
            this.observers.splice(index, 1);
        }
    }
    
    notifyObservers(result: AlgorithmResult): void {
        for (const observer of this.observers) {
            observer.update(result);
        }
    }
}

class ResultLogger implements PopulationObserver {
    update(result: AlgorithmResult): void {
        console.log(`结果: 年份=${result.year}, 人口=${result.maxPopulation}, 耗时=${result.executionTime?.toFixed(2)}ms`);
    }
}

// 测试函数
function testMaximumPopulation(): void {
    console.log('=== TypeScript版本测试 ===');
    
    // 测试用例
    const testCases: { name: string; logs: LogEntry[]; expected: number }[] = [
        {
            name: '测试用例1',
            logs: [[1950, 1961], [1960, 1971], [1970, 1981]],
            expected: 1960
        },
        {
            name: '测试用例2',
            logs: [[1993, 1999], [2000, 2010]],
            expected: 1993
        },
        {
            name: '测试用例3',
            logs: [[1950, 1951], [1951, 1952], [1952, 1953]],
            expected: 1950
        }
    ];
    
    // 测试所有算法
    const manager = SingletonAlgorithmManager.getInstance();
    
    for (const testCase of testCases) {
        console.log(`\n${testCase.name}:`);
        const results = manager.compareAlgorithms(testCase.logs);
        
        for (const [algorithmName, result] of results) {
            const isCorrect = result.year === testCase.expected;
            console.log(`  ${algorithmName}: ${result.year} ${isCorrect ? '✓' : '✗'} (${result.executionTime?.toFixed(2)}ms)`);
        }
    }
    
    // 测试函数式版本
    console.log('\n函数式版本:', maximumPopulationFunctional(testCases[0].logs));
    
    // 测试生成器版本
    console.log('生成器版本:', maximumPopulationGenerator(testCases[0].logs));
    
    // 测试泛型版本
    console.log('泛型版本:', maximumPopulationWithGeneric(testCases[0].logs));
    
    // 测试异步版本
    maximumPopulationAsync(testCases[0].logs).then(result => {
        console.log('异步版本:', result);
    });
}

// 性能测试
function performanceTest(): void {
    console.log('\n=== 性能测试 ===');
    
    // 生成大量测试数据
    const largeLogs: LogEntry[] = Array.from({ length: 100000 }, (): LogEntry => {
        const birth = 1950 + Math.floor(Math.random() * 80);
        const death = Math.min(birth + 1 + Math.floor(Math.random() * 20), 2050);
        return [birth, death];
    });
    
    const manager = SingletonAlgorithmManager.getInstance();
    const results = manager.compareAlgorithms(largeLogs);
    
    // 按执行时间排序
    const sortedResults = Array.from(results.entries())
        .sort(([, a], [, b]) => (a.executionTime || 0) - (b.executionTime || 0));
    
    console.log('性能排名（从快到慢）:');
    for (const [name, result] of sortedResults) {
        const complexity = manager.getAlgorithmComplexity(name);
        console.log(`  ${name}: ${result.executionTime?.toFixed(2)}ms (${complexity?.time})`);
    }
}

// 内存使用分析
function memoryAnalysis(): void {
    console.log('\n=== 内存分析 ===');
    
    if (typeof performance !== 'undefined' && (performance as any).memory) {
        const memory = (performance as any).memory;
        const before = memory.usedJSHeapSize;
        
        const logs: LogEntry[] = Array.from({ length: 10000 }, (): LogEntry => {
            const birth = 1950 + Math.floor(Math.random() * 80);
            const death = Math.min(birth + 1 + Math.floor(Math.random() * 20), 2050);
            return [birth, death];
        });
        
        maximumPopulation(logs);
        
        const after = memory.usedJSHeapSize;
        console.log(`内存使用: ${((after - before) / 1024 / 1024).toFixed(2)} MB`);
    } else {
        console.log('内存分析不可用');
    }
}

// 主函数
function main(): void {
    console.log('=== LeetCode 1854: 人口最多的年份 (TypeScript版本) ===');
    testMaximumPopulation();
    performanceTest();
    memoryAnalysis();
    
    // 演示设计模式
    console.log('\n=== 设计模式演示 ===');
    
    // 策略模式
    const context = new PopulationContext(AlgorithmFactory.createCalculator('difference-array'));
    const testLogs: LogEntry[] = [[1950, 1961], [1960, 1971], [1970, 1981]];
    console.log('策略模式结果:', context.execute(testLogs));
    
    // 观察者模式
    const subject = new PopulationSubject();
    const logger = new ResultLogger();
    subject.addObserver(logger);
    
    const result: AlgorithmResult = {
        year: 1960,
        maxPopulation: 2,
        executionTime: 1.23
    };
    subject.notifyObservers(result);
}

// 导出（Node.js环境）
export {
    maximumPopulation,
    maximumPopulationFunctional,
    maximumPopulationGenerator,
    maximumPopulationAsync,
    maximumPopulationWithGeneric,
    DifferenceArray,
    PopulationAlgorithmManager,
    AlgorithmFactory,
    PopulationContext,
    testMaximumPopulation,
    performanceTest,
    type LogEntry,
    type PopulationData,
    type AlgorithmResult,
    type PopulationCalculator,
    type AlgorithmType
};

// 浏览器环境直接运行
if (typeof window !== 'undefined') {
    main();
}

/*
TypeScript特性应用总结：

1. 类型系统
   - 基础类型：number, string, boolean
   - 数组类型：number[], LogEntry[]
   - 元组类型：[number, number]
   - 联合类型：AlgorithmType
   - 接口：PopulationCalculator, PopulationObserver
   - 泛型：DifferenceArray<T>, Generator<T>

2. 面向对象编程
   - 类：BruteForceCalculator, DifferenceArray
   - 继承：implements PopulationCalculator
   - 访问修饰符：private, public, protected
   - 静态方法：AlgorithmFactory.createCalculator
   - 抽象：interface定义契约

3. 高级特性
   - 装饰器：@performanceMonitor
   - 泛型约束：T extends number
   - 条件类型：TypedPropertyDescriptor
   - 映射类型：Map<string, PopulationCalculator>
   - 字面量类型：'brute-force' | 'difference-array'

4. 设计模式
   - 单例模式：SingletonAlgorithmManager
   - 工厂模式：AlgorithmFactory
   - 策略模式：PopulationContext
   - 观察者模式：PopulationSubject/Observer

5. 函数式编程
   - 箭头函数：const func = () => {}
   - 高阶函数：Array.reduce, Array.filter
   - 纯函数：maximumPopulationFunctional
   - 不可变性：const, readonly

6. 异步编程
   - Promise：Promise<number>
   - async/await：async function
   - 生成器：function* Generator<T>

7. 模块系统
   - 导入导出：export, import
   - 命名空间：namespace
   - 模块解析：Node.js/浏览器兼容

8. 工具类型
   - Partial<T>：可选属性
   - Required<T>：必需属性
   - Pick<T, K>：选择属性
   - Omit<T, K>：排除属性

算法复杂度对比：
1. 差分数组：O(n + 101) 时间，O(101) 空间 - 最优
2. 暴力解法：O(101 * n) 时间，O(1) 空间
3. 事件排序：O(n log n) 时间，O(n) 空间
4. Map解法：O(n log n) 时间，O(n) 空间

适用场景：
- 年份范围固定且较小：差分数组
- 年份范围很大：事件排序
- 需要动态查询：Map解法
- 内存受限：暴力解法
*/