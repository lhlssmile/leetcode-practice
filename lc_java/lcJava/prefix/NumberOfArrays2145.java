package prefix;

public class NumberOfArrays2145 {
    public int numberOfArrays(int[] differences, int lower, int upper) {
        long s = 0, minS = 0, maxS = 0; // s[0] = 0
        for (int d : differences) {
            s += d;
            minS = Math.min(minS, s);
            maxS = Math.max(maxS, s);
        }
        return (int) Math.max(upper - lower - maxS + minS + 1, 0);
    }

    public static void main(String[] args) {
        int[] differences = {1,-3,4};
        int lower = 1,upper = 6;
        NumberOfArrays2145 sol = new NumberOfArrays2145();
        System.out.println(sol.numberOfArrays(differences, lower, upper));
    }
}
