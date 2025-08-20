//
// Created by 24276 on 2025/8/20.
//
using namespace std;
#define V vector
#include <vector>
#include <unordered_map>
typedef unordered_map<int, V<int>> uivi;
#include "../template/mylib.h"
class count_pairs {
public:
    int countPairsA(V<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size() - 1, ans = 0;
        while (i < j) {
            if (nums[i] + nums[j] < target) {
                ans += j - i;
                i++;
            }else {
                j--;
            }
        }
        return ans;
    }
};

int main() {
    return 0;
}
