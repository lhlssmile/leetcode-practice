package dp;


class MaxProduct152{
    public int maxProduct(int[] nums){
        int n = nums.length;
        int[] dpMax = new int[n];
        int[] dpMin = new int[n];
        dpMax[0] = dpMin[0] = nums[0];
        int maxProducts = nums[0];
        for (int i = 1;i < n;i++){
            int a_max = Math.max(dpMax[i - 1] * nums[i],dpMin[i - 1] * nums[i]);
            int a_min = Math.min(dpMax[i - 1] * nums[i],dpMin[i - 1] * nums[i]);
            dpMax[i] = Math.max(a_max,nums[i]);
            dpMin[i] = Math.min(a_min,nums[i]);
            maxProducts = Math.max(dpMax[i],maxProducts);
        }
        return maxProducts;
    }

    public static void main(String[] args) {
        MaxProduct152 sol = new MaxProduct152();
        int[] nums = {-2,3,-4};
        System.out.println(sol.maxProduct(nums));
    }
}
