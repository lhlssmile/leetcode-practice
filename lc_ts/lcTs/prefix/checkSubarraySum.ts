function checkSubarraySum(nums: number[], k: number): boolean {
    const m: number = nums.length;
    const modMap: Map<number, number> = new Map();
    modMap.set(0, -1);
    let prefixS: number = 0;
    
    for (let i = 0; i < m; i++) {
        prefixS += nums[i];
        
        const mod: number = prefixS % k;
        
        if (modMap.has(mod)) {
            if (i - modMap.get(mod)! >= 2) {
                return true;
            }
        } else {
            modMap.set(mod, i);
        }
    }
    return false;
}