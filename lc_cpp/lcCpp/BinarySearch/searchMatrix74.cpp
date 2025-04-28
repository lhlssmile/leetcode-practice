//
// Created by 24276 on 2025/3/28.
//
#include <vector>
#include <iostream>
using namespace std;

class search_matrix74 {
public:
    bool searchMatrix(vector<vector<int>>& matrix,int target) {
        //直接把二维矩阵看成一维矩阵
        auto m = matrix.size(),n = matrix[0].size();
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left  + (right - left) / 2;
            int row = mid / n;  //行号
            int col = mid % n;  //列号
            if(matrix[row][col] == target) {
                return true;
            }else if(matrix[row][col] > target) {
                right = mid - 1;
            }else {
                left = mid + 1;
            }
        }
        return false;
    }
};

int main() {
    search_matrix74 solution;
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    cout << solution.searchMatrix(matrix,3) << endl;
    return 0;
}
