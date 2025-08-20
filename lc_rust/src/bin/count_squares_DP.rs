struct Solution;

impl Solution {
    pub fn count_squares(matrix : Vec<Vec<i32>>) -> i32 {
        let mut cnt = 0;
        let m = matrix.len();
        let n = matrix[0].len();
        let mut prev = vec![0; n + 1];
        let mut curr = vec![0;n + 1];

        for i in 0..m {
            for j in 0..n {

                if matrix[i][j] == 0 {
                    curr[j + 1] = 0;
                    continue;
                }
                curr[j + 1] = Self::min_judge(curr[j],prev[j], prev[j + 1]) + 1;
                cnt += curr[j + 1];
            }
            // 交换 prev 和 curr
            std::mem::swap(&mut prev, &mut curr);
            // 重置 curr 为全 0
            curr.fill(0);
        }
        cnt
    }
    fn min_judge(mut a:  i32, b:  i32, c : i32) -> i32 {
        if a > b {
            a = b
        }
        if a > c {
            a = c
        }
        a
    }
}

fn main() {
    let matrix = vec!{
        vec![0, 1, 1, 1],
        vec![1, 1, 1, 1],
        vec![0, 1, 1, 1]
    };
    Solution::count_squares(matrix);
}