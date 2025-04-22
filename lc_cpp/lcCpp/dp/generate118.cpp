#include <vector>
#include <iostream>
using namespace std;
class generate118 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for(int i = 0; i < numRows;++i) {
            res[i].resize(i + 1,1);
            //怎么更新 当前行?
            for(int j = 1;j < i;++j) {
                res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
            }
        }
        return res;
    }
};

int main() {
    generate118 ps;
    auto res = ps.generate(4);
    return 0;
}
