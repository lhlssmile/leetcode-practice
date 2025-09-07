// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

// KMP算法实现
function repeatedSubstringPatternKMP(s) {
    const n = s.length;
    if (n <= 1) return false;
    
    // 构建KMP的next数组
    const next = new Array(n + 1);
    next[0] = -1;
    let j = -1;
    
    for (let i = 0; i < n; i++) {
        while (j >= 0 && s[i] !== s[j]) {
            j = next[j];
        }
        j++;
        next[i + 1] = j;
    }
    
    const periodLen = n - next[n];
    return n % periodLen === 0 && periodLen !== n;
}

// 字符串拼接方法
function repeatedSubstringPatternConcat(s) {
    // 将字符串与自身拼接，然后去掉首尾字符
    // 如果原字符串是重复模式，那么在新字符串中一定能找到原字符串
    const doubleS = s + s;
    return doubleS.slice(1, -1).includes(s);
}

// 暴力枚举方法
function repeatedSubstringPatternBrute(s) {
    const n = s.length;
    if (n <= 1) return false;
    
    for (let i = 1; i <= Math.floor(n / 2); i++) {
        if (n % i === 0) {
            const pattern = s.substring(0, i);
            const constructed = pattern.repeat(n / i);
            if (constructed === s) {
                return true;
            }
        }
    }
    return false;
}

// 正则表达式方法
function repeatedSubstringPatternRegex(s) {
    // 使用正则表达式匹配重复模式
    const pattern = /^(.+)\1+$/;
    return pattern.test(s);
}

// 函数式编程方法
function repeatedSubstringPatternFunctional(s) {
    const n = s.length;
    if (n <= 1) return false;
    
    return Array.from({ length: Math.floor(n / 2) }, (_, i) => i + 1)
        .filter(len => n % len === 0)
        .some(len => {
            const pattern = s.substring(0, len);
            return pattern.repeat(n / len) === s;
        });
}

// ES6+ 现代JavaScript方法
function repeatedSubstringPatternModern(s) {
    const n = s.length;
    if (n <= 1) return false;
    
    const possibleLengths = [...Array(Math.floor(n / 2))]
        .map((_, i) => i + 1)
        .filter(len => n % len === 0);
    
    return possibleLengths.some(len => {
        const pattern = s.slice(0, len);
        return s === pattern.repeat(n / len);
    });
}

function main() {
    const testCases = [
        "abab",
        "aba",
        "abcabcabcabc",
        "a",
        "aa"
    ];
    
    console.log("=== 重复的子字符串模式检测 ===");
    
    testCases.forEach((s, i) => {
        console.log(`\n测试用例 ${i + 1}: "${s}"`);
        
        const result1 = repeatedSubstringPatternKMP(s);
        const result2 = repeatedSubstringPatternConcat(s);
        const result3 = repeatedSubstringPatternBrute(s);
        const result4 = repeatedSubstringPatternRegex(s);
        const result5 = repeatedSubstringPatternFunctional(s);
        const result6 = repeatedSubstringPatternModern(s);
        
        console.log(`KMP算法: ${result1}`);
        console.log(`字符串拼接: ${result2}`);
        console.log(`暴力枚举: ${result3}`);
        console.log(`正则表达式: ${result4}`);
        console.log(`函数式编程: ${result5}`);
        console.log(`现代JavaScript: ${result6}`);
        
        // 验证结果一致性
        const results = [result1, result2, result3, result4, result5, result6];
        if (!results.every(r => r === results[0])) {
            console.log("警告: 结果不一致!");
        }
    });
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        repeatedSubstringPatternKMP,
        repeatedSubstringPatternConcat,
        repeatedSubstringPatternBrute,
        repeatedSubstringPatternRegex,
        repeatedSubstringPatternFunctional,
        repeatedSubstringPatternModern
    };
}

// 运行测试
main();