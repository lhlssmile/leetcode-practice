use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn find_substring(s: String, words: Vec<String>) -> Vec<i32> {
        let n = words.len();
        let m = s.len();
        let k = words[0].len();
        let total_len = n * k;
        let mut ans = Vec::new();
        
        if m < total_len {
            return ans;
        }
        
        // 需求表
        let mut need = HashMap::new();
        for word in &words {
            *need.entry(word.clone()).or_insert(0) += 1;
        }
        
        // 遍历起点：对齐方式
        for offset in 0..k {
            let mut left = offset;
            let mut window = HashMap::new();
            let mut count = 0; // 窗口内匹配的单词数
            
            // 枚举每个单词起点
            let mut right = offset;
            while right + k <= m {
                let w = s[right..right + k].to_string();
                
                // 窗口右扩
                if need.contains_key(&w) {
                    *window.entry(w.clone()).or_insert(0) += 1;
                    count += 1;
                    
                    // 如果某个单词超频，收缩窗口
                    while window.get(&w).unwrap_or(&0) > need.get(&w).unwrap_or(&0) {
                        let lw = s[left..left + k].to_string();
                        if let Some(count_val) = window.get_mut(&lw) {
                            *count_val -= 1;
                        }
                        left += k;
                        count -= 1;
                    }
                    
                    // 如果窗口刚好包含n个单词
                    if count == n {
                        ans.push(left as i32);
                        // 再往前收缩一步，准备找下一个
                        let lw = s[left..left + k].to_string();
                        if let Some(count_val) = window.get_mut(&lw) {
                            *count_val -= 1;
                        }
                        left += k;
                        count -= 1;
                    }
                } else {
                    // 不在need中，清空窗口
                    window.clear();
                    count = 0;
                    left = right + k;
                }
                
                right += k;
            }
        }
        
        ans
    }
}

fn main() {
    let s = "barfoothefoobarman".to_string();
    let words = vec!["foo".to_string(), "bar".to_string()];
    
    let result = Solution::find_substring(s, words);
    
    println!("Result: {:?}", result);
}