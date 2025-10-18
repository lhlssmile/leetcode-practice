package lcJava.backtrack;

import java.util.ArrayList;
import java.util.List;

public class LetterCasePermutation {
    public List<String> letterCasePermutation(String s) {
        List<String> ans = new ArrayList<>();
        StringBuilder path = new StringBuilder();
        
        dfs(s, 0, path, ans);
        return ans;
    }
    
    private void dfs(String s, int i, StringBuilder path, List<String> ans) {
        if (i == s.length()) {
            ans.add(path.toString());
            return;
        }
        
        char ch = s.charAt(i);
        if (Character.isDigit(ch)) {
            path.append(ch);
            dfs(s, i + 1, path, ans);
            path.deleteCharAt(path.length() - 1);
        } else {
            // 小写
            path.append(Character.toLowerCase(ch));
            dfs(s, i + 1, path, ans);
            path.deleteCharAt(path.length() - 1);
            
            // 大写
            path.append(Character.toUpperCase(ch));
            dfs(s, i + 1, path, ans);
            path.deleteCharAt(path.length() - 1);
        }
    }
    
    // 测试函数
    public static void main(String[] args) {
        LetterCasePermutation solution = new LetterCasePermutation();
        
        // 测试用例1
        String s1 = "a1b2";
        List<String> result1 = solution.letterCasePermutation(s1);
        System.out.println("Input: " + s1);
        System.out.println("Output: " + result1);
        
        // 测试用例2
        String s2 = "3z4";
        List<String> result2 = solution.letterCasePermutation(s2);
        System.out.println("Input: " + s2);
        System.out.println("Output: " + result2);
    }
}

/*
算法思路：递归回溯生成所有可能的字母大小写排列
时间复杂度：O(2^n)，其中n是字符串中字母的数量
空间复杂度：O(n)，递归栈的深度和临时字符串的空间
*/