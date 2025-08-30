package lcJava.array;

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
public class ValidSudoku36 {
    
    /**
     * 使用位运算检查数独是否有效
     * 时间复杂度: O(n²)，其中 n = 9 是数独的大小
     * 空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
     */
    public boolean isValidSudoku(char[][] board) {
        // 检查行
        for (int i = 0; i < 9; i++) {
            int mask = 0;
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                if ((mask & (1 << num)) != 0) return false;
                mask |= (1 << num);
            }
        }
        
        // 检查列
        for (int j = 0; j < 9; j++) {
            int mask = 0;
            for (int i = 0; i < 9; i++) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                if ((mask & (1 << num)) != 0) return false;
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
                    if ((mask & (1 << num)) != 0) return false;
                    mask |= (1 << num);
                }
            }
        }
        
        return true;
    }
    
    /**
     * 使用数组检查数独是否有效（替代方案）
     */
    public boolean isValidSudokuArray(char[][] board) {
        // 行、列、块的标记数组
        boolean[][] rowUsed = new boolean[9][9];
        boolean[][] colUsed = new boolean[9][9];
        boolean[][] boxUsed = new boolean[9][9];
        
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
    
    // 测试方法
    public static void main(String[] args) {
        ValidSudoku36 solution = new ValidSudoku36();
        
        char[][] validBoard = {
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
        
        char[][] invalidBoard = {
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
        
        System.out.println("Valid board: " + solution.isValidSudoku(validBoard));
        System.out.println("Invalid board: " + solution.isValidSudoku(invalidBoard));
        
        System.out.println("Valid board (array method): " + solution.isValidSudokuArray(validBoard));
        System.out.println("Invalid board (array method): " + solution.isValidSudokuArray(invalidBoard));
    }
}