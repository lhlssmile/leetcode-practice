//
// Created by 24276 on 2025/7/19.
//

#include <climits>
#include <vector>
using namespace std;
class min_path_sum64 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(),n = grid[0].size();
        vector memo(m, vector<int>(n, -1));
        auto dfs = [&](this auto&& dfs,int i,int j) -> int {
            if (i < 0 || j < 0) {
                return INT_MAX;
            }
            if (i == 0 && j == 0) {
                return grid[i][j];
            }
            int& res = memo[i][j];
            if (res != -1) {
                return res;
            }
            return res = min(dfs(i, j - 1),dfs(i - 1, j)) + grid[i][j];
        };
        return dfs(m - 1,n - 1);
    }
};

int main() {
    return 0;
}
