//
// Created by 24276 on 2025/4/21.
//
#include <vector>
#include <iostream>
using namespace std;
class maximum_possible_size3523 {
public:
    int maximumPossibleSize(vector<int>& nums) {
        int ans = 0, mx = 0;
        for (int x : nums) {
            if (x >= mx) {
                mx = x;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    maximum_possible_size3523 sol;
    vector<int> nums = {4,2,5,3,5};
    cout << sol.maximumPossibleSize(nums);
    return 0;
}
