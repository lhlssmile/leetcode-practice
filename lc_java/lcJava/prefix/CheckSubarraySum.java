class Solution {
    public boolean checkSubarraySum(int[] nums, int k) {
        int m = nums.length;
        Map<Integer, Integer> modMap = new HashMap<>();
        modMap.put(0, -1);
        int prefixS = 0;
        
        for (int i = 0; i < m; i++) {
            prefixS += nums[i];
            
            int mod = prefixS % k;
            
            if (modMap.containsKey(mod)) {
                if (i - modMap.get(mod) >= 2) {
                    return true;
                }
            } else {
                modMap.put(mod, i);
            }
        }
        return false;
    }
}