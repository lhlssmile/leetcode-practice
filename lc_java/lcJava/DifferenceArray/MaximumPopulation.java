import java.util.*;

/**
 * LeetCode 1854. 人口最多的年份
 * 
 * 给你一个二维整数数组 logs，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。
 * 年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在区间 [birthi, deathi - 1] 内。
 * 注意，人在死亡当年不被计入人口内。
 * 返回 人口最多 的年份。
 * 
 * 算法思路：差分数组
 * 1. 使用差分数组记录每年人口变化
 * 2. 出生年份+1，死亡年份-1
 * 3. 通过前缀和还原每年实际人口
 * 4. 找到人口最多的年份
 * 
 * 时间复杂度：O(n + 101) = O(n)
 * 空间复杂度：O(101) = O(1)
 */

public class MaximumPopulation {
    
    // 差分数组解法
    public int maximumPopulation(int[][] logs) {
        int[] diff = new int[101];  // 1950-2050年的差分数组
        
        // 构建差分数组
        for (int[] log : logs) {
            int birth = log[0], death = log[1];
            diff[birth - 1950] += 1;   // 出生年份人口+1
            diff[death - 1950] -= 1;   // 死亡年份人口-1
        }
        
        int maxPop = 0, year = 1950, curr = 0;
        
        // 通过前缀和还原实际人口，同时找最大值
        for (int i = 0; i < 101; i++) {
            curr += diff[i];
            if (curr > maxPop) {
                maxPop = curr;
                year = 1950 + i;
            }
        }
        
        return year;
    }
    
    // 暴力解法（用于对比）
    public int maximumPopulationBruteForce(int[][] logs) {
        int maxPop = 0, resultYear = 1950;
        
        // 枚举每一年
        for (int year = 1950; year <= 2050; year++) {
            int population = 0;
            
            // 统计这一年的人口
            for (int[] log : logs) {
                int birth = log[0], death = log[1];
                if (year >= birth && year < death) {
                    population++;
                }
            }
            
            // 更新最大人口年份
            if (population > maxPop) {
                maxPop = population;
                resultYear = year;
            }
        }
        
        return resultYear;
    }
    
    // 优化版本：使用事件排序
    public int maximumPopulationEvents(int[][] logs) {
        List<int[]> events = new ArrayList<>();  // {年份, 变化量}
        
        // 收集所有事件
        for (int[] log : logs) {
            events.add(new int[]{log[0], 1});   // 出生事件
            events.add(new int[]{log[1], -1});  // 死亡事件
        }
        
        // 按年份排序，同年份死亡事件在前
        events.sort((a, b) -> {
            if (a[0] == b[0]) {
                return Integer.compare(a[1], b[1]);  // 死亡事件(-1)在出生事件(1)前
            }
            return Integer.compare(a[0], b[0]);
        });
        
        int maxPop = 0, resultYear = 1950, currentPop = 0;
        
        // 处理事件
        for (int[] event : events) {
            currentPop += event[1];
            if (currentPop > maxPop) {
                maxPop = currentPop;
                resultYear = event[0];
            }
        }
        
        return resultYear;
    }
    
    // 函数式编程风格解法
    public int maximumPopulationFunctional(int[][] logs) {
        return Arrays.stream(logs)
            .collect(() -> new int[101], 
                    (diff, log) -> {
                        diff[log[0] - 1950] += 1;
                        diff[log[1] - 1950] -= 1;
                    },
                    (diff1, diff2) -> {
                        for (int i = 0; i < 101; i++) {
                            diff1[i] += diff2[i];
                        }
                    })
            .let(diff -> {
                int maxPop = 0, year = 1950, curr = 0;
                for (int i = 0; i < 101; i++) {
                    curr += diff[i];
                    if (curr > maxPop) {
                        maxPop = curr;
                        year = 1950 + i;
                    }
                }
                return year;
            });
    }
    
    // 使用TreeMap的解法
    public int maximumPopulationTreeMap(int[][] logs) {
        TreeMap<Integer, Integer> changes = new TreeMap<>();
        
        // 记录每年的人口变化
        for (int[] log : logs) {
            changes.merge(log[0], 1, Integer::sum);   // 出生年份+1
            changes.merge(log[1], -1, Integer::sum);  // 死亡年份-1
        }
        
        int maxPop = 0, resultYear = 1950, currentPop = 0;
        
        // 按年份顺序处理变化
        for (Map.Entry<Integer, Integer> entry : changes.entrySet()) {
            currentPop += entry.getValue();
            if (currentPop > maxPop) {
                maxPop = currentPop;
                resultYear = entry.getKey();
            }
        }
        
        return resultYear;
    }
    
    // 泛型版本的差分数组工具类
    public static class DifferenceArray {
        private final int[] diff;
        private final int offset;
        
        public DifferenceArray(int start, int end) {
            this.offset = start;
            this.diff = new int[end - start + 1];
        }
        
