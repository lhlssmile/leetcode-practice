#include <queue>
//
// Created by hana on 2025/10/10.
//
using namespace std;
#define V vector
#include <vector>
struct Cmp {
    // nums1[j] > xi && nums2[j] > yi && maximum(nums1[j] + nums2[j] = s
// s有多个 & 相同的s有不同组合(并且同时满足前边两个条件?)?
    bool operator() (const V<int, pair<int, int>>& a, const V<int, pair<int, int>>& b) {

    }
};
class maximum_queries {
    using pii = pair<int, int>;
public:
    V<int> maximumQueries(V<int>& nums1, V<int>& nums2, V<V<int>>& queries) {
        V<int> ans;
        priority_queue<V<int, pii>, V<V<int, pii>>, Cmp> pq;

        return ans;
    }

};

int main() {
    return 0;
}
