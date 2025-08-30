/**
 * @param {string} s - 输入字符串，只包含数字0-4
 * @param {number} k - 窗口大小下限
 * @return {number} - 满足条件的最大差值
 */
function maxDifference(s, k) {
    const inf = Number.MAX_SAFE_INTEGER / 2;
    let ans = -inf;
    
    for (let x = 0; x < 5; x++) {
        for (let y = 0; y < 5; y++) {
            if (y === x) continue;
            
            const cur_s = new Array(5).fill(0);
            const pre_s = new Array(5).fill(0);
            const min_s = [[inf, inf], [inf, inf]];
            let left = 0;
            
            for (let i = 0; i < s.length; i++) {
                cur_s[parseInt(s[i])]++;
                const r = i + 1;
                
                while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
                    const parityX = pre_s[x] & 1;
                    const parityY = pre_s[y] & 1;
                    min_s[parityX][parityY] = Math.min(min_s[parityX][parityY], pre_s[x] - pre_s[y]);
                    pre_s[parseInt(s[left])]++;
                    left++;
                }
                
                const currentParityX = (cur_s[x] & 1) ^ 1;
                const currentParityY = cur_s[y] & 1;
                ans = Math.max(ans, cur_s[x] - cur_s[y] - min_s[currentParityX][currentParityY]);
            }
        }
    }
    
    return ans;
}

/**
 * 优化版本：使用更具描述性的变量名和注释
 * @param {string} s - 输入字符串，只包含数字0-4
 * @param {number} k - 窗口大小下限
 * @return {number} - 满足条件的最大差值
 */
function maxDifferenceOptimized(s, k) {
    const INF = Number.MAX_SAFE_INTEGER / 2;
    let maxDiff = -INF;
    
    // 枚举所有可能的字符对(x,y)，其中x!=y
    for (let x = 0; x < 5; x++) {
        for (let y = 0; y < 5; y++) {
            if (y === x) continue;
            
            // 当前窗口中各字符的计数
            const currentCount = new Array(5).fill(0);
            // 前缀窗口中各字符的计数
            const prefixCount = new Array(5).fill(0);
            // 存储最小差值，按奇偶性分类
            const minDifference = [[INF, INF], [INF, INF]];
            
            let left = 0;
            for (let i = 0; i < s.length; i++) {
                // 更新当前窗口计数
                currentCount[parseInt(s[i])]++;
                const right = i + 1;
                
                // 当窗口大小>=k且满足条件时，更新最小差值
                while (right - left >= k && 
                       currentCount[x] > prefixCount[x] && 
                       currentCount[y] > prefixCount[y]) {
                    // 根据x和y的奇偶性选择对应的最小差值
                    const parityX = prefixCount[x] & 1; // x的奇偶性
                    const parityY = prefixCount[y] & 1; // y的奇偶性
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
                const currentParityX = (currentCount[x] & 1) ^ 1;
                const currentParityY = currentCount[y] & 1;
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
 * 现代JavaScript版本：利用现代JavaScript特性
 * @param {string} s - 输入字符串，只包含数字0-4
 * @param {number} k - 窗口大小下限
 * @return {number} - 满足条件的最大差值
 */
function maxDifferenceModern(s, k) {
    const INF = Number.MAX_SAFE_INTEGER / 2;
    let maxDiff = -INF;
    
    // 将字符串转换为数字数组，避免重复转换
    const digits = [...s].map(ch => parseInt(ch));
    
    // 生成所有可能的(x,y)对，其中x!=y
    const pairs = Array.from({ length: 5 }, (_, x) => 
        Array.from({ length: 5 }, (_, y) => [x, y])
    ).flat().filter(([x, y]) => x !== y);
    
    for (const [x, y] of pairs) {
        const currentCount = new Array(5).fill(0);
        const prefixCount = new Array(5).fill(0);
        const minDifference = Array.from({ length: 2 }, () => Array(2).fill(INF));
        
        let left = 0;
        for (let i = 0; i < digits.length; i++) {
            currentCount[digits[i]]++;
            const right = i + 1;
            
            while (right - left >= k && 
                   currentCount[x] > prefixCount[x] && 
                   currentCount[y] > prefixCount[y]) {
                const parityX = prefixCount[x] & 1;
                const parityY = prefixCount[y] & 1;
                minDifference[parityX][parityY] = Math.min(
                    minDifference[parityX][parityY],
                    prefixCount[x] - prefixCount[y]
                );
                prefixCount[digits[left]]++;
                left++;
            }
            
            const currentParityX = (currentCount[x] & 1) ^ 1;
            const currentParityY = currentCount[y] & 1;
            maxDiff = Math.max(
                maxDiff,
                currentCount[x] - currentCount[y] - minDifference[currentParityX][currentParityY]
            );
        }
    }
    
    return maxDiff;
}

// 测试代码
function runTests() {
    const testCases = [
        { s: "01234", k: 2, expected: 0 },
        { s: "00110", k: 2, expected: 0 }
    ];
    
    testCases.forEach((tc, i) => {
        const result1 = maxDifference(tc.s, tc.k);
        const result2 = maxDifferenceOptimized(tc.s, tc.k);
        const result3 = maxDifferenceModern(tc.s, tc.k);
        
        console.log(`测试用例${i + 1}: s=${tc.s}, k=${tc.k}`);
        console.log(`  基本版本结果: ${result1}`);
        console.log(`  优化版本结果: ${result2}`);
        console.log(`  现代JS版本结果: ${result3}`);
        console.log();
    });
}

runTests();