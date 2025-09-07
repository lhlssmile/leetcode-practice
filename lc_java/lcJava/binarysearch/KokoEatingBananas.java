// LeetCode 875: 爱吃香蕉的珂珂
// 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
// 警卫已经离开了，将在 h 小时后回来。
// 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
// 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

package lcJava.binarysearch;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class KokoEatingBananas {
    
    // 标准二分查找实现
    public int minEatingSpeedBinarySearch(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int left = 1;
        int right = Arrays.stream(piles).max().orElse(0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            long totalHours = 0;
            
            for (int pile : piles) {
                totalHours += (pile + mid - 1) / mid; // ceil(pile / mid)
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 使用Math.ceil的版本
    public int minEatingSpeedWithCeil(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int left = 1;
        int right = Arrays.stream(piles).max().orElse(0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            long totalHours = 0;
            
            for (int pile : piles) {
                totalHours += (long) Math.ceil((double) pile / mid);
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 暴力枚举版本
    public int minEatingSpeedBruteForce(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int maxPile = Arrays.stream(piles).max().orElse(0);
        
        for (int k = 1; k <= maxPile; k++) {
            long totalHours = 0;
            for (int pile : piles) {
                totalHours += (pile + k - 1) / k;
            }
            
            if (totalHours <= h) {
                return k;
            }
        }
        
        return maxPile;
    }
    
    // 使用Stream API的函数式编程版本
    public int minEatingSpeedFunctional(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int maxPile = Arrays.stream(piles).max().orElse(0);
        
        // 使用Stream API进行函数式编程
        return IntStream.rangeClosed(1, maxPile)
                .filter(k -> calculateTotalHours(piles, k) <= h)
                .findFirst()
                .orElse(maxPile);
    }
    
    // 使用并行流的版本
    public int minEatingSpeedParallel(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int maxPile = Arrays.stream(piles).max().orElse(0);
        
        // 使用并行流提高性能（适用于大数据集）
        return IntStream.rangeClosed(1, maxPile)
                .parallel()
                .filter(k -> calculateTotalHours(piles, k) <= h)
                .findFirst()
                .orElse(maxPile);
    }
    
    // 优化版本 - 计算理论最小值
    public int minEatingSpeedOptimized(int[] piles, int h) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        // 计算总香蕉数
        long totalBananas = Arrays.stream(piles).asLongStream().sum();
        
        // 理论最小速度
        int minSpeed = (int) ((totalBananas + h - 1) / h);
        int maxSpeed = Arrays.stream(piles).max().orElse(0);
        
        // 如果最小速度就能完成，直接返回
        if (canFinishInTime(piles, h, minSpeed)) {
            return minSpeed;
        }
        
        int left = minSpeed, right = maxSpeed;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canFinishInTime(piles, h, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 使用泛型和函数式接口的版本
    public <T extends Number> int minEatingSpeedGeneric(T[] piles, int h, 
                                                       Function<T, Integer> converter) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int[] intPiles = Arrays.stream(piles)
                .mapToInt(converter::apply)
                .toArray();
        
        return minEatingSpeedBinarySearch(intPiles, h);
    }
    
    // 使用策略模式的版本
    public interface EatingStrategy {
        long calculateHours(int pile, int speed);
    }
    
    public static class StandardStrategy implements EatingStrategy {
        @Override
        public long calculateHours(int pile, int speed) {
            return (pile + speed - 1) / speed;
        }
    }
    
    public static class CeilStrategy implements EatingStrategy {
        @Override
        public long calculateHours(int pile, int speed) {
            return (long) Math.ceil((double) pile / speed);
        }
    }
    
    public int minEatingSpeedWithStrategy(int[] piles, int h, EatingStrategy strategy) {
        if (piles == null || piles.length == 0) {
            return 0;
        }
        
        int left = 1;
        int right = Arrays.stream(piles).max().orElse(0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            long totalHours = 0;
            
            for (int pile : piles) {
                totalHours += strategy.calculateHours(pile, mid);
            }
            
            if (totalHours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // 使用Builder模式的配置类
    public static class SolutionConfig {
        private boolean useParallel = false;
        private boolean useOptimization = false;
        private EatingStrategy strategy = new StandardStrategy();
        
        public static class Builder {
            private SolutionConfig config = new SolutionConfig();
            
            public Builder useParallel(boolean parallel) {
                config.useParallel = parallel;
                return this;
            }
            
            public Builder useOptimization(boolean optimization) {
                config.useOptimization = optimization;
                return this;
            }
            
            public Builder strategy(EatingStrategy strategy) {
                config.strategy = strategy;
                return this;
            }
            
            public SolutionConfig build() {
                return config;
            }
        }
        
        public static Builder builder() {
            return new Builder();
        }
    }
    
    public int minEatingSpeedConfigurable(int[] piles, int h, SolutionConfig config) {
        if (config.useOptimization) {
            return minEatingSpeedOptimized(piles, h);
        } else if (config.useParallel) {
            return minEatingSpeedParallel(piles, h);
        } else {
            return minEatingSpeedWithStrategy(piles, h, config.strategy);
        }
    }
    
    // 辅助方法
    private long calculateTotalHours(int[] piles, int k) {
        return Arrays.stream(piles)
                .asLongStream()
                .map(pile -> (pile + k - 1) / k)
                .sum();
    }
    
    private boolean canFinishInTime(int[] piles, int h, int k) {
        long totalHours = 0;
        for (int pile : piles) {
            totalHours += (pile + k - 1) / k;
            if (totalHours > h) {
                return false; // 提前退出优化
            }
        }
        return true;
    }
    
    // 测试方法
    public static void main(String[] args) {
        KokoEatingBananas solution = new KokoEatingBananas();
        
        int[][] testPiles = {
            {3, 6, 7, 11},
            {30, 11, 23, 4, 20},
            {30, 11, 23, 4, 20},
            {1, 1, 1, 1},
            {312884470}
        };
        
        int[] testHours = {8, 5, 6, 4, 312884469};
        
        System.out.println("=== 爱吃香蕉的珂珂 ===");
        
        for (int i = 0; i < testPiles.length; i++) {
            int[] piles = testPiles[i];
            int h = testHours[i];
            
            System.out.printf("\n测试用例 %d: piles=%s, h=%d\n", 
                            i + 1, Arrays.toString(piles), h);
            
            int result1 = solution.minEatingSpeedBinarySearch(piles, h);
            int result2 = solution.minEatingSpeedWithCeil(piles, h);
            int result3 = solution.minEatingSpeedBruteForce(piles, h);
            int result4 = solution.minEatingSpeedFunctional(piles, h);
            int result5 = solution.minEatingSpeedParallel(piles, h);
            int result6 = solution.minEatingSpeedOptimized(piles, h);
            
            // 泛型版本测试
            Integer[] integerPiles = Arrays.stream(piles).boxed().toArray(Integer[]::new);
            int result7 = solution.minEatingSpeedGeneric(integerPiles, h, Integer::intValue);
            
            // 策略模式测试
            int result8 = solution.minEatingSpeedWithStrategy(piles, h, new StandardStrategy());
            int result9 = solution.minEatingSpeedWithStrategy(piles, h, new CeilStrategy());
            
            // Builder模式测试
            SolutionConfig config = SolutionConfig.builder()
                    .useOptimization(true)
                    .strategy(new StandardStrategy())
                    .build();
            int result10 = solution.minEatingSpeedConfigurable(piles, h, config);
            
            System.out.println("标准二分查找: " + result1);
            System.out.println("使用Math.ceil: " + result2);
            System.out.println("暴力枚举: " + result3);
            System.out.println("函数式编程: " + result4);
            System.out.println("并行流版本: " + result5);
            System.out.println("优化版本: " + result6);
            System.out.println("泛型版本: " + result7);
            System.out.println("策略模式(标准): " + result8);
            System.out.println("策略模式(ceil): " + result9);
            System.out.println("Builder模式: " + result10);
            
            // 验证结果一致性
            int[] results = {result1, result2, result3, result4, result5, 
                           result6, result7, result8, result9, result10};
            
            for (int j = 1; j < results.length; j++) {
                assert results[j] == results[0] : 
                    String.format("结果不一致! 期望: %d, 实际: %d", results[0], results[j]);
            }
            System.out.println("✓ 所有实现结果一致");
        }
        
        System.out.println("\n=== Java特性说明 ===");
        System.out.println("1. 面向对象: 类、继承、多态、封装");
        System.out.println("2. Stream API: 函数式编程支持");
        System.out.println("3. 泛型: 类型安全的集合和方法");
        System.out.println("4. Lambda表达式: 简洁的函数式编程");
        System.out.println("5. 接口: 多重继承和默认方法");
        System.out.println("6. 注解: 元数据和AOP支持");
        System.out.println("7. 反射: 运行时类型信息");
        System.out.println("8. 垃圾回收: 自动内存管理");
        System.out.println("9. 并发: 线程、锁、并发集合");
        System.out.println("10. 设计模式: 策略、建造者、工厂等");
    }
}

/*
Java特性详解:

1. **面向对象编程**:
   - 类和对象: 数据和行为的封装
   - 继承: extends关键字实现代码复用
   - 多态: 接口和抽象类支持
   - 封装: private/protected/public访问控制

2. **泛型系统**:
   - 类型参数: <T>, <? extends T>, <? super T>
   - 类型擦除: 编译时类型检查
   - 通配符: 协变和逆变
   - 泛型方法和泛型类

3. **Stream API**:
   - 函数式编程支持
   - 链式操作: map, filter, reduce
   - 并行流: parallel()提高性能
   - 惰性求值: 中间操作延迟执行

4. **Lambda表达式**:
   - 函数式接口: @FunctionalInterface
   - 方法引用: Class::method
   - 闭包: 捕获外部变量
   - 简化匿名内部类

5. **集合框架**:
   - List, Set, Map接口
   - ArrayList, LinkedList, HashMap等实现
   - 并发集合: ConcurrentHashMap
   - 工具类: Collections, Arrays

6. **并发编程**:
   - Thread类和Runnable接口
   - synchronized关键字
   - java.util.concurrent包
   - 线程池: ExecutorService

7. **异常处理**:
   - try-catch-finally机制
   - 检查异常和运行时异常
   - 自定义异常类
   - try-with-resources语法

8. **反射机制**:
   - Class对象获取类信息
   - 动态创建对象和调用方法
   - 注解处理
   - 框架开发基础

9. **内存管理**:
   - 垃圾回收器自动管理
   - 堆内存和栈内存
   - 强引用、软引用、弱引用
   - 内存泄漏预防

10. **设计模式**:
    - 单例模式: 确保唯一实例
    - 工厂模式: 对象创建抽象
    - 策略模式: 算法封装
    - 观察者模式: 事件驱动
    - 建造者模式: 复杂对象构建
*/