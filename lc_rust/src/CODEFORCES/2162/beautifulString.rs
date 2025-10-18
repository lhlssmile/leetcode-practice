use std::io::{self, Read};

fn is_palindrome(s: &Vec<u8>) -> bool {
    let mut l = 0;
    let mut r = s.len().wrapping_sub(1);
    while l < r {
        if s[l] != s[r] {
            return false;
        }
        l += 1;
        r -= 1;
    }
    true
}

fn is_non_decreasing(s: &Vec<u8>) -> bool {
    for i in 1..s.len() {
        if s[i] < s[i - 1] {
            return false;
        }
    }
    true
}

fn solve(s: &Vec<u8>) -> (i32, Vec<usize>) {
    let n = s.len();
    for mask in 0..(1 << n) {
        let mut p = Vec::new();
        let mut x = Vec::new();
        let mut idx = Vec::new();
        for i in 0..n {
            if (mask >> i) & 1 == 1 {
                p.push(s[i]);
                idx.push(i + 1);
            } else {
                x.push(s[i]);
            }
        }
        if is_non_decreasing(&p) && is_palindrome(&x) {
            return (idx.len() as i32, idx);
        }
    }
    (-1, Vec::new())
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();
    let t: usize = it.next().unwrap().parse().unwrap();

    for _ in 0..t {
        let _n: usize = it.next().unwrap().parse().unwrap();
        let s = it.next().unwrap().as_bytes().to_vec();
        let (k, idx) = solve(&s);
        if k == -1 {
            println!("-1");
        } else {
            println!("{}", k);
            if k > 0 {
                for (i, v) in idx.iter().enumerate() {
                    if i > 0 {
                        print!(" ");
                    }
                    print!("{}", v);
                }
                println!();
            }
        }
    }
}
