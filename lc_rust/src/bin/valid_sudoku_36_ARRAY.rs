// LeetCode 36. 有效的数独
//
// 请你判断一个 9 x 9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
// 1. 数字 1-9 在每一行只能出现一次。
// 2. 数字 1-9 在每一列只能出现一次。
// 3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
//
// 注意：
// - 一个有效的数独（部分已填充）不一定是可解的。
// - 只需要根据以上规则，验证已经填入的数字是否有效即可。
// - 空白格用 '.' 表示。

// 基本实现：使用位运算检查数独是否有效
// 时间复杂度: O(n²)，其中 n = 9 是数独的大小
// 空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
pub fn is_valid_sudoku(board: Vec<Vec<char>>) -> bool {
    // 检查行
    for i in 0..9 {
        let mut mask = 0;
        for j in 0..9 {
            if board[i][j] == '.' {
                continue;
            }
            let num = (board[i][j] as u8 - b'0') as i32;
            if mask & (1 << num) != 0 {
                return false;
            }
            mask |= 1 << num;
        }
    }
    
    // 检查列
    for j in 0..9 {
        let mut mask = 0;
        for i in 0..9 {
            if board[i][j] == '.' {
                continue;
            }
            let num = (board[i][j] as u8 - b'0') as i32;
            if mask & (1 << num) != 0 {
                return false;
            }
            mask |= 1 << num;
        }
    }
    
    // 检查 3×3 宫
    for block in 0..9 {
        let mut mask = 0;
        for i in 0..3 {
            for j in 0..3 {
                let r = (block / 3) * 3 + i;
                let c = (block % 3) * 3 + j;
                if board[r][c] == '.' {
                    continue;
                }
                let num = (board[r][c] as u8 - b'0') as i32;
                if mask & (1 << num) != 0 {
                    return false;
                }
                mask |= 1 << num;
            }
        }
    }
    
    true
}

// 高级实现：使用 Rust 的函数式编程特性和 HashSet 集合
// 时间复杂度: O(n²)，其中 n = 9 是数独的大小
// 空间复杂度: O(n²)，使用了 HashSet 来存储每行、每列和每个3x3宫格中的数字
pub fn is_valid_sudoku_functional(board: Vec<Vec<char>>) -> bool {
    use std::collections::HashSet;
    
    // 使用 HashSet 来跟踪每行、每列和每个3x3宫格中的数字
    let mut rows = vec![HashSet::new(); 9];
    let mut cols = vec![HashSet::new(); 9];
    let mut boxes = vec![HashSet::new(); 9];
    
    // 使用迭代器和闭包来检查数独
    !board.iter().enumerate().any(|(i, row)| {
        row.iter().enumerate().any(|(j, &cell)| {
            if cell == '.' {
                return false; // 跳过空格
            }
            
            let box_idx = (i / 3) * 3 + j / 3;
            
            // 检查是否已在行、列或块中出现
            if !rows[i].insert(cell) || !cols[j].insert(cell) || !boxes[box_idx].insert(cell) {
                return true; // 发现重复
            }
            
            false // 没有重复
        })
    })
}

// 更高级的实现：使用 Rust 的迭代器和函数式编程特性
// 时间复杂度: O(n²)，其中 n = 9 是数独的大小
// 空间复杂度: O(n)，使用了位掩码来跟踪每行、每列和每个3x3宫格中的数字
pub fn is_valid_sudoku_advanced(board: Vec<Vec<char>>) -> bool {
    let mut rows = [0; 9];
    let mut cols = [0; 9];
    let mut boxes = [0; 9];
    
    // 使用迭代器和闭包来检查数独
    board.iter().enumerate().all(|(i, row)| {
        row.iter().enumerate().all(|(j, &cell)| {
            if cell == '.' {
                return true; // 跳过空格
            }
            
            let num = (cell as u8 - b'0') as usize;
            let bit = 1 << num;
            let box_idx = (i / 3) * 3 + j / 3;
            
            // 检查是否已在行、列或块中出现
            if (rows[i] & bit != 0) || (cols[j] & bit != 0) || (boxes[box_idx] & bit != 0) {
                return false; // 发现重复
            }
            
            // 标记为已使用
            rows[i] |= bit;
            cols[j] |= bit;
            boxes[box_idx] |= bit;
            
            true // 没有重复
        })
    })
}

fn main() {
    let valid_board = vec![
        vec!['5', '3', '.', '.', '7', '.', '.', '.', '.'],
        vec!['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        vec!['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        vec!['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        vec!['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        vec!['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        vec!['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        vec!['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        vec!['.', '.', '.', '.', '8', '.', '.', '7', '9'],
    ];
    
    let invalid_board = vec![
        vec!['8', '3', '.', '.', '7', '.', '.', '.', '.'],
        vec!['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        vec!['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        vec!['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        vec!['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        vec!['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        vec!['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        vec!['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        vec!['.', '.', '.', '.', '8', '.', '.', '7', '9'],
    ];
    
    println!("基本实现:");
    println!("Valid board: {}", is_valid_sudoku(valid_board.clone()));
    println!("Invalid board: {}", is_valid_sudoku(invalid_board.clone()));
    
    println!("\n函数式实现:");
    println!("Valid board: {}", is_valid_sudoku_functional(valid_board.clone()));
    println!("Invalid board: {}", is_valid_sudoku_functional(invalid_board.clone()));
    
    println!("\n高级实现:");
    println!("Valid board: {}", is_valid_sudoku_advanced(valid_board));
    println!("Invalid board: {}", is_valid_sudoku_advanced(invalid_board));
}

// 以下是对 Rust 高级特性的解释：
// 
// 1. 迭代器和闭包：
//    - `iter()` 和 `enumerate()` 方法用于遍历集合并获取索引
//    - 闭包（匿名函数）用于简洁地表达逻辑
// 
// 2. 所有权和借用：
//    - 使用引用 `&` 来借用数据而不是获取所有权
//    - `clone()` 方法用于创建数据的副本
// 
// 3. 模式匹配：
//    - 使用模式匹配来解构元组和其他数据结构
// 
// 4. 函数式编程：
//    - `all()` 方法用于检查所有元素是否满足条件
//    - `any()` 方法用于检查是否有元素满足条件
// 
// 5. 类型转换：
//    - 使用 `as` 关键字进行类型转换
//    - 使用 `b'0'` 语法表示字节字面量
// 
// 6. 集合类型：
//    - `HashSet` 用于高效地检查元素是否存在
//    - `insert()` 方法返回布尔值表示插入是否成功