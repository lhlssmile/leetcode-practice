// TypeScript版本 - 展示类型安全和高级TypeScript特性

// 定义类型别名
type Digit = string;
type Stack = Digit[];
type ProcessResult = [Stack, number];

// 定义接口
interface RemoveKdigitsStrategy {
    execute(num: string, k: number): string;
}

// 定义枚举
enum OperationType {
    REMOVE = 'remove',
    ADD = 'add',
    TRIM = 'trim'
}

// 定义操作记录接口
interface Operation {
    type: OperationType;
    digit: Digit;
    stack: Stack;
    step: number;
}

// 泛型工具类型
type ProcessorState<T> = {
    stack: T[];
    remainingOperations: number;
    operations: Operation[];
};

// 主要解决方案类
class RemoveKdigitsSolution {
    // 标准实现
    public removeKdigits(num: string, k: number): string {
        const stack: Stack = [];
        let remainingK = k;
        
        for (const digit of num) {
            // 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
            while (stack.length > 0 && remainingK > 0 && stack[stack.length - 1] > digit) {
                stack.pop();
                remainingK--;
            }
            stack.push(digit);
        }
        
        // 如果还没删完，从后面删
        while (remainingK > 0 && stack.length > 0) {
            stack.pop();
            remainingK--;
        }
        
        // 去掉前导零
        const result = stack.join('').replace(/^0+/, '');
        return result || '0';
    }
    
    // 函数式编程版本，使用泛型和高阶函数
    public removeKdigitsFunctional(num: string, k: number): string {
        const processDigit = (acc: ProcessResult, digit: Digit): ProcessResult => {
            const [stack, remainingK] = acc;
            
            // 移除比当前数字大的栈顶元素
            while (stack.length > 0 && remainingK > 0 && stack[stack.length - 1] > digit) {
                stack.pop();
                remainingK--;
            }
            
            stack.push(digit);
            return [stack, remainingK];
        };
        
        const [resultStack, remainingK] = [...num].reduce(processDigit, [[], k] as ProcessResult);
        
        // 处理剩余删除次数
        const trimmed = remainingK > 0 
            ? resultStack.slice(0, resultStack.length - remainingK)
            : resultStack;
        
        return this.formatResult(trimmed);
    }
    
    // 使用装饰器模式的版本（模拟装饰器）
    public removeKdigitsWithLogging(num: string, k: number): string {
        const startTime = performance.now();
        console.log(`开始处理: num='${num}', k=${k}`);
        
        const result = this.removeKdigits(num, k);
        
        const endTime = performance.now();
        console.log(`处理完成: 结果='${result}', 耗时=${(endTime - startTime).toFixed(2)}ms`);
        
        return result;
    }
    
    // 私有辅助方法
    private formatResult(stack: Stack): string {
        const result = stack.join('').replace(/^0+/, '');
        return result || '0';
    }
}

// 策略模式实现
class StandardStrategy implements RemoveKdigitsStrategy {
    execute(num: string, k: number): string {
        return new RemoveKdigitsSolution().removeKdigits(num, k);
    }
}

class FunctionalStrategy implements RemoveKdigitsStrategy {
    execute(num: string, k: number): string {
        return new RemoveKdigitsSolution().removeKdigitsFunctional(num, k);
    }
}

// 上下文类
class RemoveKdigitsContext {
    private strategy: RemoveKdigitsStrategy;
    
    constructor(strategy: RemoveKdigitsStrategy) {
        this.strategy = strategy;
    }
    
    public setStrategy(strategy: RemoveKdigitsStrategy): void {
        this.strategy = strategy;
    }
    
    public execute(num: string, k: number): string {
        return this.strategy.execute(num, k);
    }
}

// 泛型处理器类
class DigitProcessor<T extends string | number> {
    private operations: Operation[] = [];
    
    public process(input: T[], k: number): T[] {
        const stack: T[] = [];
        let remainingK = k;
        let step = 0;
        
        for (const item of input) {
            while (stack.length > 0 && remainingK > 0 && this.compare(stack[stack.length - 1], item)) {
                const removed = stack.pop()!;
                remainingK--;
                
                this.operations.push({
                    type: OperationType.REMOVE,
                    digit: String(removed),
                    stack: [...stack].map(String),
                    step: step++
                });
            }
            
            stack.push(item);
            this.operations.push({
                type: OperationType.ADD,
                digit: String(item),
                stack: [...stack].map(String),
                step: step++
            });
        }
        
        // 处理剩余删除次数
        while (remainingK > 0 && stack.length > 0) {
            const removed = stack.pop()!;
            remainingK--;
            
            this.operations.push({
                type: OperationType.TRIM,
                digit: String(removed),
                stack: [...stack].map(String),
                step: step++
            });
        }
        
        return stack;
    }
    
    private compare(a: T, b: T): boolean {
        return String(a) > String(b);
    }
    
    public getOperations(): Operation[] {
        return [...this.operations];
    }
    
    public clearOperations(): void {
        this.operations = [];
    }
}

// 异步版本，使用Promise和async/await
class AsyncRemoveKdigits {
    public async removeKdigitsAsync(num: string, k: number): Promise<string> {
        return new Promise((resolve) => {
            // 模拟异步处理
            setTimeout(() => {
                const solution = new RemoveKdigitsSolution();
                const result = solution.removeKdigits(num, k);
                resolve(result);
            }, 10);
        });
    }
    
