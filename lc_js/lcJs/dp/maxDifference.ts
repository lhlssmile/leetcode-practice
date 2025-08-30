/**
 * 计算满足条件的最大差值
 * @param s - 输入字符串，只包含数字0-4
 * @param k - 窗口大小下限
 * @returns 满足条件的最大差值
 */
function maxDifference(s: string, k: number): number {
    const inf: number = Number.MAX_SAFE_INTEGER / 2;
    let ans: number = -inf;
    
    for (let x = 0; x < 5; x++) {
        for (let y = 0; y < 5; y++) {
            if (y === x) continue;
            
            const cur_s: number[] = new Array(5).fill(0);
            const pre_s: number[] = new Array(5).fill(0);
            const min_s: number[][] = [[inf, inf], [inf, inf]];
            let left: number = 0;
            
            for (let i = 0; i < s.length; i++) {
                cur_s[parseInt(s[i])]++;
                const r: number = i + 1;
                
                while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
                    const parityX: number = pre_s[x] & 1;
                    const parityY: number = pre_s[y] & 1;
                    min_s[parityX][parityY] = Math.min(min_s[parityX][parityY], pre_s[x] - pre_s[y]);
                    pre_s[parseInt(s[left])]++;
                    left++;
                }
                
                const currentParityX: number = (cur_s[x] & 1) ^ 1;
                const currentParityY: number = cur_s[y] & 1;
                ans = Math.max(ans, cur_s[x] - cur_s[y] - min_s[currentParityX][currentParityY]);
            }
        }
    }
    
    return ans;
}

/**
 * 优化版本：使用更具描述性的变量名和注释
 * @param s - 输入字符串，只包含数字0-4
 * @param k - 窗口大小下限
 * @returns 满足条件的最大差值
 */
function maxDifferenceOptimized(s: string, k: number): number {
    const INF: number = Number.MAX_SAFE_INTEGER / 2;
    let maxDiff: number = -INF;
    
    // 枚举所有可能的字符对(x,y)，其中x!=y
    for (let x = 0; x < 5; x++) {
        for (let y = 0; y < 5; y++) {
            if (y === x) continue;
            
            // 当前窗口中各字符的计数
            const currentCount: number[] = new Array(5).fill(0);
            // 前缀窗口中各字符的计数
            const prefixCount: number[] = new Array(5).fill(0);
            // 存储最小差值，按奇偶性分类
            const minDifference: number[][] = [[INF, INF], [INF, INF]];
            
            let left: number = 0;
            for (let i = 0; i < s.length; i++) {
                // 更新当前窗口计数
                currentCount[parseInt(s[i])]++;
                const right: number = i + 1;
                
                // 当窗口大小>=k且满足条件时，更新最小差值
                while (right - left >= k && 
                       currentCount[x] > prefixCount[x] && 
                       currentCount[y] > prefixCount[y]) {
                    // 根据x和y的奇偶性选择对应的最小差值
                    const parityX: number = prefixCount[x] & 1; // x的奇偶性
                    const parityY: number = prefixCount[y] & 1; // y的奇偶性
                    minDifference[parityX][parityY] = Math.min(
                        minDifference[parityX][parityY],
                        prefixCount[x] - prefixCount[y]
                    );
                    
                    // 移动左指针，更新前缀计数
                    prefixCount[parseInt(s[left])]++;
                    left++;
                }
                
                // 计算当前最大差值
                // 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
                const currentParityX: number = (currentCount[x] & 1) ^ 1;
                const currentParityY: number = currentCount[y] & 1;
                maxDiff = Math.max(
                    maxDiff,
                    currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY]
                );
            }
        }
    }
    
    return maxDiff;
}

/**
 * 现代TypeScript版本：利用TypeScript的类型系统和现代特性
 * @param s - 输入字符串，只包含数字0-4
 * @param k - 窗口大小下限
 * @returns 满足条件的最大差值
 */
