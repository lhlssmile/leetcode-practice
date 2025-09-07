class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int m = nums.size();
        unordered_map<int, int> mod_map;
        mod_map[0] = -1;
        int prefix_s = 0;
        
        for (int i = 0; i < m; i++) {
            prefix_s += nums[i];
            
            int mod = prefix_s % k;
            
            if (mod_map.find(mod) != mod_map.end()) {
                if (i - mod_map[mod] >= 2) {
                    return true;
                }
            } else {
                mod_map[mod] = i;
            }
        }
        return false;
    }
};