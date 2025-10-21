use std::collections::HashMap;
use std::hash::Hash;

fn solve(a: &Vec<i32>, k: i32, op: i32) -> i32 {
    let mut ans:i32 = 0i32;
    let mut sum_d = 0i32;

    let mut cnt: HashMap<i32, i32> = HashMap::new();
    let mut diff :HashMap<i32, i32> = HashMap::new();

    for &x in a {
        *cnt.entry(x).or_insert(0) += 1;
        *diff.entry(x - k).or_insert(0) += 1;
        *diff.entry(x + k + 1).or_insert(0) -= 1;
    }
    let mut items: Vec<_> = diff.into_iter().collect();
    items.sort_by_key(|(x, _)| *x);
    for (x, d) in items {
        sum_d += d;
        ans = ans.max(sum_d.min(cnt[&x] + op as i32))
    }

    ans
}

fn main() {

}