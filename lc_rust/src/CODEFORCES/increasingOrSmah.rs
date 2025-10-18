use std::io::{self, BufRead};
use std::collections::HashSet;

const N: usize = 101;

fn solve(a: &Vec<i32>) -> i32 {
    let mut st: HashSet<i32> = HashSet::new();
    for &x in a {
        st.insert(x);
    }
    let k = st.len() as i32;
    2 * k - 1
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    
    let t_line = lines.next().unwrap().unwrap();
    let t: usize = t_line.trim().parse().unwrap();
    
    for _ in 0..t {
        let n_line = lines.next().unwrap().unwrap();
        let n: usize = n_line.trim().parse().unwrap();
        
        let a_line = lines.next().unwrap().unwrap();
        let a: Vec<i32> = a_line
            .trim()
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        
        println!("{}", solve(&a));
    }
}