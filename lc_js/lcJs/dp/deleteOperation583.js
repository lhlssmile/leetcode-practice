// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

/**
 * 方法一：基于最长公共子序列(LCS)的解法
 * 时间复杂度：O(m*n)，空间复杂度：O(m*n)
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
function minDistanceLCS(word1, word2) {
    const m = word1.length;
    const n = word2.length;
    
    // 创建LCS矩阵
    const lcs = Array(m + 1).fill().map(() => Array(n + 1).fill(0));
    
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (word1[i - 1] === word2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = Math.max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }
    
    // 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
    return m + n - 2 * lcs[m][n];
}

/**
 * 方法二：直接使用动态规划
 * 时间复杂度：O(m*n)，空间复杂度：O(m*n)
 * @param {string} word1
 * @param {string} word2
 * @return {number}
 */
function minDistance(word1, word2) {
    const m = word1.length;
    const n = word2.length;
    
    // 创建DP矩阵
    const dp = Array(m + 1).fill().map(() => Array(n + 1).fill(0));
    
    // 初始化
    for (let i = 0; i <= m; i++) {
        dp[i][0] = i; // 删除 word1 的前 i 个字符
    }
    for (let j = 0; j <= n; j++) {
        dp[0][j] = j; // 删除 word2 的前 j 个字符
    }
    
    // 动态规划
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (word1[i - 1] === word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // 字符相同，无需删除
            } else {
                dp[i][j] = Math.min(dp[i - 1][j] + 1, dp[i][j - 1] + 1); // 删除一个字符
            }
        }
    }
    
    return dp[m][n];
}

// 测试函数
function testSolution() {
    // 测试用例
    const testCases = [
        ["sea", "eat"],           // 期望输出: 2
        ["leetcode", "etco"],     // 期望输出: 4
        ["", "a"],                 // 期望输出: 1
        ["a", ""],                 // 期望输出: 1
        ["intention", "execution"] // 期望输出: 8
    ];
    
    for (const [word1, word2] of testCases) {
        console.log(`Word1: "${word1}", Word2: "${word2}"`);
        console.log(`方法一 (LCS): ${minDistanceLCS(word1, word2)}`);
        console.log(`方法二 (DP): ${minDistance(word1, word2)}`);
        console.log("-------------------");
    }
}

// 运行测试
testSolution();

// 导出函数供其他模块使用
module.exports = {
    minDistanceLCS,
    minDistance
};