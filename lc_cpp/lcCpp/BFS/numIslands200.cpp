//
// Created by 24276 on 2025/3/28.
//

#include <iostream>
#include <vector>
#include <ranges>
using namespace std;

class num_islands200 {
public:
    /**
     * 和找字符串类似?dfs 一堆1 上下左右全是0那么可以当作一个岛屿
     * @param grid
     * @return
     */
    int numIslands(vector<vector<char>>& grid) {
        auto m = grid.size(),n = grid[0].size();
        //找到所有可能的岛屿?    先不考虑优化性能?
        int island_num = 0;

        int directions[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};

        auto dfs = [&](this auto&& dfs,int i,int j) -> void {
            //怎么判断一小片为岛屿?       <0停止,出界,不是0停止,碰到标记过的也停止
            if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1') {
                return;
            }
            //标记此处
            grid[i][j] = '2';
            dfs(i,j - 1);
            dfs(i,j + 1);
            dfs(i + 1,j);
            dfs(i - 1,j);
        };

        for(int i = 0;i < m;i++) {
            for(int j = 0;j < n;j++) {
                //是1 直接标记 然后对此处进行dfs
                if(grid[i][j] == '1') {
                    dfs(i,j);
                    ++island_num;
                }
            }
        }
        return island_num;
    }
};

int main() {
    num_islands200 solution;
    vector<vector<char>> grid = {
        {1,1,1,1,0},
        {1,1,0,1,0},
        {1,1,0,0,0},
        {0,0,0,0,0}
    };
    vector<int> nums  = {2,4,3,7,13};
    ranges::sort(nums);
    cout << solution.numIslands(grid) << endl;
    return 0;
}
