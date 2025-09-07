func checkSubarraySum(nums []int, k int) bool {
    m := len(nums)
    modMap := make(map[int]int)
    modMap[0] = -1
    prefixS := 0
    
    for i := 0; i < m; i++ {
        prefixS += nums[i]
        
        mod := prefixS % k
        
        if prevIndex, exists := modMap[mod]; exists {
            if i-prevIndex >= 2 {
                return true
            }
        } else {
            modMap[mod] = i
        }
    }
    return false
}