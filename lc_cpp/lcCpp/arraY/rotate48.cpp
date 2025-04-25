//
// Created by 24276 on 2025/4/25.
//

#include <bits/stdc++.h>
#include <vector>

using namespace std;

class rotate48 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int layer = 0;layer < n / 2;layer++) {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first;i < last;i++) {
                int offset = i - first;
                int top = matrix[first][i];
                matrix[first][i] = matrix[last - offset][first];
                matrix[last - offset][first] = matrix[last][last - offset];
                matrix[last][last - offset] = matrix[i][last];
                matrix[i][last] = top;
            }
        }
    }
};

int main() {
    rotate48 sol;
    vector<vector<int>> matrix = {
        {1,2,3},{4,5,6},{7,8,9}
    };
    sol.rotate(matrix);
    return 0;
}
