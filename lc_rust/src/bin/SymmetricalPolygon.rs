use std::collections::HashMap;
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

macro_rules! print_vec {
    ($vec:expr) => {
        if $vec.is_empty() {
            println!();
        } else {
            let mut first = true;
            for x in &$vec {
                if first {
                    print!("{}", x);
                    first = false;
                } else {
                    print!(" {}", x);
                }
            }
            println!();
        }
    };
}

macro_rules! print_slice {
    ($slice:expr) => {
        if $slice.is_empty() {
            println!();
        } else {
            let mut first = true;
            for x in $slice {
                if first {
                    print!("{}", x);
                    first = false;
                } else {
                    print!(" {}", x);
                }
            }
            println!();
        }
    };
}

macro_rules! fast_print_vec {
    ($vec:expr) => {
        use std::io::{Write, BufWriter};
        let stdout = std::io::stdout();
        let mut writer = BufWriter::new(stdout.lock());
        if !$vec.is_empty() {
            for (i, x) in $vec.iter().enumerate() {
                if i > 0 {
                    write!(writer, " {}", x).unwrap();
                } else {
                    write!(writer, "{}", x).unwrap();
                }
            }
        }
        writeln!(writer).unwrap();
    };
}

macro_rules! fast_print_slice {
    ($slice:expr) => {
        use std::io::{Write, BufWriter};
        let stdout = std::io::stdout();
        let mut writer = BufWriter::new(stdout.lock());
        if !$slice.is_empty() {
            for (i, x) in $slice.iter().enumerate() {
                if i > 0 {
                    write!(writer, " {}", x).unwrap();
                } else {
                    write!(writer, "{}", x).unwrap();
                }
            }
        }
        writeln!(writer).unwrap();
    };
}

fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();


    let t = read!(it => usize);
    for _ in 0..t {
        let n = read!(it => usize);
        let a = read!(it => vec_i64, n);
        let mut cnt:HashMap<i64, usize> = HashMap::new();
        for i in 0..n {
            *cnt.entry(a[i]).or_insert(0) += 1;
        }
        let mut odd:Vec<i64> = Vec::new();
        let mut even:Vec<i64> = Vec::new();
        let mut base = 0i64;
        for (x, c) in cnt {
            base += x * (c as i64 / 2);
            if c & 1 == 1 {
                odd.push(x)
            }else if (c >= 2) {
                even.push(x)
            }
        }
        if base == 0 {println!("{}", 0); continue}
        let mut ans:i64 = 0;
        for &x in &odd {
            if 2 * base > x {ans = ans.max(2 * base + x)}
        }
        odd.sort_unstable();
        for i in 1..odd.len() {
            if odd[i - 1] + 2 * base > odd[i] {
                ans = ans.max(odd[i - 1] + 2 * base + odd[i])
            }
        }
        for x in even {
            if base - x > 0 {
                ans = ans.max(base * 2)
            }
        }
        println!("{}", ans)
    }
}