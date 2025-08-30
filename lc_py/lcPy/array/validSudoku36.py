from typing import List


class Solution:
    """
    LeetCode 36. 有效的数独
    
    请你判断一个 9 x 9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
    1. 数字 1-9 在每一行只能出现一次。
    2. 数字 1-9 在每一列只能出现一次。
    3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
    
    注意：
    - 一个有效的数独（部分已填充）不一定是可解的。
    - 只需要根据以上规则，验证已经填入的数字是否有效即可。
    - 空白格用 '.' 表示。
    """
    
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        """
        使用位运算检查数独是否有效
        时间复杂度: O(n²)，其中 n = 9 是数独的大小
        空间复杂度: O(n)，使用了固定大小的数组来跟踪每行、每列和每个3x3宫格中的数字
        """
        # 检查行
        for i in range(9):
            mask = 0
            for j in range(9):
                if board[i][j] == '.':
                    continue
                num = int(board[i][j])
                if mask & (1 << num):
                    return False
                mask |= (1 << num)
        
        # 检查列
        for j in range(9):
            mask = 0
            for i in range(9):
                if board[i][j] == '.':
                    continue
                num = int(board[i][j])
                if mask & (1 << num):
                    return False
                mask |= (1 << num)
        
        # 检查 3×3 宫
        for block in range(9):
            mask = 0
            for i in range(3):
                for j in range(3):
                    r = (block // 3) * 3 + i
                    c = (block % 3) * 3 + j
                    if board[r][c] == '.':
                        continue
                    num = int(board[r][c])
                    if mask & (1 << num):
                        return False
                    mask |= (1 << num)
        
        return True
    
    def isValidSudokuSets(self, board: List[List[str]]) -> bool:
        """
        使用集合检查数独是否有效（替代方案）
        时间复杂度: O(n²)，其中 n = 9 是数独的大小
        空间复杂度: O(n²)，使用了集合来存储每行、每列和每个3x3宫格中的数字
        """
        # 初始化行、列和块的集合
        rows = [set() for _ in range(9)]
        cols = [set() for _ in range(9)]
        boxes = [set() for _ in range(9)]
        
        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    continue
                    
                num = board[i][j]
                box_idx = (i // 3) * 3 + j // 3
                
                # 检查是否已在行、列或块中出现
                if num in rows[i] or num in cols[j] or num in boxes[box_idx]:
                    return False
                
                # 添加到集合中
                rows[i].add(num)
                cols[j].add(num)
                boxes[box_idx].add(num)
        
        return True


def test_solution():
    solution = Solution()
    
    valid_board = [
        ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
    ]
    
    invalid_board = [
        ['8', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
    ]
    
    print(f"Valid board (bit method): {solution.isValidSudoku(valid_board)}")
    print(f"Invalid board (bit method): {solution.isValidSudoku(invalid_board)}")
    
    print(f"Valid board (set method): {solution.isValidSudokuSets(valid_board)}")
    print(f"Invalid board (set method): {solution.isValidSudokuSets(invalid_board)}")


if __name__ == "__main__":
    test_solution()