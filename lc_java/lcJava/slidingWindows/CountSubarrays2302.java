package slidingWindows;


class CountSubarrays2302{
    public long countSubarrays(int[] nums, long k) {
        int n = nums.length;
        int left = 0;
        long prefixSum = 0, ans = 0;
        
        for (int right = 0; right < n; ++right) {
            prefixSum += nums[right];
            while (left <= right && prefixSum * (right - left + 1) >= k) {
                prefixSum -= nums[left++];
            }
            ans += right - left + 1;
        }
        return ans;
    }
    
    public static void main(String[] args) {
        CountSubarrays2302 sol = new CountSubarrays2302();
        int[] nums = {2,1,4,3,5};
        long k = 10;
        System.out.println(sol.countSubarrays(nums, k));
    }
}