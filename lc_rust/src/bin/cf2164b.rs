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
        use std::io::{BufWriter, Write};
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
        use std::io::{BufWriter, Write};
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

#[derive(Debug, Clone, Copy)]
struct Pair {
    fi: i64,
    se: i64,
}
fn find_odd_pair(odd: &[i64]) -> Option<Pair> {
    let m = odd.len();
    if m < 2 {
        return None;
    }

    for i in 0..m - 1 {
        let (x, y) = (odd[i], odd[i + 1]);
        if y < 2 * x {
            return Some(Pair { fi: x, se: y });
        }
    }

    for i in 0..m {
        for j in i + 1..m {
            let (x, y) = (odd[i], odd[j]);
            if (y % x) % 2 == 0 {
                return Some(Pair { fi: x, se: y });
            }
        }
    }

    None
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
        let (odd, even): (Vec<i64>, Vec<i64>) = a.iter().partition(|&&x| x % 2 != 0);
        if even.len() >= 2 {
            println!("{} {}", even[0], even[1]);
            continue;
        }

        if let Some(p) = find_odd_pair(&odd) {
            println!("{} {}", p.fi, p.se);
            continue;
        }
        if even.is_empty() {
            println!("-1");
            continue;
        }
        let e = even[0];
        let small_odd: Vec<i64> = odd.into_iter().filter(|&x| x < e).collect();
        let mut found = false;
        for x in small_odd {
            if (e % x) % 2 == 0 {
                println!("{} {}", x, e);
                found = true;
                break;
            }
        }
        if !found {
            println!("-1");
        }
    }
}
