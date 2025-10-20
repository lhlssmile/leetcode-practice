import java.util.*;

class increasingOrSmash {
    
    public static int solve(int[] a) {
        Set<Integer> st = new HashSet<>();
        for (int x : a) {
            st.add(x);
        }
        int k = st.size();
        return 2 * k - 1;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int t = scanner.nextInt();  
        
        while (t-- > 0) {
            int n = scanner.nextInt();
            int[] a = new int[n];
            
            for (int i = 0; i < n; i++) {
                a[i] = scanner.nextInt();
            }
            
            System.out.println(solve(a));
        }
        
        scanner.close();
    }
}