    public async batchProcess(inputs: Array<[string, number]>): Promise<string[]> {
        const promises = inputs.map(([num, k]) => this.removeKdigitsAsync(num, k));
        return Promise.all(promises);
    }
}

// 工厂模式
class RemoveKdigitsFactory {
    public static create(type: 'standard' | 'functional' | 'async'): RemoveKdigitsStrategy | AsyncRemoveKdigits {
        switch (type) {
            case 'standard':
                return new StandardStrategy();
            case 'functional':
                return new FunctionalStrategy();
            case 'async':
                return new AsyncRemoveKdigits();
            default:
                throw new Error(`Unknown type: ${type}`);
        }
    }
}

// 类型守卫
function isValidInput(num: unknown, k: unknown): num is string {
    return typeof num === 'string' && typeof k === 'number' && k >= 0;
}

// 测试函数
async function testAllVersions(): Promise<void> {
    const testCases: Array<[string, number]> = [
        ["1432219", 3],  // "1219"
        ["10200", 1],    // "200"
        ["10", 2],       // "0"
        ["9", 1],        // "0"
        ["112", 1]       // "11"
    ];
    
    const solution = new RemoveKdigitsSolution();
    
    console.log("=== 标准版本 ===");
    testCases.forEach(([num, k]) => {
        if (isValidInput(num, k)) {
            const result = solution.removeKdigits(num, k);
            console.log(`removeKdigits('${num}', ${k}) = '${result}'`);
        }
    });
    
    console.log("\n=== 函数式版本 ===");
    testCases.forEach(([num, k]) => {
        const result = solution.removeKdigitsFunctional(num, k);
        console.log(`removeKdigitsFunctional('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 策略模式版本 ===");
    const context = new RemoveKdigitsContext(new StandardStrategy());
    testCases.forEach(([num, k]) => {
        const result = context.execute(num, k);
        console.log(`策略模式('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 泛型处理器版本 ===");
    const processor = new DigitProcessor<string>();
    testCases.forEach(([num, k]) => {
        processor.clearOperations();
        const chars = [...num];
        const result = processor.process(chars, k);
        const finalResult = result.join('').replace(/^0+/, '') || '0';
        console.log(`泛型处理器('${num}', ${k}) = '${finalResult}'`);
        console.log(`操作步骤数: ${processor.getOperations().length}`);
    });
    
    console.log("\n=== 异步版本 ===");
    const asyncProcessor = new AsyncRemoveKdigits();
    const asyncResults = await asyncProcessor.batchProcess(testCases);
    testCases.forEach(([num, k], index) => {
        console.log(`异步处理('${num}', ${k}) = '${asyncResults[index]}'`);
    });
    
    console.log("\n=== 带日志版本 ===");
    testCases.slice(0, 2).forEach(([num, k]) => {
        const result = solution.removeKdigitsWithLogging(num, k);
    });
}

// 导出类型和类
export {
    RemoveKdigitsSolution,
    RemoveKdigitsStrategy,
    RemoveKdigitsContext,
    DigitProcessor,
    AsyncRemoveKdigits,
    RemoveKdigitsFactory,
    OperationType,
    type Digit,
    type Stack,
    type ProcessResult,
    type Operation,
    type ProcessorState
};

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    testAllVersions().catch(console.error);
}

/*
TypeScript高级特性说明：

1. **类型别名 (Type Aliases)**:
   - type Digit = string - 创建类型别名
   - 提高代码可读性和类型安全

2. **接口 (Interfaces)**:
   - interface RemoveKdigitsStrategy - 定义契约
   - 支持多态和依赖注入

3. **枚举 (Enums)**:
   - enum OperationType - 定义常量集合
   - 提供类型安全的常量

4. **泛型 (Generics)**:
   - class DigitProcessor<T> - 类型参数
   - 提供类型安全的重用性

5. **泛型约束**:
   - T extends string | number - 约束泛型类型
   - 确保类型满足特定条件

6. **工具类型**:
   - ProcessorState<T> - 复合类型定义
   - 提高类型复用性

7. **类型守卫 (Type Guards)**:
   - function isValidInput(...): num is string
   - 运行时类型检查

8. **访问修饰符**:
   - public, private, protected
   - 控制成员访问权限

9. **装饰器模式**:
   - removeKdigitsWithLogging - 功能增强
   - 不修改原有代码的情况下添加功能

10. **策略模式**:
    - RemoveKdigitsStrategy接口
    - 算法族的封装和互换

11. **工厂模式**:
    - RemoveKdigitsFactory.create()
    - 对象创建的封装

12. **Promise和async/await**:
    - 异步编程的类型安全
    - Promise<T>类型注解

13. **模块系统**:
    - export/import语法
    - 命名空间和模块化

14. **非空断言操作符**:
    - stack.pop()! - 告诉编译器值不为null
    - 谨慎使用，确保运行时安全

15. **联合类型**:
    - string | number - 多种可能的类型
    - 提供灵活性同时保持类型安全

TypeScript提供了强大的类型系统，在保持JavaScript灵活性的同时，
提供了编译时类型检查，大大提高了代码的可维护性和可靠性。
*/