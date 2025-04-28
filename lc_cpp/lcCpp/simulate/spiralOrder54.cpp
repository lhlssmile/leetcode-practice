//
// Created by 24276 on 2025/4/17.
//

#include <vector>
#include <iostream>
using namespace std;

class spiral_order54 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(),n = matrix[0].size();
        int left = 0,right = n,top = 0,bottom = m;
        vector<int> ans;
        while (left < right && top < bottom) {
            for (int j = left; j < right; j++) {
                ans.push_back(matrix[top][j]);
            }
            top++;

            // 上 → 下
            for (int i = top; i < bottom; i++) {
                ans.push_back(matrix[i][right - 1]);
            }
            right--;

            if (top < bottom) {
                // 右 → 左
                for (int j = right - 1; j >= left; j--) {
                    ans.push_back(matrix[bottom - 1][j]);
                }
                bottom--;
            }

            if (left < right) {
                // 下 → 上
                for (int i = bottom - 1; i >= top; i--) {
                    ans.push_back(matrix[i][left]);
                }
                left++;
            }
        }
        return ans;
    }
};

int main() {
    spiral_order54 sol;
    vector<vector<int>> matrix = {
        {1,2,3},{4,5,6},{7,8,9}
    };
    sol.spiralOrder(matrix);
    return 0;
}
