package prefix;

import java.util.HashMap;
import java.util.Map;

/**
 * LeetCode 2845: 统计趣味子数组 (Count Interesting Subarrays)
 * https://leetcode.cn/problems/count-interesting-subarrays/
 */
public class CountInterestingSubarrays2845 {

    /**
     * 统计趣味子数组
     * 思路：前缀和 + 哈希表 + 模运算
     *
     * @param nums   整数数组
     * @param modulo 模数
     * @param k      目标余数
     * @return 满足条件的子数组数量
     */
    public long countInterestingSubarrays(int[] nums, int modulo, int k) {
        // 哈希表，存储 <前缀和 % modulo, 出现次数>
        Map<Integer, Long> count = new HashMap<>();
        // 初始化，处理 l=0 的情况，空前缀和模 modulo 为 0
        count.put(0, 1L);
        long ans = 0;         // 结果
        int prefixSum = 0; // 当前的前缀和（满足 num % modulo == k 的元素个数）

        for (int num : nums) { // 遍历数组
            if (num % modulo == k) { // 如果当前元素满足条件
                prefixSum++;      // 前缀和加 1
            }

            // 计算我们需要的前一个前缀和模 modulo 的值
            // P[l] % modulo == (P[r+1] % modulo - k % modulo + modulo) % modulo
            int need = (prefixSum - k % modulo + modulo) % modulo;

            // 查找哈希表中是否存在需要的 need 值
            ans += count.getOrDefault(need, 0L);

            // 将当前的前缀和模 modulo 加入哈希表
            count.put(prefixSum % modulo, count.getOrDefault(prefixSum % modulo, 0L) + 1);
        }
        return ans;
    }

    public static void main(String[] args) {
        CountInterestingSubarrays2845 solver = new CountInterestingSubarrays2845();

        int[] nums1 = {3, 1, 9, 6};
        int modulo1 = 3;
        int k1 = 0;
        System.out.println(solver.countInterestingSubarrays(nums1, modulo1, k1)); // 预期输出 2

        int[] nums2 = {3, 2, 4};
        int modulo2 = 2;
        int k2 = 1;
        System.out.println(solver.countInterestingSubarrays(nums2, modulo2, k2)); // 预期输出 3
    }
}