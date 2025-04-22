#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
class setZeroesSolution{
public:
    void setZeroes(vector<vector<int>>& matrix){
        int m = matrix.size(), n = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;

        // 1. 先检查第一列是否有 0
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        // 2. 先检查第一行是否有 0
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        // 3. 记录 0 的位置，使用第一行和第一列来存储信息
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // 该行的标记
                    matrix[0][j] = 0; // 该列的标记
                }
            }
        }

        // 4. 置 0：根据第一行和第一列的标记，把相应行列的元素置 0
        for (int i = 1; i < m; ++i) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < n; ++j) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int j = 1; j < n; ++j) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < m; ++i) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 5. 处理第一行和第一列
        if (firstColZero) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
        if (firstRowZero) {
            for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        }
    }
    void setZeroe(vector<vector<int>>& matrix) {
        auto m = matrix.size();
        auto n = matrix[0].size();
        bool firstRowHasZero = false;
        bool firstColumnHasZero = false;
        for(int i = 0;i < m;++i) {
            for(int j = 0; j < n; ++j) {
                if(matrix[i][j] == 0) {
                    if(i == 0) firstRowHasZero = true;
                    if(j == 0) firstColumnHasZero = true;
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i = 1;i < m;++i) {
            for(int j = 1;j < n;++j) {
                if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        //处理第一行 第一列
        if(firstRowHasZero) {
            for(int i = 0;i < m;++i) {
                matrix[i][0] = 0;
            }
        }
        if(firstColumnHasZero) {
            for(int j = 0;j < n;++j) {
                matrix[0][j] = 0;
            }
        }
    }
};
int main() {
    setZeroesSolution ps;
    vector<vector<int>> matrix = {{1,0,3}};
    ps.setZeroe(matrix);
    for(const auto& vec : matrix){
        for(const auto& ele : vec){
            std::cout << ele << " ";
        }
    }
    return 0;
}
