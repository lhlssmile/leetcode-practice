struct Solution;

impl Solution {
    pub fn count_pairs(mut nums: Vec<i32>, target: i32) -> i32 {
        let mut i = 0;
        let mut j = nums.len() - 1;
        let mut ans = 0;
        nums.sort();
        while i < j {
            if nums[i] + nums[j] < target {
                ans += j - i;
                i += 1;
            } else {
                j -= 1;
            }
        }

        ans as i32
    }
}
fn main() {
    let nums = vec![-1, 1, 2, 3, 1];
    let target = 2;
    println!("{}", Solution::count_pairs(nums, target));
}
