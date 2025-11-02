use std::cmp::min;
use std::io::{self, Read};
use std::ptr::read;
use std::thread::current;

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
fn abs(x: i64) -> i64{
    if x < 0 {return -x}
    x
}
fn solve(n: usize, a: &[i64]) -> i64 {
    const INF:i64 = 1_000_000_000_000;
    let mut ans = INF;

    fn cost2 (x: i64, y: i64) -> i64 {
        abs(x- y)
    }
    fn cost3(x: i64, y: i64, z: i64) -> i64 {
        let mut a: [i64; 3] = [x, y, z];
        a.sort_unstable();
        abs(a[1] - a[0]) + abs(a[2] - a[1])
    }
    fn dp(re: &Vec<i64>) -> i64 {
        let m = re.len();
        let mut f = vec![INF; m + 1];
        f[0] = 0;
        for i in 2..m+1{
            f[i] = std::cmp::min(f[i], f[i - 2] + cost2(re[i - 2], re[i - 1]));
            if i >= 3 {
                f[i] = std::cmp::min(f[i], f[i - 3] + cost3(re[i - 2], re[i - 1], re[i - 3]));
            }
        }
        // n = 4 b1 = b(1 + 4 - 2) = b3
        // b2 = b4/b
        f[m]
    }
    const R:usize = 3;
    for cut in 0..R {
        if cut >= n {continue}
        let mut recorded: Vec<i64> = vec![0; n];
        for i in 0..n {
            recorded[i] = a[(i + cut) % n];
        }
        let res = dp(recorded.as_ref());
        ans = min(ans, res);
    }
    ans
}
fn main() {
    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    // 示例3：多测试用例
    let t = read!(it => usize);
    for _ in 0..t {
        let n = read!(it => usize);
        let a = read!(it => vec_i64, n);
        println!("{}", solve(n, &a))
    }
}