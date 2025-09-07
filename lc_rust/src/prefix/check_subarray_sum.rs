use std::collections::HashMap;

// 双指针解法
pub fn check_subarray_sum(nums: Vec<i32>, k: i32) -> bool {
    let m = nums.len();
    let mut mod_map = HashMap::new();
    mod_map.insert(0, -1);
    let mut prefix_s = 0;
    
    for i in 0..m {
        prefix_s += nums[i];
        
        let mod_val = prefix_s % k;
        
        if let Some(&prev_index) = mod_map.get(&mod_val) {
            if i as i32 - prev_index >= 2 {
                return true;
            }
        } else {
            mod_map.insert(mod_val, i as i32);
        }
    }
    false
}

// 函数式编程解法
pub fn check_subarray_sum_functional(nums: Vec<i32>, k: i32) -> bool {
    let mut mod_map = HashMap::new();
    mod_map.insert(0, -1);
    
    nums.iter()
        .enumerate()
        .scan(0, |prefix_s, (i, &num)| {
            *prefix_s += num;
            Some((i as i32, *prefix_s % k))
        })
        .any(|(i, mod_val)| {
            if let Some(&prev_index) = mod_map.get(&mod_val) {
                if i - prev_index >= 2 {
                    return true;
                }
            } else {
                mod_map.insert(mod_val, i);
            }
            false
        })
}
