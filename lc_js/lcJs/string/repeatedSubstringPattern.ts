// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

// 类型定义
type PatternChecker = (s: string) => boolean;

interface PatternResult {
    method: string;
    result: boolean;
    executionTime?: number;
}

interface TestCase {
    input: string;
    expected?: boolean;
    description?: string;
}

// KMP算法实现
function repeatedSubstringPatternKMP(s: string): boolean {
    const n: number = s.length;
    if (n <= 1) return false;
    
    // 构建KMP的next数组
    const next: number[] = new Array(n + 1);
    next[0] = -1;
    let j: number = -1;
    
    for (let i = 0; i < n; i++) {
        while (j >= 0 && s[i] !== s[j]) {
            j = next[j];
        }
        j++;
        next[i + 1] = j;
    }
    
    const periodLen: number = n - next[n];
    return n % periodLen === 0 && periodLen !== n;
}

// 字符串拼接方法
function repeatedSubstringPatternConcat(s: string): boolean {
    const doubleS: string = s + s;
    return doubleS.slice(1, -1).includes(s);
}

// 暴力枚举方法
function repeatedSubstringPatternBrute(s: string): boolean {
    const n: number = s.length;
    if (n <= 1) return false;
    
    for (let i = 1; i <= Math.floor(n / 2); i++) {
        if (n % i === 0) {
            const pattern: string = s.substring(0, i);
            const constructed: string = pattern.repeat(n / i);
            if (constructed === s) {
                return true;
            }
        }
    }
    return false;
}

// 正则表达式方法
function repeatedSubstringPatternRegex(s: string): boolean {
    const pattern: RegExp = /^(.+)\1+$/;
    return pattern.test(s);
}

// 泛型函数式编程方法
function repeatedSubstringPatternGeneric<T extends string>(s: T): boolean {
    const n: number = s.length;
    if (n <= 1) return false;
    
    const range = (start: number, end: number): number[] => 
        Array.from({ length: end - start }, (_, i) => start + i);
    
    return range(1, Math.floor(n / 2) + 1)
        .filter((len: number) => n % len === 0)
        .some((len: number) => {
            const pattern: string = s.substring(0, len);
            return pattern.repeat(n / len) === s;
        });
}

// 类实现
class PatternMatcher {
    private readonly input: string;
    
    constructor(input: string) {
        this.input = input;
    }
    
    public checkWithKMP(): boolean {
        return repeatedSubstringPatternKMP(this.input);
    }
    
    public checkWithConcat(): boolean {
        return repeatedSubstringPatternConcat(this.input);
    }
    
    public checkWithBrute(): boolean {
        return repeatedSubstringPatternBrute(this.input);
    }
    
    public checkWithRegex(): boolean {
        return repeatedSubstringPatternRegex(this.input);
    }
    
    public getAllResults(): PatternResult[] {
        const methods: Array<{ name: string; fn: PatternChecker }> = [
            { name: "KMP算法", fn: repeatedSubstringPatternKMP },
            { name: "字符串拼接", fn: repeatedSubstringPatternConcat },
            { name: "暴力枚举", fn: repeatedSubstringPatternBrute },
            { name: "正则表达式", fn: repeatedSubstringPatternRegex }
        ];
        
        return methods.map(({ name, fn }) => {
            const startTime = performance.now();
            const result = fn(this.input);
            const endTime = performance.now();
            
            return {
                method: name,
                result,
                executionTime: endTime - startTime
            };
        });
    }
}

// 异步版本
async function repeatedSubstringPatternAsync(s: string): Promise<boolean> {
    return new Promise((resolve) => {
        setTimeout(() => {
            resolve(repeatedSubstringPatternKMP(s));
        }, 0);
    });
}

// 装饰器模式
function measureTime<T extends any[], R>(
    target: any,
    propertyName: string,
    descriptor: TypedPropertyDescriptor<(...args: T) => R>
): TypedPropertyDescriptor<(...args: T) => R> {
    const method = descriptor.value!;
    
    descriptor.value = function (...args: T): R {
        const start = performance.now();
        const result = method.apply(this, args);
        const end = performance.now();
        console.log(`${propertyName} 执行时间: ${end - start}ms`);
        return result;
    };
    
    return descriptor;
}

class OptimizedPatternMatcher {
    @measureTime
    public static checkPattern(s: string): boolean {
        return repeatedSubstringPatternKMP(s);
    }
}

// 主函数
function main(): void {
    const testCases: TestCase[] = [
        { input: "abab", expected: true, description: "简单重复模式" },
        { input: "aba", expected: false, description: "非重复模式" },
        { input: "abcabcabcabc", expected: true, description: "长重复模式" },
        { input: "a", expected: false, description: "单字符" },
        { input: "aa", expected: true, description: "双字符重复" }
    ];
    
    console.log("=== 重复的子字符串模式检测 ===");
    
    testCases.forEach((testCase, i) => {
        const { input, expected, description } = testCase;
        console.log(`\n测试用例 ${i + 1}: "${input}" - ${description}`);
        
        const matcher = new PatternMatcher(input);
        const results = matcher.getAllResults();
        
        results.forEach(({ method, result, executionTime }) => {
            const status = expected !== undefined ? 
                (result === expected ? "✓" : "✗") : "";
            console.log(`${method}: ${result} ${status} (${executionTime?.toFixed(4)}ms)`);
        });
        
        // 验证结果一致性
        const allResults = results.map(r => r.result);
        if (!allResults.every(r => r === allResults[0])) {
            console.log("⚠️ 警告: 结果不一致!");
        }
        
        // 测试泛型版本
        const genericResult = repeatedSubstringPatternGeneric(input);
        console.log(`泛型版本: ${genericResult}`);
        
        // 测试装饰器版本
        console.log("装饰器版本:");
        OptimizedPatternMatcher.checkPattern(input);
    });
    
    // 异步测试
    console.log("\n=== 异步测试 ===");
    Promise.all(
        testCases.map(async ({ input }) => {
            const result = await repeatedSubstringPatternAsync(input);
            console.log(`异步结果 "${input}": ${result}`);
        })
    );
}

// 导出类型和函数
export {
    PatternChecker,
    PatternResult,
    TestCase,
    PatternMatcher,
    OptimizedPatternMatcher,
    repeatedSubstringPatternKMP,
    repeatedSubstringPatternConcat,
    repeatedSubstringPatternBrute,
    repeatedSubstringPatternRegex,
    repeatedSubstringPatternGeneric,
    repeatedSubstringPatternAsync
};

// 运行测试
main();

/*
TypeScript高级特性说明:

1. **类型系统**:
   - 基本类型注解 (string, number, boolean)
   - 接口定义 (interface)
   - 类型别名 (type)
   - 泛型约束 (<T extends string>)

2. **类和接口**:
   - 类的访问修饰符 (private, public)
   - 接口实现
   - 构造函数参数属性

3. **泛型编程**:
   - 泛型函数
   - 泛型约束
   - 类型推断

4. **装饰器**:
   - 方法装饰器
   - 元数据操作
   - AOP编程

5. **异步编程**:
   - Promise类型
   - async/await
   - 类型安全的异步操作

6. **高级类型**:
   - 联合类型
   - 交叉类型
   - 条件类型
   - 映射类型

7. **模块系统**:
   - ES6模块导入导出
   - 命名空间
   - 模块解析

8. **编译时检查**:
   - 静态类型检查
   - 空值检查
   - 严格模式
*/