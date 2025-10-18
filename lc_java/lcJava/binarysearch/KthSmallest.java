package lcJava.binarySearch;

import java.util.PriorityQueue;

public class KthSmallest {
    
    // 二分查找解法
    public int kthSmallest(int[][] matrix, int k) {
        int n = matrix.length;
        int lo = matrix[0][0];
        int hi = matrix[n-1][n-1];
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int count = countLessEqual(matrix, mid);
            if (count < k) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
    
    private int countLessEqual(int[][] matrix, int target) {
        int n = matrix.length;
        int i = n - 1;
        int j = 0;
        int count = 0;
        
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= target) {
                count += i + 1; // 当前列中有i+1个元素小于等于target
                j++;
            } else {
                i--;
            }
        }
        return count;
    }
    
    // 最小堆解法
    public int kthSmallestHeap(int[][] matrix, int k) {
        int n = matrix.length;
        // 使用优先队列（最小堆）
        // 存储三元组 [值, 行, 列]
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        
        // 将第一列的元素加入堆
        for (int i = 0; i < Math.min(n, k); i++) {
            pq.offer(new int[]{matrix[i][0], i, 0});
        }
        
        // 弹出k-1个元素
        for (int i = 1; i < k; i++) {
            int[] curr = pq.poll();
            
            int row = curr[1];
            int col = curr[2];
            
            if (col + 1 < n) {
                pq.offer(new int[]{matrix[row][col + 1], row, col + 1});
            }
        }
        
        return pq.peek()[0];
    }
    
    // 测试函数
    public static void main(String[] args) {
        KthSmallest solution = new KthSmallest();
        
        // 测试用例1
        int[][] matrix1 = {
            {1, 5, 9},
            {10, 11, 13},
            {12, 13, 15}
        };
        int k1 = 8;
        System.out.println("Binary Search: " + solution.kthSmallest(matrix1, k1));
        System.out.println("Heap: " + solution.kthSmallestHeap(matrix1, k1));
        
        // 测试用例2
        int[][] matrix2 = {
            {1, 2},
            {1, 3}
        };
        int k2 = 2;
        System.out.println("Binary Search: " + solution.kthSmallest(matrix2, k2));
        System.out.println("Heap: " + solution.kthSmallestHeap(matrix2, k2));
    }
}

/*
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
*/