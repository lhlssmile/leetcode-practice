#include <vector>
#include <iostream>
using namespace std;
class generateMatrixSolution{
public:
    vector<vector<int>> generateMatrix(int n){
        vector<vector<int>> matrix(n,vector<int>(n));
        int times = n * n,left = 0,right = n - 1,top = 0,bottom = n - 1,num = 1;
        while(num <= times){
            for(int i = left;i <= right;++i) matrix[top][i] = num++;
            ++top;
            for(int i = top; i <= bottom;++i) matrix[i][right] = num++;
            --right;
            for(int i = right; i >= left;--i) matrix[bottom][i] = num++;
            --bottom;
            for(int i = bottom;i >= top; --i) matrix[i][left] = num++;
            ++left;
        }
        return matrix;
    }
};
int main() {
    generateMatrixSolution ps;
    int n = 3;
    auto res = ps.generateMatrix(n);
    for(const auto& vec : res){
        for(const auto& ele : vec){
            std::cout << ele << " ";
        }
    }
    return 0;
}
