// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

package stack;

import java.util.*;
import java.util.function.BinaryOperator;

public class EvalRPN {
    
    public int evalRPN(String[] tokens) {
        Stack<Integer> stack = new Stack<>();
        
        for (String token : tokens) {
            if ("+".equals(token) || "-".equals(token) || "*".equals(token) || "/".equals(token)) {
                int b = stack.pop();  // 右操作数
                int a = stack.pop();  // 左操作数
                
                switch (token) {
                    case "+":
                        stack.push(a + b);
                        break;
                    case "-":
                        stack.push(a - b);
                        break;
                    case "*":
                        stack.push(a * b);
                        break;
                    case "/":
                        stack.push(a / b);
                        break;
                }
            } else {
                stack.push(Integer.parseInt(token));
            }
        }
        
        return stack.peek();
    }
    
    // 使用Map和Lambda的实现
    public int evalRPNWithMap(String[] tokens) {
        Stack<Integer> stack = new Stack<>();
        Map<String, BinaryOperator<Integer>> operators = new HashMap<>();
        
        operators.put("+", (a, b) -> a + b);
        operators.put("-", (a, b) -> a - b);
        operators.put("*", (a, b) -> a * b);
        operators.put("/", (a, b) -> a / b);
        
        for (String token : tokens) {
            if (operators.containsKey(token)) {
                int b = stack.pop();
                int a = stack.pop();
                stack.push(operators.get(token).apply(a, b));
            } else {
                stack.push(Integer.parseInt(token));
            }
        }
        
        return stack.peek();
    }
    
    // 使用Deque的实现
    public int evalRPNWithDeque(String[] tokens) {
        Deque<Integer> deque = new ArrayDeque<>();
        
        for (String token : tokens) {
            switch (token) {
                case "+":
                    deque.push(deque.pop() + deque.pop());
                    break;
                case "-":
                    int b = deque.pop();
                    int a = deque.pop();
                    deque.push(a - b);
                    break;
                case "*":
                    deque.push(deque.pop() * deque.pop());
                    break;
                case "/":
                    int divisor = deque.pop();
                    int dividend = deque.pop();
                    deque.push(dividend / divisor);
                    break;
                default:
                    deque.push(Integer.parseInt(token));
                    break;
            }
        }
        
        return deque.peek();
    }
    
    public static void testEvalRPN() {
        System.out.println("=== 逆波兰表达式求值测试 ===");
        
        EvalRPN solution = new EvalRPN();
        
        // 测试用例
        String[][] testCases = {
            {"2", "1", "+", "3", "*"},  // ((2 + 1) * 3) = 9
            {"4", "13", "5", "/", "+"},  // (4 + (13 / 5)) = 6
            {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}  // 22
        };
        
        int[] expected = {9, 6, 22};
        
        for (int i = 0; i < testCases.length; i++) {
            int result1 = solution.evalRPN(testCases[i]);
            int result2 = solution.evalRPNWithMap(testCases[i]);
            int result3 = solution.evalRPNWithDeque(testCases[i]);
            
            System.out.printf("测试用例%d: %s%n", i + 1, Arrays.toString(testCases[i]));
            System.out.printf("标准实现结果: %d%n", result1);
            System.out.printf("Map实现结果: %d%n", result2);
            System.out.printf("Deque实现结果: %d%n", result3);
            System.out.printf("期望结果: %d%n", expected[i]);
            System.out.printf("所有实现正确: %b%n", 
                result1 == expected[i] && result2 == expected[i] && result3 == expected[i]);
            System.out.println();
        }
        
        System.out.println("=== Java特性说明 ===");
        System.out.println("1. 面向对象: 类和方法封装");
        System.out.println("2. 集合框架: Stack、Map、Deque");
        System.out.println("3. Lambda表达式: 函数式编程");
        System.out.println("4. 泛型: 类型安全的集合");
        System.out.println("5. 自动装箱: 基本类型和包装类转换");
    }
    
    public static void main(String[] args) {
        testEvalRPN();
    }
}

/*
Java实现特点:

1. **面向对象**:
   - 类和方法封装
   - 继承和多态
   - 接口和抽象类

2. **集合框架**:
   - Stack栈数据结构
   - HashMap哈希表
   - Deque双端队列

3. **函数式编程**:
   - Lambda表达式
   - 函数式接口
   - Stream API

4. **类型安全**:
   - 泛型系统
   - 编译时类型检查
   - 自动装箱拆箱

5. **内存管理**:
   - 自动垃圾回收
   - 堆内存管理
   - 引用类型

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/