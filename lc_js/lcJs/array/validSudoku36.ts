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

type SudokuBoard = string[][];

/**
 * 使用位运算检查数独是否有效
 * 时间复杂度: O(n²)，其中 n = 9 是数独的大小
 * 空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
 */
function isValidSudoku(board: SudokuBoard): boolean {
    // 检查行
    for (let i = 0; i < 9; i++) {
        let mask = 0;
        for (let j = 0; j < 9; j++) {
            if (board[i][j] === '.') continue;
            const num = parseInt(board[i][j]);
            if (mask & (1 << num)) return false;
            mask |= (1 << num);
        }
    }
    
    // 检查列
    for (let j = 0; j < 9; j++) {
        let mask = 0;
        for (let i = 0; i < 9; i++) {
            if (board[i][j] === '.') continue;
            const num = parseInt(board[i][j]);
            if (mask & (1 << num)) return false;
            mask |= (1 << num);
        }
    }
    
    // 检查 3×3 宫
    for (let block = 0; block < 9; block++) {
        let mask = 0;
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                const r = Math.floor(block / 3) * 3 + i;
                const c = (block % 3) * 3 + j;
                if (board[r][c] === '.') continue;
                const num = parseInt(board[r][c]);
                if (mask & (1 << num)) return false;
                mask |= (1 << num);
            }
        }
    }
    
    return true;
}

/**
 * 使用集合检查数独是否有效（替代方案）
 * 时间复杂度: O(n²)，其中 n = 9 是数独的大小
 * 空间复杂度: O(n²)，使用了集合来存储每行、每列和每个3x3宫格中的数字
 */
function isValidSudokuSets(board: SudokuBoard): boolean {
    // 初始化行、列和块的集合
    const rows: Set<string>[] = Array(9).fill(null).map(() => new Set<string>());
    const cols: Set<string>[] = Array(9).fill(null).map(() => new Set<string>());
    const boxes: Set<string>[] = Array(9).fill(null).map(() => new Set<string>());
    
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            if (board[i][j] === '.') continue;
            
            const num = board[i][j];
            const boxIdx = Math.floor(i / 3) * 3 + Math.floor(j / 3);
            
            // 检查是否已在行、列或块中出现
            if (rows[i].has(num) || cols[j].has(num) || boxes[boxIdx].has(num)) {
                return false;
            }
            
            // 添加到集合中
            rows[i].add(num);
            cols[j].add(num);
            boxes[boxIdx].add(num);
        }
    }
    
    return true;
}

// 测试函数
function testSolution(): void {
    const validBoard: SudokuBoard = [
        ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
    ];
    
    const invalidBoard: SudokuBoard = [
        ['8', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
    ];
    
    console.log(`Valid board (bit method): ${isValidSudoku(validBoard)}`);
    console.log(`Invalid board (bit method): ${isValidSudoku(invalidBoard)}`);
    
    console.log(`Valid board (set method): ${isValidSudokuSets(validBoard)}`);
    console.log(`Invalid board (set method): ${isValidSudokuSets(invalidBoard)}`);
}

// 运行测试
testSolution();

// 导出函数供其他模块使用
export {
    isValidSudoku,
    isValidSudokuSets,
    SudokuBoard
};