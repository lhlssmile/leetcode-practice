//
// Created by 24276 on 2025/7/5.
//
#define V vector
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class find_lucky1394 {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int,int> cnt;
        for(int x : arr) {
            cnt[x]++;
        }
        int ans = -1;
        for(auto& [x,c] : cnt) {
            if (x == c) {
                ans = max(ans,x);
            }
        }
        return ans;
    }
};

int main() {
    find_lucky1394 ps;
    vector<int> arr = {2,2,3,4};
    ps.findLucky(arr);
    return 0;
}
