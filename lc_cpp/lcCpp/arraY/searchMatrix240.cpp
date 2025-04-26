#include <bits/stdc++.h>
#include <vector>

using namespace std;

class search_matrix240 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int row = m - 1, col = 0;  // 注意这里是m-1，不是n-1！
        while (row >= 0 && col < n) {
            if (matrix[row][col] == target) {
                return true;
            } else if (target < matrix[row][col]) {
                row--;  // 当前值太大，往上走
            } else {
                col++;  // 当前值太小，往右走
            }
        }
        return false;
    }
};
int main(){
    
}