struct Solution;

impl Solution {
    pub fn results_array(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let n :usize = nums.len();
        let mut ans = vec![-1; n - k as usize + 1];
        let mut cnt = 0;
        for (i, &val) in nums.iter().enumerate() {
            if i == 0 || val == &nums[i - 1] + 1 {
                cnt += 1;
            }else {
                cnt = 1;
            }
            if cnt >= k {
                ans[i - k as usize + 1] = nums[i];
            }
        };
        ans
    }
    fn calculate(s : &String ) {
        s.len();
    }
    fn change(s : &mut String) {
        s.push_str(", world")
    }
}
fn main() {
    let s1 = String::from("hello");
    Solution::calculate(&s1);

}