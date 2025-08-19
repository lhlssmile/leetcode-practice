
struct Solution;

use std::collections::HashMap;

impl Solution {
    fn digit_sum(mut n: i32) -> i32 {
        let mut s = 0;
        while n > 0 {
            s += n % 10;
            n /= 10;
        }
        s
    }

    pub fn min_swaps(nums: Vec<i32>) -> i32 {
        let n = nums.len();

        // 1. 得到排序后的数组
        let mut sorted_nums = nums.clone();
        sorted_nums.sort_by(|&a, &b| {
            let sa = Self::digit_sum(a);
            let sb = Self::digit_sum(b);
            if sa != sb {
                sa.cmp(&sb)    // 数位和小的在前
            } else {
                a.cmp(&b)      // 数位和相等，数值小的在前
            }
        });

        // 2. 值 -> 目标位置
        let mut pos = HashMap::new();
        for (i, &val) in sorted_nums.iter().enumerate() {
            pos.insert(val, i);
        }

        // 3. 置换分解
        let mut visited = vec![false; n];
        let mut swaps = 0;

        for i in 0..n {
            if visited[i] || pos[&nums[i]] == i {
                continue;
            }
            let mut cycle_len = 0;
            let mut j = i;
            while !visited[j] {
                visited[j] = true;
                j = pos[&nums[j]];
                cycle_len += 1;
            }
            swaps += cycle_len - 1;
        }
        swaps as i32
    }
}

fn main() {

}