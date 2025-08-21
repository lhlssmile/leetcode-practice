struct Solution;

impl Solution {
    pub fn k_length_apart(nums : Vec<i32>, k: i32) -> bool {
        let mut last:i32 = -1;
        for (i, &x) in nums.iter().enumerate() {
            if x == 1 {
                let i = i as i32;
                if last != -1 && i - last <= k {
                    return false
                }
                last = i
            }
        }
        true
    }
}
fn main() {

}