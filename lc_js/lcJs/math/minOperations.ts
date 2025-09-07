function prefix(n: number): number {
    let ans: number = 0;
    let base: number = 1;
    let k: number = 1;
    
    while (true) {
        const nextBase: number = base * 4;
        const L: number = base;
        const R: number = nextBase - 1;
        if (n >= R) {
            ans += (R - L + 1) * k;
        } else {
            ans += (n - L + 1) * k;
            break;
        }
        base = nextBase;
        k++;
    }
    return ans;
}

function minOperations(queries: number[][]): number {
    let total: number = 0;
    for (const q of queries) {
        const l: number = q[0];
        const r: number = q[1];
        const S: number = prefix(r) - prefix(l - 1);
        total += Math.floor((S + 1) / 2);
    }
    return total;
}

// 类型定义
type Query = [number, number];
type QueryResult = number;

// 接口定义
interface Solution {
    minOperations(queries: number[][]): number;
}

// 类实现
class MinOperationsSolution implements Solution {
    minOperations(queries: number[][]): number {
        let total: number = 0;
        for (const q of queries) {
            const l: number = q[0];
            const r: number = q[1];
            const S: number = prefix(r) - prefix(l - 1);
            total += Math.floor((S + 1) / 2);
        }
        return total;
    }
}

// 测试函数
function testMinOperations(): void {
    console.log("=== LeetCode 最小操作数问题 ===");
    
    const solution = new MinOperationsSolution();
    
    // 测试用例1
    const queries1: number[][] = [[1, 4], [2, 6], [3, 8]];
    const result1: number = minOperations(queries1);
    const result1Class: number = solution.minOperations(queries1);
    console.log(`测试用例1: ${JSON.stringify(queries1)} -> 结果: ${result1} (类方法: ${result1Class})`);
    
    // 测试用例2
    const queries2: number[][] = [[1, 10], [5, 15]];
    const result2: number = minOperations(queries2);
    const result2Class: number = solution.minOperations(queries2);
    console.log(`测试用例2: ${JSON.stringify(queries2)} -> 结果: ${result2} (类方法: ${result2Class})`);
    
    // 测试用例3
    const queries3: number[][] = [[1, 1], [2, 2], [3, 3]];
    const result3: number = minOperations(queries3);
    const result3Class: number = solution.minOperations(queries3);
    console.log(`测试用例3: ${JSON.stringify(queries3)} -> 结果: ${result3} (类方法: ${result3Class})`);
    
    // 测试prefix函数
    console.log("\nprefix函数测试:");
    for (let i: number = 1; i <= 10; i++) {
        console.log(`prefix(${i}) = ${prefix(i)}`);
    }
    
    // 验证结果一致性
    console.log("\n验证结果一致性:");
    console.log(`函数式 vs 类方法 - 测试1: ${result1 === result1Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试2: ${result2 === result2Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试3: ${result3 === result3Class ? '✓' : '✗'}`);
}

// 泛型函数示例
function processQueries<T extends number[][]>(queries: T, processor: (queries: T) => number): number {
    return processor(queries);
}

// 高阶函数示例
function createMinOperationsProcessor(): (queries: number[][]) => number {
    return (queries: number[][]): number => minOperations(queries);
}

// 导出
export { minOperations, prefix, MinOperationsSolution, testMinOperations };
export type { Query, QueryResult, Solution };

// 如果直接运行此文件
if (typeof window === 'undefined' && typeof process !== 'undefined') {
    testMinOperations();
    
    // 泛型和高阶函数测试
    console.log("\n=== TypeScript高级特性测试 ===");
    const testQueries: number[][] = [[1, 5], [3, 7]];
    const processor = createMinOperationsProcessor();
    const genericResult = processQueries(testQueries, processor);
    console.log(`泛型处理结果: ${genericResult}`);
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是Math.floor((S+1)/2)

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

TypeScript特性:
1. 静态类型检查
2. 接口和类型定义
3. 泛型编程
4. 类和接口
5. 模块系统
6. 高阶函数
7. 类型推断
8. 编译时错误检查
*/