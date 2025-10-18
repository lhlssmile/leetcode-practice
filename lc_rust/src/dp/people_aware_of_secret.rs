pub struct Solution;

impl Solution {
    pub fn people_aware_of_secret(n: i32, delay: i32, forget: i32) -> i32 {
        const MOD: i32 = 1_000_000_007;
        let n = n as usize;
        let delay = delay as usize;
        let forget = forget as usize;
        
        // f[i]表示第i天新知道秘密的人数
        let mut f = vec![0; n + 1];
        f[1] = 1; // 第1天有1个人知道秘密
        
        // 计算每天新知道秘密的人数
        for i in 2..=n {
            // j表示在第j天知道秘密的人
            // 这些人在第i天仍然记得秘密(i-j < forget)且已经可以分享(i-j >= delay)
            for j in (1.max(i.saturating_sub(forget) + 1))..=(i.saturating_sub(delay)) {
                f[i] = (f[i] + f[j]) % MOD;
            }
        }
        
        // 计算第n天仍然记得秘密的总人数
        let mut ans = 0;
        for i in (1.max(n.saturating_sub(forget) + 1))..=n {
            ans = (ans + f[i]) % MOD;
        }
        
        ans
    }
    
    // 优化版本：使用前缀和减少内层循环
    pub fn people_aware_of_secret_optimized(n: i32, delay: i32, forget: i32) -> i32 {
        const MOD: i32 = 1_000_000_007;
        let n = n as usize;
        let delay = delay as usize;
        let forget = forget as usize;
        
        // f[i]表示第i天新知道秘密的人数
        let mut f = vec![0; n + 1];
        // 前缀和数组，prefix_sum[i]表示f[1]到f[i]的和
        let mut prefix_sum = vec![0; n + 1];
        
        f[1] = 1;
        prefix_sum[1] = 1;
        
        for i in 2..=n {
            // 计算能够分享秘密的人的范围
            let share_start = (i.saturating_sub(forget) + 1).max(1);
            let share_end = i.saturating_sub(delay);
            
            if share_start <= share_end {
                // 使用前缀和计算区间和
                let sum = (prefix_sum[share_end] - prefix_sum[share_start - 1] + MOD) % MOD;
                f[i] = sum;
            }
            
            // 更新前缀和
            prefix_sum[i] = (prefix_sum[i - 1] + f[i]) % MOD;
        }
        
        // 计算第n天仍然记得秘密的总人数
        let forget_start = (n.saturating_sub(forget) + 1).max(1);
        
        // 使用前缀和计算区间和
        (prefix_sum[n] - prefix_sum[forget_start - 1] + MOD) % MOD
    }
}

// 测试函数
pub fn test_people_aware_of_secret() {
    // 测试用例1: n=6, delay=2, forget=4
    println!("Test Case 1: {}", Solution::people_aware_of_secret(6, 2, 4)); // 预期输出: 5
    println!("Test Case 1 (Optimized): {}", Solution::people_aware_of_secret_optimized(6, 2, 4));
    
    // 测试用例2: n=4, delay=1, forget=3
    println!("Test Case 2: {}", Solution::people_aware_of_secret(4, 1, 3)); // 预期输出: 6
    println!("Test Case 2 (Optimized): {}", Solution::people_aware_of_secret_optimized(4, 1, 3));
    
    // 测试用例3: n=10, delay=2, forget=5
    println!("Test Case 3: {}", Solution::people_aware_of_secret(10, 2, 5));
    println!("Test Case 3 (Optimized): {}", Solution::people_aware_of_secret_optimized(10, 2, 5));
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_basic_cases() {
        assert_eq!(Solution::people_aware_of_secret(6, 2, 4), 5);
        assert_eq!(Solution::people_aware_of_secret(4, 1, 3), 6);
        
        assert_eq!(Solution::people_aware_of_secret_optimized(6, 2, 4), 5);
        assert_eq!(Solution::people_aware_of_secret_optimized(4, 1, 3), 6);
    }
}

/*
算法思路：

1. 定义状态：f[i]表示第i天新知道秘密的人数

2. 初始条件：f[1] = 1，表示第1天有1个人知道秘密

3. 状态转移：
   - 对于第i天，新知道秘密的人数等于所有能够分享秘密的人分享的总和
   - 一个人在知道秘密的第j天，需要经过delay天才能分享，并且在forget天后会忘记
   - 因此，对于第i天，我们需要考虑在第j天知道秘密的人，其中j满足：
     * j >= i - forget + 1（这些人在第i天仍然记得秘密）
     * j <= i - delay（这些人在第i天已经可以分享秘密）

4. 最终答案：
   - 第n天仍然记得秘密的总人数，即在第[n-forget+1, n]天内知道秘密的人的总和

5. 优化：
   - 使用前缀和优化内层循环，将时间复杂度从O(n * forget)降低到O(n)

时间复杂度：
- 基础版本：O(n * forget)，其中n是总天数
- 优化版本：O(n)

空间复杂度：O(n)
*/