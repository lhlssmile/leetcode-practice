#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
class difference_of_distinct_values2711 {
public:
    /**
     *  analysis:
     *      subscript started at 0, (answer)ele(r,c) = topLeft(r_i,c_i) - bottomRight(r_i,c_i)
     *      topLeft[r_i][c_i](bottomRight) record different value(can be equals to [r][c] pos ele
     *      use dp?
     * @param grid input matrix
     * @return 对角线上不同值的数量差
     */
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        auto m = grid.size();
        auto n = grid[0].size();
        vector<vector<int>> answer(m,vector<int>(n,0));
        for(int i = 0;i < m;++i) {
            for(int j = 0;j < n;++j) {
                unordered_set<int> topLeftSet;
                int tp_diff_values = 0;
                auto tl_r = i - 1,tl_c = j - 1;
                while(tl_r >= 0 && tl_c >= 0) {
                    topLeftSet.insert(grid[tl_r][tl_c]);
                    tl_r--,tl_c--;
                }
                tp_diff_values = topLeftSet.size();
                unordered_set<int> rightBottomSet;
                int rb_diff_values = 0,rb_r = i + 1,rb_c = j + 1;
                while(rb_r < m && rb_c < n) {
                    rightBottomSet.insert(grid[rb_r][rb_c]);
                    rb_r++,rb_c++;
                }
                rb_diff_values = rightBottomSet.size();
                answer[i][j] = abs(tp_diff_values - rb_diff_values);
            }
        }
        return answer;
    }
    vector<vector<int>> differenceOfDistinctValuesUP(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector ans(m, vector<int>(n));
        unordered_set<int> st;

        // 第一排在右上，最后一排在左下
        // 每排从左上到右下
        // 令 k=i-j+n，那么右上角 k=1，左下角 k=m+n-1
        for (int k = 1; k < m + n; k++) {
            // 核心：计算 j 的最小值和最大值
            int min_j = max(n - k, 0); // i=0 的时候，j=n-k，但不能是负数
            int max_j = min(m + n - 1 - k, n - 1); // i=m-1 的时候，j=m+n-1-k，但不能超过 n-1

            st.clear();
            for (int j = min_j; j <= max_j; j++) {
                int i = k + j - n;
                ans[i][j] = st.size(); // top_left[i][j] == st.size()
                st.insert(grid[i][j]);
            }

            st.clear();
            for (int j = max_j; j >= min_j; j--) {
                int i = k + j - n;
                ans[i][j] = abs(ans[i][j] - (int) st.size()); // bottom_right[i][j] == st.size()
                st.insert(grid[i][j]);
            }
        }
        return ans;
    }

};

int main() {
    difference_of_distinct_values2711 solution;
    vector<vector<int>> grid = {{1,2,3},{3,1,5},{3,2,1}};
    auto res = solution.differenceOfDistinctValuesUP(grid);
    for (auto const& vec : res) {
        cout << "[" << " ";
        for(auto ele : vec) {
           cout << ele << " ";
        }
        cout << "]";
    }
    return 0;
}
