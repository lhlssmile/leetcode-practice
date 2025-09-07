use std::collections::BinaryHeap;
use std::cmp::Ordering;

impl Solution {
    // 方法1: 二分扩展法
    pub fn find_closest_elements(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let n = arr.len();
        let k = k as usize;
        let idx = arr.binary_search(&x).unwrap_or_else(|e| e);
        
        let mut left = idx as i32 - 1;
        let mut right = idx as i32;
        
        while (right - left - 1) < k as i32 {
            if left < 0 {
                right += 1;
            } else if right >= n as i32 {
                left -= 1;
            } else {
                if x - arr[left as usize] <= arr[right as usize] - x {
                    left -= 1;
                } else {
                    right += 1;
                }
            }
        }
        
        arr[(left + 1) as usize..right as usize].to_vec()
    }
    
    // 方法2: 滑动窗口法
    pub fn find_closest_elements_sliding_window(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let k = k as usize;
        let mut left = 0;
        let mut right = arr.len() - k;
        
        while left < right {
            let mid = left + (right - left) / 2;
            if x - arr[mid] > arr[mid + k] - x {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        arr[left..left + k].to_vec()
    }
    
    // 方法3: 大根堆法
    pub fn find_closest_elements_max_heap(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let k = k as usize;
        let mut heap = BinaryHeap::new();
        
        for (i, &num) in arr.iter().enumerate() {
            let distance = (num - x).abs();
            let item = HeapItem { distance, value: num, index: i };
            
            if heap.len() < k {
                heap.push(item);
            } else if let Some(top) = heap.peek() {
                if distance < top.distance || (distance == top.distance && num < top.value) {
                    heap.pop();
                    heap.push(item);
                }
            }
        }
        
        let mut result: Vec<_> = heap.into_iter().collect();
        result.sort_by_key(|item| item.index);
        result.into_iter().map(|item| item.value).collect()
    }
    
    // 方法3优化: 大根堆法 - 提前终止
    pub fn find_closest_elements_optimized_heap(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let k = k as usize;
        let mut heap = BinaryHeap::new();
        
        for (i, &num) in arr.iter().enumerate() {
            let distance = (num - x).abs();
            let item = HeapItem { distance, value: num, index: i };
            
            if heap.len() < k {
                heap.push(item);
            } else if let Some(top) = heap.peek() {
                if distance < top.distance || (distance == top.distance && num < top.value) {
                    heap.pop();
                    heap.push(item);
                } else if distance > top.distance {
                    break; // 提前终止
                }
            }
        }
        
        let mut result: Vec<_> = heap.into_iter().collect();
        result.sort_by_key(|item| item.index);
        result.into_iter().map(|item| item.value).collect()
    }
    
    // 函数式编程解法
    pub fn find_closest_elements_functional(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let k = k as usize;
        let mut indexed: Vec<_> = arr.iter()
            .enumerate()
            .map(|(i, &val)| (i, val, (val - x).abs()))
            .collect();
        
        // 按距离和值排序
        indexed.sort_by(|a, b| {
            match a.2.cmp(&b.2) {
                Ordering::Equal => a.1.cmp(&b.1),
                other => other,
            }
        });
        
        // 取前k个并按原顺序排序
        indexed.truncate(k);
        indexed.sort_by_key(|item| item.0);
        indexed.into_iter().map(|item| item.1).collect()
    }
    
    // 迭代器链式调用
    pub fn find_closest_elements_iterator(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let k = k as usize;
        let mut result: Vec<_> = arr.iter()
            .enumerate()
            .map(|(i, &val)| (i, val, (val - x).abs()))
            .collect();
        
        result.sort_by(|a, b| {
            a.2.cmp(&b.2).then(a.1.cmp(&b.1))
        });
        
        result.into_iter()
            .take(k)
            .collect::<Vec<_>>()
            .into_iter()
            .fold(Vec::new(), |mut acc, item| {
                acc.push(item);
                acc.sort_by_key(|x| x.0);
                acc
            })
            .into_iter()
            .map(|item| item.1)
            .collect()
    }
}

#[derive(Debug, Clone)]
struct HeapItem {
    distance: i32,
    value: i32,
    index: usize,
}

impl PartialEq for HeapItem {
    fn eq(&self, other: &Self) -> bool {
        self.distance == other.distance && self.value == other.value
    }
}

impl Eq for HeapItem {}

impl PartialOrd for HeapItem {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for HeapItem {
    fn cmp(&self, other: &Self) -> Ordering {
        // 大根堆：距离大的在前，距离相同时值大的在前
        match self.distance.cmp(&other.distance) {
            Ordering::Equal => self.value.cmp(&other.value),
            other => other,
        }
    }
}

struct Solution;

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_find_closest_elements() {
        let arr = vec![1, 2, 3, 4, 5];
        let k = 4;
        let x = 3;
        
        println!("二分扩展法: {:?}", Solution::find_closest_elements(arr.clone(), k, x));
        println!("滑动窗口法: {:?}", Solution::find_closest_elements_sliding_window(arr.clone(), k, x));
        println!("大根堆法: {:?}", Solution::find_closest_elements_max_heap(arr.clone(), k, x));
        println!("优化堆法: {:?}", Solution::find_closest_elements_optimized_heap(arr.clone(), k, x));
        println!("函数式编程: {:?}", Solution::find_closest_elements_functional(arr.clone(), k, x));
        println!("迭代器链式: {:?}", Solution::find_closest_elements_iterator(arr, k, x));
    }
}

fn main() {
    let arr = vec![1, 2, 3, 4, 5];
    let result = Solution::find_closest_elements(arr, 4, 3);
    println!("{:?}", result);
}