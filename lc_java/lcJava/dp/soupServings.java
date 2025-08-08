package dp;

public class soupServings {
    public double soupServings(int n) {
        if (n >= 5000) return 1.0; // 大输入直接返回

        n = (n + 24) / 25; // 缩成 25ml 为单位
        double[][] dp = new double[n + 1][n + 1];

        // 初始化边界
        dp[0][0] = 0.5;
        for (int b = 1; b <= n; b++) dp[0][b] = 1.0; // A 先空
        for (int a = 1; a <= n; a++) dp[a][0] = 0.0; // B 先空

        // 填表
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                dp[a][b] = 0.25 * (
                        dp[Math.max(0, a - 4)][b] +
                                dp[Math.max(0, a - 3)][Math.max(0, b - 1)] +
                                dp[Math.max(0, a - 2)][Math.max(0, b - 2)] +
                                dp[Math.max(0, a - 1)][Math.max(0, b - 3)]
                );
            }
        }

        return dp[n][n];
    }
}