        public void update(int left, int right, int delta) {
            diff[left - offset] += delta;
            if (right + 1 - offset < diff.length) {
                diff[right + 1 - offset] -= delta;
            }
        }
        
        public int[] getPrefixSum() {
            int[] result = new int[diff.length];
            result[0] = diff[0];
            for (int i = 1; i < diff.length; i++) {
                result[i] = result[i - 1] + diff[i];
            }
            return result;
        }
        
        public int findMaxIndex() {
            int[] prefixSum = getPrefixSum();
            int maxVal = prefixSum[0], maxIdx = 0;
            for (int i = 1; i < prefixSum.length; i++) {
                if (prefixSum[i] > maxVal) {
                    maxVal = prefixSum[i];
                    maxIdx = i;
                }
            }
            return maxIdx + offset;
        }
    }
    
    // 使用工具类的解法
    public int maximumPopulationWithUtil(int[][] logs) {
        DifferenceArray diffArray = new DifferenceArray(1950, 2050);
        
        for (int[] log : logs) {
            diffArray.update(log[0], log[1] - 1, 1);
        }
        
        return diffArray.findMaxIndex();
    }
    
    // 测试方法
    public static void main(String[] args) {
        MaximumPopulation solution = new MaximumPopulation();
        
        // 测试用例1
        int[][] logs1 = {{1950, 1961}, {1960, 1971}, {1970, 1981}};
        System.out.println("测试用例1 - 差分数组: " + solution.maximumPopulation(logs1));  // 期望: 1960
        System.out.println("测试用例1 - 暴力解法: " + solution.maximumPopulationBruteForce(logs1));
        System.out.println("测试用例1 - 事件解法: " + solution.maximumPopulationEvents(logs1));
        System.out.println("测试用例1 - TreeMap: " + solution.maximumPopulationTreeMap(logs1));
        System.out.println("测试用例1 - 工具类: " + solution.maximumPopulationWithUtil(logs1));
        
        // 测试用例2
        int[][] logs2 = {{1993, 1999}, {2000, 2010}};
        System.out.println("测试用例2: " + solution.maximumPopulation(logs2));  // 期望: 1993
        
        // 测试用例3：边界情况
        int[][] logs3 = {{1950, 1951}, {1951, 1952}, {1952, 1953}};
        System.out.println("测试用例3: " + solution.maximumPopulation(logs3));  // 期望: 1950
        
        // 测试用例4：重叠区间
        int[][] logs4 = {{1950, 1960}, {1955, 1965}, {1958, 1968}};
        System.out.println("测试用例4: " + solution.maximumPopulation(logs4));  // 期望: 1958
        
        // 性能测试
        performanceTest();
    }
    
    // 性能测试
    public static void performanceTest() {
        MaximumPopulation solution = new MaximumPopulation();
        Random random = new Random(42);
        
        // 生成大量测试数据
        int[][] largeLogs = new int[10000][2];
        for (int i = 0; i < largeLogs.length; i++) {
            int birth = 1950 + random.nextInt(80);
            int death = birth + 1 + random.nextInt(20);
            largeLogs[i] = new int[]{birth, Math.min(death, 2050)};
        }
        
        // 测试不同算法的性能
        long start, end;
        
        start = System.nanoTime();
        solution.maximumPopulation(largeLogs);
        end = System.nanoTime();
        System.out.println("差分数组耗时: " + (end - start) / 1_000_000.0 + " ms");
        
        start = System.nanoTime();
        solution.maximumPopulationEvents(largeLogs);
        end = System.nanoTime();
        System.out.println("事件排序耗时: " + (end - start) / 1_000_000.0 + " ms");
        
        start = System.nanoTime();
        solution.maximumPopulationTreeMap(largeLogs);
        end = System.nanoTime();
        System.out.println("TreeMap耗时: " + (end - start) / 1_000_000.0 + " ms");
    }
}

/*
算法特点分析：

1. 差分数组解法 (推荐)
   - 时间复杂度：O(n + 101)
   - 空间复杂度：O(101)
   - 适用于区间更新问题
   - 代码简洁，效率最高

2. 暴力解法
   - 时间复杂度：O(101 * n)
   - 空间复杂度：O(1)
   - 思路直观，但效率较低

3. 事件排序解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 适用于年份范围很大的情况

4. TreeMap解法
   - 时间复杂度：O(n log n)
   - 空间复杂度：O(n)
   - 自动排序，代码简洁

5. 工具类解法
   - 封装差分数组逻辑
   - 提高代码复用性
   - 面向对象设计

Java特性应用：
- 集合框架：ArrayList, TreeMap
- Lambda表达式：简化排序和函数式操作
- 方法引用：Integer::sum, Integer::compare
- 泛型：类型安全
- 增强for循环：简化遍历
- 静态工具类：封装通用逻辑
- 性能测试：System.nanoTime()
*/