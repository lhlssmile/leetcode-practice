// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

// 类型定义
type Pile = number;
type Hours = number;
type Speed = number;
type Result = number;

// 接口定义
interface EatingStrategy {
    calculateHours(pile: Pile, speed: Speed): Hours;
}

interface SolutionResult {
    minSpeed: Speed;
    totalHours: Hours;
    piles: Pile[];
    timeLimit: Hours;
    efficiency: string;
}

interface BinarySearchable<T> {
    binarySearch(predicate: (value: T) => boolean): T | null;
}

// 枚举定义
enum SolutionMethod {
    BINARY_SEARCH = 'binary_search',
    BRUTE_FORCE = 'brute_force',
    FUNCTIONAL = 'functional',
    OPTIMIZED = 'optimized'
}

// 标准二分查找实现
function minEatingSpeedBinarySearch(piles: Pile[], h: Hours): Result {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    let left: Speed = 1;
    let right: Speed = Math.max(...piles);
    
    while (left < right) {
        const mid: Speed = Math.floor(left + (right - left) / 2);
        let totalHours: Hours = 0;
        
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

// 使用泛型的二分查找
function binarySearchGeneric<T>(
    start: T, 
    end: T, 
    predicate: (value: T) => boolean,
    increment: (value: T) => T,
    decrement: (value: T) => T,
    compare: (a: T, b: T) => number,
    middle: (a: T, b: T) => T
): T {
    let left = start;
    let right = end;
    
    while (compare(left, right) < 0) {
        const mid = middle(left, right);
        
        if (predicate(mid)) {
            right = mid;
        } else {
            left = increment(mid);
        }
    }
    
    return left;
}

// 数字类型的二分查找特化
function minEatingSpeedGeneric(piles: Pile[], h: Hours): Result {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const canFinish = (speed: Speed): boolean => {
        const totalHours = piles
            .map(pile => Math.ceil(pile / speed))
            .reduce((sum, hours) => sum + hours, 0);
        return totalHours <= h;
    };
    
    return binarySearchGeneric(
        1,
        Math.max(...piles),
        canFinish,
        (x: number) => x + 1,
        (x: number) => x - 1,
        (a: number, b: number) => a - b,
        (a: number, b: number) => Math.floor(a + (b - a) / 2)
    );
}

// 策略模式实现
class StandardStrategy implements EatingStrategy {
    calculateHours(pile: Pile, speed: Speed): Hours {
        return Math.ceil(pile / speed);
    }
}

class IntegerDivisionStrategy implements EatingStrategy {
    calculateHours(pile: Pile, speed: Speed): Hours {
        return Math.floor((pile + speed - 1) / speed);
    }
}

// 抽象基类
abstract class BaseSolver {
    protected piles: Pile[];
    protected h: Hours;
    
    constructor(piles: Pile[], h: Hours) {
        this.piles = piles;
        this.h = h;
    }
    
    abstract solve(): Result;
    
    protected getMaxPile(): Pile {
        return Math.max(...this.piles);
    }
    
    protected calculateTotalHours(speed: Speed, strategy: EatingStrategy = new StandardStrategy()): Hours {
        return this.piles
            .map(pile => strategy.calculateHours(pile, speed))
            .reduce((sum, hours) => sum + hours, 0);
    }
}

// 具体实现类
class BinarySearchSolver extends BaseSolver {
    private strategy: EatingStrategy;
    
    constructor(piles: Pile[], h: Hours, strategy: EatingStrategy = new StandardStrategy()) {
        super(piles, h);
        this.strategy = strategy;
    }
    
    solve(): Result {
        if (this.piles.length === 0) {
            return 0;
        }
        
        let left: Speed = 1;
        let right: Speed = this.getMaxPile();
        
        while (left < right) {
            const mid: Speed = Math.floor(left + (right - left) / 2);
            const totalHours = this.calculateTotalHours(mid, this.strategy);
            
            if (totalHours <= this.h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
}

class OptimizedSolver extends BaseSolver {
    solve(): Result {
        if (this.piles.length === 0) {
            return 0;
        }
        
        // 计算理论最小速度
        const totalBananas = this.piles.reduce((sum, pile) => sum + pile, 0);
        const minSpeed = Math.ceil(totalBananas / this.h);
        const maxSpeed = this.getMaxPile();
        
        // 如果最小速度就能完成，直接返回
        if (this.calculateTotalHours(minSpeed) <= this.h) {
            return minSpeed;
        }
        
        let left = minSpeed;
        let right = maxSpeed;
        
        while (left < right) {
            const mid = Math.floor(left + (right - left) / 2);
            
            if (this.calculateTotalHours(mid) <= this.h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
}

// 工厂模式
class SolverFactory {
    static createSolver(method: SolutionMethod, piles: Pile[], h: Hours): BaseSolver {
        switch (method) {
            case SolutionMethod.BINARY_SEARCH:
                return new BinarySearchSolver(piles, h);
            case SolutionMethod.OPTIMIZED:
                return new OptimizedSolver(piles, h);
            default:
                throw new Error(`Unsupported solution method: ${method}`);
        }
    }
}

// 函数式编程版本
const minEatingSpeedFunctional = (piles: Pile[], h: Hours): Result => {
    if (!piles?.length) return 0;
    
    const calculateHours = (speed: Speed): Hours => 
        piles.reduce((total, pile) => total + Math.ceil(pile / speed), 0);
    
    const canFinish = (speed: Speed): boolean => calculateHours(speed) <= h;
    
    const binarySearch = (left: Speed, right: Speed): Speed => {
        if (left >= right) return left;
        
        const mid = Math.floor(left + (right - left) / 2);
        return canFinish(mid) 
            ? binarySearch(left, mid)
            : binarySearch(mid + 1, right);
    };
    
    return binarySearch(1, Math.max(...piles));
};

// 使用装饰器的版本
function measureTime(target: any, propertyName: string, descriptor: PropertyDescriptor) {
    const method = descriptor.value;
    
    descriptor.value = function (...args: any[]) {
        const start = performance.now();
        const result = method.apply(this, args);
        const end = performance.now();
        console.log(`${propertyName} 执行时间: ${(end - start).toFixed(2)}ms`);
        return result;
    };
}

function validate(target: any, propertyName: string, descriptor: PropertyDescriptor) {
    const method = descriptor.value;
    
    descriptor.value = function (piles: Pile[], h: Hours, ...args: any[]) {
        if (!Array.isArray(piles)) {
            throw new Error('piles must be an array');
        }
        if (typeof h !== 'number' || h <= 0) {
            throw new Error('h must be a positive number');
        }
        if (piles.some(pile => typeof pile !== 'number' || pile <= 0)) {
            throw new Error('all piles must be positive numbers');
        }
        
        return method.apply(this, [piles, h, ...args]);
    };
}

// 带装饰器的解决方案类
class DecoratedSolver {
    @measureTime
    @validate
    solve(piles: Pile[], h: Hours): Result {
        return minEatingSpeedBinarySearch(piles, h);
    }
    
    @measureTime
    solveOptimized(piles: Pile[], h: Hours): Result {
        const solver = new OptimizedSolver(piles, h);
        return solver.solve();
    }
}

// 异步版本
async function minEatingSpeedAsync(piles: Pile[], h: Hours): Promise<Result> {
    return new Promise((resolve, reject) => {
        try {
            // 模拟异步计算
            setTimeout(() => {
                const result = minEatingSpeedBinarySearch(piles, h);
                resolve(result);
            }, 0);
        } catch (error) {
            reject(error);
        }
    });
}

// 使用生成器的版本
function* speedGenerator(maxSpeed: Speed): Generator<Speed, void, unknown> {
    for (let k = 1; k <= maxSpeed; k++) {
        yield k;
    }
}

function minEatingSpeedGenerator(piles: Pile[], h: Hours): Result {
    if (!piles || piles.length === 0) {
        return 0;
    }
    
    const maxPile = Math.max(...piles);
    
    for (const speed of speedGenerator(maxPile)) {
        const totalHours = piles
            .map(pile => Math.ceil(pile / speed))
            .reduce((sum, hours) => sum + hours, 0);
        
        if (totalHours <= h) {
            return speed;
        }
    }
    
    return maxPile;
}

// 高级类型和工具类型
type SolutionFunction = (piles: Pile[], h: Hours) => Result;
type AsyncSolutionFunction = (piles: Pile[], h: Hours) => Promise<Result>;

interface SolutionMethods {
    readonly [SolutionMethod.BINARY_SEARCH]: SolutionFunction;
    readonly [SolutionMethod.BRUTE_FORCE]: SolutionFunction;
    readonly [SolutionMethod.FUNCTIONAL]: SolutionFunction;
    readonly [SolutionMethod.OPTIMIZED]: SolutionFunction;
}

// 解决方案注册表
class SolutionRegistry {
    private methods: Partial<SolutionMethods> = {};
    
    register(method: SolutionMethod, fn: SolutionFunction): void {
        this.methods[method] = fn;
    }
    
    solve(method: SolutionMethod, piles: Pile[], h: Hours): Result {
        const fn = this.methods[method];
        if (!fn) {
            throw new Error(`Method ${method} not registered`);
        }
        return fn(piles, h);
    }
    
    getAllMethods(): SolutionMethod[] {
        return Object.keys(this.methods) as SolutionMethod[];
    }
}

// 测试用例类型
interface TestCase {
    piles: Pile[];
    h: Hours;
    expected?: Result;
}

// 测试运行器
class TestRunner {
    private testCases: TestCase[] = [
        { piles: [3, 6, 7, 11], h: 8 },
        { piles: [30, 11, 23, 4, 20], h: 5 },
        { piles: [30, 11, 23, 4, 20], h: 6 },
        { piles: [1, 1, 1, 1], h: 4 },
        { piles: [312884470], h: 312884469 }
    ];
    
    async runAllTests(): Promise<void> {
        console.log('=== 爱吃香蕉的珂珂 (TypeScript版本) ===');
        
        const registry = new SolutionRegistry();
        registry.register(SolutionMethod.BINARY_SEARCH, minEatingSpeedBinarySearch);
        registry.register(SolutionMethod.FUNCTIONAL, minEatingSpeedFunctional);
        
        const decoratedSolver = new DecoratedSolver();
        
        for (let i = 0; i < this.testCases.length; i++) {
            const { piles, h } = this.testCases[i];
            console.log(`\n测试用例 ${i + 1}: piles=[${piles.join(', ')}], h=${h}`);
            
            // 同步方法测试
            const result1 = minEatingSpeedBinarySearch(piles, h);
            const result2 = minEatingSpeedGeneric(piles, h);
            const result3 = minEatingSpeedFunctional(piles, h);
            const result4 = minEatingSpeedGenerator(piles, h);
            
            // 面向对象方法测试
            const binarySolver = new BinarySearchSolver(piles, h);
            const optimizedSolver = new OptimizedSolver(piles, h);
            const result5 = binarySolver.solve();
            const result6 = optimizedSolver.solve();
            
            // 工厂模式测试
            const factorySolver = SolverFactory.createSolver(SolutionMethod.BINARY_SEARCH, piles, h);
            const result7 = factorySolver.solve();
            
            // 装饰器测试
            const result8 = decoratedSolver.solve(piles, h);
            
            console.log('标准二分查找:', result1);
            console.log('泛型版本:', result2);
            console.log('函数式版本:', result3);
            console.log('生成器版本:', result4);
            console.log('面向对象(二分):', result5);
            console.log('面向对象(优化):', result6);
            console.log('工厂模式:', result7);
            console.log('装饰器版本:', result8);
            
            // 异步测试
            try {
                const result9 = await minEatingSpeedAsync(piles, h);
                console.log('异步版本:', result9);
                
                // 验证结果一致性
                const results = [result1, result2, result3, result4, result5, result6, result7, result8, result9];
                const allEqual = results.every(result => result === results[0]);
                
                if (allEqual) {
                    console.log('✓ 所有实现结果一致');
                } else {
                    console.error('✗ 结果不一致:', results);
                }
            } catch (error) {
                console.error('异步测试失败:', error);
            }
        }
        
        this.printFeatureExplanation();
    }
    
    private printFeatureExplanation(): void {
        console.log('\n=== TypeScript特性说明 ===');
        console.log('1. 静态类型: 编译时类型检查');
        console.log('2. 接口和类型: interface, type, enum');
        console.log('3. 泛型: <T>, 类型参数和约束');
        console.log('4. 装饰器: @decorator语法');
        console.log('5. 类和继承: class, extends, abstract');
        console.log('6. 模块系统: import/export');
        console.log('7. 高级类型: 联合类型、交叉类型');
        console.log('8. 类型守卫: typeof, instanceof');
        console.log('9. 映射类型: Partial, Required, Pick');
        console.log('10. 编译时优化: 类型擦除和优化');
    }
}

// 主函数
async function main(): Promise<void> {
    const testRunner = new TestRunner();
    await testRunner.runAllTests();
}

// 导出
export {
    minEatingSpeedBinarySearch,
    minEatingSpeedGeneric,
    minEatingSpeedFunctional,
    minEatingSpeedAsync,
    minEatingSpeedGenerator,
    BinarySearchSolver,
    OptimizedSolver,
    SolverFactory,
    DecoratedSolver,
    TestRunner,
    SolutionMethod,
    type Pile,
    type Hours,
    type Speed,
    type Result,
    type TestCase,
    type SolutionResult,
    interface EatingStrategy
};

// 如果直接运行此文件
if (require.main === module) {
    main().catch(console.error);
}

/*
TypeScript特性详解:

1. **静态类型系统**:
   - 编译时类型检查
   - 类型推断和注解
   - 严格的null检查
   - 类型安全的重构

2. **接口和类型**:
   - interface定义对象结构
   - type别名和联合类型
   - enum枚举类型
   - 可选属性和只读属性

3. **泛型编程**:
   - 类型参数<T>
   - 泛型约束extends
   - 条件类型和映射类型
   - 工具类型Partial, Required等

4. **高级类型特性**:
   - 联合类型: A | B
   - 交叉类型: A & B
   - 字面量类型
   - 模板字面量类型

5. **装饰器系统**:
   - 类装饰器
   - 方法装饰器
   - 属性装饰器
   - 参数装饰器

6. **类和继承**:
   - class关键字
   - extends继承
   - abstract抽象类
   - 访问修饰符private/protected/public

7. **模块系统**:
   - ES6模块语法
   - 命名空间namespace
   - 模块解析策略
   - 声明文件.d.ts

8. **类型守卫**:
   - typeof类型守卫
   - instanceof类型守卫
   - 自定义类型守卫
   - 断言函数

9. **编译配置**:
   - tsconfig.json配置
   - 编译选项和严格模式
   - 路径映射和模块解析
   - 增量编译

10. **与JavaScript互操作**:
    - 渐进式采用
    - any类型的使用
    - 第三方库的类型定义
    - JavaScript代码的类型化
*/