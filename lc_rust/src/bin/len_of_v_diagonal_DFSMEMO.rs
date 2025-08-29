pub struct Solution;

impl Solution {
    const DIRS :[(i32, i32); 4] = [(1, 1), (1, -1), (-1, -1), (-1, 1)];

    pub fn len_of_v_diagonal(grid: Vec<Vec<i32>>) -> i32 {
        let mut ans = 0;
        let m = grid.len();
        let n = grid[0].len();

        let mut memo = vec![vec![vec![vec![-1; 2]; 4]; n]; m];

        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 1 {
                    for dir in 0..4 {
                        ans = ans.max(1 + Self::dfs(i as i32, j as i32, dir as i32, 2,1, &grid, &mut memo))
                    }
                }
            }
        }

        ans
    }
    fn dfs(i: i32, j: i32, k: i32, target: i32, can_turn: i32, grid: &Vec<Vec<i32>>,
           memo: &mut Vec<Vec<Vec<Vec<i32>>>>) -> i32 {

        let ni = i + Self::DIRS[k as usize].0;
        let nj = j + Self::DIRS[k as usize].1;

        if ni < 0 || nj < 0 || nj > grid[0].len() as i32 || ni > grid.len() as i32 || grid[ni as usize][nj as usize] != target {
            return 0
        }
        if (memo[ni as usize][nj as usize][k as usize][can_turn as usize] != 0) {return memo[ni as usize][nj as usize][k as usize][can_turn as usize];}

        let mut res = 1 + Self::dfs(ni, nj, k, if target == 2 {0} else {2}, can_turn, grid, memo);

        if can_turn == 1 {
            let turn_k = (k + 1) % 4;
            res = res.max(1 + Self::dfs(ni, nj, turn_k, if target == 2 { 0 } else { 2 }, 0, grid, memo))
        }
        memo[ni as usize][nj as usize][k as usize][can_turn as usize] = res;
        res
    }
}
fn main() {

}