package DFS;



class ConcatenatedDivisibility3533{
    public int[] concatenatedDivisibility(int[] nums,int k){
        int n = nums.length;
        int[] pow10 = new int[n];
        for (int i = 0;i < n;i++){
            pow10[i] = (int) Math.pow(10,Integer.toString(nums[i]).length());
        }
        int[] ans = new int[n];
        boolean[][] vis = new boolean[1 << n][k];

        if (!dfs((1 << n) - 1,0,nums,pow10,k,vis,ans) ){
            return new int[]{};
        }
        return ans;
    }
    private boolean dfs(int s,int x,int[] nums,int[] pow10,int k,boolean[][] vis,int[] ans){
        if (s == 0){
            return x == 0;
        }
        if(vis[s][x]){
            return false;
        }
        vis[s][x] =true;

        // 遍历所有可能的数字
        for(int i = 0;i < nums.length;i++){
            // 检查当前数字是否未被使用（通过位运算检查）
            // s & (1 << i) > 0 表示第i位为1，即数字i未被使用
            if((s & (1 << i)) > 0){
                // 递归尝试使用当前数字
                // s ^ (1 << i) 将第i位设为0，表示使用数字i
                // (x * pow10[i] + nums[i]) % k 计算新的模值
                if(dfs(s ^ (1 << i),(x * pow10[i] + nums[i]) % k,nums,pow10,k,vis,ans)){
                    // 如果找到解，将当前数字放入正确的位置
                    // nums.length - Integer.bitCount(s) 计算当前数字应该放在ans数组的哪个位置
                    // Integer.bitCount(s) 计算s中1的个数，即未使用的数字个数
                    ans[nums.length - Integer.bitCount(s)] = nums[i];
                    return true;
                }
            }
        }
        return false;
    }


    public static void main(String[] args){
        ConcatenatedDivisibility3533 sol = new ConcatenatedDivisibility3533();
        int[]  nums = {3,12,45};
        int k = 5;
        int[] res = sol.concatenatedDivisibility(nums,k);
        for (int re : res) {
            System.out.print(re);
        }
    }
}