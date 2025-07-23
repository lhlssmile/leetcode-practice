from typing import List

'''
N 皇后问题

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题的棋盘配置，该配置中的每个 'Q' 和 '.' 分别代表了皇后和空位。

示例 1：
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],
       ["..Q.","Q...","...Q",".Q.."]]
解释：4 皇后问题存在两个不同的解法。

示例 2：
输入：n = 1
输出：[["Q"]]

提示：
1 <= n <= 9

算法思路：
N皇后是回溯算法的经典问题！核心思想：
1. 逐行放置皇后
2. 对于每一行，尝试在每一列放置皇后
3. 检查是否与之前放置的皇后冲突
4. 如果冲突，回溯；如果不冲突，继续下一行
5. 当所有行都放置完毕，找到一个解

冲突检测：
- 同列冲突：col[j] 表示第j列是否有皇后
- 主对角线冲突：diag1[i-j+n-1] 表示主对角线是否有皇后
- 副对角线冲突：diag2[i+j] 表示副对角线是否有皇后
'''

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        """标准回溯解法"""
        result = []
        board = [['.' for _ in range(n)] for _ in range(n)]
        
        def is_safe(row: int, col: int) -> bool:
            """检查在(row, col)位置放置皇后是否安全"""
            # 检查同一列
            for i in range(row):
                if board[i][col] == 'Q':
                    return False
            
            # 检查左上对角线
            i, j = row - 1, col - 1
            while i >= 0 and j >= 0:
                if board[i][j] == 'Q':
                    return False
                i -= 1
                j -= 1
            
            # 检查右上对角线
            i, j = row - 1, col + 1
            while i >= 0 and j < n:
                if board[i][j] == 'Q':
                    return False
                i -= 1
                j += 1
            
            return True
        
        def backtrack(row: int):
            """回溯函数"""
            if row == n:
                # 找到一个解，将棋盘转换为字符串格式
                solution = [''.join(row) for row in board]
                result.append(solution)
                return
            
            for col in range(n):
                if is_safe(row, col):
                    # 放置皇后
                    board[row][col] = 'Q'
                    # 递归处理下一行
                    backtrack(row + 1)
                    # 回溯，撤销选择
                    board[row][col] = '.'
        
        backtrack(0)
        return result
    
    def solveNQueens_optimized(self, n: int) -> List[List[str]]:
        """优化版本 - 使用位运算或数组标记"""
        result = []
        queens = [-1] * n  # queens[i] 表示第i行皇后所在的列
        
        # 用于快速检查冲突的标记数组
        cols = [False] * n  # 列占用情况
        diag1 = [False] * (2 * n - 1)  # 主对角线占用情况
        diag2 = [False] * (2 * n - 1)  # 副对角线占用情况
        
        def backtrack(row: int):
            if row == n:
                # 构造解
                board = []
                for i in range(n):
                    row_str = '.' * queens[i] + 'Q' + '.' * (n - queens[i] - 1)
                    board.append(row_str)
                result.append(board)
                return
            
            for col in range(n):
                # 检查是否冲突
                if cols[col] or diag1[row - col + n - 1] or diag2[row + col]:
                    continue
                
                # 放置皇后
                queens[row] = col
                cols[col] = True
                diag1[row - col + n - 1] = True
                diag2[row + col] = True
                
                # 递归
                backtrack(row + 1)
                
                # 回溯
                cols[col] = False
                diag1[row - col + n - 1] = False
                diag2[row + col] = False
        
        backtrack(0)
        return result
    
    def solveNQueens_detailed(self, n: int) -> List[List[str]]:
        """详细版本 - 带调试信息"""
        result = []
        board = [['.' for _ in range(n)] for _ in range(n)]
        
        print(f"开始解决 {n} 皇后问题")
        print(f"初始棋盘:")
        self.print_board(board)
        
        def is_safe(row: int, col: int) -> bool:
            # 检查同一列
            for i in range(row):
                if board[i][col] == 'Q':
                    return False
            
            # 检查左上对角线
            i, j = row - 1, col - 1
            while i >= 0 and j >= 0:
                if board[i][j] == 'Q':
                    return False
                i -= 1
                j -= 1
            
            # 检查右上对角线
            i, j = row - 1, col + 1
            while i >= 0 and j < n:
                if board[i][j] == 'Q':
                    return False
                i -= 1
                j += 1
            
            return True
        
        def backtrack(row: int, depth: int = 0):
            indent = "  " * depth
            print(f"{indent}尝试在第 {row} 行放置皇后")
            
            if row == n:
                print(f"{indent}找到一个解！")
                solution = [''.join(row) for row in board]
                result.append(solution)
                self.print_board(board)
                return
            
            for col in range(n):
                print(f"{indent}  尝试列 {col}")
                if is_safe(row, col):
                    print(f"{indent}  位置 ({row}, {col}) 安全，放置皇后")
                    board[row][col] = 'Q'
                    backtrack(row + 1, depth + 1)
                    print(f"{indent}  回溯，移除位置 ({row}, {col}) 的皇后")
                    board[row][col] = '.'
                else:
                    print(f"{indent}  位置 ({row}, {col}) 不安全，跳过")
        
        backtrack(0)
        print(f"\n总共找到 {len(result)} 个解")
        return result
    
    def print_board(self, board):
        """打印棋盘"""
        for row in board:
            print(''.join(row))
        print()


