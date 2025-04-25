from typing import List
class Rotate:
    def rotate(self,matrix: List[List[int]]) -> None:
        n = len(matrix)

        for i in range(n):
            for j in range(i + 1,n):
                matrix[i][j],matrix[j][i] = matrix[j][i],matrix[i][j]
        for row in matrix:
            row.reverse()

if name == "__main__":
    ro = Rotate()
    matrix = [[1,2,3],[4,5,6],[7,8,9]]
    ro.rotate(matrix)
    print(matrix)