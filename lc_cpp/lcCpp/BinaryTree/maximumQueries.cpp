#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree;
    SegmentTree(int n): n(n), tree(4 * n, -1) {}

    void update(int idx, long long val, int node, int l, int r) {
        if (l == r) {
            tree[node] = max(tree[node], val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(idx, val, node * 2, l, mid);
        else update(idx, val, node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    long long query(int ql, int qr, int node, int l, int r) {
        if (ql > r || qr < l) return -1;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return max(query(ql, qr, node * 2, l, mid),
                   query(ql, qr, node * 2 + 1, mid + 1, r));
    }
};

class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size(), q = queries.size();

        // Step 1: 离散化 nums2 和 yi
        vector<int> vals = nums2;
        for (auto& v : queries) vals.push_back(v[1]);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        auto get_id = [&](int x) {
            return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
        };
        int m = vals.size();

        // Step 2: 按 nums1 降序排序点
        vector<array<long long, 3>> points;  // {nums1, nums2, sum}
        for (int i = 0; i < n; i++)
            points.push_back({nums1[i], nums2[i], (long long)nums1[i] + nums2[i]});
        sort(points.begin(), points.end(), [](auto &a, auto &b){ return a[0] > b[0]; });

        // Step 3: 按 xi 降序排序查询
        vector<array<int, 3>> qs; // {xi, yi, index}
        for (int i = 0; i < q; i++)
            qs.push_back({queries[i][0], queries[i][1], i});
        sort(qs.begin(), qs.end(), [](auto &a, auto &b){ return a[0] > b[0]; });

        // Step 4: 离线处理
        SegmentTree seg(m);
        vector<int> ans(q, -1);
        int idx = 0;

        for (auto& [xi, yi, qi] : qs) {
            while (idx < n && points[idx][0] >= xi) {
                int yid = get_id(points[idx][1]);
                seg.update(yid, points[idx][2], 1, 0, m - 1);
                idx++;
            }
            int yid = int(lower_bound(vals.begin(), vals.end(), yi) - vals.begin());
            if (yid < m) {
                long long res = seg.query(yid, m - 1, 1, 0, m - 1);
                ans[qi] = (int)res;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {4, 3, 1, 2};
    vector<int> nums2 = {2, 4, 9, 5};
    vector<vector<int>> queries = {{4,1}, {1,3}, {2,5}};

    auto ans = sol.maximumSumQueries(nums1, nums2, queries);
    for (int x : ans) cout << x << " ";
    cout << endl; // 输出: 6 10 7

    return 0;
}
