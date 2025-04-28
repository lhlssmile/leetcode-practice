#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class row_and_maximum_ones2643 {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        //用数组 或者 hashtable
        auto m = mat.size();
        auto n = mat[0].size();

        int max_ones = 0;
        int max_row = 0;
        for(int i = 0;i < m;++i) {
            int one = 0;
            for(int j = 0; j < n;++j) {
                if(mat[i][j] == 1) {
                    one++;
                }
            }
            if(one > max_ones) {
                max_ones = one;
                max_row = i;
            }
        }
        return {max_row,max_ones};
    }
};

int main() {
    row_and_maximum_ones2643 ps;
    vector<vector<int>> mat = {{0,1},{0,1}};
    auto res = ps.rowAndMaximumOnes(mat);
    for(auto const rowAndOneNums : res) {
        cout << rowAndOneNums << " ";
    }
    return 0;
}
