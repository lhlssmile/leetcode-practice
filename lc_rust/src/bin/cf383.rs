use std::collections::VecDeque;
use std::io::{self, Read};
use std::ptr::read;

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
#[derive(Clone, Copy)]
struct Pair {
    node: usize,
    parent: usize
}
struct FenwickTree {
    n: usize,
    t: Vec<i32>,

}
impl FenwickTree {
    fn new(n: usize) -> Self  {
        Self {n, t: vec![0; n + 2]}
    }
    fn add(&mut self, mut i: usize, w: i32) {
        while i <= self.n {
            self.t[i] += w;
            let low_bit = i & i.wrapping_neg();  // -i = wrapping_neg(i)
            i = (i as isize + low_bit as isize) as usize;
        }
    }
    fn sum(&self, mut i :usize) {
        let mut r = 0i64;
        while i > 0 {
            r += self.t[i] as i64;
            let low_bit = i & i.wrapping_neg();
            i = (i as isize - low_bit as isize) as usize;
        }
        r
    }
}
fn main() {

    // 读取所有输入到字符串（全split_whitespace，一次过）
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let (n, m) = multi_read!(it => usize, usize);
    let a = read!(it => vec_i64, n);
    let mut g: Vec<Vec<i32>> = Vec::new();
    for i in 0..n - 1 {
        let (u, v) = multi_read!(it => usize, usize);
        g[u].push(v); g[v].push(u);
    }
    let mut in_ = vec![0usize; n + 1];
    let mut out_ = vec![0usize; n + 1];
    let mut dep_ = vec![0usize; n + 1];
    let mut state = vec![0i32; n + 1];  // 0:未访, 1:进入
    let mut st: VecDeque<Pair> = VecDeque::new();
    st.push_back(Pair { node: 1, parent: 0 });
    let mut timer = 1usize;
    while let Some(pair) = st.pop_back() {
        let (u, p) = (pair.node, pair.parent);
        if state[u] == 0 {
            state[u] = 1;
            dep_[u] = if p != 0 {dep_[p] + 1} else {0};
            in_[u] = timer; timer += 1;
            st.push_back(pair);
            for &v in g[u].iter()
                .rev() {
                if v != p {st.push_back(Pair{node:v, parent:u})}
            }
        }
    }
    let mut ft = FenwickTree::new(n);
    for _ in 0..m {
        let op = read!(it => i32);
        if op == 1 {
            let (u, w) = multi_read!(it => usize, i64);
            let s = if dep_[u] % 2 == 0 {1i64} else {0i64};
            let delta = w * s;
            ft.add(in_[u], delta as i32);
            if out_[u] <= n {ft.add(out_[u], (-delta) as i32)}

        }else {
            let u = read!(it => usize);
            let s = if dep_[u] % 2 == 0 { 1i64 } else { -1i64 };
            let path = ft.sum(in_[u]);
            println!("{}", a[u] + s * path);
        }
    }
}