struct Solution;

impl Solution {
    pub fn permute(nums : Vec<i32> ) -> Vec<Vec<i32>> {
        let mut ans = Vec::new();
        let n = nums.len();
        let mut res = Vec::new();
        let mut vis = vec![false; n];

        fn dfs(nums: &Vec<i32>, i: usize, res: &mut Vec<i32>, vis: &mut Vec<bool>, ans : &mut Vec<Vec<i32>>) {
            if i == nums.len() {
                ans.push(res.clone());
                return ;
            }
            for j in 0..nums.len() {
                if !vis[j] {
                    res.push(nums[j]);
                    vis[j] = true;
                    dfs(nums, i + 1, res, vis, ans);
                    res.pop();
                    vis[j] = false;
                }
            }
        }
        dfs(&nums,0, &mut res, &mut vis, &mut ans );
        ans
    }
}
fn main() {

}