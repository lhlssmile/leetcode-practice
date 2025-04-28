#include <vector>
#include <iostream>
using namespace std;
class uniquePathsWithObstaclesSolution {
public:
    uniquePathsWithObstaclesSolution() = default;
    ~uniquePathsWithObstaclesSolution() = default;

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid){
        //用dp[i][j]存储中途路径cache
        auto m = obstacleGrid.size();
        auto n = obstacleGrid[0].size();
        //起点(终点)就是障碍 没有可行路径
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) return 0;
        //开始定义dp cache
        vector<vector<long long>> dp(m,vector<long long>(n,0));
        //开始从0走 此时0不是障碍 是一条路径
        dp[0][0] = 1;
        for(int i = 0; i < m;++i){
            for(int j = 0; j < n;++j){
              if(obstacleGrid[i][j] == 1){
                dp[i][j] = 0;
              }else{
                if(i > 0){
                    dp[i][j] += dp[i - 1][j];
                }
                if(j > 0){
                    dp[i][j] += dp[i][j - 1];
                }
              }
            }
        }
        return dp[m - 1][n - 1];
    }

};
int main() {
    uniquePathsWithObstaclesSolution ps;
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    std::cout << ps.uniquePathsWithObstacles(obstacleGrid) << std::endl;
    return 0;
}

