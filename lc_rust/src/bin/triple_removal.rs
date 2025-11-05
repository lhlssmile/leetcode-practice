use std::io::{self, Read};

macro_rules! read {
    ($it:ident => $t:ty) => {
        $it.next().unwrap().parse::<$t>().unwrap()
    };
    ($it:ident => vec_i64, $n:expr) => {
        (0..$n).map(|_| read!($it => i64)).collect::<Vec<_>>()
    };
}

macro_rules! multi_read {
    ($it:ident => $($t:ty),+ $(,)?) => {
        ($(read!($it => $t)),+)
    };
}

fn main() {
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut it = input.split_whitespace();

    let t = read!(it => usize);
    for _ in 0..t {
        let (n, q) = multi_read!(it => usize, usize);
        let a = read!(it => vec_i64, n);

        let mut sum_0 = vec![0i64; n + 1];
        let mut sum_1 = vec![0i64; n + 1];
        // diff_sum[0] = 0 默认即可
        let mut diff_sum = vec![0i64; n + 1];

        for i in 0..n {
            sum_0[i + 1] = sum_0[i] + if a[i] == 0 { 1 } else { 0 };
            sum_1[i + 1] = sum_1[i] + if a[i] == 1 { 1 } else { 0 };

            if i > 0 {
                diff_sum[i + 1] = diff_sum[i] + if a[i] != a[i - 1] { 1 } else { 0 };
            }
        }

        for _ in 0..q {
            let (l, r) = multi_read!(it => usize, usize);

            let z = sum_0[r] - sum_0[l - 1];
            let o = sum_1[r] - sum_1[l - 1];

            if z % 3 != 0 || o % 3 != 0 {
                println!("-1");
                continue;
            }

            let mut ans = z / 3 + o / 3;
            let num_pairs = r - l;
            let switches = diff_sum[r] - diff_sum[l];

            if num_pairs as i64 == switches {
                ans += 1;
            }

            println!("{}", ans);
        }
    }
}
