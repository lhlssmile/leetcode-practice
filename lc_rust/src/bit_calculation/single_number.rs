impl Solution {
    // 位运算解法
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut ans = 0;
        for i in 0..32 {
            let cnt1 = nums.iter().map(|&x| (x >> i) & 1).sum::<i32>();
            ans |= (cnt1 % 3) << i;
        }
        ans
    }
    
    // 状态机解法
    pub fn single_number_state_machine(nums: Vec<i32>) -> i32 {
        let (mut ones, mut twos) = (0, 0);
        for num in nums {
            ones = (ones ^ num) & !twos;
            twos = (twos ^ num) & !ones;
        }
        ones
    }
    
    // 函数式编程解法
    pub fn single_number_functional(nums: Vec<i32>) -> i32 {
        (0..32)
            .map(|i| {
                let cnt1 = nums.iter().map(|&x| (x >> i) & 1).sum::<i32>();
                (cnt1 % 3) << i
            })
            .fold(0, |acc, bit| acc | bit)
    }
    
    // 迭代器链式调用
    pub fn single_number_iterator(nums: Vec<i32>) -> i32 {
        (0..32)
            .fold(0, |ans, i| {
                let cnt1 = nums.iter()
                    .map(|&x| (x >> i) & 1)
                    .sum::<i32>();
                ans | ((cnt1 % 3) << i)
            })
    }
}

struct Solution;

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_single_number() {
        assert_eq!(Solution::single_number(vec![2, 2, 3, 2]), 3);
        assert_eq!(Solution::single_number(vec![0, 1, 0, 1, 0, 1, 99]), 99);
        
        assert_eq!(Solution::single_number_functional(vec![2, 2, 3, 2]), 3);
        assert_eq!(Solution::single_number_iterator(vec![0, 1, 0, 1, 0, 1, 99]), 99);
    }
}

fn main() {
    println!("{}", Solution::single_number(vec![2, 2, 3, 2])); // 3
    println!("{}", Solution::single_number(vec![0, 1, 0, 1, 0, 1, 99])); // 99
}