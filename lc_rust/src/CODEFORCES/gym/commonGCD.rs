use std::io::{self, Read};

fn gcd(mut a: usize, mut b: usize) -> usize {
    while b != 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a
}

fn main() {
    // Fast input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();

    let n: usize = iter.next().unwrap().parse().unwrap();
    let mut nums: Vec<usize> = (0..n)
        .map(|_| iter.next().unwrap().parse().unwrap())
        .collect();

    // 1️⃣ 计算全局 gcd
    let mut g = nums[0];
    for &x in &nums[1..] {
        g = gcd(g, x);
    }

    // 2️⃣ 去除公共因子
    for x in nums.iter_mut() {
        *x /= g;
    }

    // 3️⃣ 构建最小质因数表
    let m = *nums.iter().max().unwrap();
    let mut spf: Vec<usize> = (0..=m).collect();
    for i in 2..=m {
        if spf[i] == i {
            for j in (i..=m).step_by(i) {
                spf[j] = i;
            }
        }
    }

    // 4️⃣ 检查冲突
    let mut vis = vec![false; m + 1];
    for mut x in nums {
        while x > 1 {
            let p = spf[x];
            if vis[p] {
                println!("NO");
                return;
            }
            vis[p] = true;
            while x % p == 0 {
                x /= p;
            }
        }
    }

    println!("YES");
}
