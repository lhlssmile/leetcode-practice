// 力扣第583题：两个字符串的删除操作（滚动数组优化版本）
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

package lcJava.dp;

public class DeleteOperation583Optimized {
    
    /**
     * 方法一：基于最长公共子序列(LCS)的解法 - 使用滚动数组优化空间
     * 时间复杂度：O(m*n)，空间复杂度：O(n)
     */
    public int minDistanceLCS(String word1, String word2) {
        // 确保word2是较短的字符串，优化空间使用
        if (word1.length() < word2.length()) {
            return minDistanceLCS(word2, word1);
        }
        
        int m = word1.length(), n = word2.length();
        
        // 只保留两行，用于交替计算
        int[] prev = new int[n + 1];
        int[] curr = new int[n + 1];
        
        // 计算LCS
        for (int i = 1; i <= m; i++) {
            // 交换prev和curr数组的引用
            int[] temp = prev;
            prev = curr;
            curr = temp;
            
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = Math.max(prev[j], curr[j - 1]);
                }
            }
        }
        
        // 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
        return m + n - 2 * curr[n];
    }
    
    /**
     * 方法二：直接使用动态规划 - 使用滚动数组优化空间
     * 时间复杂度：O(m*n)，空间复杂度：O(n)
     */
    public int minDistance(String word1, String word2) {
        // 确保word2是较短的字符串，优化空间使用
        if (word1.length() < word2.length()) {
            return minDistance(word2, word1);
        }
        
        int m = word1.length(), n = word2.length();
        
        // 只使用一个数组，重复使用
        int[] dp = new int[n + 1];
        
        // 初始化第一行
        for (int j = 0; j <= n; j++) {
            dp[j] = j; // 删除 word2 的前 j 个字符
        }
        
        // 动态规划
        for (int i = 1; i <= m; i++) {
            // 保存dp[i-1][j-1]的值
            int prev = dp[0];
            // 更新dp[i][0]
            dp[0] = i;
            
            for (int j = 1; j <= n; j++) {
                // 保存当前dp[i-1][j]的值，用于下一次迭代
                int temp = dp[j];
                
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[j] = prev; // 使用保存的dp[i-1][j-1]
                } else {
                    dp[j] = Math.min(dp[j], dp[j - 1]) + 1; // dp[j]此时是dp[i-1][j]，dp[j-1]是dp[i][j-1]
                }
                
                // 更新prev为下一次迭代的dp[i-1][j-1]
                prev = temp;
            }
        }
        
        return dp[n];
    }
    
    /**
     * 方法三：一维数组优化 + 更简洁的实现
     * 时间复杂度：O(m*n)，空间复杂度：O(n)
     */
    public int minDistanceOptimized(String word1, String word2) {
        // 确保word2是较短的字符串
        if (word1.length() < word2.length()) {
            return minDistanceOptimized(word2, word1);
        }
        
        int m = word1.length(), n = word2.length();
        int[] dp = new int[n + 1];
        
        // 初始化
        for (int j = 0; j <= n; j++) {
            dp[j] = j;
        }
        
        // 动态规划
        for (int i = 1; i <= m; i++) {
            int prev = dp[0]; // 保存dp[i-1][0]
            dp[0] = i;        // 更新dp[i][0]
            
            for (int j = 1; j <= n; j++) {
                int curr = dp[j]; // 暂存当前值dp[i-1][j]
                
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[j] = prev;
                } else {
                    dp[j] = Math.min(dp[j], dp[j - 1]) + 1;
                }
                
                prev = curr; // 为下一个位置更新prev
            }
        }
        
        return dp[n];
    }
    
    // 测试函数
    public static void main(String[] args) {
        DeleteOperation583Optimized solution = new DeleteOperation583Optimized();
        
        // 测试用例
        String[][] testCases = {
            {"sea", "eat"},           // 期望输出: 2
            {"leetcode", "etco"},     // 期望输出: 4
            {"", "a"},                 // 期望输出: 1
            {"a", ""},                 // 期望输出: 1
            {"intention", "execution"} // 期望输出: 8
        };
        
        for (String[] tc : testCases) {
            System.out.println("Word1: \"" + tc[0] + "\", Word2: \"" + tc[1] + "\"");
            System.out.println("方法一 (LCS滚动数组): " + solution.minDistanceLCS(tc[0], tc[1]));
            System.out.println("方法二 (DP滚动数组): " + solution.minDistance(tc[0], tc[1]));
            System.out.println("方法三 (优化实现): " + solution.minDistanceOptimized(tc[0], tc[1]));
            System.out.println("-------------------");
        }
        
        // 性能测试
        System.out.println("\n性能测试：");
        String longWord1 = "pneumonoultramicroscopicsilicovolcanoconiosis"; // 45个字符
        String longWord2 = "pseudopseudohypoparathyroidism"; // 30个字符
        
        // 测量执行时间
        long startTime, endTime;
        
        startTime = System.nanoTime();
        int result1 = solution.minDistanceLCS(longWord1, longWord2);
        endTime = System.nanoTime();
        System.out.println("方法一 (LCS滚动数组): " + result1 + ", 耗时: " + (endTime - startTime) / 1000000.0 + " ms");
        
        startTime = System.nanoTime();
        int result2 = solution.minDistance(longWord1, longWord2);
        endTime = System.nanoTime();
        System.out.println("方法二 (DP滚动数组): " + result2 + ", 耗时: " + (endTime - startTime) / 1000000.0 + " ms");
        
        startTime = System.nanoTime();
        int result3 = solution.minDistanceOptimized(longWord1, longWord2);
        endTime = System.nanoTime();
        System.out.println("方法三 (优化实现): " + result3 + ", 耗时: " + (endTime - startTime) / 1000000.0 + " ms");
        
        // 滚动数组优化说明
        System.out.println("\n滚动数组优化说明：");
        System.out.println("1. 空间复杂度：从O(m*n)优化到O(min(m,n))，只保留必要的一行或两行数据");
        System.out.println("2. 方法一：使用两个数组交替计算，适合理解滚动数组的基本概念");
        System.out.println("3. 方法二：使用单个数组+临时变量，在计算过程中保存必要的前一个状态");
        System.out.println("4. 方法三：更简洁的实现，代码逻辑更清晰");
        System.out.println("5. 优化技巧：确保较短的字符串作为列维度，进一步减少空间使用");
    }
}