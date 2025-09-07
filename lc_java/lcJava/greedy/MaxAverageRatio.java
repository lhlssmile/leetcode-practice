import java.util.*;

class Solution {
    public double maxAverageRatio(int[][] classes, int extraStudents) {
        // 使用优先队列，按增益降序排列
        PriorityQueue<double[]> pq = new PriorityQueue<>((a, b) -> 
            Double.compare(b[0], a[0])
        );
        
        // 初始化堆
        for (int[] c : classes) {
            double pass = c[0], total = c[1];
            double gain = (pass + 1) / (total + 1) - pass / total;
            pq.offer(new double[]{gain, pass, total});
        }
        
        // 分配额外学生
        for (int i = 0; i < extraStudents; i++) {
            double[] top = pq.poll();
            double pass = top[1] + 1;
            double total = top[2] + 1;
            double gain = (pass + 1) / (total + 1) - pass / total;
            pq.offer(new double[]{gain, pass, total});
        }
        
        // 计算平均通过率
        double totalRatio = 0.0;
        while (!pq.isEmpty()) {
            double[] top = pq.poll();
            totalRatio += top[1] / top[2];
        }
        
        return totalRatio / classes.length;
    }
    
    public static void main(String[] args) {
        Solution s = new Solution();
        
        // 测试用例1
        int[][] classes1 = {{1,2},{3,5},{2,2}};
        int extraStudents1 = 2;
        double result1 = s.maxAverageRatio(classes1, extraStudents1);
        System.out.printf("测试用例1: %.5f%n", result1);
        
        // 测试用例2
        int[][] classes2 = {{2,4},{3,9},{4,5},{2,10}};
        int extraStudents2 = 4;
        double result2 = s.maxAverageRatio(classes2, extraStudents2);
        System.out.printf("测试用例2: %.5f%n", result2);
    }
}