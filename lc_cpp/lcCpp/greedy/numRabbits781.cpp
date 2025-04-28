//
// Created by 24276 on 2025/4/20.
//


#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class num_rabbits781 {
public:
    const int MAX_LENGTH = 1001;
    int numRabbits(vector<int>& answers) {
        vector<int> num_rabbits(MAX_LENGTH,0);
        int all_rabbits = 0;
        for (auto answer : answers){
            num_rabbits[answer]++;
        }
        for (int i = 0;i < MAX_LENGTH;i++){
            if (num_rabbits[i] == 0){
                continue;
            }
            //answer 最多 有answer + 1个兔子 如果再出现 那么是 另一种颜色
            int k = num_rabbits[i];
            int group_size = i + 1;
            int groups = (k + group_size - 1) / group_size;
            //TODO:怎么累加？
            all_rabbits += groups * group_size;
        }
        return all_rabbits;
    }
    int numRabbit(vector<int>& answers) {
        unordered_map<int,int> num_rabbits;
        for(auto answer : answers){
            num_rabbits[answer]++;
        }
        int all_rabbits = 0;
        for(const auto& [answer,rest] : num_rabbits){
            int group_size = answer + 1;
            int groups = (rest + group_size - 1) / group_size;
            all_rabbits += group_size * groups;
        }
        return all_rabbits;
    }
};

int main() {
    num_rabbits781 sol;
    vector<int> answers = {10,10,10};
    cout << sol.numRabbits(answers);
    return 0;
}
