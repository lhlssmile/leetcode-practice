#include <stdio.h>
#include <stdbool.h>

/**
 * LeetCode 36. 有效的数独
 * 
 * 请你判断一个 9 x 9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
 * 1. 数字 1-9 在每一行只能出现一次。
 * 2. 数字 1-9 在每一列只能出现一次。
 * 3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 * 
 * 注意：
 * - 一个有效的数独（部分已填充）不一定是可解的。
 * - 只需要根据以上规则，验证已经填入的数字是否有效即可。
 * - 空白格用 '.' 表示。
 */

/**
 * 使用位运算检查数独是否有效
 * 时间复杂度: O(n²)，其中 n = 9 是数独的大小
 * 空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
 */
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // 检查行
    for (int i = 0; i < 9; i++) {
        int mask = 0;
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') continue;
            int num = board[i][j] - '0';
            if (mask & (1 << num)) return false;
            mask |= (1 << num);
        }
    }
    
    // 检查列
    for (int j = 0; j < 9; j++) {
        int mask = 0;
        for (int i = 0; i < 9; i++) {
            if (board[i][j] == '.') continue;
            int num = board[i][j] - '0';
            if (mask & (1 << num)) return false;
            mask |= (1 << num);
        }
    }
    
    // 检查 3×3 宫
    for (int block = 0; block < 9; block++) {
        int mask = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int r = (block / 3) * 3 + i;
                int c = (block % 3) * 3 + j;
                if (board[r][c] == '.') continue;
                int num = board[r][c] - '0';
                if (mask & (1 << num)) return false;
                mask |= (1 << num);
            }
        }
    }
    
    return true;
}

/**
 * 使用数组检查数独是否有效（替代方案）
 * 时间复杂度: O(n²)，其中 n = 9 是数独的大小
 * 空间复杂度: O(n²)，使用了数组来存储每行、每列和每个3x3宫格中的数字
 */
bool isValidSudokuArray(char** board, int boardSize, int* boardColSize) {
    // 行、列、块的标记数组
    bool rowUsed[9][9] = {false};
    bool colUsed[9][9] = {false};
    bool boxUsed[9][9] = {false};
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') continue;
            
            int num = board[i][j] - '1'; // 转换为0-8的索引
            int boxIndex = (i / 3) * 3 + j / 3;
            
            // 检查是否已在行、列或块中使用
            if (rowUsed[i][num] || colUsed[j][num] || boxUsed[boxIndex][num]) {
                return false;
            }
            
            // 标记为已使用
            rowUsed[i][num] = true;
            colUsed[j][num] = true;
            boxUsed[boxIndex][num] = true;
        }
    }
    
    return true;
}

// 测试函数
int main() {
    // 由于C语言中二维数组的内存分配比较复杂，这里简化为一维数组的测试
    char validBoard[9][9] = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    
    char invalidBoard[9][9] = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    
    // 创建指向每行的指针数组
    char* validBoardPtr[9];
    char* invalidBoardPtr[9];
    for (int i = 0; i < 9; i++) {
        validBoardPtr[i] = validBoard[i];
        invalidBoardPtr[i] = invalidBoard[i];
    }
    
    int colSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    
    printf("Valid board (bit method): %s\n", isValidSudoku(validBoardPtr, 9, colSize) ? "true" : "false");
    printf("Invalid board (bit method): %s\n", isValidSudoku(invalidBoardPtr, 9, colSize) ? "true" : "false");
    
    printf("Valid board (array method): %s\n", isValidSudokuArray(validBoardPtr, 9, colSize) ? "true" : "false");
    printf("Invalid board (array method): %s\n", isValidSudokuArray(invalidBoardPtr, 9, colSize) ? "true" : "false");
    
    return 0;
}