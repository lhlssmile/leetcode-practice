//
// Created by 24276 on 2025/8/5.
//
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
    vector<int> t;

    // 把 i 处的值改成 val
    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            t[o] = val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, i, val);
        } else {
            update(o * 2 + 1, m + 1, r, i, val);
        }
        t[o] = max(t[o * 2], t[o * 2 + 1]);
    }

    // 查询 [0,R] 中的最大值
    int query(int o, int l, int r, int R) {
        if (r <= R) {
            return t[o];
        }
        int m = (l + r) / 2;
        if (R <= m) {
            return query(o * 2, l, m, R);
        }
        return max(t[o * 2], query(o * 2 + 1, m + 1, r, R));
    }

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int m = 0;
        for (auto& q : queries) {
            m = max(m, q[1]);
        }
        m++;

        set<int> st{0, m}; // 哨兵
        t.resize(2 << (32 - __builtin_clz(m)));

        vector<bool> ans;
        for (auto& q : queries) {
            int x = q[1];
            auto it = st.lower_bound(x);
            int pre = *prev(it); // x 左侧最近障碍物的位置
            if (q[0] == 1) {
                int nxt = *it; // x 右侧最近障碍物的位置
                st.insert(x);
                update(1, 0, m, x, x - pre);   // 更新 d[x] = x - pre
                update(1, 0, m, nxt, nxt - x); // 更新 d[nxt] = nxt - x
            } else {
                // 最大长度要么是 [0,pre] 中的最大 d，要么是 [pre,x] 这一段的长度
                int max_gap = max(query(1, 0, m, pre), x - pre);
                ans.push_back(max_gap >= q[2]);
            }
        }
        return ans;
    }
};


int main() {
    vector<vector<int>> queries ={
        {1,2}, {2, 3, 3}, {2, 3, 1}, {2, 2, 2}
    };
    Solution ps;
    ps.getResults(queries);
    return 0;
}
