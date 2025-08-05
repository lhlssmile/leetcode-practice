//
// Created by 24276 on 2025/8/5.
//
#include <iostream>
#include <vector>
using namespace std;
class SegmentTree {
    vector<pair<int, int>> tree; // {最大高度, 索引}
    int n;

    void maintain(int p) {
        // 选择高度较大或索引较小的节点
        if (tree[p * 2 + 1].first >= tree[p * 2 + 2].first) {
            tree[p] = tree[p * 2 + 1];
        } else {
            tree[p] = tree[p * 2 + 2];
        }
    }

    void build(const vector<int>& a, int l, int r, int p) {
        if (l == r) {
            tree[p] = {a[l], l};
            return;
        }
        int m = (l + r) / 2;
        build(a, l, m, p * 2 + 1);
        build(a, m + 1, r, p * 2 + 2);
        maintain(p);
    }

    int query(int l, int r, int h, int cl, int cr, int p) {
        if (l > cr || r < cl || tree[p].first <= h) {
            return -1;
        }
        if (l <= cl && r >= cr && cl == cr) {
            return tree[p].first > h ? tree[p].second : -1;
        }
        int m = (cl + cr) / 2;
        int left = query(l, r, h, cl, m, p * 2 + 1);
        if (left != -1) return left;
        return query(l, r, h, m + 1, cr, p * 2 + 2);
    }

public:
    SegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(a, 0, n - 1, 0); // 从索引 0 开始
    }

    int query(int l, int r, int h) {
        return query(l, r, h, 0, n - 1, 0);
    }
};

class leftmost_building_queries {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        SegmentTree t(heights);
        int n = heights.size();
        vector<int> ans(queries.size(), -1);

        for (int i = 0; i < queries.size(); ++i) {
            int ai = queries[i][0], bi = queries[i][1];
            if (ai > bi) swap(ai, bi); // 确保 ai <= bi
            if (ai == bi) {
                ans[i] = ai; // 同一建筑
                continue;
            }
            if (heights[ai] < heights[bi] && ai < bi) {
                ans[i] = bi; // Alice 可直接到达 bi
                continue;
            }
            if (heights[bi] < heights[ai] && bi < ai) {
                ans[i] = ai; // Bob 可直接到达 ai
                continue;
            }
            int start = max(ai, bi) + 1; // 相遇点必须在 max(ai, bi) 右边
            int h = max(heights[ai], heights[bi]);
            ans[i] = t.query(start, n - 1, h);
        }

        return ans;
    }
};

int main() {
    leftmost_building_queries ps;
    vector<int> heights = {6,4,8,5,2,7};
    vector<vector<int>> queries = {
    {0, 1}, {0, 3}, {2, 4}, {3, 4}, {2, 2}
    };
    auto res = ps.leftmostBuildingQueries(heights, queries);
    for (int re : res) {
        cout << re << " ";
    }
    return 0;
}
