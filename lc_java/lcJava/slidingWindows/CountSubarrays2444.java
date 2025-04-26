package slidingWindows;

public class CountSubarrays2444 {
    public long countSubarrays(int[] nums,int minK,int maxK){
        long ans = 0;
        int n = nums.length;
        int minKPos = -1,maxKPos = -1,left = -1;
        for(int i = 0;i < n;i++){
            if (nums[i] < minK || nums[i] > maxK){
                left = i;
            }
            if (nums[i] == minK) minKPos = i;
            if (nums[i] == maxK) maxKPos = i;

            int validStart = Math.min(minKPos,maxKPos);
            if (validStart > left){
                ans += validStart - left;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        int[] nums = {1,3,5,2,7,5};
        int minK = 1,maxK = 5;
        CountSubarrays2444 sol = new CountSubarrays2444();
        System.out.println(sol.countSubarrays(nums, minK, maxK));
    }
}
