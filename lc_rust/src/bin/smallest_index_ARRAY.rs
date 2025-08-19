struct Solution;

impl Solution {
    pub fn smallest_index(nums: Vec<i32>) -> i32 {
        for (i, &x) in nums.iter().enumerate() {
            let digit_sum: i32 = x.abs().to_string()
                .chars()
                .map(|c| (c as u8 - b'0') as i32)
                .sum();
            if digit_sum == i as i32 {
                return i as i32;
            }
        }
        -1
    }
    fn digit_sum (mut n :i32) -> i32{
        let mut sum = 0;
        n = n.abs();
        while n > 0 {
            sum += n % 10;
            n /= 10;
        }
        sum
    }
    
}
fn main() {
    let nums = vec![1, 2, 3];
    Solution::smallest_index(nums);
}