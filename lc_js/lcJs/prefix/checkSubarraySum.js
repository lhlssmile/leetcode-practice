function checkSubarraySum(nums, k) {
    const m = nums.length;
    const modMap = new Map();
    modMap.set(0, -1);
    let prefixS = 0;
    
    for (let i = 0; i < m; i++) {
        prefixS += nums[i];
        
        const mod = prefixS % k;
        
        if (modMap.has(mod)) {
            if (i - modMap.get(mod) >= 2) {
                return true;
            }
        } else {
            modMap.set(mod, i);
        }
    }
    return false;
}