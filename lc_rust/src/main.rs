struct Solution;

impl Solution {
    pub fn perfect_pairs(nums: Vec<i32>) -> i64 {
        let mut nums = nums; // 接管所有权
        for x in nums.iter_mut() {
            if *x < 0 {
                *x = -*x;
            }
        }

        nums.sort();

        let mut ans: i64 = 0;
        let mut left: usize = 0;

        for (j, &b) in nums.iter().enumerate() {
            while left < nums.len() && nums[left] * 2 < b {
                left += 1;
            }
            ans += (j as i64) - (left as i64);
        }
        ans
    }
}

fn main() {
    let test_cases = vec![
        vec![1, -2, 3, -4], // 预期输出：4
        vec![1, 2, 3],     // 预期输出：3
        vec![-1, -2, -3],  // 预期输出：3
    ];

    for nums in test_cases {
        let ans = Solution::perfect_pairs(nums);
        println!("Output: {}", ans);
    }

}