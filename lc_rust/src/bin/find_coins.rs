struct Solution;

impl Solution {
    pub fn find_coins (num_ways: Vec<i32>) -> Vec<i32> {
        let mut ans = Vec::new();
        let n = num_ways.len();
        let mut f = vec![0; n + 1];
        f[0] = 1;

        for i in 1..=n {
            let mut ways = num_ways[i - 1];
            if ways == f[i]{
                continue
            }
            if ways - 1 != f[i] {
                return Vec::new()
            }
            ans.push(i as i32);
            for j in i..=n {
                f[j] += f[j - i]
            }
        }

        ans
    }
}
fn main() {

}