package lcJava.slidingWindows;

import java.util.*;

public class FindSubstring {
    public List<Integer> findSubstring(String s, String[] words) {
        int n = words.length;
        int m = s.length();
        int k = words[0].length();
        int totalLen = n * k;
        List<Integer> ans = new ArrayList<>();
        
        if (m < totalLen) return ans;
        
        // 需求表
        Map<String, Integer> need = new HashMap<>();
        for (String w : words) {
            need.put(w, need.getOrDefault(w, 0) + 1);
        }
        
        // 遍历起点：对齐方式
        for (int offset = 0; offset < k; offset++) {
            int left = offset;
            Map<String, Integer> window = new HashMap<>();
            int count = 0; // 窗口内匹配的单词数
            
            // 枚举每个单词起点
            for (int right = offset; right + k <= m; right += k) {
                String w = s.substring(right, right + k);
                
                // 窗口右扩
                if (need.containsKey(w)) {
                    window.put(w, window.getOrDefault(w, 0) + 1);
                    count++;
                    
                    // 如果某个单词超频，收缩窗口
                    while (window.get(w) > need.get(w)) {
                        String lw = s.substring(left, left + k);
                        window.put(lw, window.get(lw) - 1);
                        left += k;
                        count--;
                    }
                    
                    // 如果窗口刚好包含n个单词
                    if (count == n) {
                        ans.add(left);
                        // 再往前收缩一步，准备找下一个
                        String lw = s.substring(left, left + k);
                        window.put(lw, window.get(lw) - 1);
                        left += k;
                        count--;
                    }
                } else {
                    // 不在need中，清空窗口
                    window.clear();
                    count = 0;
                    left = right + k;
                }
            }
        }
        
        return ans;
    }
    
    public static void main(String[] args) {
        FindSubstring solution = new FindSubstring();
        String s = "barfoothefoobarman";
        String[] words = {"foo", "bar"};
        
        List<Integer> result = solution.findSubstring(s, words);
        
        System.out.print("Result: ");
        for (int pos : result) {
            System.out.print(pos + " ");
        }
        System.out.println();
    }
}