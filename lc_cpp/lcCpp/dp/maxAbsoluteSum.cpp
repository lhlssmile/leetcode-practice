//
// Created by 24276 on 2025/8/12.
//
#include <vector>

using namespace std;

class max_absolute_sum {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int mx_sum = 0, min_sum = 0;
        int mx_end = 0, min_end = 0;
        for(int v : nums ) {
            mx_end = max(v, mx_end + v);
            mx_sum = max(mx_sum, mx_end);
            min_end = min(v, min_end + v);
            min_sum = min(min_sum, min_end);
        }
        return max(mx_sum, -min_sum);
    }
};

int main() {
    max_absolute_sum ps;
    vector<int> nums = {1, -3, 2, 3, -4};
    vector <int> nums2 = {2,-5,1,-4,3,-2};
    ps.maxAbsoluteSum(nums2);
    return 0;
}