function maxDifferenceModern(s: string, k: number): number {
    const INF: number = Number.MAX_SAFE_INTEGER / 2;
    let maxDiff: number = -INF;
    
    // 将字符串转换为数字数组，避免重复转换
    const digits: number[] = [...s].map(ch => parseInt(ch));
    
    // 定义类型别名，使代码更清晰
    type Pair = [number, number];
    type ParityMatrix = number[][];
    
    // 生成所有可能的(x,y)对，其中x!=y
    const pairs: Pair[] = [];
    for (let x = 0; x < 5; x++) {
        for (let y = 0; y < 5; y++) {
            if (x !== y) {
                pairs.push([x, y]);
            }
        }
    }
    
    for (const [x, y] of pairs) {
        const currentCount: number[] = new Array(5).fill(0);
        const prefixCount: number[] = new Array(5).fill(0);
        const minDifference: ParityMatrix = Array.from({ length: 2 }, () => Array(2).fill(INF));
        
        let left: number = 0;
        for (let i = 0; i < digits.length; i++) {
            currentCount[digits[i]]++;
            const right: number = i + 1;
            
            while (right - left >= k && 
                   currentCount[x] > prefixCount[x] && 
                   currentCount[y] > prefixCount[y]) {
                const parityX: number = prefixCount[x] & 1;
                const parityY: number = prefixCount[y] & 1;
                minDifference[parityX][parityY] = Math.min(
                    minDifference[parityX][parityY],
                    prefixCount[x] - prefixCount[y]
                );
                prefixCount[digits[left]]++;
                left++;
            }
            
            const currentParityX: number = (currentCount[x] & 1) ^ 1;
            const currentParityY: number = currentCount[y] & 1;
            maxDiff = Math.max(
                maxDiff,
                currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY]
            );
        }
    }
    
    return maxDiff;
}

/**
 * 函数式TypeScript版本：使用更多函数式编程特性
 * @param s - 输入字符串，只包含数字0-4
 * @param k - 窗口大小下限
 * @returns 满足条件的最大差值
 */
function maxDifferenceFunctional(s: string, k: number): number {
    const INF: number = Number.MAX_SAFE_INTEGER / 2;
    
    // 将字符串转换为数字数组
    const digits: number[] = [...s].map(ch => parseInt(ch));
    
    // 生成所有可能的(x,y)对，其中x!=y
    const pairs: [number, number][] = Array.from({ length: 5 }, (_, x) => 
        Array.from({ length: 5 }, (_, y) => [x, y] as [number, number])
    ).flat().filter(([x, y]) => x !== y);
    
    // 计算每对(x,y)的最大差值
    const pairResults: number[] = pairs.map(([x, y]) => {
        const currentCount: number[] = new Array(5).fill(0);
        const prefixCount: number[] = new Array(5).fill(0);
        const minDifference: number[][] = Array.from({ length: 2 }, () => Array(2).fill(INF));
        
        let left: number = 0;
        let maxPairDiff: number = -INF;
        
        // 处理每个位置
        for (let i = 0; i < digits.length; i++) {
            currentCount[digits[i]]++;
            const right: number = i + 1;
            
            // 更新最小差值
            while (right - left >= k && 
                   currentCount[x] > prefixCount[x] && 
                   currentCount[y] > prefixCount[y]) {
                const parityX: number = prefixCount[x] & 1;
                const parityY: number = prefixCount[y] & 1;
                minDifference[parityX][parityY] = Math.min(
                    minDifference[parityX][parityY],
                    prefixCount[x] - prefixCount[y]
                );
                prefixCount[digits[left]]++;
                left++;
            }
            
            // 计算当前差值
            const currentParityX: number = (currentCount[x] & 1) ^ 1;
            const currentParityY: number = currentCount[y] & 1;
            maxPairDiff = Math.max(
                maxPairDiff,
                currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY]
            );
        }
        
        return maxPairDiff;
    });
    
    // 返回所有对中的最大差值
    return Math.max(...pairResults);
}

// 测试接口定义
interface TestCase {
    s: string;
    k: number;
    expected: number;
}

// 测试代码
function runTests(): void {
    const testCases: TestCase[] = [
        { s: "01234", k: 2, expected: 0 },
        { s: "00110", k: 2, expected: 0 }
    ];
    
    testCases.forEach((tc, i) => {
        const result1 = maxDifference(tc.s, tc.k);
        const result2 = maxDifferenceOptimized(tc.s, tc.k);
        const result3 = maxDifferenceModern(tc.s, tc.k);
        const result4 = maxDifferenceFunctional(tc.s, tc.k);
        
        console.log(`测试用例${i + 1}: s=${tc.s}, k=${tc.k}`);
        console.log(`  基本版本结果: ${result1}`);
        console.log(`  优化版本结果: ${result2}`);
        console.log(`  现代TS版本结果: ${result3}`);
        console.log(`  函数式版本结果: ${result4}`);
        console.log();
    });
}

// 运行测试
runTests();