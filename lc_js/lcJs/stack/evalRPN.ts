// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

class Solution {
    evalRPN(tokens: string[]): number {
        const stack: number[] = [];
        
        for (const token of tokens) {
            if (['+', '-', '*', '/'].includes(token)) {
                const b: number = stack.pop()!;  // 右操作数
                const a: number = stack.pop()!;  // 左操作数
                
                switch (token) {
                    case '+':
                        stack.push(a + b);
                        break;
                    case '-':
                        stack.push(a - b);
                        break;
                    case '*':
                        stack.push(a * b);
                        break;
                    case '/':
                        // TypeScript的除法需要向零截断
                        stack.push(Math.trunc(a / b));
                        break;
                }
            } else {
                stack.push(parseInt(token));
            }
        }
        
        return stack[0];
    }
}

// 类型定义
type Operator = '+' | '-' | '*' | '/';
type Token = string;
type OperatorFunction = (a: number, b: number) => number;

// 接口定义
interface IRPNEvaluator {
    evaluate(tokens: string[]): number;
}

// 泛型栈类
class Stack<T> {
    private items: T[] = [];
    
    push(item: T): void {
        this.items.push(item);
    }
    
    pop(): T | undefined {
        return this.items.pop();
    }
    
    peek(): T | undefined {
        return this.items[this.items.length - 1];
    }
    
    isEmpty(): boolean {
        return this.items.length === 0;
    }
    
    size(): number {
        return this.items.length;
    }
}

// 实现接口的类
class TypedRPNEvaluator implements IRPNEvaluator {
    private readonly operators: Map<Operator, OperatorFunction> = new Map([
        ['+', (a: number, b: number): number => a + b],
        ['-', (a: number, b: number): number => a - b],
        ['*', (a: number, b: number): number => a * b],
        ['/', (a: number, b: number): number => Math.trunc(a / b)]
    ]);
    
    evaluate(tokens: string[]): number {
        const stack = new Stack<number>();
        
        for (const token of tokens) {
            if (this.isOperator(token)) {
                const b: number = stack.pop()!;
                const a: number = stack.pop()!;
                const operation = this.operators.get(token as Operator)!;
                stack.push(operation(a, b));
            } else {
                stack.push(parseInt(token));
            }
        }
        
        return stack.peek()!;
    }
    
    private isOperator(token: string): token is Operator {
        return this.operators.has(token as Operator);
    }
}

// 函数式编程实现
function evalRPNFunctional(tokens: string[]): number {
    const operations: Record<Operator, OperatorFunction> = {
        '+': (a, b) => a + b,
        '-': (a, b) => a - b,
        '*': (a, b) => a * b,
        '/': (a, b) => Math.trunc(a / b)
    };
    
    return tokens.reduce<number[]>((stack, token) => {
        if (token in operations) {
            const b = stack.pop()!;
            const a = stack.pop()!;
            stack.push(operations[token as Operator](a, b));
        } else {
            stack.push(parseInt(token));
        }
        return stack;
    }, [])[0];
}

// 抽象类
abstract class AbstractRPNEvaluator {
    abstract evaluate(tokens: string[]): number;
    
    protected isNumber(token: string): boolean {
        return !isNaN(parseInt(token));
    }
    
    protected parseNumber(token: string): number {
        return parseInt(token);
    }
}

// 继承抽象类
class ConcreteRPNEvaluator extends AbstractRPNEvaluator {
    evaluate(tokens: string[]): number {
        const stack: number[] = [];
        
        for (const token of tokens) {
            if (this.isNumber(token)) {
                stack.push(this.parseNumber(token));
            } else {
                const b = stack.pop()!;
                const a = stack.pop()!;
                stack.push(this.performOperation(a, b, token as Operator));
            }
        }
        
        return stack[0];
    }
    
    private performOperation(a: number, b: number, operator: Operator): number {
        switch (operator) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return Math.trunc(a / b);
            default: throw new Error(`Unknown operator: ${operator}`);
        }
    }
}

// 测试接口
interface TestCase {
    tokens: string[];
    expected: number;
    description: string;
}

function testEvalRPN(): void {
    console.log("=== 逆波兰表达式求值测试 ===");
    
    const solution = new Solution();
    const typedEvaluator = new TypedRPNEvaluator();
    const concreteEvaluator = new ConcreteRPNEvaluator();
    
    // 测试用例
    const testCases: TestCase[] = [
        {
            tokens: ["2", "1", "+", "3", "*"],
            expected: 9,
            description: "((2 + 1) * 3) = 9"
        },
        {
            tokens: ["4", "13", "5", "/", "+"],
            expected: 6,
            description: "(4 + (13 / 5)) = 6"
        },
        {
            tokens: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"],
            expected: 22,
            description: "复杂表达式 = 22"
        }
    ];
    
    testCases.forEach((testCase: TestCase, index: number) => {
        const { tokens, expected, description } = testCase;
        
        const result1: number = solution.evalRPN([...tokens]);
        const result2: number = evalRPNFunctional([...tokens]);
        const result3: number = typedEvaluator.evaluate([...tokens]);
        const result4: number = concreteEvaluator.evaluate([...tokens]);
        
        console.log(`测试用例${index + 1}: ${description}`);
        console.log(`输入: [${tokens.map(t => `"${t}"`).join(', ')}]`);
        console.log(`Solution类结果: ${result1}`);
        console.log(`函数式实现结果: ${result2}`);
        console.log(`接口实现结果: ${result3}`);
        console.log(`抽象类实现结果: ${result4}`);
        console.log(`期望结果: ${expected}`);
        
        const allCorrect: boolean = [result1, result2, result3, result4]
            .every((result: number) => result === expected);
        console.log(`所有实现正确: ${allCorrect}`);
        console.log();
    });
    
    console.log("=== TypeScript特性说明 ===");
    console.log("1. 静态类型: 编译时类型检查");
    console.log("2. 泛型: 类型安全的代码复用");
    console.log("3. 接口: 契约定义和实现");
    console.log("4. 抽象类: 部分实现的基类");
    console.log("5. 类型守卫: 运行时类型检查");
}

// 导出
export {
    Solution,
    TypedRPNEvaluator,
    ConcreteRPNEvaluator,
    Stack,
    IRPNEvaluator,
    AbstractRPNEvaluator,
    evalRPNFunctional,
    testEvalRPN,
    type Operator,
    type Token,
    type OperatorFunction,
    type TestCase
};

// 默认导出
export default Solution;

// 如果在Node.js环境中直接运行
if (typeof require !== 'undefined' && require.main === module) {
    testEvalRPN();
}

/*
TypeScript实现特点:

1. **静态类型系统**:
   - 编译时类型检查
   - 类型推断和注解
   - 严格的类型安全

2. **面向对象特性**:
   - 类和接口
   - 抽象类和继承
   - 访问修饰符

3. **泛型编程**:
   - 类型参数
   - 约束泛型
   - 类型安全的数据结构

4. **高级类型**:
   - 联合类型
   - 类型守卫
   - 映射类型

5. **模块系统**:
   - ES6模块语法
   - 类型导出导入
   - 命名空间

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/