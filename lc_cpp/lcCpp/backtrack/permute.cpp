
//
// Created by 24276 on 2025/8/20.
//
#define V vector
#define pb push_back
#include <vector>
using namespace std;
class permute_s {
public:
    V<V<int>> permute(V<int>& nums) {
        int n = nums.size();
        V<int> res;
        V<V<int>> ans;
        V<bool> visited(n, false);
        auto backTrack = [&](this auto&& backTrack) -> void {
            if (res.size() == n) {
                ans.pb(res);
                return ;
            }
            for (int start = 0; start < n; start++) {
                if (!visited[start]) {
                    res.pb(nums[start]);
                    visited[start] = true;
                    backTrack();
                    res.pop_back();
                    visited[start] = false;
                }


            }
        };
        backTrack();
        return ans;
    }
};

int main() {
    return 0;
}
