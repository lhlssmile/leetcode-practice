//
// Created by 24276 on 2025/4/20.
//

#include <vector>
#include <iostream>

using namespace std;

class calculate_score100549 {
    using ll = long long;
    const string JUMP_INS = "jump";
    const string ADD_INS = "add";
public:
    ll calculateScore(vector<string>& instructions,vector<int>& values) {
        // 不能越界 i 属于 (0,n)  instructions[i] 只执行一次
        int n = instructions.size();
        vector<bool> executed(n,false);
        int score = 0;
        for (int  i = 0;i < n;i++) {
            string ins = instructions[i];
            //当前指令 已经执行
            executed[i] = true;
            if (ins == JUMP_INS && i + values[i] < n && i + values[i] > 0) {
                i = i + values[i] - 1;
            }
            if (ins == ADD_INS && !executed[i]) {
                score += values[i];
            }
        }
        return score;
    }

};

int main() {
    calculate_score100549 sol;
    vector<string> instructions ={"jump","add","add"};
    vector<int> values = {3,1,1};
    cout << sol.calculateScore(instructions,values);

    return 0;
}
