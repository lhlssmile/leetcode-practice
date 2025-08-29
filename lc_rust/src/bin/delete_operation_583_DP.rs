// 力扣第583题：两个字符串的删除操作
// 题目描述：给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

fn main() {
    // 运行测试用例
    test_delete_operation();
}

/// 方法一：基本实现 - 基于最长公共子序列(LCS)的解法
/// 
/// # 算法思路
/// 1. 计算两个字符串的最长公共子序列长度
/// 2. 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
/// 
/// # 参数
/// * `word1` - 第一个字符串
/// * `word2` - 第二个字符串
/// 
/// # 返回值
/// * 使得两个字符串相同所需的最小删除次数
fn min_distance_lcs(word1: &str, word2: &str) -> i32 {
    // 获取字符串长度
    let m = word1.len();
    let n = word2.len();
    
    // 创建LCS矩阵
    // 注意：Rust中创建二维数组需要使用vec!宏
    let mut lcs = vec![vec![0; n + 1]; m + 1];
    
    // 将字符串转换为字符数组，便于按索引访问
    let word1_chars: Vec<char> = word1.chars().collect();
    let word2_chars: Vec<char> = word2.chars().collect();
    
    // 计算LCS
    for i in 1..=m {
        for j in 1..=n {
            if word1_chars[i - 1] == word2_chars[j - 1] {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = lcs[i - 1][j].max(lcs[i][j - 1]);
            }
        }
    }
    
    // 最小删除次数 = 字符串总长度 - 2*最长公共子序列长度
    (m + n) as i32 - 2 * lcs[m][n]
}

/// 方法二：基本实现 - 直接使用动态规划
/// 
/// # 算法思路
/// 1. 创建DP矩阵，dp[i][j]表示使word1的前i个字符和word2的前j个字符相同所需的最小删除次数
/// 2. 如果字符相同，无需删除；否则，选择删除一个字符的最小值
/// 
/// # 参数
/// * `word1` - 第一个字符串
/// * `word2` - 第二个字符串
/// 
/// # 返回值
/// * 使得两个字符串相同所需的最小删除次数
fn min_distance(word1: &str, word2: &str) -> i32 {
    // 获取字符串长度
    let m = word1.len();
    let n = word2.len();
    
    // 创建DP矩阵
    let mut dp = vec![vec![0; n + 1]; m + 1];
    
    // 初始化
    // 删除 word1 的前 i 个字符
    for i in 0..=m {
        dp[i][0] = i as i32;
    }
    // 删除 word2 的前 j 个字符
    for j in 0..=n {
        dp[0][j] = j as i32;
    }
    
    // 将字符串转换为字符数组
    let word1_chars: Vec<char> = word1.chars().collect();
    let word2_chars: Vec<char> = word2.chars().collect();
    
    // 动态规划
    for i in 1..=m {
        for j in 1..=n {
            if word1_chars[i - 1] == word2_chars[j - 1] {
                dp[i][j] = dp[i - 1][j - 1]; // 字符相同，无需删除
            } else {
                dp[i][j] = dp[i - 1][j].min(dp[i][j - 1]) + 1; // 删除一个字符
            }
        }
    }
    
    dp[m][n]
}

