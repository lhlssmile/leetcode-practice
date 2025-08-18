struct Solution;

impl Solution {
    pub fn maximum69_number(num: i32) -> i32 {
        let mut v = num;
        let mut max_base = 0;
        let mut base = 1;

        while v > 0 {
            if v % 10 == 6 {
                max_base = base;
            }
            v /= 10;
            base *= 10;
        }

        num + max_base * 3
    }
}

fn main() {
    let num = 9669;
    let ans = Solution::maximum69_number(num);
    println!("Input: {num}, Output: {ans}");
}
