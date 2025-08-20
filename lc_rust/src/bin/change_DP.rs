struct Solution;

impl Solution {
    pub fn change(amount: i32, coins: Vec<i32>) -> i32 {
        // 将 amount 转换为 usize，因为 Vec 索引需要 usize
        let amount = amount as usize;
        // 初始化 dp 数组，长度为 amount + 1，全为 0
        let mut f = vec![0i32; amount + 1];
        f[0] = 1; // 金额 0 有一种方案（不选硬币）
        
        // 遍历每种硬币
        for &coin in coins.iter() {
            // 将 coin 转换为 usize
            let coin = coin as usize;
            // 从 coin 开始到 amount，确保不会越界
            for c in coin..=amount {
                f[c] += f[c - coin];
            }
        }

        f[amount]
    }
}

fn main() {
    // 测试代码
    let amount = 5;
    let coins = vec![1, 2, 5];
    println!("{}", Solution::change(amount, coins)); // 输出 4
}