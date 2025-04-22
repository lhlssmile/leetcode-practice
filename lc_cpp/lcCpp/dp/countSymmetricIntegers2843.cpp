//
// Created by 24276 on 2025/4/11.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class count_symmetric_integers2843 {
public:
    /**
     *  FAQ:
     *      1.为什么memo的count为m*18 + 1?
     *
     * @param low 下界
     * @param high 上界
     * @return
     */
    int countSymmetricIntegers(int low,int high) {
        string low_s = to_string(low),high_s = to_string(high);
        int n = high_s.size(),m = n /2;
        int diff_lh = n - low_s.size();
        vector memo(n, vector(diff_lh + 1, vector<int>(m * 18 + 1, -1))); // 注意 start <= diff_lh
        auto dfs = [&](auto&& dfs,int i,int start,int diff,bool limit_low,bool limit_high) -> int {
          if (i == n) {
              return diff == m * 9;
          }
            if (start != -1 && !limit_low && !limit_high && memo[i][start][diff] != -1) {
                return memo[i][start][diff];
            }
            int lo = limit_low && i >= diff_lh ? low_s[i - diff_lh] - '0' : 0;
            int hi = limit_high ? high_s[i] - '0' : 9;

            //如果前边没有数字 且剩余位数为奇数个 那么当前位不能填数字
            if (start < 0 && (n - i) % 2) {
                return lo > 0 ? 0 : dfs(dfs,i + 1,start,diff,true,false);
            }
            int res = 0;
            bool is_left = start < 0 || i < (start + n) / 2;
            for (int d = lo;d <= hi;d++) {
                res  += dfs(dfs,
                            i + 1,
                            start < 0 && d > 0 ? i :start,
                            diff + (is_left ? d : -d),
                            limit_low && d == lo,
                            limit_high && d == hi
                );
            }
            if (start != -1 && !limit_low && !limit_high) {
                memo[i][start][diff] = res;
            }
            return res;
        };
        return dfs(dfs,0,-1,m * 9,true,true);
    }
};

int main() {
    count_symmetric_integers2843 solution;
    cout << solution.countSymmetricIntegers(1,100);
    return 0;
}
