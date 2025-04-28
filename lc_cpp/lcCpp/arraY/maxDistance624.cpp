#include <vector>
#include <iostream>
using namespace std;
class max_distance_624 {
public:
    static int maxDistance(vector<vector<int>>& arrays) {
        int mn = INT_MAX / 2,mx = INT_MIN / 2;
        //枚举右 维护左
        int ans = 0;
        for(auto &a : arrays) {
            ans = max({ans,a.back() - mn,mx - a[0]});
            mn = min(mn , a[0]);
            mx = max(mx,a.back());
        }
        return ans;
    }
};

int main() {
    max_distance_624 ps;
    vector<vector<int>> arrays = {{1, 2, 3}, {4, 5}, {10, 20}};

    cout << ps.maxDistance(arrays) << endl;
    return 0;
}
