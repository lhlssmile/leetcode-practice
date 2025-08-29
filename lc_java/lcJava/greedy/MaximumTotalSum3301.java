package lcJava.greedy;

import java.util.Arrays;

/**
 * 力扣第3301题：高度互不相同的最大塔高和
 * 
 * 题目描述：给定一个数组 maximumHeight，求高度互不相同的最大塔高和
 */
public class MaximumTotalSum3301 {
    
    /**
     * 计算高度互不相同的最大塔高和
     * 
     * @param maximumHeight 塔的高度数组
     * @return 高度互不相同的最大塔高和，如果无法满足条件则返回-1
     */
    public long maximumTotalSum(int[] maximumHeight) {
        // 创建副本以避免修改原始数组
        int[] heights = Arrays.copyOf(maximumHeight, maximumHeight.length);
        
        // 按降序排序
        Arrays.sort(heights);
        reverseArray(heights);
        
        int prev = Integer.MAX_VALUE;
        long ans = 0;
        
        for (int h : heights) {
            // 确保当前高度严格小于前一个高度
            int curr = Math.min(h, prev - 1);
            if (curr <= 0) return -1;
            ans += curr;
            prev = curr;
        }
        
        return ans;
    }
    
    /**
     * 反转数组
     * 
     * @param arr 要反转的数组
     */
    private void reverseArray(int[] arr) {
        int left = 0;
        int right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    
    /**
     * 测试方法
     */
    public static void main(String[] args) {
        MaximumTotalSum3301 solution = new MaximumTotalSum3301();
        
        // 测试用例1
        int[] heights1 = {5, 3, 4, 1, 1};
        System.out.println("测试用例1: " + solution.maximumTotalSum(heights1)); // 预期输出：13
        
        // 测试用例2
        int[] heights2 = {6, 5, 3, 9, 2, 7};
        System.out.println("测试用例2: " + solution.maximumTotalSum(heights2)); // 预期输出：29
        
        // 测试用例3
        int[] heights3 = {3, 2, 1};
        System.out.println("测试用例3: " + solution.maximumTotalSum(heights3)); // 预期输出：6
        
        // 测试用例4 - 无法满足条件
        int[] heights4 = {1, 1, 1};
        System.out.println("测试用例4: " + solution.maximumTotalSum(heights4)); // 预期输出：-1
    }
}