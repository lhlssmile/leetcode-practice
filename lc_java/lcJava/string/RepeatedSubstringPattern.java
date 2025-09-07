// LeetCode 459: 重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。

package string;

import java.util.regex.Pattern;

public class RepeatedSubstringPattern {
    
    // KMP算法实现
    public static boolean repeatedSubstringPatternKMP(String s) {
        int n = s.length();
        if (n <= 1) return false;
        
        // 构建KMP的next数组
        int[] next = new int[n + 1];
        next[0] = -1;
        int j = -1;
        
        for (int i = 0; i < n; i++) {
            while (j >= 0 && s.charAt(i) != s.charAt(j)) {
                j = next[j];
            }
            j++;
            next[i + 1] = j;
        }
        
        int periodLen = n - next[n];
        return n % periodLen == 0 && periodLen != n;
    }
    
    // 字符串拼接方法
    public static boolean repeatedSubstringPatternConcat(String s) {
        // 将字符串与自身拼接，然后去掉首尾字符
        // 如果原字符串是重复模式，那么在新字符串中一定能找到原字符串
        String doubleS = s + s;
        return doubleS.substring(1, doubleS.length() - 1).contains(s);
    }
    
    // 暴力枚举方法
    public static boolean repeatedSubstringPatternBrute(String s) {
        int n = s.length();
        if (n <= 1) return false;
        
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                String pattern = s.substring(0, i);
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n / i; j++) {
                    sb.append(pattern);
                }
                if (sb.toString().equals(s)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // 正则表达式方法
    public static boolean repeatedSubstringPatternRegex(String s) {
        // 使用正则表达式匹配重复模式
        return Pattern.matches("^(.+)\\1+$", s);
    }
    
    // StringBuilder优化方法
    public static boolean repeatedSubstringPatternStringBuilder(String s) {
        int n = s.length();
        if (n <= 1) return false;
        
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                String pattern = s.substring(0, i);
                StringBuilder sb = new StringBuilder();
                int repeatCount = n / i;
                
                for (int j = 0; j < repeatCount; j++) {
                    sb.append(pattern);
                }
                
                if (sb.toString().equals(s)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    public static void main(String[] args) {
        String[] testCases = {
            "abab",
            "aba",
            "abcabcabcabc",
            "a",
            "aa"
        };
        
        System.out.println("=== 重复的子字符串模式检测 ===");
        
        for (int i = 0; i < testCases.length; i++) {
            String s = testCases[i];
            System.out.printf("\n测试用例 %d: \"%s\"\n", i + 1, s);
            
            boolean result1 = repeatedSubstringPatternKMP(s);
            boolean result2 = repeatedSubstringPatternConcat(s);
            boolean result3 = repeatedSubstringPatternBrute(s);
            boolean result4 = repeatedSubstringPatternRegex(s);
            boolean result5 = repeatedSubstringPatternStringBuilder(s);
            
            System.out.printf("KMP算法: %b\n", result1);
            System.out.printf("字符串拼接: %b\n", result2);
            System.out.printf("暴力枚举: %b\n", result3);
            System.out.printf("正则表达式: %b\n", result4);
            System.out.printf("StringBuilder: %b\n", result5);
            
            // 验证结果一致性
            if (result1 != result2 || result2 != result3 || 
                result3 != result4 || result4 != result5) {
                System.out.println("警告: 结果不一致!");
            }
        }
    }
}