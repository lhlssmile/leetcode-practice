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

    let (n, e) = multi_read!(it => usize, usize);
    let mut g:Vec<Vec<usize>> = Vec::new();
    let mut ans:Vec<i32> = vec![0; n];
    let mut sz_ = vec![0; n];
    for i in 0..e {
        let (u, v) = multi_read!(it => usize, usize);
        g[u].push(v);
        g[v].push(u);
    }
    fn dfs_d(u: usize, p: usize, d: i32) {
        ans[0] += d;
        sz_[u] = 1;
        for &v in &g[u] {
            if v != p {
                dfs_d(v, u, d + 1);
                sz_[u] += sz_[v]
            }

        }
    }
    dfs_d(0, -1, 0);

    fn dfs_c (u:usize, p: usize, curr_ans:i32) {
        ans[u] = curr_ans;
        for &v in &g[u] {
            if v != p {
                let new_ans = ans[u] + n as i32 - 2 * sz_[v];
                dfs_c(v, u, new_ans);
            }

        }
    }
    dfs_c(0, -1, ans[0]);
    fast_print_slice!(ans)
}