use std::collections::VecDeque;

struct Solution;
impl Solution {
    pub fn minimum_obstacles(grid: Vec<Vec<i32>>) -> i32 {
        let (m, n) = (grid.len(), grid[0].len());
        let mut dist = vec![vec![i32::MAX; n]; m];
        let dirs = [(-1, 0), (1, 0), (0, 1), (0, -1)];
        let mut dq = VecDeque::new();

        dist[0][0] = 0;
        dq.push_front((0, 0));

        while let Some((x, y)) = dq.pop_front() {
            let d = dist[x][y];

            for &(dx, dy) in &dirs {
                let nx = x as i32 + dx;
                let ny = y as i32 + dy;
                if nx < 0 || ny < 0 || nx >= m as i32 || ny >= n as i32 {
                    continue;
                }
                let (nx, ny) = (nx as usize, ny as usize);
                let nd = d + grid[nx][ny];
                if nd < dist[nx][ny] {
                    dist[nx][ny] = nd;
                    if grid[nx][ny] == 1 {
                        dq.push_back((nx, ny));   // cost = 1
                    } else {
                        dq.push_front((nx, ny));  // cost = 0
                    }
                }
            }
        }

        dist[m - 1][n - 1]
    }
}

fn main() {
    let grid = vec![
        vec![0, 1, 1],
        vec![1, 1, 0],
        vec![1, 1, 0],
    ];
    println!("{}", Solution::minimum_obstacles(grid)); // 输出 2
}
