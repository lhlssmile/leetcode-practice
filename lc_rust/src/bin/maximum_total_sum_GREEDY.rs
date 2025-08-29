// 力扣第3301题：高度互不相同的最大塔高和

fn main() {
    // 运行测试用例
    test_maximum_total_sum();
}

/// 计算高度互不相同的最大塔高和
/// 
/// # 算法思路
/// 1. 将高度数组按降序排序
/// 2. 从最高的塔开始，确保每个塔的高度严格小于前一个塔
/// 3. 如果无法满足条件，返回-1
/// 4. 否则，返回所有调整后高度的总和
/// 
/// # 参数
/// * `maximum_height` - 塔的高度数组
/// 
/// # 返回值
/// * 高度互不相同的最大塔高和，如果无法满足条件则返回-1
fn maximum_total_sum(maximum_height: Vec<i32>) -> i64 {
    // 创建一个可变的克隆，避免修改原始数据
    let mut heights = maximum_height.clone();
    
    // 使用Rust的排序功能，按降序排序
    heights.sort_unstable_by(|a, b| b.cmp(a));
    
    // 使用Option来处理可能的无效情况，更符合Rust的错误处理风格
    let result = heights.iter()
        .fold(
            (i32::MAX, 0i64), // (prev, sum)
            |(prev, sum), &h| {
                let curr = h.min(prev - 1);
                if curr <= 0 {
                    (0, -1) // 标记为无效
                } else {
                    (curr, sum + curr as i64)
                }
            }
        );
    
    // 返回结果
    result.1
}

/// 使用更高级的Rust特性实现的版本
/// 利用迭代器、Result和函数式编程风格
fn maximum_total_sum_functional(maximum_height: Vec<i32>) -> i64 {
    // 创建一个不可变的克隆
    let mut heights = maximum_height.clone();
    heights.sort_unstable_by(|a, b| b.cmp(a));
    
    // 使用scan迭代器适配器来维护状态
    let result = heights.iter()
        .scan(i32::MAX, |prev, &h| {
            let curr = h.min(*prev - 1);
            if curr <= 0 {
                None // 提前终止迭代
            } else {
                *prev = curr;
                Some(curr as i64)
            }
        })
        .sum::<i64>();
    
    // 如果迭代提前终止，说明无法满足条件
    if heights.len() as i64 != heights.iter()
        .scan(i32::MAX, |prev, &h| {
            let curr = h.min(*prev - 1);
            if curr <= 0 {
                None
            } else {
                *prev = curr;
                Some(curr)
            }
        })
        .count() as i64 {
        -1
    } else {
        result
    }
}

/// 测试函数
fn test_maximum_total_sum() {
    // 使用结构体来组织测试用例
    struct TestCase {
        heights: Vec<i32>,
        expected: i64,
        name: &'static str,
    }
    
    // 定义测试用例
    let test_cases = vec![
        TestCase {
            heights: vec![5, 3, 4, 1, 1],
            expected: 13,
            name: "基本测试1",
        },
        TestCase {
            heights: vec![6, 5, 3, 9, 2, 7],
            expected: 29,
            name: "基本测试2",
        },
        TestCase {
            heights: vec![3, 2, 1],
            expected: 6,
            name: "基本测试3",
        },
        TestCase {
            heights: vec![1, 1, 1],
            expected: -1,
            name: "无法满足条件",
        },
    ];
    
    // 运行测试并输出结果
    for tc in test_cases {
        let result = maximum_total_sum(tc.heights.clone());
        let functional_result = maximum_total_sum_functional(tc.heights);
        
        println!(
            "测试 {}: 结果 = {}, 函数式结果 = {}, 预期 = {}, {}", 
            tc.name, 
            result, 
            functional_result,
            tc.expected,
            if result == tc.expected && functional_result == tc.expected { "通过" } else { "失败" }
        );
    }
}