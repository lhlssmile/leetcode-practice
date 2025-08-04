//
// Created by 24276 on 2025/8/4.
//

#include <unordered_map>
#include <vector>
using namespace std;
class total_fruit {
public:
    int totalFruit(vector<int>& fruits) {
        int ans = 0, l = 0, n = fruits.size();
        std::unordered_map<int, int> cnt;
        for (int r = 0; r < n; r++) {
            cnt[fruits[r]]++;
            while (cnt.size() > 2) {
                cnt[fruits[l]]--;
                if (cnt[fruits[l]] == 0) cnt.erase(fruits[l]);
                ++l;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 2, 1};
    total_fruit ps;
    ps.totalFruit(nums);
    return 0;
}

