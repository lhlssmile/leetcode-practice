struct Solution;

impl Solution {
    pub fn min_swaps(nums : Vec<i32>) -> i32 {
        let mut even_pos = Vec::new();
        let mut odd_pos = Vec::new();
        let mut res = i32::MAX;
        for (i, &x) in nums.iter().enumerate() {
            if x % 2 == 0 {
                even_pos.push(i as i32);
            }else {
                odd_pos.push(i as i32);
            }
        }
        let even_cnt = even_pos.len() as i32;
        let odd_cnt = odd_pos.len() as i32;

        let mut pos = 0;

        if (even_cnt - odd_cnt).abs() > 1 {
            return -1;
        }
        if even_cnt >= odd_cnt {
            let mut cost = 0;
            for (_, &posi) in even_pos.iter().enumerate() {
                cost += (posi - pos).abs();
                pos += 2;
            }
            res = res.min(cost);
        }
        pos = 0;
        if odd_cnt >= even_cnt {
            let mut cost = 0;
            for (_, &posi) in odd_pos.iter().enumerate() {
                cost += (posi - pos).abs();
                pos += 2;
            }
            res = res.min(cost);
        }
        res

    }
}
fn main() {

}