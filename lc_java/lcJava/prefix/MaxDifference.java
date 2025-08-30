package lcJava.prefix;

public class MaxDifference {
    public int maxDifference(String s, int k) {
        final int inf = Integer.MAX_VALUE / 2;
        int ans = -inf;
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                if (y == x) {
                    continue;
                }
                int[] cur_s = new int[5];
                int[] pre_s = new int[5];
                int[][] min_s = new int[][]{{inf, inf}, {inf, inf}};
                int left = 0;
                for (int i = 0; i < s.length(); i++) {
                    cur_s[s.charAt(i) - '0']++;
                    int r = i + 1;
                    while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
                        int p = min_s[pre_s[x] & 1][pre_s[y] & 1];
                        min_s[pre_s[x] & 1][pre_s[y] & 1] = Math.min(p, pre_s[x] - pre_s[y]);
                        pre_s[s.charAt(left) - '0']++;
                        left++;
                    }
                    ans = Math.max(ans, cur_s[x] - cur_s[y] - min_s[(cur_s[x] & 1) ^ 1][cur_s[y] & 1]);
                }
            }
        }
        return ans;
    }
    
    // 优化版本：使用更具描述性的变量名和注释
    public int maxDifferenceOptimized(String s, int k) {
        final int INF = Integer.MAX_VALUE / 2;
        int maxDifference = -INF;
        
        // 枚举所有可能的字符对(x,y)，其中x!=y
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                if (y == x) continue;
                
                // 当前窗口中各字符的计数
                int[] currentCount = new int[5];
                // 前缀窗口中各字符的计数
                int[] prefixCount = new int[5];
                // 存储最小差值，按奇偶性分类
                int[][] minDifference = new int[][]{{INF, INF}, {INF, INF}};
                
                int left = 0;
                for (int i = 0; i < s.length(); i++) {
                    // 更新当前窗口计数
                    currentCount[s.charAt(i) - '0']++;
                    int right = i + 1;
                    
                    // 当窗口大小>=k且满足条件时，更新最小差值
                    while (right - left >= k && currentCount[x] > prefixCount[x] && currentCount[y] > prefixCount[y]) {
                        // 根据x和y的奇偶性选择对应的最小差值
                        int parity_x = prefixCount[x] & 1; // x的奇偶性
                        int parity_y = prefixCount[y] & 1; // y的奇偶性
                        minDifference[parity_x][parity_y] = Math.min(
                            minDifference[parity_x][parity_y], 
                            prefixCount[x] - prefixCount[y]
                        );
                        
                        // 移动左指针，更新前缀计数
                        prefixCount[s.charAt(left) - '0']++;
                        left++;
                    }
                    
                    // 计算当前最大差值
                    // 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
                    int current_parity_x = (currentCount[x] & 1) ^ 1;
                    int current_parity_y = currentCount[y] & 1;
                    maxDifference = Math.max(
                        maxDifference, 
                        currentCount[x] - currentCount[y] - minDifference[current_parity_x][current_parity_y]
                    );
                }
            }
        }
        
        return maxDifference;
    }
    
    public static void main(String[] args) {
        MaxDifference solution = new MaxDifference();
        
        // 测试用例
        String s1 = "01234";
        int k1 = 2;
        System.out.println("测试用例1结果: " + solution.maxDifference(s1, k1));
        System.out.println("测试用例1结果(优化版): " + solution.maxDifferenceOptimized(s1, k1));
        
        String s2 = "00110";
        int k2 = 2;
        System.out.println("测试用例2结果: " + solution.maxDifference(s2, k2));
        System.out.println("测试用例2结果(优化版): " + solution.maxDifferenceOptimized(s2, k2));
    }
}