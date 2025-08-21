struct Solution;

impl Solution {
    pub fn is_zero_array(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> bool {
        let n = nums.len();

        let mut diff = vec![0; n + 2];

        for (_, q) in queries.iter().enumerate() {
            let v1 = q[0] as usize;
            let v2 = q[1] as usize;
            diff[v1] += 1;
            diff[v2 + 1] -= 1;
        }

        let mut s = 0;
        for i in 0..n {
            s += diff[i];
            if s < nums[i] {
                return false
            }
        }
        true
    }
}


fn main() {

}