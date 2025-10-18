pub fn letter_case_permutation_recursive(s: String) -> Vec<String> {
    let mut ans: Vec<String> = Vec::new();
    let mut path: Vec<char> = Vec::new();
    let s_chars: Vec<char> = s.chars().collect();
    
    fn dfs(s: &[char], i: usize, path: &mut Vec<char>, ans: &mut Vec<String>) {
        if i == s.len() {
            ans.push(path.iter().collect());
            return;
        }
        
        let ch = s[i];
        if ch.is_ascii_digit() {
            path.push(ch);
            dfs(s, i + 1, path, ans);
            path.pop();
        } else {
            // 小写
            path.push(ch.to_ascii_lowercase());
            dfs(s, i + 1, path, ans);
            path.pop();
            
            // 大写
            path.push(ch.to_ascii_uppercase());
            dfs(s, i + 1, path, ans);
            path.pop();
        }
    }
    
    dfs(&s_chars, 0, &mut path, &mut ans);
    ans
}

// 函数式编程版本的递归解法
pub fn letter_case_permutation_functional(s: String) -> Vec<String> {
    fn backtrack(chars: &[char], index: usize, current: &mut Vec<char>) -> Vec<String> {
        if index == chars.len() {
            return vec![current.iter().collect()];
        }
        
        let mut result = Vec::new();
        
        if chars[index].is_ascii_digit() {
            current.push(chars[index]);
            result.extend(backtrack(chars, index + 1, current));
            current.pop();
        } else {
            // 小写
            current.push(chars[index].to_ascii_lowercase());
            result.extend(backtrack(chars, index + 1, current));
            current.pop();
            
            // 大写
            current.push(chars[index].to_ascii_uppercase());
            result.extend(backtrack(chars, index + 1, current));
            current.pop();
        }
        
        result
    }
    
    let chars: Vec<char> = s.chars().collect();
    backtrack(&chars, 0, &mut Vec::new())
}

// 位掩码解法
pub fn letter_case_permutation_bitmask(s: String) -> Vec<String> {
    let s_chars: Vec<char> = s.chars().collect();
    let letter_indices: Vec<usize> = s_chars.iter()
        .enumerate()
        .filter(|(_, &c)| c.is_alphabetic())
        .map(|(i, _)| i)
        .collect();
    
    let letter_count = letter_indices.len();
    let total_permutations = 1 << letter_count; // 2^letter_count
    let mut result = Vec::with_capacity(total_permutations);
    
    for mask in 0..total_permutations {
        let mut chars = s_chars.clone();
        
        for (bit_pos, &char_pos) in letter_indices.iter().enumerate() {
            let is_uppercase = (mask >> bit_pos) & 1 == 1;
            chars[char_pos] = if is_uppercase {
                chars[char_pos].to_ascii_uppercase()
            } else {
                chars[char_pos].to_ascii_lowercase()
            };
        }
        
        result.push(chars.iter().collect());
    }
    
    result
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_letter_case_permutation() {
        // 测试用例1
        let s1 = "a1b2".to_string();
        let mut result1_recursive = letter_case_permutation_recursive(s1.clone());
        let mut result1_bitmask = letter_case_permutation_bitmask(s1.clone());
        let mut result1_functional = letter_case_permutation_functional(s1.clone());
        
        result1_recursive.sort();
        result1_bitmask.sort();
        result1_functional.sort();
        
        let mut expected1 = vec!["a1b2", "a1B2", "A1b2", "A1B2"].into_iter().map(String::from).collect::<Vec<String>>();
        expected1.sort();
        
        assert_eq!(result1_recursive, expected1);
        assert_eq!(result1_bitmask, expected1);
        assert_eq!(result1_functional, expected1);
        
        // 测试用例2
        let s2 = "3z4".to_string();
        let mut result2_recursive = letter_case_permutation_recursive(s2.clone());
        let mut result2_bitmask = letter_case_permutation_bitmask(s2.clone());
        let mut result2_functional = letter_case_permutation_functional(s2.clone());
        
        result2_recursive.sort();
        result2_bitmask.sort();
        result2_functional.sort();
        
        let mut expected2 = vec!["3z4", "3Z4"].into_iter().map(String::from).collect::<Vec<String>>();
        expected2.sort();
        
        assert_eq!(result2_recursive, expected2);
        assert_eq!(result2_bitmask, expected2);
        assert_eq!(result2_functional, expected2);
    }
}

/*
算法思路：
1. 递归解法：使用回溯法生成所有可能的字母大小写排列
2. 位掩码解法：利用位运算，对于n个字母，有2^n种可能的大小写组合，每个位掩码表示一种组合

时间复杂度：
- 递归解法：O(2^n)，其中n是字符串中字母的数量
- 位掩码解法：O(2^n * n)，需要生成2^n个排列，每个排列需要O(n)时间构建

空间复杂度：
- 递归解法：O(n)，递归栈的深度和临时字符串的空间
- 位掩码解法：O(2^n * n)，需要存储2^n个长度为n的字符串
*/