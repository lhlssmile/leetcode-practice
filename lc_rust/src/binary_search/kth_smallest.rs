use std::cmp::Reverse;
use std::collections::BinaryHeap;

pub struct Solution;

impl Solution {
    // 二分查找解法
    pub fn kth_smallest(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len();
        let mut lo = matrix[0][0];
        let mut hi = matrix[n - 1][n - 1];
        
        while lo < hi {
            let mid = lo + (hi - lo) / 2;
            let count = Self::count_less_equal(&matrix, mid);
            if count < k {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        lo
    }
    
    fn count_less_equal(matrix: &Vec<Vec<i32>>, target: i32) -> i32 {
        let n = matrix.len();
        let mut i = n as i32 - 1;
        let mut j = 0;
        let mut count = 0;
        
        while i >= 0 && j < n {
            if matrix[i as usize][j] <= target {
                count += i + 1; // 当前列中有i+1个元素小于等于target
                j += 1;
            } else {
                i -= 1;
            }
        }
        count
    }
    
    // 最小堆解法
    pub fn kth_smallest_heap(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len();
        // 使用最小堆（通过BinaryHeap和Reverse实现）
        // 存储三元组 (值, 行, 列)
        let mut heap = BinaryHeap::new();
        
        // 将第一列的元素加入堆
        for i in 0..std::cmp::min(n, k as usize) {
            heap.push(Reverse((matrix[i][0], i, 0)));
        }
        
        // 弹出k-1个元素
        for _ in 1..k {
            if let Some(Reverse((_, row, col))) = heap.pop() {
                if col + 1 < n {
                    heap.push(Reverse((matrix[row][col + 1], row, col + 1)));
                }
            }
        }
        
        // 返回堆顶元素的值
        if let Some(Reverse((val, _, _))) = heap.pop() {
            val
        } else {
            -1 // 不应该到达这里
        }
    }
}

// 测试函数
pub fn test_kth_smallest() {
    // 测试用例1
    let matrix1 = vec![
        vec![1, 5, 9],
        vec![10, 11, 13],
        vec![12, 13, 15],
    ];
    let k1 = 8;
    println!("Binary Search: {}", Solution::kth_smallest(matrix1.clone(), k1));
    println!("Heap: {}", Solution::kth_smallest_heap(matrix1, k1));
    
    // 测试用例2
    let matrix2 = vec![
        vec![1, 2],
        vec![1, 3],
    ];
    let k2 = 2;
    println!("Binary Search: {}", Solution::kth_smallest(matrix2.clone(), k2));
    println!("Heap: {}", Solution::kth_smallest_heap(matrix2, k2));
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_kth_smallest_binary_search() {
        let matrix = vec![
            vec![1, 5, 9],
            vec![10, 11, 13],
            vec![12, 13, 15],
        ];
        assert_eq!(Solution::kth_smallest(matrix, 8), 13);
        
        let matrix = vec![
            vec![1, 2],
            vec![1, 3],
        ];
        assert_eq!(Solution::kth_smallest(matrix, 2), 1);
    }
    
    #[test]
    fn test_kth_smallest_heap() {
        let matrix = vec![
            vec![1, 5, 9],
            vec![10, 11, 13],
            vec![12, 13, 15],
        ];
        assert_eq!(Solution::kth_smallest_heap(matrix, 8), 13);
        
        let matrix = vec![
            vec![1, 2],
            vec![1, 3],
        ];
        assert_eq!(Solution::kth_smallest_heap(matrix, 2), 1);
    }
}

/*
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
*/