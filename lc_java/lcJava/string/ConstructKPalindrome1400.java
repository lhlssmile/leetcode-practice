package string;

public class ConstructKPalindrome1400 {
    public boolean canConstruct(String s, int k) {
        int n = s.length();
        if (n < k) {
            return false;
        }
        int[] cnt = new int[26];
        for (int i = 0; i < n; ++i) {
            ++cnt[s.charAt(i) - 'a'];
        }
        int x = 0;
        for (int v : cnt) {
            x += v & 1;
        }
        return x <= k;
    }

    public static void main(String[] args) {
        String s = "ilovyuki";
        int k = 2;
        ConstructKPalindrome1400 sol = new ConstructKPalindrome1400();
        System.out.println(sol.canConstruct(s, k));
    }
}
