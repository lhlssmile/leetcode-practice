use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn find_smallest_integer(mut nums: Vec<i32>, m: i32) -> i32 {
        let mut cnt: HashMap<i32, usize> = HashMap::new();

        for x in nums {
            *cnt.entry((x % m + m) % m).or_insert(0) += 1;
        }
        for mex in 0.. {
            if let Some(c) = cnt.get_mut(&(mex % m)) {
                if *c > 0 {
                    *c -= 1;
                    continue
                }
            }
            return mex
        }
        unreachable!()
    }
}
fn main() {

}