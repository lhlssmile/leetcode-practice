#include <iostream>
#include <vector>
class diagonalSumSolution{
public:
    int diagonalSum(std::vector<std::vector<int>>& mat){
        int sum = 0;
        int n = mat.size();
        if(n == 0) return 0;
        for(int i = 0;i < mat.size(); ++i){
            sum += mat[i][i] + mat[n - 1 - i][i];
        }
        if(n % 2 == 1) sum -= mat[n / 2][n / 2];
        return sum;
    }
};
int main() {
    diagonalSumSolution ps;
    std::vector<std::vector<int>> matrix = {{7,3,1,9},{3,4,6,9},{6,9,6,6},{9,5,8,5}};
    std::cout << ps.diagonalSum(matrix) << std::endl;

    return 0;
}
