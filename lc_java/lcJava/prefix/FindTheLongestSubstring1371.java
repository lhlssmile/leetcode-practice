package lcJava.prefix;

import java.util.HashMap;
import java.util.Map;

/**
 * LeetCode 1371. 每个元音包含偶数次的最长子字符串
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
 */
public class FindTheLongestSubstring1371 {
    
    /**
     * 使用前缀和+状态压缩的方法
     * 时间复杂度: O(n)，其中n是字符串长度
     * 空间复杂度: O(1)，状态数最多为2^5=32种
     */
    public int findTheLongestSubstring(String s) {
        int n = s.length();
        Map<Integer, Integer> first = new HashMap<>(); // 记录状态第一次出现的位置
        first.put(0, -1); // 空字符串状态为0，位置-1
        int state = 0; // 当前前缀的元音奇偶状态
        int maxLen = 0; // 最长子字符串长度
        
        // 元音映射：a=0, e=1, i=2, o=3, u=4
        int[] vowelPos = new int[128];
        for (int i = 0; i < vowelPos.length; i++) {
            vowelPos[i] = -1;
        }
        vowelPos['a'] = 0;
        vowelPos['e'] = 1;
        vowelPos['i'] = 2;
        vowelPos['o'] = 3;
        vowelPos['u'] = 4;
        
        // 遍历字符串
        for (int i = 0; i < n; i++) {
            // 如果是元音，更新状态（翻转对应位的奇偶性）
            int pos = vowelPos[s.charAt(i)];
            if (pos != -1) {
                state ^= (1 << pos); // 翻转第pos位
            }
            
            // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
            if (first.containsKey(state)) {
                maxLen = Math.max(maxLen, i - first.get(state));
            } else {
                // 记录状态第一次出现的位置
                first.put(state, i);
            }
        }
        
        return maxLen;
    }
    
    /**
     * 测试函数
     */
    public static void main(String[] args) {
        FindTheLongestSubstring1371 solution = new FindTheLongestSubstring1371();
        String s = "eleetminicoworoep";
        System.out.println(solution.findTheLongestSubstring(s)); // 应输出13
        
        s = "leetcodeisgreat";
        System.out.println(solution.findTheLongestSubstring(s)); // 应输出5
        
        s = "bcbcbc";
        System.out.println(solution.findTheLongestSubstring(s)); // 应输出6
    }
}