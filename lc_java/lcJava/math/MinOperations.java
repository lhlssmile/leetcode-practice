package lcJava.math;

import java.util.*;

public class MinOperations {
    
    public static long prefix(long n) {
        long ans = 0;
        long base = 1;
        int k = 1;
        
        while (true) {
            long nextBase = base * 4;
            long L = base;
            long R = nextBase - 1;
            if (n >= R) {
                ans += (R - L + 1) * 1L * k;
            } else {
                ans += (n - L + 1) * 1L * k;
                break;
            }
            base = nextBase;
            k++;
        }
        return ans;
    }
    
    public long minOperations(int[][] queries) {
        long total = 0;
        for (int[] q : queries) {
            long l = q[0];
            long r = q[1];
            long S = prefix(r) - prefix(l - 1);
            total += (S + 1) / 2;
        }
        return total;
    }
    
    // 测试方法
    public static void testMinOperations() {
        MinOperations solution = new MinOperations();
        
        System.out.println("=== LeetCode 最小操作数问题 ===");
        
        // 测试用例1
        int[][] queries1 = {{1, 4}, {2, 6}, {3, 8}};
        long result1 = solution.minOperations(queries1);
        System.out.print("测试用例1: ");
        printQueries(queries1);
        System.out.println(" -> 结果: " + result1);
        
        // 测试用例2
        int[][] queries2 = {{1, 10}, {5, 15}};
        long result2 = solution.minOperations(queries2);
        System.out.print("测试用例2: ");
        printQueries(queries2);
        System.out.println(" -> 结果: " + result2);
        
        // 测试用例3
        int[][] queries3 = {{1, 1}, {2, 2}, {3, 3}};
        long result3 = solution.minOperations(queries3);
        System.out.print("测试用例3: ");
        printQueries(queries3);
        System.out.println(" -> 结果: " + result3);
        
        // 测试prefix函数
        System.out.println("\nprefix函数测试:");
        for (int i = 1; i <= 10; i++) {
            System.out.println("prefix(" + i + ") = " + prefix(i));
        }
    }
    
    private static void printQueries(int[][] queries) {
        for (int[] q : queries) {
            System.out.print("[" + q[0] + ", " + q[1] + "] ");
        }
    }
    
    public static void main(String[] args) {
        testMinOperations();
    }
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是(S+1)/2

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

Java特性:
1. 面向对象编程
2. 静态类型系统
3. 垃圾回收
4. 平台无关性
5. 丰富的标准库
*/