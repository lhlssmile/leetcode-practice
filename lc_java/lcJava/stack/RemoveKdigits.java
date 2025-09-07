package lcJava.stack;

import java.util.*;
import java.util.stream.*;

public class RemoveKdigits {
    
    public String removeKdigits(String num, int k) {
        Deque<Character> stack = new ArrayDeque<>();
        
        for (char digit : num.toCharArray()) {
            // 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
            while (!stack.isEmpty() && k > 0 && stack.peekLast() > digit) {
                stack.removeLast();
                k--;
            }
            stack.addLast(digit);
        }
        
        // 如果还没删完，从后面删
        while (k > 0 && !stack.isEmpty()) {
            stack.removeLast();
            k--;
        }
        
        // 去掉前导零
        StringBuilder sb = new StringBuilder();
        boolean leadingZero = true;
        for (char c : stack) {
            if (c != '0' || !leadingZero) {
                sb.append(c);
                leadingZero = false;
            }
        }
        
        return sb.length() == 0 ? "0" : sb.toString();
    }
    
    // 使用Stream API的函数式版本
    public String removeKdigitsStream(String num, int k) {
        final int[] remainingK = {k};
        Deque<Character> stack = new ArrayDeque<>();
        
        num.chars()
           .mapToObj(c -> (char) c)
           .forEach(digit -> {
               // 移除比当前数字大的栈顶元素
               while (!stack.isEmpty() && remainingK[0] > 0 && stack.peekLast() > digit) {
                   stack.removeLast();
                   remainingK[0]--;
               }
               stack.addLast(digit);
           });
        
        // 如果还有剩余删除次数，从后面删除
        while (remainingK[0] > 0 && !stack.isEmpty()) {
            stack.removeLast();
            remainingK[0]--;
        }
        
        // 去掉前导零并构建结果
        String result = stack.stream()
                            .map(String::valueOf)
                            .collect(Collectors.joining())
                            .replaceFirst("^0+", "");
        
        return result.isEmpty() ? "0" : result;
    }
    
    public static void main(String[] args) {
        RemoveKdigits solution = new RemoveKdigits();
        
        // 测试用例
        String[][] testCases = {
            {"1432219", "3"},  // "1219"
            {"10200", "1"},    // "200"
            {"10", "2"},       // "0"
            {"9", "1"},        // "0"
            {"112", "1"}       // "11"
        };
        
        System.out.println("=== 标准版本 ===");
        for (String[] testCase : testCases) {
            String num = testCase[0];
            int k = Integer.parseInt(testCase[1]);
            String result = solution.removeKdigits(num, k);
            System.out.printf("removeKdigits('%s', %d) = '%s'%n", num, k, result);
        }
        
        System.out.println("\n=== Stream版本 ===");
        for (String[] testCase : testCases) {
            String num = testCase[0];
            int k = Integer.parseInt(testCase[1]);
            String result = solution.removeKdigitsStream(num, k);
            System.out.printf("removeKdigitsStream('%s', %d) = '%s'%n", num, k, result);
        }
    }
}