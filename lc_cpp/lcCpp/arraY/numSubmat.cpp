//
// Created by 24276 on 2025/8/21.
//
#include <vector>
using namespace std;
class nums {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int ans = 0;
        for (int top = 0; top < m; top++) { // 枚举上边界
            vector<int> a(n);
            for (int bottom = top; bottom < m; bottom++) { // 枚举下边界
                int h = bottom - top + 1; // 高
                // 2348. 全 h 子数组的数目
                int last = -1;
                for (int j = 0; j < n; j++) {
                    a[j] += mat[bottom][j]; // 把 bottom 这一行的值加到 a 中
                    if (a[j] != h) {
                        last = j; // 记录上一个非 h 元素的位置
                    } else {
                        ans += j - last;
                    }
                }
            }
        }
        return ans;
    }
};