class SearchMatrix:
    def searchMatrix(self,matrix: List[List[int]],target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        row, col = m - 1, 0  # 从左下角开始
        while row >= 0 and col < n:
            if matrix[row][col] == target:
                return True
            elif target < matrix[row][col]:
                row -= 1  # 当前值太大，往上走
            else:
                col += 1  # 当前值太小，往右走
        return False