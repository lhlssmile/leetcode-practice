#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
class minCostClimbingStairSolution{
public:
#define maxn 1024
    int f[maxn];
    int minCostClimbing(vector<int>& cost){
        f[0] = f[1] = 0;
        for(int i = 2; i <= cost.size(); ++i){
            f[i] = std::min(cost[i - 1] + f[i - 1],cost[i - 2] + f[i - 2]);
        }
        
        return f[cost.size()];
    }
    int minCostClimbingStairs(vector<int>& cost){
        vector<int> dp(cost.size(),0);
        dp[0] = 0;dp[1] = 0;
        for(auto i = 2; i <= cost.size();++i) {
            dp[i] = std::min(dp[i - 1] + cost[i - 1],cost[i - 2] + dp[i - 2]);
        }
        return dp[cost.size()];
    }

};
int main() {
    minCostClimbingStairSolution ps;
    std::vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    std::cout << ps.minCostClimbing(cost) << std::endl;
    return 0;
}
