package slidingWindows;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class countCompleteSubarrays2799{
    public int countCompleteSubarrays(int[] nums){
        Set<Integer> all = new HashSet<>();
        for (int num : nums ){
            all.add(num);
        }
        int totalKinds = all.size();

        Map<Integer,Integer> freq = new HashMap<>();
        int left = 0,ans = 0;
        for (int right = 0;right < nums.length;right++){
            freq.put(nums[right],freq.getOrDefault(nums[right],0) + 1);
            while(freq.size() == totalKinds){
                ans += nums.length - right;     //当前右端点 已经满足完全子数组 再加右端点也是冗余 所以不用知道具体子数组是什么
                freq.put(nums[left],freq.get(nums[left]) - 1);
                if (freq.get(nums[left]) == 0) freq.remove(nums[left]);
                left++;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        countCompleteSubarrays2799 sol = new countCompleteSubarrays2799();
        int[] nums = {1,3,1,2,2};
        System.out.println(sol.countCompleteSubarrays(nums));
    }
}