def test_n_queens():
    """测试函数"""
    solution = Solution()
    
    test_cases = [1, 4, 8]
    
    print("=== N皇后问题测试 ===")
    for n in test_cases:
        print(f"\n--- {n} 皇后问题 ---")
        result = solution.solveNQueens(n)
        print(f"解的数量: {len(result)}")
        
        if n <= 4:  # 只显示小规模的解
            for i, sol in enumerate(result):
                print(f"\n解 {i + 1}:")
                for row in sol:
                    print(row)
    
    print("\n=== 优化版本测试 ===")
    result_opt = solution.solveNQueens_optimized(4)
    print(f"4皇后问题优化版本解的数量: {len(result_opt)}")
    
    print("\n=== 详细过程演示 (2皇后) ===")
    solution.solveNQueens_detailed(2)


def analyze_n_queens_complexity():
    """分析N皇后问题的复杂度"""
    print("\n=== N皇后问题复杂度分析 ===")
    
    print("\n时间复杂度:")
    print("- 最坏情况: O(N!)")
    print("- 实际情况: 由于剪枝，通常远小于 O(N!)")
    print("- 第一行有N种选择，第二行最多N-2种选择...")
    
    print("\n空间复杂度:")
    print("- 递归栈深度: O(N)")
    print("- 棋盘存储: O(N²)")
    print("- 标记数组: O(N)")
    print("- 总体: O(N²)")
    
    print("\n解的数量 (前几个N值):")
    solutions_count = {
        1: 1, 2: 0, 3: 0, 4: 2, 5: 10, 6: 4, 7: 40, 8: 92
    }
    for n, count in solutions_count.items():
        print(f"N={n}: {count} 个解")


def backtrack_learning_tips():
    """回溯算法学习要点"""
    print("\n=== N皇后回溯算法学习要点 ===")
    
    print("\n1. 回溯三要素:")
    print("   - 选择: 在当前行的每一列尝试放置皇后")
    print("   - 约束: 检查是否与已放置的皇后冲突")
    print("   - 目标: 成功放置N个皇后")
    
    print("\n2. 冲突检测优化:")
    print("   - 列冲突: 用数组标记")
    print("   - 对角线冲突: 用数组标记")
    print("   - 主对角线: row - col + n - 1")
    print("   - 副对角线: row + col")
    
    print("\n3. 剪枝策略:")
    print("   - 提前检测冲突")
    print("   - 逐行放置（减少搜索空间）")
    print("   - 对称性剪枝（可选）")
    
    print("\n4. 常见错误:")
    print("   - 忘记回溯（撤销选择）")
    print("   - 冲突检测不完整")
    print("   - 结果格式化错误")
    print("   - 边界条件处理不当")
    
    print("\n5. 扩展问题:")
    print("   - N皇后计数问题")
    print("   - 其他棋子的放置问题")
    print("   - 约束满足问题(CSP)")


if __name__ == "__main__":
    test_n_queens()
    analyze_n_queens_complexity()
    backtrack_learning_tips()
        