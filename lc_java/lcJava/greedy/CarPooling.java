// Java版本 - 拼车问题 (LeetCode 1094)
import java.util.*;

public class CarPooling {
    
    // 事件类
    static class Event {
        int location;
        int change;
        
        Event(int location, int change) {
            this.location = location;
            this.change = change;
        }
    }
    
    // 事件排序法
    public boolean carPooling(int[][] trips, int capacity) {
        List<Event> events = new ArrayList<>();
        
        // 构建事件列表
        for (int[] trip : trips) {
            int passengers = trip[0], from = trip[1], to = trip[2];
            events.add(new Event(from, passengers));   // 上车事件
            events.add(new Event(to, -passengers));    // 下车事件
        }
        
        // 排序事件：先按位置，再按变化量（下车优先）
        events.sort((a, b) -> {
            if (a.location == b.location) {
                return Integer.compare(a.change, b.change);
            }
            return Integer.compare(a.location, b.location);
        });
        
        int currentPassengers = 0;
        
        // 处理所有事件
        for (Event event : events) {
            currentPassengers += event.change;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
    
    // 差分数组法
    public boolean carPoolingDiffArray(int[][] trips, int capacity) {
        Map<Integer, Integer> diff = new TreeMap<>();
        
        // 构建差分数组
        for (int[] trip : trips) {
            int passengers = trip[0], from = trip[1], to = trip[2];
            diff.put(from, diff.getOrDefault(from, 0) + passengers);
            diff.put(to, diff.getOrDefault(to, 0) - passengers);
        }
        
        int currentPassengers = 0;
        
        // 按位置顺序处理
        for (int change : diff.values()) {
            currentPassengers += change;
            if (currentPassengers > capacity) {
                return false;
            }
        }
        
        return true;
    }
    
    public static void main(String[] args) {
        CarPooling solution = new CarPooling();
        
        // 测试用例
        int[][][] testCases = {
            {{2,1,5},{3,3,7}},           // capacity = 4, expected: false
            {{2,1,5},{3,3,7}},           // capacity = 5, expected: true
            {{2,1,5},{3,5,7}},           // capacity = 3, expected: true
            {{3,2,7},{3,7,9},{8,3,9}}    // capacity = 11, expected: true
        };
        
        int[] capacities = {4, 5, 3, 11};
        boolean[] expected = {false, true, true, true};
        
        System.out.println("=== 拼车问题测试 ===");
        
        for (int i = 0; i < testCases.length; i++) {
            int[][] trips = testCases[i];
            int capacity = capacities[i];
            
            boolean result1 = solution.carPooling(trips, capacity);
            boolean result2 = solution.carPoolingDiffArray(trips, capacity);
            
            System.out.printf("测试用例 %d: trips = %s, capacity = %d%n", 
                            i + 1, Arrays.deepToString(trips), capacity);
            System.out.printf("事件排序法: %b%n", result1);
            System.out.printf("差分数组法: %b%n", result2);
            System.out.printf("预期结果: %b%n", expected[i]);
            System.out.printf("结果: %s%n%n", 
                            (result1 == expected[i] && result2 == expected[i]) ? "✓" : "✗");
        }
    }
}

/*
算法说明：
1. 事件排序法：
   - 将每个行程转换为上车和下车事件
   - 按位置排序，同位置时下车优先
   - 模拟整个过程，检查是否超载
   
2. 差分数组法：
   - 使用差分思想，记录每个位置的乘客变化
   - 按位置顺序累加，检查是否超载
   
时间复杂度: O(n log n)
空间复杂度: O(n)
*/