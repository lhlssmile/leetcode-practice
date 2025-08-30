use std::cmp::{max, min};

/// 计算满足条件的最大差值
/// 
/// # 参数
/// * `s` - 输入字符串，只包含数字0-4
/// * `k` - 窗口大小下限
/// 
/// # 返回值
/// 满足条件的最大差值
fn max_difference(s: &str, k: i32) -> i32 {
    let inf = i32::MAX / 2;
    let mut ans = -inf;
    
    for x in 0..5 {
        for y in 0..5 {
            if y == x {
                continue;
            }
            
            let mut cur_s = [0; 5];
            let mut pre_s = [0; 5];
            let mut min_s = [[inf, inf], [inf, inf]];
            let mut left = 0;
            
            for (i, ch) in s.chars().enumerate() {
                let digit = ch.to_digit(10).unwrap() as usize;
                cur_s[digit] += 1;
                let r = i + 1;
                
                while r - left >= k as usize && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y] {
                    let parity_x = (pre_s[x] & 1) as usize;
                    let parity_y = (pre_s[y] & 1) as usize;
                    min_s[parity_x][parity_y] = min(min_s[parity_x][parity_y], pre_s[x] - pre_s[y]);
                    
                    let left_digit = s.chars().nth(left).unwrap().to_digit(10).unwrap() as usize;
                    pre_s[left_digit] += 1;
                    left += 1;
                }
                
                let current_parity_x = ((cur_s[x] & 1) ^ 1) as usize;
                let current_parity_y = (cur_s[y] & 1) as usize;
                ans = max(ans, cur_s[x] - cur_s[y] - min_s[current_parity_x][current_parity_y]);
            }
        }
    }
    
    ans
}

/// 优化版本：使用更具描述性的变量名和注释
fn max_difference_optimized(s: &str, k: i32) -> i32 {
    let inf = i32::MAX / 2;
    let mut max_diff = -inf;
    
    // 将字符串转换为数字向量，避免重复转换
    let digits: Vec<usize> = s.chars()
        .map(|ch| ch.to_digit(10).unwrap() as usize)
        .collect();
    
    // 枚举所有可能的字符对(x,y)，其中x!=y
    for x in 0..5 {
        for y in 0..5 {
            if y == x {
                continue;
            }
            
            // 当前窗口中各字符的计数
            let mut current_count = [0; 5];
            // 前缀窗口中各字符的计数
            let mut prefix_count = [0; 5];
            // 存储最小差值，按奇偶性分类
            let mut min_difference = [[inf, inf], [inf, inf]];
            
            let mut left = 0;
            for (i, &digit) in digits.iter().enumerate() {
                // 更新当前窗口计数
                current_count[digit] += 1;
                let right = i + 1;
                
                // 当窗口大小>=k且满足条件时，更新最小差值
                while right - left >= k as usize && 
                      current_count[x] > prefix_count[x] && 
                      current_count[y] > prefix_count[y] {
                    // 根据x和y的奇偶性选择对应的最小差值
                    let parity_x = (prefix_count[x] & 1) as usize; // x的奇偶性
                    let parity_y = (prefix_count[y] & 1) as usize; // y的奇偶性
                    min_difference[parity_x][parity_y] = min(
                        min_difference[parity_x][parity_y],
                        prefix_count[x] - prefix_count[y]
                    );
                    
                    // 移动左指针，更新前缀计数
                    prefix_count[digits[left]] += 1;
                    left += 1;
                }
                
                // 计算当前最大差值
                // 注意这里使用了异或操作来获取当前x计数的奇偶性的相反值
                let current_parity_x = ((current_count[x] & 1) ^ 1) as usize;
                let current_parity_y = (current_count[y] & 1) as usize;
                max_diff = max(
                    max_diff,
                    current_count[x] - current_count[y] - min_difference[current_parity_x][current_parity_y]
                );
            }
        }
    }
    
    max_diff
}

