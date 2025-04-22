//
// Created by 24276 on 2025/4/1.
//
#include <vector>
#include <iostream>
using namespace std;

class most_points2140 {
public:
    using ll = long long;
    ll mostPoints(vector<vector<int>>& questions) {
        auto n = questions.size();
     // 用dp存[0,i - 1]能获取得到最大的分数
        vector<ll> dp(n + 1,0);
        //倒着往前算 从前往后计算dp[i]要综合考虑dp[0~i-1]的选择 很麻烦
        for(int i = n - 1;i >= 0;i--) {
            int points = questions[i][0];
            int brainPower = questions[i][1];
            int next = i + brainPower + 1;

            //如果跳过的题目数超出范围 就只能获的当前题目的分数
            if(next > n) {
                dp[i] = std::max(dp[i + 1],(ll)points);
            }else {
                dp[i] = max(dp[i + 1],points + dp[next]);
            }
        }
        return dp[0];
    }
};

int main() {
    most_points2140 solution;
    vector<vector<int>> questions = {
            {3,2},
              {4,3},
                {4,4},
        {2,5},
    };
    cout << solution.mostPoints(questions) <<  endl;
    return 0;
}
