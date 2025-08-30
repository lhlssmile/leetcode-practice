/**
 * LeetCode 1371. 每个元音包含偶数次的最长子字符串
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
 */

/**
 * 使用前缀和+状态压缩的方法
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 * @param s 输入字符串
 * @returns 满足条件的最长子字符串的长度
 */
function findTheLongestSubstring(s: string): number {
    const n: number = s.length;
    const first: Map<number, number> = new Map(); // 记录状态第一次出现的位置
    first.set(0, -1); // 空字符串状态为0，位置-1
    let state: number = 0; // 当前前缀的元音奇偶状态
    let maxLen: number = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    const vowelPos: number[] = new Array(128).fill(-1);
    vowelPos['a'.charCodeAt(0)] = 0;
    vowelPos['e'.charCodeAt(0)] = 1;
    vowelPos['i'.charCodeAt(0)] = 2;
    vowelPos['o'.charCodeAt(0)] = 3;
    vowelPos['u'.charCodeAt(0)] = 4;
    
    // 遍历字符串
    for (let i = 0; i < n; i++) {
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        const pos: number = vowelPos[s.charCodeAt(i)];
        if (pos !== -1) {
            state ^= (1 << pos); // 翻转第pos位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if (first.has(state)) {
            maxLen = Math.max(maxLen, i - first.get(state)!);
        } else {
            // 记录状态第一次出现的位置
            first.set(state, i);
        }
    }
    
    return maxLen;
}

/**
 * 使用对象代替Map的实现
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 * @param s 输入字符串
 * @returns 满足条件的最长子字符串的长度
 */
function findTheLongestSubstring_withObject(s: string): number {
    const n: number = s.length;
    // 使用Record类型来表示状态到位置的映射
    const first: Record<number, number> = { '0': -1 }; // 记录状态第一次出现的位置，空字符串状态为0，位置-1
    let state: number = 0; // 当前前缀的元音奇偶状态
    let maxLen: number = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    const vowels: Record<string, number> = { 'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4 };
    
    // 遍历字符串
    for (let i = 0; i < n; i++) {
        const char: string = s[i];
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        if (char in vowels) {
            state ^= (1 << vowels[char]); // 翻转对应位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if (state.toString() in first) {
            maxLen = Math.max(maxLen, i - first[state]);
        } else {
            // 记录状态第一次出现的位置
            first[state] = i;
        }
    }
    
    return maxLen;
}

/**
 * 使用更现代的TypeScript特性和函数式编程
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 * @param s 输入字符串
 * @returns 满足条件的最长子字符串的长度
 */
function findTheLongestSubstring_functional(s: string): number {
    // 元音映射
    const vowels: Record<string, number> = { 'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4 };
    const seen: Map<number, number> = new Map([[0, -1]]); // 状态->位置映射，空字符串状态为0，位置-1
    
    // 定义累积器类型
    interface Accumulator {
        state: number;
        maxLen: number;
    }
    
    // 使用reduce遍历字符串并累积结果
    return [...s].reduce(({ state, maxLen }: Accumulator, char: string, i: number): Accumulator => {
        // 更新状态
        if (char in vowels) {
            state ^= (1 << vowels[char]);
        }
        
        // 更新最大长度
        if (seen.has(state)) {
            maxLen = Math.max(maxLen, i - seen.get(state)!);
        } else {
            seen.set(state, i);
        }
        
        return { state, maxLen };
    }, { state: 0, maxLen: 0 }).maxLen;
}

/**
 * 使用数组代替Map的优化实现（因为状态数最多为2^5=32种）
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 * @param s 输入字符串
 * @returns 满足条件的最长子字符串的长度
 */
function findTheLongestSubstring_optimized(s: string): number {
    const n: number = s.length;
    // 使用数组代替Map，因为状态数最多为2^5=32种
    const first: number[] = new Array(1 << 5).fill(-2); // 记录状态第一次出现的位置，初始化为-2表示未出现过
    first[0] = -1; // 空字符串状态为0，位置-1
    let state: number = 0; // 当前前缀的元音奇偶状态
    let maxLen: number = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    const vowels: Record<string, number> = { 'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4 };
    
    // 遍历字符串
    for (let i = 0; i < n; i++) {
        const char: string = s[i];
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        if (char in vowels) {
            state ^= (1 << vowels[char]); // 翻转对应位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if (first[state] !== -2) {
            maxLen = Math.max(maxLen, i - first[state]);
        } else {
            // 记录状态第一次出现的位置
            first[state] = i;
        }
    }
    
    return maxLen;
}

/**
 * 测试函数
 */
function testSolution(): void {
    const testCases: Array<{ input: string; expected: number }> = [
        { input: "eleetminicoworoep", expected: 13 },
        { input: "leetcodeisgreat", expected: 5 },
        { input: "bcbcbc", expected: 6 }
    ];
    
    for (const { input, expected } of testCases) {
        const result1: number = findTheLongestSubstring(input);
        const result2: number = findTheLongestSubstring_withObject(input);
        const result3: number = findTheLongestSubstring_functional(input);
        const result4: number = findTheLongestSubstring_optimized(input);
        
        console.log(`Input: "${input}"`);
        console.log(`Map版本: ${result1}, 对象版本: ${result2}, 函数式版本: ${result3}, 优化版本: ${result4}`);
        console.log(`Expected: ${expected}`);
        console.log(`结果: ${result1 === expected && result2 === expected && result3 === expected && result4 === expected ? '通过' : '失败'}`);
        console.log();
    }
}

// 运行测试
testSolution();

export {
    findTheLongestSubstring,
    findTheLongestSubstring_withObject,
    findTheLongestSubstring_functional,
    findTheLongestSubstring_optimized
};