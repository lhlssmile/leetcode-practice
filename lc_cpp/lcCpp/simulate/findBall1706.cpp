#include <vector>
#include <iostream>
using namespace std;
class find_ball1706 {
public:
    static vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size(); // 行数
        int n = grid[0].size(); // 列数
        vector<int> res(n, -1); // 初始答案为-1，表示球卡住了

        for (int col = 0; col < n; ++col) { // 遍历每列的球
            int currCol = col;
            for (int row = 0; row < m; ++row) { // 遍历每行
                if (grid[row][currCol] == 1) { // 如果是 1，向右移动
                    if (currCol + 1 < n && grid[row][currCol + 1] != -1) { // 判断右下方是否能通过
                        currCol++; // 向右移
                    } else {
                        currCol = -1; // 卡住了，返回-1
                        break;
                    }
                } else if (grid[row][currCol] == -1) { // 如果是 -1，向左移动
                    if (currCol - 1 >= 0 && grid[row][currCol - 1] != 1) { // 判断左下方是否能通过
                        currCol--; // 向左移
                    } else {
                        currCol = -1; // 卡住了，返回-1
                        break;
                    }
                }
            }
            res[col] = currCol; // 最终落到的列（如果没卡住）
        }
        return res;
    }
    static vector<int> simulate_move(int start_row,int start_column,vector<vector<int>>& grid,vector<int>& res) {
        //遍历每列的球
        for(int i = 1;i <= grid[0].size();++i) {
            //遍历球到每行的情况
            for(;start_row <= grid.size();++start_row) {
                if(grid[start_row][i] == 1 && grid[start_row][i + 1] == -1) {
                    //卡住了
                    res.push_back(-1);
                }
                else {
                    //落到下一行? 左下还是右下?
                    if(grid[start_row][i] == 1) simulate_move(start_row + 1,
                        start_column + 1,grid,res);
                    else {
                        simulate_move(start_row + 1,
                        start_column - 1,grid,res);
                    }
                }
            }
            //落下 添加到res
            if(start_row > grid.size()) res.push_back(start_column);
        }
        return res;
    }
};

int main() {
    find_ball1706 ps;
    vector<vector<int>> grid = {{1,1,1,-1,-1},{1,1,1,-1,-1},
        {-1,-1,-1,1,1},{-1,-1,-1,-1,-1}};

    auto res = ps.findBall(grid);
    for(const auto& ele : res) {
        cout << ele << " ";
    }
    return 0;
}
