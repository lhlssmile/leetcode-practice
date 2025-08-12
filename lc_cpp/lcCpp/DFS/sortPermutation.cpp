#include <vector>
using namespace std;
#define pb push_back
class Union {
public:
    vector<int> parent, count;
    Union(int n) {
        parent.resize(n);
        count.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unionSet(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return;
        if (count[rootX] < count[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if (count[rootX] == count[rootY]) count[rootX]++;
    }
    
};
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        // nums[i] <= n - 1 (n == length) -> 让元素回到正确位置
        int n = nums.size();
        bool sorted = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != i ) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;
        int k = 0;
        for (int bit = 1; bit >= 0; bit--) {
            // 直接从大到小选出一个k 看是否能排序
            int pos_k = k | (1 << bit);
            Union u(n);

            vector<int> idx;

            for (int i = 0; i < n; i++) {
                if ((nums[i] & pos_k) == pos_k) {
                    idx.pb(i);
                }
            }

            for (int i = 1; i < idx.size(); i++) {
                u.unionSet(idx[0], idx[i]);
            }
            
            bool ok = true;

            for (int i = 0; i < n; i++) {
                if (u.find(i) != u.find(nums[i])) {
                    ok = false;
                    break;
                }
            }
            if (ok) k = pos_k;
        }
        return k;
    }
};
int main() {
    Solution ps;
    vector<int> nums = {0,3,2,1};
    ps.sortPermutation(nums);
}