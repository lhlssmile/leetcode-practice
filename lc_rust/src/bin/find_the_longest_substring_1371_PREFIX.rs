use std::collections::HashMap;

/**
 * LeetCode 1371. 每个元音包含偶数次的最长子字符串
 * 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
 */

/**
 * 基本实现：使用前缀和+状态压缩的方法
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 */
fn find_the_longest_substring(s: String) -> i32 {
    let n = s.len();
    let mut first: HashMap<i32, i32> = HashMap::new(); // 记录状态第一次出现的位置
    first.insert(0, -1); // 空字符串状态为0，位置-1
    let mut state = 0; // 当前前缀的元音奇偶状态
    let mut max_len = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    let mut vowel_pos = vec![-1; 128];
    vowel_pos[b'a' as usize] = 0;
    vowel_pos[b'e' as usize] = 1;
    vowel_pos[b'i' as usize] = 2;
    vowel_pos[b'o' as usize] = 3;
    vowel_pos[b'u' as usize] = 4;
    
    // 遍历字符串
    for (i, &c) in s.as_bytes().iter().enumerate() {
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        let pos = vowel_pos[c as usize];
        if pos != -1 {
            state ^= 1 << pos; // 翻转第pos位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if let Some(&j) = first.get(&state) {
            max_len = max_len.max(i as i32 - j);
        } else {
            // 记录状态第一次出现的位置
            first.insert(state, i as i32);
        }
    }
    
    max_len
}

/**
 * 优化实现：使用数组代替哈希表（因为状态数最多为2^5=32种）
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 */
fn find_the_longest_substring_optimized(s: String) -> i32 {
    let n = s.len();
    let mut first = vec![-2; 1 << 5]; // 记录状态第一次出现的位置，初始化为-2表示未出现过
    first[0] = -1; // 空字符串状态为0，位置-1
    let mut state = 0; // 当前前缀的元音奇偶状态
    let mut max_len = 0; // 最长子字符串长度
    
    // 元音映射：a=0, e=1, i=2, o=3, u=4
    let mut vowel_pos = vec![-1; 128];
    vowel_pos[b'a' as usize] = 0;
    vowel_pos[b'e' as usize] = 1;
    vowel_pos[b'i' as usize] = 2;
    vowel_pos[b'o' as usize] = 3;
    vowel_pos[b'u' as usize] = 4;
    
    // 遍历字符串
    for (i, &c) in s.as_bytes().iter().enumerate() {
        // 如果是元音，更新状态（翻转对应位的奇偶性）
        let pos = vowel_pos[c as usize];
        if pos != -1 {
            state ^= 1 << pos; // 翻转第pos位
        }
        
        // 如果当前状态见过，说明[left+1, i]的元音频次差为偶数
        if first[state as usize] != -2 {
            max_len = max_len.max(i as i32 - first[state as usize]);
        } else {
            // 记录状态第一次出现的位置
            first[state as usize] = i as i32;
        }
    }
    
    max_len
}

/**
 * 函数式实现：使用更多Rust的函数式特性
 * 时间复杂度: O(n)，其中n是字符串长度
 * 空间复杂度: O(1)，状态数最多为2^5=32种
 */
fn find_the_longest_substring_functional(s: String) -> i32 {
    let vowels = [('a', 0), ('e', 1), ('i', 2), ('o', 3), ('u', 4)]
        .iter()
        .cloned()
        .collect::<HashMap<char, i32>>();
    
    let mut seen = HashMap::new();
    seen.insert(0, -1); // 空字符串状态为0，位置-1
    
    s.chars().enumerate().fold((0, 0), |(state, max_len), (i, c)| {
        // 更新状态
        let new_state = if let Some(&pos) = vowels.get(&c) {
            state ^ (1 << pos)
        } else {
            state
        };
        
        // 更新最大长度
        let new_max_len = if let Some(&j) = seen.get(&new_state) {
            max_len.max(i as i32 - j)
        } else {
            seen.insert(new_state, i as i32);
            max_len
        };
        
        (new_state, new_max_len)
    }).1 // 返回元组的第二个元素（max_len）
}

fn main() {
    let test_cases = vec![
        ("eleetminicoworoep".to_string(), 13),
        ("leetcodeisgreat".to_string(), 5),
        ("bcbcbc".to_string(), 6)
    ];
    
    for (s, expected) in test_cases {
        let result1 = find_the_longest_substring(s.clone());
        let result2 = find_the_longest_substring_optimized(s.clone());
        let result3 = find_the_longest_substring_functional(s.clone());
        
        println!("Input: {}", s);
        println!("Basic: {}, Optimized: {}, Functional: {}", result1, result2, result3);
        println!("Expected: {}", expected);
        println!();
        
        assert_eq!(result1, expected);
        assert_eq!(result2, expected);
        assert_eq!(result3, expected);
    }
    
    println!("All tests passed!");
}