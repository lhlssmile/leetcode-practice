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

    // 示例1：读一行n a b，像Python LII()
    let (n, a, b) = multi_read!(it => usize, usize, usize);
    println!("n={}, a={}, b={}", n, a, b);

    // 示例2：读n个i64成Vec，像LII()但动态n
    let vec_a: Vec<i64> = read!(it => vec_i64, n);
    print_vec!(vec_a); // 普通输出
    // fast_print_vec!(vec_a); // 高性能缓冲输出

    // 示例3：多测试用例
    let t = read!(it => usize);
    for _ in 0..t {
        let n2 = read!(it => usize);
        let arr = read!(it => vec_i64, n2); // 读n2个i64
        fast_print_vec!(arr); // 高性能缓冲输出
    }
}