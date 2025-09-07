package lcJava.array;

import java.util.*;

public class CanThreePartsEqualSum {
    
    public boolean canThreePartsEqualSum(int[] arr) {
        int sum = 0;
        for (int v : arr) {
            sum += v;
        }
        if (sum % 3 != 0) {
            return false;
        }
        
        int part = 0, currentSum = 0;
        
        for (int x : arr) {
            currentSum += x;
            if (currentSum == sum / 3) {
                currentSum = 0;
                part++;
            }
        }
        return part >= 3;
    }
    
    // 测试方法
    public static void testCanThreePartsEqualSum() {
        CanThreePartsEqualSum solution = new CanThreePartsEqualSum();
        
        System.out.println("=== LeetCode 1013: 将数组分成和相等的三个部分 ===");
        
        // 测试用例1
        int[] arr1 = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};
        boolean result1 = solution.canThreePartsEqualSum(arr1);
        System.out.println("测试用例1: " + Arrays.toString(arr1) + " -> 结果: " + result1);
        
        // 测试用例2
        int[] arr2 = {0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1};
        boolean result2 = solution.canThreePartsEqualSum(arr2);
        System.out.println("测试用例2: " + Arrays.toString(arr2) + " -> 结果: " + result2);
        
        // 测试用例3
        int[] arr3 = {3, 3, 3};
        boolean result3 = solution.canThreePartsEqualSum(arr3);
        System.out.println("测试用例3: " + Arrays.toString(arr3) + " -> 结果: " + result3);
        
        // 测试用例4
        int[] arr4 = {1, 1, 1, 1};
        boolean result4 = solution.canThreePartsEqualSum(arr4);
        System.out.println("测试用例4: " + Arrays.toString(arr4) + " -> 结果: " + result4);
        
        // 测试用例5
        int[] arr5 = {0, 0, 0, 0};
        boolean result5 = solution.canThreePartsEqualSum(arr5);
        System.out.println("测试用例5: " + Arrays.toString(arr5) + " -> 结果: " + result5);
    }
    
    public static void main(String[] args) {
        testCanThreePartsEqualSum();
    }
}

/*
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回false
2. 遍历数组，累加当前和
3. 当累加和等于目标值(sum/3)时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)

Java特性:
1. 面向对象编程
2. 静态类型系统
3. 垃圾回收
4. 平台无关性
5. 丰富的标准库
*/