/// Rust风格版本：利用Rust的特性
fn max_difference_rust(s: &str, k: i32) -> i32 {
    const INF: i32 = i32::MAX / 2;
    
    // 将字符串转换为数字向量
    let digits: Vec<usize> = s.chars()
        .map(|ch| ch.to_digit(10).unwrap() as usize)
        .collect();
    
    // 生成所有可能的(x,y)对，其中x!=y
    let pairs: Vec<(usize, usize)> = (0..5)
        .flat_map(|x| (0..5).map(move |y| (x, y)))
        .filter(|&(x, y)| x != y)
        .collect();
    
    // 计算每对(x,y)的最大差值
    pairs.iter()
        .map(|&(x, y)| {
            let mut current_count = [0; 5];
            let mut prefix_count = [0; 5];
            let mut min_difference = [[INF, INF], [INF, INF]];
            let mut left = 0;
            let mut max_pair_diff = -INF;
            
            for (i, &digit) in digits.iter().enumerate() {
                current_count[digit] += 1;
                let right = i + 1;
                
                while right - left >= k as usize && 
                      current_count[x] > prefix_count[x] && 
                      current_count[y] > prefix_count[y] {
                    let parity_x = (prefix_count[x] & 1) as usize;
                    let parity_y = (prefix_count[y] & 1) as usize;
                    min_difference[parity_x][parity_y] = min(
                        min_difference[parity_x][parity_y],
                        prefix_count[x] - prefix_count[y]
                    );
                    prefix_count[digits[left]] += 1;
                    left += 1;
                }
                
                let current_parity_x = ((current_count[x] & 1) ^ 1) as usize;
                let current_parity_y = (current_count[y] & 1) as usize;
                max_pair_diff = max(
                    max_pair_diff,
                    current_count[x] - current_count[y] - min_difference[current_parity_x][current_parity_y]
                );
            }
            
            max_pair_diff
        })
        .max()
        .unwrap_or(-INF)
}

/// 使用迭代器和函数式编程特性的高级Rust实现
fn max_difference_functional(s: &str, k: i32) -> i32 {
    const INF: i32 = i32::MAX / 2;
    
    // 将字符串转换为数字向量
    let digits: Vec<usize> = s.chars()
        .map(|ch| ch.to_digit(10).unwrap() as usize)
        .collect();
    
    // 生成所有可能的(x,y)对，其中x!=y
    (0..5).flat_map(|x| (0..5).filter(move |&y| x != y).map(move |y| (x, y)))
        .map(|(x, y)| {
            // 为每对(x,y)计算最大差值
            let mut state = (
                [0; 5],           // current_count
                [0; 5],           // prefix_count
                [[INF, INF], [INF, INF]], // min_difference
                0,                // left
                -INF,             // max_pair_diff
            );
            
            // 处理每个位置
            for (i, &digit) in digits.iter().enumerate() {
                let (ref mut current_count, ref mut prefix_count, ref mut min_difference, ref mut left, ref mut max_pair_diff) = state;
                
                // 更新当前窗口计数
                current_count[digit] += 1;
                let right = i + 1;
                
                // 当窗口大小>=k且满足条件时，更新最小差值
                while right - *left >= k as usize && 
                      current_count[x] > prefix_count[x] && 
                      current_count[y] > prefix_count[y] {
                    let parity_x = (prefix_count[x] & 1) as usize;
                    let parity_y = (prefix_count[y] & 1) as usize;
                    min_difference[parity_x][parity_y] = min(
                        min_difference[parity_x][parity_y],
                        prefix_count[x] - prefix_count[y]
                    );
                    prefix_count[digits[*left]] += 1;
                    *left += 1;
                }
                
                // 计算当前最大差值
                let current_parity_x = ((current_count[x] & 1) ^ 1) as usize;
                let current_parity_y = (current_count[y] & 1) as usize;
                *max_pair_diff = max(
                    *max_pair_diff,
                    current_count[x] - current_count[y] - min_difference[current_parity_x][current_parity_y]
                );
            }
            
            state.4 // 返回max_pair_diff
        })
        .max()
        .unwrap_or(-INF)
}

fn main() {
    // 测试用例
    let test_cases = [
        ("01234", 2),
        ("00110", 2),
    ];
    
    for (i, &(s, k)) in test_cases.iter().enumerate() {
        let result1 = max_difference(s, k);
        let result2 = max_difference_optimized(s, k);
        let result3 = max_difference_rust(s, k);
        let result4 = max_difference_functional(s, k);
        
        println!("测试用例{}: s={}, k={}", i + 1, s, k);
        println!("  基本版本结果: {}", result1);
        println!("  优化版本结果: {}", result2);
        println!("  Rust风格版本结果: {}", result3);
        println!("  函数式版本结果: {}", result4);
        println!();
    }
}