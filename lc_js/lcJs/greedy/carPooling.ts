// TypeScript版本 - 拼车问题 (LeetCode 1094)

// 定义类型
type Trip = [number, number, number]; // [passengers, from, to]
type Event = [number, number]; // [location, change]
type TestCase = [Trip[], number, boolean]; // [trips, capacity, expected]

// 事件接口
interface IEvent {
    location: number;
    change: number;
}

// 事件类
class CarEvent implements IEvent {
    constructor(
        public readonly location: number,
        public readonly change: number
    ) {}
    
    // 比较方法
    compareTo(other: CarEvent): number {
        if (this.location === other.location) {
            return this.change - other.change; // 下车优先
        }
        return this.location - other.location;
    }
}

// 拼车解决方案类
class CarPoolingSolution {
    // 标准实现 - 事件排序法
    public carPooling(trips: Trip[], capacity: number): boolean {
        const events: Event[] = [];
        
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
    public carPoolingDiffArray(trips: Trip[], capacity: number): boolean {
        const diff = new Map<number, number>();
        
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
            currentPassengers += diff.get(pos)!;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
    
    // 使用类的版本
    public carPoolingWithClass(trips: Trip[], capacity: number): boolean {
        const events: CarEvent[] = [];
        
        // 构建事件列表
        for (const [passengers, from, to] of trips) {
            events.push(new CarEvent(from, passengers));   // 上车事件
            events.push(new CarEvent(to, -passengers));    // 下车事件
        }
        
        // 排序事件
        events.sort((a, b) => a.compareTo(b));
        
        let currentPassengers = 0;
        
        // 处理所有事件
        for (const event of events) {
            currentPassengers += event.change;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
}

// 函数式编程版本
const carPoolingFunctional = (trips: Trip[], capacity: number): boolean => {
    const events = trips
        .flatMap(([passengers, from, to]) => [
            [from, passengers] as Event,
            [to, -passengers] as Event
        ])
        .sort((a, b) => a[0] === b[0] ? a[1] - b[1] : a[0] - b[0]);
    
    let currentPassengers = 0;
    
    return events.every(([, change]) => {
        currentPassengers += change;
        return currentPassengers <= capacity;
    });
};

// 泛型版本
function carPoolingGeneric<T extends readonly [number, number, number]>(
    trips: T[], 
    capacity: number
): boolean {
    const events = trips
        .flatMap(([passengers, from, to]) => [
            [from, passengers] as const,
            [to, -passengers] as const
        ])
        .sort((a, b) => a[0] === b[0] ? a[1] - b[1] : a[0] - b[0]);
    
    let currentPassengers = 0;
    
    for (const [, change] of events) {
        currentPassengers += change;
        if (currentPassengers > capacity) {
            return false;
        }
    }
    
    return true;
}

// 类型守卫
function isValidTrip(trip: unknown): trip is Trip {
    return Array.isArray(trip) && 
           trip.length === 3 && 
           trip.every(x => typeof x === 'number') &&
           trip[0] >= 0 && trip[1] >= 0 && trip[2] >= 0 && trip[1] < trip[2];
}

function isValidTrips(trips: unknown): trips is Trip[] {
    return Array.isArray(trips) && trips.every(isValidTrip);
}

// 带验证的版本
function carPoolingWithValidation(
    trips: unknown, 
    capacity: unknown
): boolean | string {
    if (typeof capacity !== 'number' || capacity < 0) {
        return 'Invalid capacity';
    }
    
    if (!isValidTrips(trips)) {
        return 'Invalid trips format';
    }
    
    return carPoolingFunctional(trips, capacity);
}

// 异步版本
async function carPoolingAsync(trips: Trip[], capacity: number): Promise<boolean> {
    return new Promise((resolve) => {
        // 模拟异步处理
        setTimeout(() => {
            const result = carPoolingFunctional(trips, capacity);
            resolve(result);
        }, 10);
    });
}

// 测试函数
async function runTests(): Promise<void> {
    const solution = new CarPoolingSolution();
    
    // 测试用例
    const testCases: TestCase[] = [
        [[[2,1,5],[3,3,7]], 4, false],      // 测试用例1
        [[[2,1,5],[3,3,7]], 5, true],       // 测试用例2
        [[[2,1,5],[3,5,7]], 3, true],       // 测试用例3
        [[[3,2,7],[3,7,9],[8,3,9]], 11, true]  // 测试用例4
    ];
    
    console.log("=== 拼车问题测试 ===");
    
    for (let i = 0; i < testCases.length; i++) {
        const [trips, capacity, expected] = testCases[i];
        
        console.log(`测试用例 ${i + 1}: trips = ${JSON.stringify(trips)}, capacity = ${capacity}`);
        
        // 标准实现
        const result1 = solution.carPooling(trips, capacity);
        console.log(`事件排序法: ${result1}`);
        
        // 差分数组法
        const result2 = solution.carPoolingDiffArray(trips, capacity);
        console.log(`差分数组法: ${result2}`);
        
        // 类版本
        const result3 = solution.carPoolingWithClass(trips, capacity);
        console.log(`类版本: ${result3}`);
        
        // 函数式版本
        const result4 = carPoolingFunctional(trips, capacity);
        console.log(`函数式版本: ${result4}`);
        
        // 泛型版本
        const result5 = carPoolingGeneric(trips, capacity);
        console.log(`泛型版本: ${result5}`);
        
        // 带验证版本
        const result6 = carPoolingWithValidation(trips, capacity);
        console.log(`带验证版本: ${result6}`);
        
        // 异步版本
        const result7 = await carPoolingAsync(trips, capacity);
        console.log(`异步版本: ${result7}`);
        
        console.log(`预期结果: ${expected}`);
        
        const allResults = [result1, result2, result3, result4, result5, result7];
        const allCorrect = allResults.every(r => r === expected) && result6 === expected;
        console.log(`结果: ${allCorrect ? '✓' : '✗'}`);
        console.log();
    }
}

// 导出
export {
    CarPoolingSolution,
    CarEvent,
    carPoolingFunctional,
    carPoolingGeneric,
    carPoolingWithValidation,
    carPoolingAsync,
    isValidTrip,
    isValidTrips,
    type Trip,
    type Event,
    type TestCase,
    type IEvent
};

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    runTests().catch(console.error);
}

/*
TypeScript高级特性说明：

1. **类型系统**:
   - type Trip = [number, number, number] - 元组类型
   - interface IEvent - 接口定义
   - 泛型约束: T extends readonly [number, number, number]

2. **类和接口**:
   - class CarEvent implements IEvent
   - public readonly 属性修饰符
   - 方法重载和类型注解

3. **类型守卫**:
   - function isValidTrip(trip: unknown): trip is Trip
   - 运行时类型检查和类型收窄

4. **泛型编程**:
   - 函数泛型: <T extends ...>
   - 约束泛型参数确保类型安全

5. **联合类型和字面量类型**:
   - boolean | string - 联合类型
   - as const - 常量断言

6. **异步编程**:
   - Promise<boolean> - 泛型Promise
   - async/await语法糖

7. **模块系统**:
   - export/import ES6模块
   - 命名导出和类型导出

8. **高级类型操作**:
   - readonly修饰符
   - 非空断言操作符 !
   - 可选链操作符 ?.

9. **函数式编程**:
   - 箭头函数和类型推断
   - flatMap, every等数组方法
   - 不可变数据处理

10. **编译时类型检查**:
    - 静态类型分析
    - 类型推断和类型收窄
    - 编译时错误检测

TypeScript提供了JavaScript的所有灵活性，同时添加了强大的类型系统，
使得大型项目的开发更加安全和可维护。
*/