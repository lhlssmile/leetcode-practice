struct Solution;
impl Solution {
    pub fn num_submat(mat: Vec<Vec<i32>>) -> i32 {
        let m = mat.len();
        let n = mat[0].len();
        let mut ans = 0;

        for top in 0..m {
            let mut a = vec![0; n];
            for bottom in top..m {
                let mut last :i32 = -1;
                let h = bottom - top + 1;
                for j in 0..n {

                    a[j] += mat[bottom][j];
                    if a[j] != h as i32 {
                        last = j as i32;
                    }else {
                        ans += j as i32 - last;
                    }
                }
            }
        }
        ans
    }
}
fn main() {

}