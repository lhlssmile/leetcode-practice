use std::ops::Add;

struct Solution;

impl Solution {
    pub fn judge_point24(cards: Vec<i32>) -> bool {
        const EPS: f64 = 1e-9;

        fn dfs(cards: Vec<f64>) -> bool {
            let n = cards.len();
            if n == 1 {
                return (cards[0] - 24.0).abs() < EPS;
            }
            for (i, x) in cards.iter().enumerate() {
                for j in i + 1..n {
                    let y = cards[j];

                    let mut candidates = vec![x + y, x - y, y - x, x * y];
                    if y.abs() > EPS {
                        candidates.push(x / y);
                    }
                    if x.abs() > EPS {
                        candidates.push(y / x);
                    }
                    for res in candidates {
                        let mut new_cards = cards.clone();
                        new_cards.remove(j);
                        new_cards[i] = res;
                        if dfs(new_cards) {
                            return true;
                        }
                    }
                }
            }
            false
        }

        let a = cards.into_iter().map(|x| x as f64)
            .collect::<Vec<f64>>();
        dfs(a)
    }
}
fn main() {
    let test_case = vec![4, 1, 8, 7];
    let ans = Solution::judge_point24(test_case);
}