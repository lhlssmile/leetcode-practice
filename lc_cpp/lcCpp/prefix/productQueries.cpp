//
// Created by 24276 on 2025/8/11.
//
using namespace std;
#include <vector>
class SegmentTree {
public:
    static const long long MOD = 1e9 + 7;
    vector<long long> tree;
    int n;

    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, 1);
        build(arr, 1, 0, n - 1);
    }

    void build(const vector<long long>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l] % MOD;
            return;
        }
        int mid = (l + r) / 2;
        build(arr, idx * 2, l, mid);
        build(arr, idx * 2 + 1, mid + 1, r);
        tree[idx] = (tree[idx * 2] * tree[idx * 2 + 1]) % MOD;
    }

    long long query(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 1; // 乘法单位元
        if (ql <= l && r <= qr) return tree[idx];
        int mid = (l + r) / 2;
        long long leftVal = query(idx * 2, l, mid, ql, qr);
        long long rightVal = query(idx * 2 + 1, mid + 1, r, ql, qr);
        return (leftVal * rightVal) % MOD;
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

class product_queries {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        // 1. 构造 powers 数组
        vector<long long> powers;
        for (int i = 0; (1LL << i) <= n; i++) {
            if (n & (1LL << i)) {
                powers.push_back(1LL << i);
            }
        }

        // 2. 建立线段树
        SegmentTree st(powers);

        // 3. 回答 queries
        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            ans.push_back((int)st.query(q[0], q[1]));
        }
        return ans;
    }
};
