struct Solution;
impl Solution {
    pub fn number_of_points(nums: Vec<Vec<i32>>) -> i32 {
        let max_end = nums.iter().map(|x| x[1]).max().unwrap_or(0) as usize;
        let mut diff = vec![0; (max_end + 2) as usize]; // 差分数组，+2防越界

        // 构建差分数组
        for interval in nums {
            let start = interval[0] as usize;
            let end = interval[1] as usize;
            diff[start] += 1; // 起点+1
            diff[end + 1] -= 1; // 终点+1处-1
        }

        // 恢复覆盖次数并计数
        let mut count = 0;
        let mut cover = 0;
        for i in 1..=max_end {
            cover += diff[i]; // 前缀和
            if cover > 0 {
                count += 1; // 被覆盖的点
            }
        }

        count
    }

}
fn main() {
    let nums = vec!{
        vec!{3, 6},
        vec!{1, 5},
        vec!{4, 7}
    };
    Solution::number_of_points(nums);
}