/// 方法三：高级实现 - 使用Rust的高级特性
/// 
/// # 算法思路
/// 与方法二相同，但使用Rust的迭代器、闭包和函数式编程特性
/// 
/// # 参数
/// * `word1` - 第一个字符串
/// * `word2` - 第二个字符串
/// 
/// # 返回值
/// * 使得两个字符串相同所需的最小删除次数
fn min_distance_functional(word1: &str, word2: &str) -> i32 {
    // 获取字符串长度
    let m = word1.len();
    let n = word2.len();
    
    // 如果有一个字符串为空，直接返回另一个字符串的长度
    if m == 0 || n == 0 {
        return (m + n) as i32;
    }
    
    // 将字符串转换为字符向量
    let word1_chars: Vec<char> = word1.chars().collect();
    let word2_chars: Vec<char> = word2.chars().collect();
    
    // 创建初始行，相当于dp[0][j]
    let mut prev_row: Vec<i32> = (0..=n).map(|j| j as i32).collect();
    
    // 使用迭代器和fold进行动态规划计算
    // 这里使用了函数式编程的思想，每次迭代更新一行dp值
    (1..=m).fold(prev_row, |mut prev_row, i| {
        // 创建新行，从dp[i][0]开始
        let mut curr_row = vec![i as i32; n + 1];
        
        // 计算当前行的dp值
        for j in 1..=n {
            curr_row[j] = if word1_chars[i - 1] == word2_chars[j - 1] {
                prev_row[j - 1] // 字符相同，无需删除
            } else {
                prev_row[j].min(curr_row[j - 1]) + 1 // 删除一个字符
            };
        }
        
        // 返回当前行作为下一次迭代的prev_row
        curr_row
    })[n] // 取最后一行的最后一个元素，即dp[m][n]
}

/// 测试函数
fn test_delete_operation() {
    // 使用结构体来组织测试用例
    struct TestCase {
        word1: &'static str,
        word2: &'static str,
        expected: i32,
        name: &'static str,
    }
    
    // 定义测试用例
    let test_cases = vec![
        TestCase {
            word1: "sea",
            word2: "eat",
            expected: 2,
            name: "基本测试1",
        },
        TestCase {
            word1: "leetcode",
            word2: "etco",
            expected: 4,
            name: "基本测试2",
        },
        TestCase {
            word1: "",
            word2: "a",
            expected: 1,
            name: "空字符串测试1",
        },
        TestCase {
            word1: "a",
            word2: "",
            expected: 1,
            name: "空字符串测试2",
        },
        TestCase {
            word1: "intention",
            word2: "execution",
            expected: 8,
            name: "复杂测试",
        },
    ];
    
    // 运行测试并输出结果
    for tc in test_cases {
        let lcs_result = min_distance_lcs(tc.word1, tc.word2);
        let dp_result = min_distance(tc.word1, tc.word2);
        let functional_result = min_distance_functional(tc.word1, tc.word2);
        
        println!(
            "测试 {}: LCS结果 = {}, DP结果 = {}, 函数式结果 = {}, 预期 = {}, {}", 
            tc.name, 
            lcs_result,
            dp_result,
            functional_result,
            tc.expected,
            if lcs_result == tc.expected && dp_result == tc.expected && functional_result == tc.expected { 
                "通过" 
            } else { 
                "失败" 
            }
        );
    }
    
    // 解释Rust高级特性
    println!("\n=== Rust高级特性解释 ===");
    println!("1. 迭代器(Iterator)：Rust的迭代器允许你以函数式编程的方式处理集合，如map、fold等。");
    println!("2. 闭包(Closure)：类似于匿名函数，可以捕获环境中的变量。");
    println!("3. 所有权(Ownership)：Rust的核心特性，确保内存安全而无需垃圾回收。");
    println!("4. 借用(Borrowing)：通过引用访问数据而不获取所有权，分为可变借用和不可变借用。");
    println!("5. 生命周期(Lifetime)：确保引用的有效性，防止悬垂引用。");
    println!("6. 模式匹配(Pattern Matching)：强大的解构和匹配能力，常用于match表达式。");
    println!("7. 特质(Trait)：类似于接口，定义类型行为的抽象。");
    println!("8. 泛型(Generic)：实现类型参数化，提高代码复用性。");
    println!("\n在min_distance_functional函数中，我们使用了：");
    println!("- 迭代器的map方法创建初始行");
    println!("- fold方法进行累积计算，替代传统的for循环");
    println!("- 闭包来定义fold的操作");
    println!("- 函数式编程风格处理整个动态规划过程");
}