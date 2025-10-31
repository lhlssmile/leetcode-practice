
use std::io::{self, Read};

macro_rules! read {
    // 单个值：read!(it => usize) 或 read!(it => i64)
    ($it:ident => $t:ty) => {
        $it.next().unwrap().parse::<$t>().unwrap()
    };
    ($it:ident => str) => {
        $it.next().unwrap().to_string()
    };
    // Vec：read!(it => vec_i64(n)) 读n个i64成Vec<i64>
    ($it:ident => vec_usize($n:expr)) => {
        (0..$n).map(|_| read!($it => usize)).collect::<Vec<_>>()
    };
    ($it:ident => vec_i64($n:expr)) => {
        (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
    };
    ($it:ident => vec_str($n:expr)) => {
        (0..$n).map(|_| read!($it => str)).collect::<Vec<_>>()
    };
    // 简化版本，直接接受数量参数
    ($it:ident => vec_usize, $n:expr) => {
        (0..$n).map(|_| read!($it => usize)).collect::<Vec<_>>()
    };
    ($it:ident => vec_i64, $n:expr) => {
        (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
    };
    ($it:ident => vec_str, $n:expr) => {
        (0..$n).map(|_| read!($it => str)).collect::<Vec<_>>()
    };
}

macro_rules! multi_read {
    // 多值一行：multi_read!(it => usize, usize, usize) → (n, a, b)
    ($it:ident => $($t:ty),+ $(,)?) => {
        ($(read!($it => $t)),+)
    };
}

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t = read!(it => usize);
    for _ in 0..t {
        let (n, x) = multi_read!(it => usize, i64);
        let mut prices = read!(it => vec_i64, n);

        // earn bonus_points maximum
        let sum_ :i64 = prices.iter().sum();
        let levels = (sum_ / x) as usize;
        prices.sort_by(|a, b| b.cmp(a));
        let bonus_points:i64 = if levels > 0 {
            prices[..std::cmp::min(levels, prices.len())].iter().sum()
        }else {
            0
        };
        let mut small_items = if levels < n {
            prices[levels..].to_vec()
        }else {
            vec![]
        };
        let mut large_items = if levels > 0 {
            prices[..std::cmp::min(levels, prices.len())].to_vec()
        }else {
            vec![]
        };
        let mut cur_s: i64 = 0;
        let mut res: Vec<i64> = Vec::new();
        let mut large_idx:usize = 0;
        for l in 1..=levels {
            let target = (l as i64) * (x as i64);
            while cur_s < target - large_items[large_idx] && !small_items.is_empty() {
                if let Some(item) = small_items.pop() {
                    res.push(item);
                    cur_s += item
                }
                if large_idx < large_items.len() {
                    res.push(large_items[large_idx]);
                    cur_s += large_items[large_idx];
                    large_idx += 1;
                }
            }
        }
        res.extend(small_items);
        println!("{}", bonus_points);

        if !res.is_empty() {
            let mut out = String::new();
            for (i, &p) in res.iter().enumerate() {
                if i > 0 {
                    out.push(' ');
                }
                out.push_str(&p.to_string());
            }
            println!("{}", out);
        } else {
            println!();
        }

    }
}

